/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/07 22:59:38 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	hunk_analysis(t_list *node)
{
	int		i;
	int		line_break;

	i = 0;
	line_break = 0;
	while (node->content[i] != '\0')
	{
		if (node->content[i] == '\n')
		{
			line_break = 1;
			node->len = i + 1;
		}
		i++;
	}
	node->i += 1;
	if (line_break == 1)
	{
		node->i -= 1;
		return (1);
	}
	return (0);
}

// read line creating a nodes
int	get_hunk_of_line(t_list **head, int fd)
{
	ssize_t	read_bytes;
	t_list	*actual;

	read_bytes = 0;
	if (*head == NULL)
		*head = malloc(sizeof(t_list));
	actual = *head;
	while (actual->next != NULL)
	{
		if (actual->next->next == NULL)
			actual->next->i = actual->i;
		actual = actual->next;
	}
	actual->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	actual->content[BUFFER_SIZE] = '\0';
	read_bytes = read(fd, actual->content, BUFFER_SIZE);
	if (hunk_analysis(actual))
	{
		actual->next = malloc(sizeof(t_list));
		return (1);
	}
	actual->next = malloc(sizeof(t_list));
	return (0);
}

char	*recreate_line(t_list **node)
{
	t_list	*last;
	char	*line;
	int		len;
	int		i;
	int		j;

	last = *node;
	while (last->next != NULL)
		last = last->next;
	len = (last->i * BUFFER_SIZE) + (int)last->len + 1;
	line = malloc(len + 1 * sizeof(char));
	line[len + 1] = '\0';
	last = *node;
	i = -1;
	j = -1;
	while (last->next != NULL)
	{
		line[++j] = last->content[++i];
		if (last->content[i + 1] == '\0')
		{
			last = last->next;
			i = -1;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*node;
	int				find_n;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	find_n = 0;
	while (find_n == 0)
		find_n = get_hunk_of_line(&node, fd);
	return (recreate_line(&node));
}

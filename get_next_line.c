/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:47:52 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/14 18:54:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*head;
	char			*line;
	int				break_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_list(&head);
		return (NULL);
	}
	break_line = 0;
	while (break_line == 0)
	{
		if (get_hunk_line(&head, fd))
			free_list(&head);
		break_line = get_info_node(&head);
	}
	get_line(&head, &line);
	if (!line)
		return (free_list(&head));
	head = check_remain(&head);
	return (line);
}

int	get_hunk_line(t_list **head, int fd)
{
	t_list	*actual;

	if (!*head)
		*head = init_node();
	if ((*head)->len > (*head)->read_bytes)
		return (0);
	if (!*head)
		return (1);
	actual = *head;
	while (actual->next != NULL)
		actual = actual->next;
	actual->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!actual->content)
		return (1);
	actual->read_bytes = read(fd, actual->content, BUFFER_SIZE);
	if (actual->read_bytes < 0)
		return (1);
	return (0);
}

ssize_t	get_info_node(t_list **head)
{
	t_list	*actual;

	if (!head)
		return (0);
	actual = *head;
	while (actual->next != NULL)
		actual = actual->next;
	actual->len = 0;
	while (actual->content[actual->len] != '\0')
	{
		actual->len++;
		if (actual->content[actual->len] == '\n')
			return (1);
	}
	if (actual->len > actual->read_bytes)
		actual->read_bytes = actual->len;
	actual->next = init_node();
	return (0);
}

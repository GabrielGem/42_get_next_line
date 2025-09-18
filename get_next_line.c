/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:47:52 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/18 12:18:19 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*line;
	int				break_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	break_line = 0;
	while (break_line == 0)
	{
		if (get_hunk_line(&head, fd))
			return (free_list(&head));
		if (last_node(&head)->content[0] == 0)
			break ;
		break_line = get_info_node(&head);
	}
	line = NULL;
	if (!head->read_bytes)
		return (free_list(&head));
	join_line(&head, &line, 0);
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
	if (!*head)
		return (1);
	if ((*head)->len != (*head)->read_bytes)
		return (0);
	actual = last_node(head);
	actual->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!actual->content)
		return (1);
	actual->read_bytes = read(fd, actual->content, BUFFER_SIZE);
	if (actual->read_bytes < 0)
		return (1);
	actual->content[actual->read_bytes] = '\0';
	return (0);
}

int	get_info_node(t_list **head)
{
	t_list	*actual;

	if (!head)
		return (0);
	actual = last_node(head);
	if (actual->content[0] == 0)
		return (++actual->len);
	actual->len = 0;
	while (actual->content[actual->len] != '\0')
	{
		if (actual->content[actual->len] == '\n'
			|| ((actual->content[actual->len] == 0)
				&& (actual->len < actual->read_bytes)))
			return (++actual->len);
		actual->len++;
	}
	if (actual->len > actual->read_bytes)
		actual->read_bytes = actual->len;
	actual->next = init_node();
	return (0);
}

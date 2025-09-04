/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/04 18:14:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*node;
	ssize_t			find_n;
	char			*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	find_n = 0;
	node = malloc(sizeof(t_list));
	if (node->content == 0)
		node->content = NULL;
	while (find_n == 0)
		find_n = get_line(&node, fd);
	fill_array(node);
	return (line);
}

// read line creating a nodes
ssize_t	get_line(t_list **head, int fd)
{
	ssize_t	read_bytes;

	node->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while ()
	{
		read_bytes = read(fd, node->content, BUFFER_SIZE);
		if (lstlen(&node, read_bytes))
			return (1);
	}
	return (0);
}

int	lstlen(t_list *node, ssize_t read_bytes)
{
	int			len;

	len = 0;
	node.i = 1;
	while (ptr[len])
		len++;
	if (len < BUFFER_SIZE)
	{
		node.len = len;
		node.i = 0;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/05 18:17:20 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	hunk_len(t_list *node)
{
	int		i;

	i = -1;
	while (node->content[i] != '\n' || node->content[i] != '\0')
		i++;
	if (i < BUFFER_SIZE)
		
}

// read line creating a nodes
int	get_hunk_of_line(t_list *node, int fd)
{
	ssize_t	read_bytes;

	read_bytes = 0;
	node->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	node->content[BUFFER_SIZE] = '\0';
	read_bytes = read(fd, node->content, BUFFER_SIZE);
	if (read_bytes > 0)
		hunk_len(node);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*node;
	int				find_n;
	//char			*line;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	if (node.i = 0)
		node = malloc(sizeof(t_list));
	find_n = 0;
	while (find_n == 0)
		find_n = get_hunk_of_line(node, fd);
	//fill_array(node);
	return (node->content);
}

/*
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
*/

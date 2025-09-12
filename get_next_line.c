/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:36:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/12 19:20:53 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_hunk_of_line(t_handle **sewing, int fd)
{
	ssize_t	read_bytes;
	t_list	*actual;

	read_bytes = 0;
	if (*sewing == NULL)
	{
		*sewing = malloc(sizeof(t_handle));
		(*sewing)->head = malloc(sizeof(t_list));
		(*sewing)->tail = (*sewing)->head;
	}
	actual = (*sewing)->tail;
	actual->content = malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_bytes = read(fd, actual->content, BUFFER_SIZE);
	actual->content[read_bytes] = '\0';
	if (hunk_analysis(actual))
	{
		actual->next = malloc(sizeof(t_list));
		return (1);
	}
	actual->next = malloc(sizeof(t_list));
	(*sewing)->tail = actual->next;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_handle	*sewing;
	char			*line;
	int				break_line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	break_line = 0;
	while (break_line == 0)
		if (get_hunk_of_line(&sewing, fd))
			break_line = 1;
	line = recreate_line(&sewing);
	cheak_remain(t_handle(&sewing));
	return (line);
}

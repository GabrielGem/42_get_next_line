/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:39:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/14 16:20:42 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				i;
	ssize_t			len;
	ssize_t			read_bytes;
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		get_hunk_line(t_list **head, int fd);
ssize_t	get_info_node(t_list **node);
char	*get_line(t_list **head, char **line);
t_list	*check_remain(t_list **head);
void	*free_list(t_list **head);

#endif

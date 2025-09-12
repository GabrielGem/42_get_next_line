/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:39:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/11 20:15:37 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_handle
{
	struct s_list	*head;
	struct s_list	*tail;
}	t_handle;

typedef struct s_list
{
	int				i;
	ssize_t			len;
	ssize_t			read_bytes;
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		get_hunk_of_line(t_handle **sewing, int fd);
int		hunk_analysis(t_list *node);
char	*recreate_line(t_handle **sewing);

#endif

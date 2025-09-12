/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:10:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/12 16:32:32 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	hunk_analysis(t_list *node)
{
	int		i;
	int		line_break;

	i = 0;
	line_break = 0;
	while (node->content[i] != '\0' && line_break == 0)
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

char	*recreate_line(t_handle **sewing)
{
	t_list	*temp;
	char	*line;
	int		i[2];

	temp = (*sewing)->head;
	while (temp->next != NULL)
	{
		if (temp->i != 0)
			(*sewing)->tail->len += temp->i * BUFFER_SIZE;
		temp = temp->next;
	}
	line = malloc((*sewing)->tail->len + 1 * sizeof(char));
	line[(*sewing)->tail->len] = '\0';
	temp = (*sewing)->head;
	i[0] = 0;
	i[1] = 0;
	while (temp->next != NULL)
	{
		line[i[0]++] = temp->content[i[1]++];
		if (temp->content[i[1]] == '\0')
		{
			temp = temp->next;
			i[1] = 0;
		}
	}
	return (line);
}

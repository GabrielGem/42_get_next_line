/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:59:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/16 20:19:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(t_list **head, char **line, int i_line)
{
	t_list	*node;
	int		len;

	node = *head;
	len = 0;
	while (node)
	{
		len += node->len;
		node = node->next;
	}
	*line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	(*line)[len] = '\0';
	node = *head;
	while (len--)
	{
		(*line)[i_line++] = node->content[node->i++];
		if (node->content[node->i] == '\0')
			node = node->next;
		if (node && node->content[node->i] == 0 && node->i == node->read_bytes)
			return (NULL);
	}
	return (*line);
}

t_list	*check_remain(t_list **head)
{
	t_list	*tail;
	t_list	*remain;
	int		i;
	int		len;

	tail = last_node(head);
	if (!(tail->i + 1 < tail->read_bytes))
		return (free_list(head));
	remain = init_node();
	if (!remain)
		free(remain);
	len = tail->read_bytes - tail->i;
	remain->content = malloc(len + 1 * sizeof(char));
	if (!remain)
		return (free_list(&remain));
	remain->content[len] = '\0';
	i = 0;
	while (++tail->i < tail->read_bytes)
		remain->content[i++] = tail->content[tail->i];
	*head = free_list(head);
	remain->len = i;
	return (remain);
}

t_list	*init_node(void)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->i = 0;
	node->len = 0;
	node->read_bytes = 0;
	node->content = NULL;
	node->next = NULL;
	return (node);
}

t_list	*last_node(t_list **head)
{
	t_list	*aux;

	aux = *head;
	while (aux->next != NULL)
		aux = aux->next;
	return (aux);
}

void	*free_list(t_list **head)
{
	t_list	*aux;

	aux = *head;
	while (aux != NULL)
	{
		if (aux->content)
			free(aux->content);
		*head = aux->next;
		free(aux);
		aux = *head;
	}
	return ((void *)0);
}

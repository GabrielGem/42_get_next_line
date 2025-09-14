/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:59:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/09/14 18:56:18 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(t_list **head, char **line)
{
	t_list	*node;
	int		len;
	int		i_line;

	node = *head;
	len = 0;
	while (node->next != NULL)
	{
		len += node->len;
		node = node->next;
	}
	len += node->len;
	*line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	(*line)[len] = '\0';
	node = *head;
	i_line = 0;
	while (len--)
	{
		(*line)[i_line++] = node->content[node->i++];
		if (node->content[node->i] == '\0')
			node = node->next;
	}
	(*line)[i_line] = '\n';
	return (*line);
}

t_list	*check_remain(t_list **head)
{
	t_list	*tail;
	t_list	*remain;
	int		i;
	int		len;

	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
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

void	*free_list(t_list **head)
{
	t_list	*aux;

	aux = *head;
	while (aux->next != NULL)
	{
		(*head) = (*head)->next;
		free(aux->content);
		free(aux);
		aux = *head;
	}
	free(aux->content);
	free(aux);
	return ((void *)0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:43:01 by jbesnier          #+#    #+#             */
/*   Updated: 2021/12/12 18:24:46 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_data	*lstnew(char *key, char *value, t_global *g)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (new == NULL)
	{
		g->status = errno;
		return (NULL);
	}
	new -> key = key;
	new -> value = value;
	new -> next = NULL;
	return (new);
}

int	lst_add(char *key, char *value, t_data **lst, t_global *g)
{
	t_data	*new;

	new = lstnew(key, value, g);
	if (new == NULL)
		return (ERROR);
	if (*lst == NULL)
	{
		*lst = new;
		return (OK);
	}
	new -> next = *lst;
	*lst = new;
	return (OK);
}

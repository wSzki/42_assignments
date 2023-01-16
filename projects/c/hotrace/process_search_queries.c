/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_search_queries.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 00:09:09 by wszurkow          #+#    #+#             */
/*   Updated: 2021/12/12 20:14:05 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*compare_key(t_data *lst, char *to_search)
{
	while (lst)
	{
		if (ft_strcmp(lst->key, to_search) == 0)
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

void	search_key(char *key, t_global *g)
{
	unsigned long int	hash;
	char				*collision;

	hash = hash_function(key);
	if (g->ret[hash] == NULL)
	{
		ft_putstr(key, 2);
		ft_putstr(": not found\n", 2);
	}
	else
	{
		collision = compare_key(g->ret[hash], key);
		if (collision == NULL)
		{
			ft_putstr(key, 2);
			ft_putstr(": not found\n", 2);
		}
		else
		{
			ft_putstr(collision, 1);
			ft_putstr("\n", 1);
		}
		return ;
	}
}

void	process_search_queries(t_global *g, char **line)
{
	(void)g;
	while (get_next_line(line) > 0)
	{
		if (**line == '\0')
		{
			free(*line);
			*line = NULL;
			continue ;
		}
		search_key(*line, g);
		free(*line);
		*line = NULL;
	}
}

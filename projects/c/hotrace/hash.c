/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:27:02 by wszurkow          #+#    #+#             */
/*   Updated: 2021/12/12 18:25:27 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static unsigned	long int	power(int a, int b)
{
	unsigned long int	ret;

	ret = a;
	while (b-- > 1)
		ret *= a;
	return (ret);
}

unsigned long	hash_function(char *str)
{
	int					i;
	unsigned long int	ret;

	i = 0;
	ret = str[0];
	while (str[++i])
		ret += str[i] * (power(P, i - 1));
	return (ret % MAGIC_NUMBER);
}

int	sub_hash_haystack(t_global *g, t_data **gret, unsigned long index, int *i)
{
	char	**hs;

	hs = g->haystack;
	if ((gret)[index] == NULL)
	{
		(gret)[index] = ft_calloc(1, sizeof(*((gret)[index])));
		if (gret[index] == NULL)
		{
			g->status = errno;
			return (ERROR);
		}
		((gret)[index])->key = (g->haystack)[*i];
		((gret)[index])->value = (g->haystack)[*i + 1];
	}
	else
	{
		if (lst_add(hs[*i], hs[*i + 1], &(gret)[index], g) == ERROR)
			return (ERROR);
	}
	return (OK);
}

void	hash_haystack(t_global *g)
{
	int				i;
	unsigned long	hashed_index;

	i = 0;
	while (i < g->nb_hay)
	{
		hashed_index = hash_function(g->haystack[i]);
		if (sub_hash_haystack(g, g->ret, hashed_index, &i) == ERROR)
			return ;
		i += 2;
	}
}

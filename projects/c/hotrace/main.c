/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:38:41 by wszurkow          #+#    #+#             */
/*   Updated: 2021/12/12 20:14:21 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	free_g(t_global *g)
{
	t_data		*tmp;
	int			hashed_indexes;

	hashed_indexes = MAGIC_NUMBER - 1;
	if (g)
	{
		while (hashed_indexes-- > 0)
		{
			while ((g->ret)[hashed_indexes])
			{
				tmp = (g->ret)[hashed_indexes]->next;
				(void)tmp;
				free((g->ret)[hashed_indexes]);
				(g->ret)[hashed_indexes] = tmp;
			}
		}
		while (g->nb_hay-- > 0)
			free(g->haystack[g->nb_hay]);
		while (g->nb_needles-- > 0)
			free(g->needles[g->nb_needles]);
		free(g->haystack);
		free(g->needles);
		free(g->ret);
		free(g);
	}
}

void	free_all(t_global *g, char **line)
{
	if (line)
		free(*line);
	free_g(g);
	free(line);
}

char	**init(t_global *g)
{
	char	**line;

	g->status = 0;
	g->nb_hay = 0;
	g->nb_needles = 0;
	g ->ret = ft_calloc(MAGIC_NUMBER, sizeof(t_data **));
	if (g->ret == NULL)
		g->status = errno;
	g->haystack = malloc(sizeof(char *) * MEMORY_SIZE);
	if (g->haystack == NULL)
		g->status = errno;
	g->needles = malloc(sizeof(char *) * MEMORY_SIZE);
	if (g->needles == NULL)
		g->status = errno;
	line = malloc(sizeof(char **));
	if (line == NULL)
		g->status = errno;
	return (line);
}

void	g_error(t_global *g)
{
	if (g->status)
	{
		if (g->status == ERR_PARSING)
			ft_putstr("Error\nParsing error\n", 2);
		else
			strerror(g->status);
	}
}

int	main(void)
{
	t_global	*g;
	char		**line;
	int			status;

	g = calloc(1, sizeof(*g));
	if (g == NULL)
	{
		strerror(errno);
		return (errno);
	}
	line = init(g);
	if (g->status == 0)
		parse_input_file(g, line);
	if (g->status == 0)
		hash_haystack(g);
	if (g->status == 0)
		process_search_queries(g, line);
	g_error(g);
	status = g->status;
	free_all(g, line);
	return (status);
}

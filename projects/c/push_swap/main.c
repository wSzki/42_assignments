/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:38:31 by wszurkow          #+#    #+#             */
/*   Updated: 2021/06/09 16:39:13 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pushswap.h"

static t_global	*init_g(t_global *g)
{
	g = malloc(sizeof(t_global));
	if (!g)
		print_error_and_exit();
	g->a = NULL;
	g->b = NULL;
	return (g);
}

static t_global	*init_tab_a_and_b(t_global *g)
{
	g->a = malloc(sizeof(t_tab));
	if (!g->a)
	{
		free(g);
		print_error_and_exit();
	}
	g->b = malloc(sizeof(t_tab));
	if (!g->b)
	{
		free(g->a);
		free(g);
		print_error_and_exit();
	}
	g->a->data = NULL;
	g->b->data = NULL;
	g->a->id = 0;
	g->b->id = 1;
	return (g);
}

static t_global	*init_tab_data(t_global *g, int ac)
{
	g->a->data = malloc(sizeof(int) * ac - 1);
	if (!g->a->data)
		free_everything_and_exit(g);
	g->b->data = malloc(sizeof(int));
	if (!g->b->data)
		free_everything_and_exit(g);
	g->a->size = ac - 1;
	g->b->size = 0;
	return (g);
}

static t_global	*init_struct(t_global *g, int ac)
{
	g = init_g(g);
	g = init_tab_a_and_b(g);
	g = init_tab_data(g, ac);
	return (g);
}

int	main(int ac, char **av)
{
	t_global	*g;

	g = NULL;
	if (ac == 1)
		return (0);
	if (ac < 2)
		print_error_and_exit();
	if (ac == 2)
		return (0);
	g = init_struct(g, ac);
	fill_tab_a(g, ac, av);
	sort(g, 0);
	free_everything(g);
	return (0);
}

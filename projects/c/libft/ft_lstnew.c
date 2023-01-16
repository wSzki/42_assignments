/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:08:39 by wszurkow          #+#    #+#             */
/*   Updated: 2020/10/14 18:28:40 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *child;

	if (!(child = (t_list*)malloc(sizeof(*child))))
		return (NULL);
	child->content = content;
	child->next = NULL;
	return (child);
}

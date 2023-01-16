/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_getenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:15:52 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/19 16:23:03 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define EQUAL 1

char	*custom_getenv(char *str, char **env)
{
	int	i;
	int	len;

	if (!str)
		return (extract_string("", 1));
	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], len) == 0)
		{
			if (env[i][len] == '=')
				return (extract_string(&env[i][len + EQUAL], FULL_LENGTH));
		}
		i++;
	}
	return (extract_string("", 1));
}

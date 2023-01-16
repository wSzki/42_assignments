/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing.utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:31:22 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:32:19 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_parsing_is_whitespace(char c)
{
	int		i;
	char	*w;

	i = -1;
	w = "\t\n\r\v\f";
	while (w[++i])
		if (w[i] == c)
			return (TRUE);
	return (FALSE);
}

int	cub_parsing_is_in_charset(char *str, char *charset)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (charset[++j])
			if (charset[j] == str[i])
				break ;
		if (charset[j] == '\0')
			return (FALSE);
	}
	return (TRUE);
}

int	cub_parsing_is_in(char tile, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
		if (tile == charset[i])
			return (TRUE);
	return (FALSE);
}

int	cub_parsing_get_array_len(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	cub_parsing_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

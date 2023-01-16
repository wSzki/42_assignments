/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:47:10 by adlancel          #+#    #+#             */
/*   Updated: 2021/11/12 13:59:05 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*wrap_each_word_with_double_quotes(char *ret_str, int i, int j, int k)
{
	char	**split;
	char	*buffer_str;

	if (only_whitespaces(ret_str) == YES)
		return (ret_str);
	j = ft_strlen(ret_str);
	split = ft_split(ret_str, ' ');
	i = tablen(split);
	buffer_str = malloc(sizeof(char ) * (j + (i * 3) + 1));
	if (!buffer_str)
		error_management("", errno);
	i = -1;
	while (split[++i])
	{
		j = -1;
		buffer_str[++k] = '\"';
		while (split[i][++j])
			buffer_str[++k] = split[i][j];
		buffer_str[++k] = '\"';
		buffer_str[++k] = ' ';
	}
	buffer_str[k] = '\0';
	double_free((void **)split);
	free (ret_str);
	return (buffer_str);
}

int	is_alphabet(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (YES);
	return (NO);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*ret_str;

	ret_str = NULL;
	if (s1 || s2)
	{
		ret_str = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return (ret_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:18:48 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/01 18:11:28 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_free(char **tab, int index)
{
	while (index >= 0)
	{
		free((void *)tab[index]);
		index--;
	}
	free(tab);
	return (NULL);
}

static int	count_words(char const *str, char charset)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] != charset)
			i++;
		words++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (words);
}

static char	**count_letters(char const *str, char charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && str[i] != charset)
		{
			letters++;
			i++;
		}
		tab[index] = malloc(sizeof(char) * (letters + 1));
		if (!(tab))
			return (ft_free(tab, index));
		tab[index][letters] = 0;
		index++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (tab);
}

static char	**split_copy(char const *str, char charset, char **tab)
{
	int	i;
	int	index;
	int	letters;

	i = 0;
	index = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] && str[i] != charset)
			tab[index][letters++] = str[i++];
		index++;
		while (str[i] && str[i] == charset)
			i++;
	}
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		words;

	if (!str)
		return (NULL);
	while (*str && *str == c)
		str++;
	words = count_words(str, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(tab))
		error_management("", errno);
	tab[words] = 0;
	tab = count_letters(str, c, tab);
	tab = split_copy(str, c, tab);
	return (tab);
}

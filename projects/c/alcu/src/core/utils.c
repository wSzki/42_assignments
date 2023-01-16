/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 07:22:30 by jraffin           #+#    #+#             */
/*   Updated: 2022/02/13 20:55:29 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (src == dest)
		return (dest);
	while (n)
	{
		n--;
		((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0 && *(unsigned char *)s != (unsigned char)c)
	{
		s++;
		n--;
	}
	if (n > 0)
		return ((void *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_intlen(int n)
{
	int		i;

	i = (n <= 0);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int value, char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_intlen(value);
	if (value > 0)
		value = -value;
	str[i--] = '\0';
	str[i--] = '0' - (value % 10);
	value /= 10;
	while (value)
	{
		str[i--] = '0' - (value % 10);
		value /= 10;
	}
	if (i >= 0)
		str[0] = '-';
	return (str);
}

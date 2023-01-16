/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:48:26 by jbesnier          #+#    #+#             */
/*   Updated: 2021/12/12 20:29:41 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

# define MEMORY_SIZE 1000000000

# define ERROR      -1
# define OK          0
# define ERR_MEMORY  -2
# define ERR_PARSING -3

# define NO  0
# define YES 1

# define P            257
# define MAGIC_NUMBER 10000009

typedef struct s_data
{
	char			*key;
	char			*value;
	struct s_data	*next;
}		t_data;

typedef struct s_global
{
	char			**haystack;
	char			**needles;
	int				nb_needles;
	int				nb_hay;
	unsigned int	smallest_char;
	unsigned int	largest_char;
	t_data			**ret;
	int				status;

}	t_global;

void			free_all(t_global *g, char **line);
void			*ft_calloc(unsigned long long nmemb, size_t size);
int				get_next_line(char **line);
void			ft_putstr(char *str, int fd);
int				ft_strcmp(char *str1, char *str2);
char			*ft_strdup(t_global *g, const char *src);
void			parse_input_file(t_global *g, char **line);
int				lst_add(char *key, char *value, t_data **lst, t_global *g);
void			hash_haystack(t_global *g);
unsigned long	hash_function(char *str);
void			process_search_queries(t_global *g, char **line);

#endif

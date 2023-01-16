/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 04:07:08 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/02 18:24:41 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <errno.h>

# include "mlx.h"

# define PI 3.1415926535
# define CIRCLE 360.0

# define TRUE 1
# define FALSE 0

# define SCALE 4

# define YELLOW 0x00fabd2f
# define GREEN  0x00a9b665
# define RED    0x00ea6962
# define BLUE   0x007C9C90

# define NO BLUE
# define SO GREEN
# define ES RED
# define WE YELLOW

# define N 2
# define S 3
# define E 4
# define W 5

# define NORTH 1.57079632675 // PI / 2
# define SOUTH 4.71238898025 // PI / 2 * 3
# define EAST  PI
# define WEST  0

# define WIDTH 640
# define HEIGHT 640

# define VIEW_RANGE        60.0
# define VIEW_ANGLE_OFFSET 30.0

# define PIXELS_PER_STEP 15
# define DEGREES_PER_STEP 2

# define MM_FLOOR_COLOR  0x00DDDDDD
# define MM_WALL_COLOR   0x00666666
# define MM_PLAYER_COLOR 0x00ea6962

# define UP    65362
# define DOWN  65364
# define LEFT  65361
# define RIGHT 65363
# define ESC   65307
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define W_KEY 119

# define LOG   108

# define ERR_PARSING_MAP       1
# define ERR_PARSING_RGB       2
# define ERR_CANNOT_OPEN       3
# define ERR_PATH_TEXTURE      4
# define ERR_PARAM_ALREADY_SET 5
# define ERR_PARAM_INVALID     6
# define ERR_PARAM_NOT_ENOUGH  7
# define ERR_MLX               8
# define ERR_PARSING           9
# define ERR_SYS               10
# define ERR_MALLOC            11

# define MERR_PARSING_MAP       "Invalid map\n"
# define MERR_PARSING_RGB       "Invalid RGB format(s)\n"
# define MERR_CANNOT_OPEN_MAP   "Cannot open/read .cub file\n"
# define MERR_MAP_EXTENSION     "Invalid filename or missing .cub extension\n"
# define MERR_PATH_TEXTURE      "Cannot open/read .xpm file\n"
# define MERR_PARAM_ALREADY_SET "Parameter(s) has been set multiple times\n"
# define MERR_PARAM_INVALID     "Invalid or missing parameter(s)\n"
# define MERR_PARAM_NOT_ENOUGH  "Parameter(s) missing\n"
# define MERR_MLX               "MLX error\n"
# define MERR_MLX_IMG           "MLX image error\n"
# define MERR_PARSING           "Parsing error\n"
# define MERR_SYS               "Syscall error\n"
# define MERR_MALLOC            "Malloc error\n"
# define MERR_TRAILING_MAP      "Data detected after map\n"
# define MERR_MAP_TOO_SMALL     "Map must be at least 3x3\n"
# define MERR_MULT_PLAYER_POS   "Player position set multiple times\n"
# define MERR_MAP_NOT_CLOSED    "Map is not closed\n"
# define MERR_MAP_INVALID_CHAR  "Invalid character in map\n"
# define MERR_PLAYER_NOT_SET    "Player position (NSEW) has not been set\n"

# define WINDOW_NAME "CUB3D"

typedef struct s_data
{
	char			*n;
	char			*s;
	char			*w;
	char			*e;
	char			*r;
	unsigned int	f;
	unsigned int	c;
}	t_data;

typedef struct s_map
{
	char	**map;
	int		rows;
	int		cols;
	int		in_map;
	int		player;
}	t_map;

typedef struct s_win
{
	int	w;
	int	h;
}	t_win;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_px;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	int	x;
	int	y;
	int	angle;
}	t_player;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_vector
{
	t_coord			start;
	t_coord			end;
	unsigned int	color;
}	t_vector;

typedef struct s_minimap
{
	int				block_size;
	int				player_size;
	unsigned int	wall_color;
	unsigned int	floor_color;
	unsigned int	player_color;
}	t_minimap;

typedef struct s_wall
{
	double			start;
	double			end;
	double			size;
	int				offset_x;
	int				offset_y;
	unsigned int	color;
}	t_wall;
/////////////////////////////////////////

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	buffer;
	t_img	background;
	t_img	north;
	t_img	east;
	t_img	west;
	t_img	south;
	t_img	minimap;
	t_img	mm_wall;
	t_img	mm_floor;
	t_img	mm_player;
}	t_mlx;

typedef struct s_global
{
	t_data		d;
	t_map		m;
	t_win		w;
	t_mlx		x;
	t_player	p;
	t_minimap	mm;
	t_wall		wall;
	char		*line;
	char		**split;
	int			fd;
}	t_global;

// MEMORY
void			cub_error(t_global *g, int error);
void			cub_error_str(t_global *g, char *error);
void			cub_free_all(t_global *g);

// INITIALIZATION
void			cub_init(t_global **g);
void			cub_init_img(t_global *g, t_img *img, int w, int h);
void			cub_init_xpm(t_global **g);
void			cub_init_mlx(t_global **g);
void			cub_init_angle(t_global *g, char dir);

// PIXELS   
unsigned int	cub_get_pixel(t_img *img, int w, int h);
void			cub_put_pixel(t_img *img, int w, int h, unsigned int color);

// DISPLAY
void			cub_display(t_global *g);
void			cub_display_refresh(t_global *g);
void			cub_put_map(t_global *g);
void			cub_render_walls(t_global *g);
void			cub_img_join(t_img *dest, t_img *src, int w_off, int h_off);
int				cub_keypress(int keycode, t_global *g);

// CALCULUS
int				get_infinite(t_global *g, double ra, int flag);
t_vector		get_first_out_v(t_global *g, t_vector v, double ra);
t_vector		get_first_out_h(t_global *g, t_vector v, double ra);
t_coord			cub_vector_end(t_coord start, double len, double angle);
t_coord			cub_get_wall_pos(\
		t_global *g, t_vector v, double ray, unsigned int *color);

// PARSING
// Utils
int				cub_parsing_strcmp(char *s1, char *s2);
int				cub_parsing_is_in(char tile, char *charset);
int				cub_parsing_is_in_charset(char *str, char *charset);
int				cub_parsing_is_whitespace(char c);
int				cub_parsing_get_array_len(char **arr);
void			cub_parsing_free_split(char ***s, char **line);

// Main Parsing
void			cub_parsing_fetch_data(t_global *g, int fd, int *checks);
void			cub_parsing_fill_path(t_global *g, char **c, int *checks);
void			cub_parsing_skip_newlines(t_global *g, int fd, int check);
void			cub_parsing_fetch_map(t_global *g, int fd);
void			cub_parsing_check_after_map(t_global *g, int fd);
void			cub_parsing_validate_map(t_global *g);
void			cub_parsing_fill_color(\
		t_global *g, unsigned int *c, int *checks);

// UTILS
double			cub_get_axis_dist(t_vector v, t_coord end);
double			cub_normalize(double angle);
int				ft_max(int a, int b);
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
char			**ft_split(const char *s1, char c);
char			*ft_strdup(const char *s1);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
int				get_next_line(int fd, char **line);
int				ft_is_in_c(char c, char *charset);

// # ##########################       ARCHIVE   ##############################
int				cub_circle(t_global *g); // TODO useless
void			cub_bresenham(t_img *img, t_vector vector, unsigned int color);

// Old Parsing (unused)
int				is_map_line(const char *line);
int				is_correct_map(t_global *g);
int				check_borders(t_global *g, int y, int x);
void			check_args(t_global *g, char *path);
void			get_line(char *line, t_global *g);
void			get_path_or_value(const char *line, t_global *g);
int				check_map(t_global *g, int fd);
void			check_hexa(const char *raw, t_global *g, int flag);
void			check_path(const char *raw, t_global *g, int flag);
// # ##########################       ARCHIVE   ##############################
#endif

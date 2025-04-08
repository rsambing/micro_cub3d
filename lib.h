#ifndef LIB_H
# define LIB_H

# include "minilibx_linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846
# define FOV M_PI / 3
# define MAP_SIZE 8
# define BLOCK 64

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}			t_player;

typedef struct s_ray
{
	double	x;
	double	y;
	double	dist;
}			t_ray;

typedef struct s_map
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    t_player player;
}			t_map;

int			raycasting(t_map *map);
int			close_window(t_map *map);
#endif

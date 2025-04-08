#include "lib.h"

int		real_map[MAP_SIZE][MAP_SIZE] = {{1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0,
			0, 0, 0, 1}, {1, 0, 1, 1, 1, 1, 0, 1}, {1, 0, 1, 0, 0, 1, 0, 1}, {1,
			0, 1, 0, 0, 1, 0, 1}, {1, 0, 1, 1, 1, 1, 0, 1}, {1, 0, 0, 0, 0, 0,
			0, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};

void	draw_pixel(t_map *map, int x, int y, int color)
{
	mlx_pixel_put(map->mlx, map->win, x, y, color);
}

double	cast_ray(double angle, t_map *map)
{
	double	x;
	double	y;
	double	dx;
	double	dy;

	x = map->player.x;
	y = map->player.y;
	dx = cos(angle) * 0.1;
	dy = sin(angle) * 0.1;
	while (real_map[(int)x / BLOCK][(int)y / BLOCK] == 0)
	{
		x += dx;
		y += dy;
	}
	return (sqrt(pow(x - map->player.x, 2) + pow(y - map->player.y, 2)) * cos(angle - map->player.angle));
}

int	raycasting(t_map *map)
{
	double	angle;
	double	step;
	double	dist;
	int		wall_height;

	angle = map->player.angle - (FOV / 2);
	step = FOV / WIDTH;
	for (int i = 0; i < WIDTH; i++, angle += step)
	{
		dist = cast_ray(angle, map);
		wall_height = (int)(BLOCK / dist * 500);
		for (int y = HEIGHT / 2 - wall_height / 2; y < HEIGHT / 2 + wall_height
			/ 2; y++)
			draw_pixel(map, i, y, 0xFFFFFF);
	}
	return (0);
}

int	key_hook(int keycode, t_map *map)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
	{
		map->player.x += cos(map->player.angle) * 10;
		map->player.y += sin(map->player.angle) * 10;
	}
	if (keycode == 115)
	{
		map->player.x -= cos(map->player.angle) * 10;
		map->player.y -= sin(map->player.angle) * 10;
	}
	if (keycode == 97)
		map->player.angle -= 0.1;
	if (keycode == 100)
		map->player.angle += 0.1;
	mlx_clear_window(map->mlx, map->win);
	raycasting(map);
	return (0);
}

int	main(void)
{
	t_map	map;

	// #### iniciliazao #####
	memset(&map, 0, sizeof(t_map));
	map.bits_per_pixel = 0;
	map.line_length = 0;
	map.endian = 0;
	map.player.x = 96; // Começa no centro de um bloco (64 + 32)
	map.player.y = 96;
	map.player.angle = M_PI / 2;
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "cub3d");
	map.img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
	map.addr = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
	// #### inicio ####
	raycasting(&map);
	mlx_key_hook(map.win, (void *)key_hook, &map);
	mlx_loop(map.mlx);
	return (0);
}

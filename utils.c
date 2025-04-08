#include "lib.h"

int close_window(t_map *map)
{
    mlx_destroy_image(map->mlx, map->img);
    mlx_destroy_window(map->mlx, map->win);
    mlx_destroy_display(map->mlx);
    free(map->mlx);
    exit(0);
    return (0);
}

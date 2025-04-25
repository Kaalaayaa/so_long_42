#ifndef SO_LONG_H
# define SO_LONG_H

// #define WIDTH 1000
// #define HEIGHT 1000
#define TILE_SIZE 32


#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

typedef struct s_game {
    char **map;                        // Map data (still the same)
    int rows;                          // Number of rows in the map
    int cols;                          // Number of columns in the map
    int player_x;                      // Player X position
    int player_y;                      // Player Y position
    int total_collectibles;            // Total number of collectibles in the map
    int collected;                     // Number of collected items
    int move_count;                    // Number of moves made by the player
    mlx_t *mlx;                        // MLX42 context
    void *mlx_win;             // MLX42 window
    mlx_image_t *img_floor;            // MLX42 image (floor)
   mlx_image_t *img_wall;             // MLX42 image (wall)
    mlx_image_t *img_collectibles;     // MLX42 image (collectibles)
    mlx_image_t *img_exit;             // MLX42 image (exit)
    mlx_image_t *img_player;           // MLX42 image (player)
    mlx_image_t *img_player_up;
    mlx_image_t *img_player_down;
    mlx_image_t *img_player_left;
    mlx_image_t *img_player_right;
    mlx_image_t *img_wall_top;
mlx_image_t *img_wall_bottom;
mlx_image_t *img_wall_left;
mlx_image_t *img_wall_right;
mlx_image_t *img_wall_topleft;
mlx_image_t *img_wall_topright;
mlx_image_t *img_wall_bottomleft;
mlx_image_t *img_wall_bottomright;
} t_game;

int parse_map(t_game *game, int map_fd, const char *filename);
int validate_map(t_game *game);
int open_file(const char *filename);
void free_map(char **map);
char ** duplicate_map(char **map, int row);
int find_player(char **map, int *x, int *y);
void flood_fill(char **map, int x, int y);
void remove_newline(char *line);
void init_game(t_game *game);
void move_player(t_game *game, int dir_x, int dir_y);
void load_images(t_game *game);
void render_map(t_game *game);
void handle_key(mlx_key_data_t keydata, void *param);

#endif
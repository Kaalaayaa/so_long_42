#include "../include/so_long.h"

void print_map(t_game *game)
{
    for (int i = 0; i < game->rows; i++)
    printf("%s\n", game->map[i]);
    printf("\n");
}

//int main(int argc, char **argv)
//{


//     t_game game;

//     game.rows = 0;
//     game.cols = 0;
//     game.map = NULL;

//     int map_fd;
    
// 	if (argc != 2)
//     {
//         printf("Usage: ./so_long <map_file>\n");
//         return (1);
//     }
// 	map_fd = open_file(argv[1]);

//     if (!parse_map(&game, map_fd, argv[1]))
//     {
//         perror("Map parsing failed");
//         return (-1);
//     }
//     if(!validate_map(&game))
//     {
//         perror("Map is not valid");
//         return(-1);
//     }

//     // Initialize the game state

//     init_game(&game);
//     game.mlx = mlx_init();
//     if (!game.mlx)
// {
//     perror("mlx_init failed\n");
//     return (1);
// }
//     game.mlx_win = mlx_new_window(game.mlx, game.cols * TILE_SIZE, game.rows * TILE_SIZE, "Hello world!");
//     load_images(&game);
//     if (!game.img_wall || !game.img_floor || !game.img_player ||
//         !game.img_collectibles || !game.img_exit)
//     {
//         printf("❌ Error: One or more images failed to load.\n");
//         exit(1);
//     }
//     mlx_put_image_to_window(game.mlx, game.mlx_win, game.img_wall, 0, 0);
//     render_map(&game);

//     //mlx_key_hook();
//     mlx_loop(game.mlx);

//     free_map(game.map);
// 	close(map_fd);
// 	return (0);
//}

#include "../include/so_long.h"

// Error handling function
static void error(void)
{
    puts(mlx_strerror(mlx_errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    t_game game;
    int map_fd;

    
    if (argc != 2)
    {
        printf("Usage: ./so_long <map_file>\n");
        return (1);
    }

    game.rows = 0;
    game.cols = 0;
    game.map = NULL;

    map_fd = open_file(argv[1]);

    if (!parse_map(&game, map_fd, argv[1]))
    {
        perror("Map parsing failed");
        return (-1);
    }
    if(!validate_map(&game))
    {
        perror("Map is not valid");
        return(-1);
    }
    init_game(&game);

    int window_width = game.cols * TILE_SIZE;
int window_height = game.rows * TILE_SIZE;
    // Initialize MLX
    mlx_t *mlx = mlx_init(window_width, window_height, "So Long Game", true); // MLX42 initialization
    if (!mlx)
        error();

    // Initialize game structure
    game.mlx = mlx;

    // Load images for the game
    load_images(&game);
    
    mlx_key_hook(mlx, handle_key, &game);

    // Render the map
    render_map(&game);
    printf("Floor instances: %zu\n", game.img_floor->count);

    // Start the game loop
    mlx_loop(mlx); // MLX42 loop

    // Clean up and terminate MLX
    mlx_terminate(mlx);
    free_map(game.map);
    close(map_fd);

    return EXIT_SUCCESS;
}
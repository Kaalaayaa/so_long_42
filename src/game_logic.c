#include "../include/so_long.h"

void init_game(t_game *game)
{
	printf("Initializing game...\n");
	int i;
	int j;

    game->collected = 0;
    game->total_collectibles = 0;
    game->move_count = 0;

    if(!find_player(game->map, &game->player_x, &game->player_y))
    {
        perror("Player position not found");
        return;
    }

    i = 0;
    while(i < game->rows)
    {
        j = 0;
        while(j < game->cols)
        {
            if(game->map[i][j] == 'C')
                game->total_collectibles++;
            j++;
        }
        i++;
    }
    printf("Player starts at (%d, %d)\n", game->player_x, game->player_y);
    printf("Total collectibles: %d\n", game->total_collectibles);
}

void exit_game(t_game *game)
{
    free_map(game->map);
    exit(0);
}

int is_move_valid(t_game *game, int x, int y)
{
    if(x < 0 || x >= game->cols || y < 0 || y >= game->rows)
        return 0;
    if(game->map[y][x] == '1')
        return 0;

    return 1;
}

void move_player(t_game *game, int dir_x, int dir_y)
{
    int new_x = game->player_x + dir_x;
    int new_y = game->player_y + dir_y;

    // Directional sprite switching
    if (dir_x == -1)
        game->img_player = game->img_player_left;
    else if (dir_x == 1)
        game->img_player = game->img_player_right;
    else if (dir_y == -1)
        game->img_player = game->img_player_up;
    else if (dir_y == 1)
        game->img_player = game->img_player_down;

    if (!is_move_valid(game, new_x, new_y))
        return;

    // Collectible
    if (game->map[new_y][new_x] == 'C')
    {
        game->collected++;
        game->map[new_y][new_x] = '0';
    }

    // Exit
    if (game->map[new_y][new_x] == 'E')
    {
        if (game->collected == game->total_collectibles)
        {
            printf("You win! Total moves: %d\n", game->move_count + 1);
            exit_game(game);
        }
        else
        {
            printf("Collect all items first!\n");
            return;
        }
    }

    // Move player on map
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    game->move_count++;

    printf("Moved: %d steps\n", game->move_count);
}

void handle_key(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;
    if(keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
        return;

         // Debugging output: Print the key that was pressed
    printf("Key pressed: %d\n", keydata.key);
    
        if (keydata.key == MLX_KEY_ESCAPE)
            exit_game(game);
        else if (keydata.key == MLX_KEY_UP)
            move_player(game, 0, -1);
        else if(keydata.key == MLX_KEY_LEFT)
            move_player(game, -1, 0);
        else if(keydata.key == MLX_KEY_DOWN)
            move_player(game, 0, 1);
        else if(keydata.key == MLX_KEY_RIGHT)
            move_player(game, 1, 0);
        
        render_map(game);
}

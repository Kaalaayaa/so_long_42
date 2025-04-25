#include "../include/so_long.h"

void load_images(t_game *game)
{
    // Floor
    mlx_texture_t *tex_floor = mlx_load_png("./assets/black.png");
    game->img_floor = mlx_texture_to_image(game->mlx, tex_floor);
    mlx_resize_image(game->img_floor, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_floor);

    // Walls
    game->img_wall = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Longbricks.png"));
    mlx_resize_image(game->img_wall, TILE_SIZE, TILE_SIZE);
    game->img_wall_top = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-horizontal.png"));
    mlx_resize_image(game->img_wall_top, TILE_SIZE, TILE_SIZE);
    game->img_wall_bottom = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-horizontal.png"));
    mlx_resize_image(game->img_wall_bottom, TILE_SIZE, TILE_SIZE);
    game->img_wall_left = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-vertical.png"));
    mlx_resize_image(game->img_wall_left, TILE_SIZE, TILE_SIZE);
    game->img_wall_right = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-vertical.png"));
    mlx_resize_image(game->img_wall_right, TILE_SIZE, TILE_SIZE);
    game->img_wall_topleft = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-top-left.png"));
    mlx_resize_image(game->img_wall_topleft, TILE_SIZE, TILE_SIZE);
    game->img_wall_topright = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-top-right.png"));
    mlx_resize_image(game->img_wall_topright, TILE_SIZE, TILE_SIZE);
    game->img_wall_bottomleft = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-bottom-left.png"));
    mlx_resize_image(game->img_wall_bottomleft, TILE_SIZE, TILE_SIZE);
    game->img_wall_bottomright = mlx_texture_to_image(game->mlx, mlx_load_png("./assets/Branchwall-bottom-right.png"));
    mlx_resize_image(game->img_wall_bottomright, TILE_SIZE, TILE_SIZE);

    // Collectibles
    mlx_texture_t *tex_collectibles = mlx_load_png("./assets/pacdot_food.png");
    game->img_collectibles = mlx_texture_to_image(game->mlx, tex_collectibles);
    mlx_resize_image(game->img_collectibles, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_collectibles);

    // Exit
    mlx_texture_t *tex_exit = mlx_load_png("./assets/portal.png");
    game->img_exit = mlx_texture_to_image(game->mlx, tex_exit);
    mlx_resize_image(game->img_exit, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_exit);

    // Player images (directions)
    mlx_texture_t *tex_player;

    tex_player = mlx_load_png("./assets/char_right.png");
    game->img_player_right = mlx_texture_to_image(game->mlx, tex_player);
    mlx_resize_image(game->img_player_right, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_player);

    tex_player = mlx_load_png("./assets/char_left.png");
    game->img_player_left = mlx_texture_to_image(game->mlx, tex_player);
    mlx_resize_image(game->img_player_left, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_player);

    tex_player = mlx_load_png("./assets/char_up.png");
    game->img_player_up = mlx_texture_to_image(game->mlx, tex_player);
    mlx_resize_image(game->img_player_up, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_player);

    tex_player = mlx_load_png("./assets/test.png");
    game->img_player_down = mlx_texture_to_image(game->mlx, tex_player);
    mlx_resize_image(game->img_player_down, TILE_SIZE, TILE_SIZE);
    mlx_delete_texture(tex_player);

    // Default direction
    game->img_player = game->img_player_right;
}

char get_tile(t_game *game, int x, int y)
{
    if (x < 0 || y < 0 || y >= game->rows || x >= game->cols)
        return ' ';
    return game->map[y][x];
}

void render_map(t_game *game)
{
    int y = 0, x;
    while (y < game->rows)
    {
        x = 0;
        while (x < game->cols)
        {
            char tile = game->map[y][x];
            int px = x * TILE_SIZE;
            int py = y * TILE_SIZE;

            // Always draw floor under everything
            mlx_image_to_window(game->mlx, game->img_floor, px, py);

            if (tile == '1')
            {
                // Check neighbors
                char up = get_tile(game, x, y - 1);
                char down = get_tile(game, x, y + 1);
                char left = get_tile(game, x - 1, y);
                char right = get_tile(game, x + 1, y);

                mlx_image_t *wall_img = game->img_wall;

                // Determine which image to use
                if (up != '1' && left != '1')
                    wall_img = game->img_wall_topleft;
                else if (up != '1' && right != '1')
                    wall_img = game->img_wall_topright;
                else if (down != '1' && left != '1')
                    wall_img = game->img_wall_bottomleft;
                else if (down != '1' && right != '1')
                    wall_img = game->img_wall_bottomright;
                else if (up != '1')
                    wall_img = game->img_wall_top;
                else if (down != '1')
                    wall_img = game->img_wall_bottom;
                else if (left != '1')
                    wall_img = game->img_wall_left;
                else if (right != '1')
                    wall_img = game->img_wall_right;

                mlx_image_to_window(game->mlx, wall_img, px, py);
            }
            else if (tile == 'C')
                mlx_image_to_window(game->mlx, game->img_collectibles, px, py);
            else if (tile == 'E')
                mlx_image_to_window(game->mlx, game->img_exit, px, py);
            else if (tile == 'P')
                mlx_image_to_window(game->mlx, game->img_player, px, py);

            x++;
        }
        y++;
    }
}
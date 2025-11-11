/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohdahma <mohdahma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:19:07 by mohdahma          #+#    #+#             */
/*   Updated: 2025/11/11 12:04:04 by mohdahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// Handle mouse movement events
int handle_mouse(int x, int y, t_game *game)
{
    t_player *player;
    int delta_x;
    static int initialized = 0;
    
    (void)y;
    player = game->player;
    
    if (!player->mouse_active)
        return (0);

    if (!initialized) {
        player->last_mouse_x = WIDTH/2;
        initialized = 1;
        mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH/2, HEIGHT/2);
        return (0);
    }

    // Calculate mouse movement from center
    delta_x = x - WIDTH/2;
    
    if (delta_x != 0) {
        // Increase sensitivity and make rotation smoother
        double rotation = delta_x * 0.005; // Increased sensitivity
        
        // Apply rotation to direction vector
        vec2_rotate_vec2(&player->dir, -rotation);
        vec2_normalized(&player->dir); // Ensure direction stays normalized
        
        // Update angle and plane
        player->angle = vec2_to_angle(player->dir);
        player->plane = calculate_plane(player->dir);
        
    // Force rendering update (render() will pick this up)
    player->is_moving = 1;
        
    // Reset mouse to center
        mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH/2, HEIGHT/2);
    }
    
    return (0);
}

// Toggle mouse control when M key is pressed
void toggle_mouse(t_game *game)
{
    static int first_toggle = 1;

    if (!game || !game->player || !game->mlx || !game->mlx->win)
        return;
    
    if (first_toggle) {
        game->player->mouse_active = 0;
        first_toggle = 0;
    }
    
    game->player->mouse_active = !game->player->mouse_active;
    
    if (game->player->mouse_active)
    {
        mlx_mouse_hide(game->mlx->mlx, game->mlx->win);
        game->player->last_mouse_x = WIDTH/2;
        mlx_mouse_move(game->mlx->mlx, game->mlx->win, WIDTH/2, HEIGHT/2);
    }
    else
        mlx_mouse_show(game->mlx->mlx, game->mlx->win);
    game->player->is_moving = 1;  // Force a redraw
}
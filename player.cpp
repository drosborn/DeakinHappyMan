#include "splashkit.h"
#include "happy_man.h"
using namespace std;

// Load bitmap for player.
bitmap player_bitmap(player_type type)
{
    switch (type)
    {
    default:
        return bitmap_named("happy_man");
    }
}

// Display player ship in window at x,y
player_data new_player()
{
    player_data result;
    
    result.x = -1;
    result.y = -1;
    result.dots = 0;
    result.type = HAPPY;

    return result;
}

void begin_player(game_data &game)
{
    bool start_not_found = true;
    game.player.super_charged = false;
    game.player.super_time = 50;
    
    for (int y = 0; y < game.level.map.y_segements_map and start_not_found; y++)
    {
        for (int x = 0; x < game.level.map.x_segements_map and start_not_found; x++)
        {
            if(game.level.map.map_array[y][x] == PATH)
            {
                game.player.x = x;
                game.player.y = y;
                start_not_found = false;
            }
        }
    }     
}

void draw_player(const game_data &game)
{
    float level_seqment_x = screen_width() / game.level.map.x_segements_map;
    float level_seqment_y = screen_height() / game.level.map.y_segements_map;

    if(game.player.super_charged)
    {
    fill_ellipse(COLOR_RED, level_seqment_x * game.player.x, level_seqment_y * game.player.y, level_seqment_x, level_seqment_y);    
    }
    else{
    fill_ellipse(COLOR_YELLOW, level_seqment_x * game.player.x, level_seqment_y * game.player.y, level_seqment_x, level_seqment_y);
    }
    
    if(game.player.next_direction == RIGHT)
    {
    fill_triangle(COLOR_BLACK
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y + level_seqment_y/2
        , level_seqment_x * game.player.x + level_seqment_x, level_seqment_y * game.player.y  + level_seqment_y/2
        , level_seqment_x * game.player.x + level_seqment_x, level_seqment_y * game.player.y + 3*level_seqment_y/4                       
    );
    fill_ellipse(COLOR_BLACK, level_seqment_x * game.player.x + 2*level_seqment_x/3 , level_seqment_y * game.player.y + level_seqment_y/3, level_seqment_x/8, level_seqment_y/8);
    }

    if(game.player.next_direction == LEFT)
    {
    fill_triangle(COLOR_BLACK
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y + level_seqment_y/2
        , level_seqment_x * game.player.x , level_seqment_y * game.player.y  + level_seqment_y/2
        , level_seqment_x * game.player.x , level_seqment_y * game.player.y + 3*level_seqment_y/4                       
    );
    fill_ellipse(COLOR_BLACK, level_seqment_x * game.player.x + 1*level_seqment_x/3 , level_seqment_y * game.player.y + level_seqment_y/3, level_seqment_x/8, level_seqment_y/8);
    }

    if(game.player.next_direction == UP)
    {
    fill_triangle(COLOR_BLACK
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y + level_seqment_y/2
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y  
        , level_seqment_x * game.player.x + 3*level_seqment_x/4, level_seqment_y * game.player.y                       
    );
    fill_ellipse(COLOR_BLACK, level_seqment_x * game.player.x + level_seqment_x/3 , level_seqment_y * game.player.y + level_seqment_y/3, level_seqment_x/8, level_seqment_y/8);
    }

    if(game.player.next_direction == DOWN)
    {
    fill_triangle(COLOR_BLACK
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y + level_seqment_y/2
        , level_seqment_x * game.player.x + level_seqment_x/2, level_seqment_y * game.player.y + level_seqment_y
        , level_seqment_x * game.player.x + 3*level_seqment_x/4, level_seqment_y * game.player.y + level_seqment_y                       
    );
    fill_ellipse(COLOR_BLACK, level_seqment_x * game.player.x + level_seqment_x/3 , level_seqment_y * game.player.y + 2*level_seqment_y/3, level_seqment_x/8, level_seqment_y/8);
    }

 


    /*  Draw Player as bitmap
    bitmap to_draw;
    to_draw = player_bitmap(game.player.type);
    float to_draw_height =  bitmap_height(to_draw);
    float to_draw_width =  bitmap_width(to_draw);
    
    draw_bitmap(to_draw, 
        game.player.x * level_seqment_x - to_draw_width/2  + level_seqment_x/2, 
        game.player.y * level_seqment_y - to_draw_height/2 + level_seqment_y/2, 
                option_scale_bmp(
                    level_seqment_x / to_draw_height,
                    level_seqment_y / to_draw_width));
    */

}

void draw_score(const player_data &player)
{
    draw_text("Score: " + to_string(player.dots),COLOR_RED,screen_width()/40,screen_width()/40);       
}

void player_hit_ghost(player_data &player, ghost_data &ghosts)
{
    int i = 0;  
    while (i < ghosts.ghost_array.size())
    {
        if(player.x == ghosts.ghost_array[i].x and player.y == ghosts.ghost_array[i].y and !player.super_charged and !ghosts.ghost_array[i].dead)
        {
            player.dots = 0;
        }
        
        if(player.x == ghosts.ghost_array[i].x and player.y == ghosts.ghost_array[i].y and player.super_charged and !ghosts.ghost_array[i].dead)
        {
            ghosts.ghost_array[i].dead = true;
            ghosts.ghost_array[i].dead_time = 50;
            player.dots += 10;
        }
        i++;
    }
}

void update_player(game_data &game)
{
    if(game.player.super_charged)
    {
        game.player.super_time--;
        if(game.player.super_time < 0)
        {
            game.player.super_charged = false;
            game.player.super_time = 50;
        }
    }

    player_hit_ghost(game.player, game.ghosts);
}
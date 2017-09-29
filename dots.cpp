#include "splashkit.h"
#include "happy_man.h"
#include <vector>


dot new_dot()
{
    dot result;
    int i;
    result.visible = true;
    
    if(rnd(100)<10)
    {
        result.dot = SUPER_DOT;    
    }
    else
    {
    result.dot = NORMAL_DOT;
    }
    return result;
}

dot no_dot()
{
    dot result;

    result.visible = false;
    result.dot = NO_DOT;
    return result;
}

void populate_dots(level_data &level)
{
    level.dots.dot_array.clear();     
    vector<dot> temp_row;
    level.in_level_dots = 0;
    
    for (int x = 0; x < level.map.x_segements_map; x++)
    {
        for (int y = 0; y < level.map.y_segements_map; y++)
        {
            if (level.map.map_array[y][x] == PATH)
            {
                temp_row.push_back(new_dot());
                level.in_level_dots++;
            }
            else
            {
                temp_row.push_back(no_dot());
            }
        }
        level.dots.dot_array.push_back(temp_row);
        temp_row.clear();
    }
}

void draw_dots(const level_data &level)
{
    int level_seqment_x = screen_width() / level.map.x_segements_map;
    int level_seqment_y = screen_height() / level.map.y_segements_map;

    for (int y = 0; y < level.map.y_segements_map; y++)
    {
        for (int x = 0; x < level.map.x_segements_map; x++)
        {
            if (level.dots.dot_array[x][y].dot == NORMAL_DOT)
            {
                fill_circle(COLOR_WHITE, level_seqment_x * x  + level_seqment_x*.5, level_seqment_y * y + level_seqment_y*.5, level_seqment_x/10);
            }   
            if (level.dots.dot_array[x][y].dot == SUPER_DOT)
            {
                fill_circle(COLOR_RED, level_seqment_x * x  + level_seqment_x*.5, level_seqment_y * y + level_seqment_y*.5, level_seqment_x/7);
            }      
        }
    }
}

void update_dots(game_data &game)
{
    if(game.level.dots.dot_array[game.player.x][game.player.y].visible)
    {
        if(game.level.dots.dot_array[game.player.x][game.player.y].dot == SUPER_DOT)
        {
            game.player.super_charged = true;
        }
        game.level.dots.dot_array[game.player.x][game.player.y] = no_dot();
        play_sound_effect("chomp");
        game.player.dots++;
        game.level.in_level_dots--;
    }        
}
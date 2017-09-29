#include "splashkit.h"
#include "happy_man.h"
#include <vector>

void populate_directions(map_data &map)
{     
    vector<map_directions> temp_row;   
    for (int x = 0; x < map.x_segements_map; x++)
    {
        for (int y = 0; y < map.y_segements_map; y++)
        {
            int x_minus = x - 1;
            int x_plus = x + 1;
            int y_minus = y - 1;
            int y_plus = y + 1;

            map_directions temp_point;
            
            if(x == map.x_segements_map-1) {x_plus = 0;}  
            if(x == 0) {x_minus = map.x_segements_map-1;}
            if(y == map.y_segements_map-1) {y_plus = 0;}  
            if(y == 0) {y_minus = map.y_segements_map-1;}

            temp_point.top_left = map.map_array[y_minus][x_minus];
            temp_point.top = map.map_array[y_minus][x];
            temp_point.top_right = map.map_array[y_minus][x_plus];

            temp_point.left = map.map_array[y][x_minus]; 
            temp_point.middle = map.map_array[y][x];
            temp_point.right = map.map_array[y][x_plus];
            
            temp_point.bot_left = map.map_array[y_plus][x_minus];
            temp_point.bot = map.map_array[y_plus][x];
            temp_point.bot_right = map.map_array[y_plus][x_plus];

            temp_row.push_back(temp_point);
        }
        map.directions.push_back(temp_row);
        temp_row.clear();
    }
}

void clear_level(game_data &game)
{
    game.level.map.directions.clear();
    game.level.map.map_array.clear();
    game.level.map.x_segements_map = 0;
    game.level.map.y_segements_map = 0;
    game.level.dots.dot_array.clear();
    game.ghosts.ghost_array.clear();
}

void update_level(game_data &game)
{
    if(game.level.in_level_dots == 0)
    {
    fill_rectangle(COLOR_YELLOW,0,0,screen_width(),screen_height()); 
    draw_text("NEXT LEVEL",COLOR_BLACK,"space_font",screen_width(),screen_width()/10,screen_height()/2);       
    refresh_screen();
    delay(1000);
    clear_level(game);
    game.level.level_number++;
    read_map(game.level);   
    populate_dots(game.level);
    populate_ghosts(game.ghosts);
    begin_player(game);
    begin_ghost(game);
    }
}

// Load data for level.
level_data new_level()
{
    level_data new_level;
    
    new_level.level_number = 0;
    read_map(new_level);
    return new_level;
}

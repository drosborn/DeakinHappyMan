#include "splashkit.h"
#include "happy_man.h"
#include <vector>


bitmap ghost_bitmap(ghost_type type)
{
    switch (type)
    {
    case RED_GHOST:
        return bitmap_named("red_ghost");
    case BLUE_GHOST:
        return bitmap_named("blue_ghost");
    default:
        return bitmap_named("green_ghost");
    }
}

ghost new_ghost()
{
    ghost result;

    result.visible = true;
    result.x = 0;
    result.y = 0;
    result.move_speed = 0;
    result.ghost = ghost_type(rnd(3));
    result.dead = false;
    return result;
}

void populate_ghosts(ghost_data &ghosts)
{
    for (int i = 0; i < 3; i++)
    {
        ghosts.ghost_array.push_back(new_ghost());
        ghosts.ghost_array[i].ghost = ghost_type(i);
    }
}

void begin_ghost(game_data &game)
{
    int i = 0;
    bool start_not_found = true;
    
    while (i < game.ghosts.ghost_array.size())
    {
        for (int y = game.level.map.y_segements_map/(i+5)+i; y < game.level.map.y_segements_map and start_not_found; y++)
        {
            for (int x = game.level.map.x_segements_map/(i+5)+i; x < game.level.map.x_segements_map and start_not_found; x++)
            {
                if(game.level.map.map_array[y][x] == PATH)
                {
                    game.ghosts.ghost_array[i].x = x;
                    game.ghosts.ghost_array[i].y = y;
                    game.ghosts.ghost_array[i].last_direction = DOWN;
                    start_not_found = false;
                }
            }
        }     
        i++;
        start_not_found = true;
        
    }
}

void update_ghost(ghost &ghost, const map_data &map)
{
    ghost.move_speed++;
    if(ghost.dead)
    {
        ghost.dead_time--;
        if(ghost.dead_time < 0)
        {
            ghost.dead = false;
        }
    }

    if (ghost.move_speed > 10)
    {
        int number_of_next_segments = 0;
        bool can_go_up= false;
        bool can_go_down= false;
        bool can_go_left = false; 
        bool can_go_right = false;
        int rnd_up = 0; 
        int rnd_down = 0;       
        int rnd_left = 0; 
        int rnd_right = 0; 
        int rnd_total = 0;
        ghost.move_speed = 0;

        if (map.directions[ghost.x][ghost.y].left == PATH)
        {
            rnd_left = rnd(100);
            can_go_left = true;
            write_line("can_left");
            number_of_next_segments++;
        }

        if (map.directions[ghost.x][ghost.y].right == PATH)
        {
            rnd_right = rnd(100);
            can_go_right = true;
            number_of_next_segments++;
            write_line("can_right");
        }

        if (map.directions[ghost.x][ghost.y].bot == PATH)
        {
            rnd_down = rnd(100);
            can_go_down = true;
            number_of_next_segments++;
            write_line("can_down");
        }

        if (map.directions[ghost.x][ghost.y].top == PATH)
        {
            rnd_up = rnd(100);
            can_go_up = true;
            number_of_next_segments++;
            write_line("can_up");
        }

        write_line("   ");
        if (number_of_next_segments == 1)
        {

            if (can_go_right) {ghost.x++;ghost.last_direction = RIGHT;write_line("left1");}
            else if (can_go_left) {ghost.x--;ghost.last_direction = LEFT;write_line("right1");}
            else if (can_go_up) {ghost.y++;ghost.last_direction = UP;write_line("up1");}
            else if (can_go_down) {ghost.y--;ghost.last_direction = DOWN;write_line("down1");} 
        }
        else if (number_of_next_segments == 2)
        {
            if (can_go_right && ghost.last_direction != LEFT) {ghost.x++;ghost.last_direction = RIGHT;write_line("right2");}
            else if (can_go_left && ghost.last_direction != RIGHT){ghost.x--;ghost.last_direction = LEFT;write_line("left2");}
            else if (can_go_up && ghost.last_direction != DOWN) {ghost.y--;ghost.last_direction = UP;write_line("up2");}
            else if (can_go_down && ghost.last_direction != UP) {ghost.y++; ghost.last_direction = DOWN;write_line("down2");}
        }
        else
        {
            if(rnd_left > rnd_total){rnd_total = rnd_left;}
            if(rnd_right > rnd_total){rnd_total = rnd_right;}
            if(rnd_up > rnd_total){rnd_total = rnd_up;}
            if(rnd_down > rnd_total){rnd_total = rnd_down;}
       
            if (can_go_right && rnd_right == rnd_total && ghost.last_direction != LEFT) {ghost.x++;ghost.last_direction = RIGHT;write_line("right3");}
            else if (can_go_left && rnd_left == rnd_total && ghost.last_direction != RIGHT){ghost.x--;ghost.last_direction = LEFT;write_line("left3");}
            else if (can_go_up && rnd_up == rnd_total && ghost.last_direction != DOWN) {ghost.y--;ghost.last_direction = UP;write_line("up3");}
            else if (can_go_down && rnd_down == rnd_total && ghost.last_direction != UP) {ghost.y++; ghost.last_direction = DOWN;write_line("down3");}
        }
    }
    if(ghost.x == map.x_segements_map) {ghost.x = 0;} 
    if(ghost.x == -1) {ghost.x = map.x_segements_map-1;}
    if(ghost.y == map.y_segements_map) {ghost.y = 0;}  
    if(ghost.y == -1) {ghost.y = map.y_segements_map-1;}
}

void update_ghosts(ghost_data &ghosts, const map_data &map)
{
    int i = 0;  
    while (i < ghosts.ghost_array.size())
    {
        update_ghost(ghosts.ghost_array[i], map);        
        i++;
    }
}

void draw_ghosts(const game_data &game)
{
    float level_seqment_x = screen_width() / game.level.map.x_segements_map;
    float level_seqment_y = screen_height() / game.level.map.y_segements_map;
    int i = 0;
    while (i < game.ghosts.ghost_array.size())
    {
            if(game.ghosts.ghost_array[i].dead)
            {
                fill_ellipse(COLOR_WHITE, level_seqment_x * game.ghosts.ghost_array[i].x, level_seqment_y * game.ghosts.ghost_array[i].y, level_seqment_x, level_seqment_y);            
            }
            else{
            bitmap to_draw;
            to_draw = ghost_bitmap(game.ghosts.ghost_array[i].ghost);
            float to_draw_height =  bitmap_height(to_draw);
            float to_draw_width =  bitmap_width(to_draw);
            
            draw_bitmap(to_draw, 
                        game.ghosts.ghost_array[i].x * level_seqment_x - to_draw_width/2  + level_seqment_x/2, 
                        game.ghosts.ghost_array[i].y * level_seqment_y - to_draw_height/2 + level_seqment_y/2, 
                        option_scale_bmp(
                            level_seqment_x / to_draw_height,
                            level_seqment_y / to_draw_width));
            }
    i++;
    }
}

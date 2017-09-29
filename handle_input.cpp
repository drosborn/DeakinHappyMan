#include "splashkit.h"
#include "happy_man.h"
#include <vector>


void handle_input_player(player_data &player, const map_data &map)
{

    delay(150);

    if (key_down(RIGHT_KEY) and map.directions[player.x][player.y].right == PATH)
        {
            player.next_direction = RIGHT;
            if(player.x == map.x_segements_map-1)
            {
                player.x = 0;
            }
            else 
            {
                player.x++;
            }
        }
    if (key_down(LEFT_KEY) and map.directions[player.x][player.y].left == PATH)
    {
        player.next_direction = LEFT;
        if(player.x == 0)
        {
            player.x = map.x_segements_map-1;
        }
        else 
        {
            player.x--;
        }
    }
    if (key_down(UP_KEY) and map.directions[player.x][player.y].top == PATH)
    {
        player.next_direction = UP;
        if(player.y == 0)
        {
            player.y = map.y_segements_map-1;
        }
        else 
        {
            player.y--;
        }
    }
    if (key_down(DOWN_KEY) and map.directions[player.x][player.y].bot == PATH)
    {
        player.next_direction = DOWN;
        if(player.y == map.y_segements_map-1)
        {
            player.y = 0;
        }
        else 
        {
            player.y++;
        }
    }
        
    // Test Keys
    if (key_down(D_KEY))
        player.x ++;
    if (key_down(A_KEY))
        player.x --;
    if (key_down(W_KEY))
        player.y --;
    if (key_down(S_KEY))
        player.y ++;
}

void handle_input(game_data &game)
{
    handle_input_player(game.player,game.level.map);
}

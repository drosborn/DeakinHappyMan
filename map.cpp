#include "splashkit.h"
#include "happy_man.h"
#include <vector>

// Load bitmap for player.
bitmap map_bitmap(map_type type)
{
    switch (type)
    {
    default:
        return bitmap_named("wall");
    }
}dd

void draw_map(const map_data &map)
{
    int level_seqment_x = screen_width() / map.x_segements_map;
    int level_seqment_y = screen_height() / map.y_segements_map;

    for (int y = 0; y < map.y_segements_map; y++)
    {
        for (int x = 0; x < map.x_segements_map; x++)
        {
            if (map.map_array[y][x] == WALL)
            {
                fill_rectangle(COLOR_BLACK, level_seqment_x * x, level_seqment_y * y, level_seqment_x, level_seqment_y);
                if (map.directions[x][y].left == PATH && x > 0)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x, level_seqment_y * y, level_seqment_x / 5, level_seqment_y);
                }
                if (map.directions[x][y].right == PATH)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x + 4 * level_seqment_x / 5, level_seqment_y * y, level_seqment_x / 5, level_seqment_y);
                }
                if (map.directions[x][y].top == PATH && y > 0)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x, level_seqment_y * y, level_seqment_x, level_seqment_y / 5);
                }
                if (map.directions[x][y].bot == PATH)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x, level_seqment_y * y + 4 * level_seqment_y / 5, level_seqment_x, level_seqment_y / 5);
                }

                if (map.directions[x][y].top == WALL  && map.directions[x][y].left == WALL && map.directions[x][y].top_left == PATH && y > 0 && x > 0) 
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x, level_seqment_y * y, level_seqment_x/5, level_seqment_y / 5);
                }
                if (map.directions[x][y].top == WALL  && map.directions[x][y].right == WALL && map.directions[x][y].top_right == PATH && y > 0)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x + 4 * level_seqment_x / 5, level_seqment_y * y, level_seqment_x/5, level_seqment_y / 5);
                }
                if (map.directions[x][y].bot == WALL  && map.directions[x][y].left == WALL && map.directions[x][y].bot_left == PATH && x > 0)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x, level_seqment_y * y + 4 * level_seqment_y / 5, level_seqment_x/5, level_seqment_y / 5);
                }
                if (map.directions[x][y].bot == WALL  && map.directions[x][y].right == WALL && map.directions[x][y].bot_right == PATH)
                {
                    fill_rectangle(COLOR_BLUE, level_seqment_x * x + 4 * level_seqment_x / 5, level_seqment_y * y + 4 * level_seqment_y / 5, level_seqment_x/5, level_seqment_y / 5);
                }   
            }
            if (map.map_array[y][x] == PATH)
            {
                fill_rectangle(COLOR_BLACK, level_seqment_x * x, level_seqment_y * y, level_seqment_x, level_seqment_y);
            }
            if (map.map_array[y][x] == BAY)
            {
                fill_rectangle(COLOR_GREEN, level_seqment_x * x, level_seqment_y * y, level_seqment_x, level_seqment_y);
            }
        }
    }
}
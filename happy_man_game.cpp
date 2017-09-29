#include "splashkit.h"
#include "happy_man.h"

game_data new_game()
{
    game_data game;
    game.level = new_level();
    //game.player = new_player();
    return game;
}

void draw_game(const game_data &game)
{
    draw_map(game.level.map); 
    draw_dots(game.level);
    draw_player(game);
    draw_score(game.player);
    draw_ghosts(game);
}

void update_game(game_data &game)
{
    update_level(game);
    update_dots(game);
    update_ghosts(game.ghosts,game.level.map);
    update_player(game);
    draw_game(game);
}

void begin_game(game_data &game)
{
    populate_dots(game.level);
    populate_ghosts(game.ghosts);
    begin_player(game);
    begin_ghost(game);
}
#include "splashkit.h"
#include "happy_man.h"
using namespace std;


void load_resources()
{
    load_resource_bundle("game_bundle", "happy_man.txt");
}
 
int main()
{
    int level_width = 600;
    int level_height = 600;
    game_data game = new_game();
    
    load_resources();
    
    open_window("Happy Man by David Osborn", level_width, level_height);

    begin_game(game);

    while (not quit_requested())
    {
        process_events();
        update_game(game);
        handle_input(game);
        refresh_screen();
    }
    delay(5000);

    return 0;
}
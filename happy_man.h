#include "splashkit.h"
#include <vector>

// Map types.
enum map_type
{
    WALL,
    PATH,
    BAY
};

enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Level Names.
enum level_type
{
    One,
    Two,
    Three
};

enum player_type
{
    HAPPY,
    NOT_HAPPY
};

enum dot_type
{
    NORMAL_DOT,
    NO_DOT,
    SUPER_DOT
};

enum ghost_type
{
    RED_GHOST,
    BLUE_GHOST,
    GREEN_GHOST
};

struct dot
{
    dot_type dot;
    bool visible = false;    
};

struct dot_data
{
    vector<vector<dot>> dot_array;    
};

struct ghost
{
    ghost_type ghost;
    int x;
    int y;
    direction last_direction;
    bool visible;
    int move_speed;
    bool dead;
    int dead_time;
};

struct ghost_data
{
    vector<ghost> ghost_array;    
};

struct map_directions 
{
    map_type top_left;
    map_type top;
    map_type top_right;

    map_type left;
    map_type middle;
    map_type right;
    
    map_type bot_left;
    map_type bot;
    map_type bot_right;
};

// Player structure
struct map_data
{
    int x_segements_map;
    int y_segements_map; 
    vector<vector<map_directions>> directions;
    vector<vector<map_type>> map_array;
};

struct level_data
{
    int level_number;
    map_data map;
    dot_data dots;
    int in_level_dots;
};

struct player_data
{
    int x;
    int y;
    int dots;
    direction next_direction;
    player_type type;
    bool super_charged;
    int super_time;
};

struct game_data
{
    level_data level;
    player_data player;
    vector<dot_data> dots;
    ghost_data ghosts;
};

void read_map(level_data &level);

void handle_input_player(player_data &player, const map_data &map);
void handle_input(game_data &game);

void player_hit_ghost(player_data &player, ghost_data &ghosts);

void begin_ghost(game_data &game);
void begin_player(game_data &game);
void begin_game(game_data &game);
 
void update_level(game_data &game);
void update_player(game_data &game);
void update_ghost(game_data &game);
void update_ghosts(ghost_data &ghosts, const map_data &map);
void update_dots(game_data &game);
void update_game(game_data &game);

void draw_ghosts(const game_data &game);
void draw_score(const player_data &player);
void draw_dots(const level_data &level);
void draw_map(const map_data &map);
void draw_player(const game_data &game);
void draw_game(const game_data &game);

void populate_directions(map_data &map);
void populate_ghosts(ghost_data &ghosts);
void populate_ghosts(ghost_data &ghosts);
void populate_dots(level_data &level);



map_data load_level_map(level_data &level);
ghost new_ghost();
dot new_dot();
dot no_dot();
level_data new_level();
player_data new_player();
game_data new_game();



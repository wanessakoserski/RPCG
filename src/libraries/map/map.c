#include "map.h"
#include "../npc/npc.h"
#include "../screenplay/screenplay.h"


ALLEGRO_BITMAP* grab_sprite_map(int x, int y, int w, int h, char m[])
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprite_map._sheet, x, y, w, h);
    must_init(true, sprite, m);
    return sprite;
}


void init_sprites_map(void)
{
    sprite_map._sheet = al_load_bitmap("src/images/inside.png");
    must_init(true, sprite_map._sheet, "inside map spritesheet");
    
    if(sprite_map._sheet != NULL) {
        sprite_map.voiding = grab_sprite_map(64, 128, 32, 32, "voiding");
        sprite_map.corner_top_left = grab_sprite_map(64, 96, 32, 32, "corner top left");
        sprite_map.corner_top_right = grab_sprite_map(32, 96, 32, 32, "corner top right");
        sprite_map.corner_bottom_left = grab_sprite_map(256, 64, 32, 32, "corner bottom left");
        sprite_map.corner_bottom_right = grab_sprite_map(0, 96, 32, 32, "corner bottom right");
        sprite_map.corner_left = grab_sprite_map(256, 96, 32, 32, "corner left");
        sprite_map.corner_right = grab_sprite_map(32, 128, 32, 32, "corner right");
        sprite_map.corner_top = grab_sprite_map(224, 96, 32, 32, "corner top");
        sprite_map.corner_bottom = grab_sprite_map(0, 128, 32, 32, "corner bottom");
        sprite_map.checkered_floor = grab_sprite_map(0, 0, 32, 32, "checkered floot");
        sprite_map.wall = grab_sprite_map(160, 32, 32, 32, "wall");
        sprite_map.red_wall = grab_sprite_map(128, 32, 32, 32, "red wall");
        sprite_map.border_top_left = grab_sprite_map(96, 96, 32, 32, "border top left");
        sprite_map.border_top_right = grab_sprite_map(192, 96, 32, 32, "border top right");
        sprite_map.border_bottom_left = grab_sprite_map(128, 96, 32, 32, "border bottom left");
        sprite_map.border_bottom_right = grab_sprite_map(160, 96, 32, 32, "border bottom right");
        sprite_map.door = grab_sprite_map(224, 64, 32, 32, "door");
        sprite_map.flag = grab_sprite_map(160, 64, 32, 32, "flag");
        sprite_map.red_flag = grab_sprite_map(192, 64, 32, 32, "red flag");
        sprite_map.rug_top_left = grab_sprite_map(96, 32, 32, 32, "rug top left");
        sprite_map.rug_top_right = grab_sprite_map(32, 32, 32, 32, "rug top right");
        sprite_map.rug_bottom_left= grab_sprite_map(64, 32, 32, 32, "rug bottom left");
        sprite_map.rug_bottom_right = grab_sprite_map(0, 32, 32, 32, "rug bottom right");
        sprite_map.rug_top_center= grab_sprite_map(256, 0, 32, 32, "rug top center");
        sprite_map.rug_bottom_center = grab_sprite_map(224, 0, 32, 32, "rug bottom center");
        sprite_map.windows = grab_sprite_map(192, 32, 32, 32, "windows");
        sprite_map.red_windows = grab_sprite_map(224, 32, 32, 32, "red windows");

        sprite_map.table_bottom_right = grab_sprite_map(32, 0, 32, 32, "table bottom right");
        sprite_map.table_bottom_left = grab_sprite_map(64, 0, 32, 32, "table bottom left");
        sprite_map.table_bottom = grab_sprite_map(96, 0, 32, 32, "table bottom");
        sprite_map.table_top_right = grab_sprite_map(128, 0, 32, 32, "table top right");
        sprite_map.table_top_left = grab_sprite_map(160, 0, 32, 32, "table top left");
        sprite_map.table_top = grab_sprite_map(192, 0, 32, 32, "table top");
        sprite_map.torch_center = grab_sprite_map(256, 32, 32, 32, "torch center");
        sprite_map.torch_left = grab_sprite_map(0, 64, 32, 32, "torch left");
        sprite_map.blue_torch_center = grab_sprite_map(96, 64, 32, 32, "blue torch center");
        sprite_map.blue_torch_left = grab_sprite_map(128, 64, 32, 32, "blue torch left");

        sprite_map.red_wall_torch_center = grab_sprite_map(32, 64, 32, 32, "red wall torch center");
        sprite_map.red_wall_torch_left = grab_sprite_map(64, 64, 32, 32, "rd wall torch left");
        sprite_map.throne = grab_sprite_map(224, 128, 32, 32, "throne");
        sprite_map.red_floor = grab_sprite_map(96, 128, 32, 32, "red flott");
        sprite_map.seat = grab_sprite_map(128, 128, 32, 32, "seat");

        sprite_map.book_top = grab_sprite_map(0, 160, 32, 32, "book top");
        sprite_map.book_bottom = grab_sprite_map(32, 160, 32, 32, "book bottom");
        sprite_map.bible = grab_sprite_map(256, 160, 32, 32, "bible");
        sprite_map.cup_wine = grab_sprite_map(192, 160, 32, 32, "cup wine");
        sprite_map.cup_water = grab_sprite_map(128, 160, 32, 32, "cup water");
        sprite_map.book = grab_sprite_map(160, 160, 32, 32, "book");

        sprite_map.arrow = grab_sprite_map(64, 160, 32, 32, "arrow");
        sprite_map.poison = grab_sprite_map(96, 160, 32, 32, "poison");
        sprite_map.cross = grab_sprite_map(224, 160, 32, 32, "cross");
        sprite_map.all_rug = grab_sprite_map(160, 192, 32, 32, "all rug");
        sprite_map.border_rug_bottom = grab_sprite_map(224, 192, 32, 32, "border rug bottom");
        sprite_map.rug_curve = grab_sprite_map(192, 192, 32, 32, "rug curve");
    }

    return;
}


void init_map(void) { 
    tile_map = fopen("src/tiles/maping.txt", "r");
    if(tile_map == NULL) {
        fprintf(stderr, "Arquivo de tiles não foi aberto\n");
        exit(1);
    }
    
    int cod = 10;
    
    for(int i = 0; i < map_lines; i++) {
        for(int j = 0; j < map_columns; j++) {
            fscanf(tile_map, "%d", &cod);
            map[i][j] = cod;
            // fprintf(stderr, "%d ", cod);
        }
            // fprintf(stderr, "\n");
    }

    fclose(tile_map);

    return;
}


bool collision(int player_x, int player_y, int x, int y, int width, int height, int play_width, int play_height) {
    if(player_x > x + width) return false;
    if(player_x + play_width < x) return false;
    if(player_y > y + height) return false;
    if(player_y + play_height < y) return false;

    return true;
}


void collision_reaction(bool collision, int *player_position_x, int *player_position_y, int x, int y, int width, int height, int play_width, int play_height, int speed) {
    if(collision) {
        if(key[ALLEGRO_KEY_LEFT] || key[ALLEGRO_KEY_A] || key[ALLEGRO_KEY_RIGHT] || key[ALLEGRO_KEY_D]) {    
            if(*player_position_x + speed < x + width) {  
                *player_position_x = x - play_width - 1;
            } else if(*player_position_x + speed + play_width > x) {
                *player_position_x = x + width + 1;
            }  
        } else if(key[ALLEGRO_KEY_UP] || key[ALLEGRO_KEY_W] || key[ALLEGRO_KEY_DOWN] || key[ALLEGRO_KEY_S]) {
            if(*player_position_y + speed < y + height) {
                *player_position_y = y - play_height - 1;
            } else if(*player_position_y + speed + play_height > y) {
                *player_position_y = y + height + 1;
            } 
        }
    } 
    
    return;
}


void detect_collision(int *player_position_x, int *player_position_y) 
{
    bool col;
    for(int i = 0; i < map_lines; i++)
    {   
        for(int j = 0; j < map_columns; j++) 
        {
            if(map[i][j] == VOIDING
            || map[i][j] == CORNER_TOP_LEFT 
            || map[i][j] == CORNER_TOP_RIGHT 
            || map[i][j] == CORNER_BOTTOM_RIGHT 
            || map[i][j] == CORNER_BOTTOM_LEFT 
            || map[i][j] == CORNER_TOP 
            || map[i][j] == CORNER_BOTTOM 
            || map[i][j] == WALL
            || map[i][j] == RED_WALL
            || map[i][j] == CORNER_LEFT 
            || map[i][j] == CORNER_RIGHT
            || map[i][j] == BORDER_TOP_LEFT 
            || map[i][j] == BORDER_TOP_RIGHT 
            || map[i][j] == BORDER_BOTTOM_RIGHT 
            || map[i][j] == BORDER_BOTTOM_LEFT
            || map[i][j] == DOOR
            || map[i][j] == FLAG 
            || map[i][j] == WINDOWS 
            || map[i][j] == RED_WINDOWS
            || map[i][j] == BLUE_TORCH_CENTER 
            || map[i][j] == TORCH_CENTER
            || map[i][j] == RED_FLAG

            || map[i][j] == RED_WALL_TORCH_CENTER 
            || map[i][j] == BLUE_TORCH_CENTER
            || map[i][j] == BOOK_TOP
            || map[i][j] == BOOK_BOTTOM
            || map[i][j] == BOOK 
            || map[i][j] == ARROW 
            || map[i][j] == CUP_WATER
            || map[i][j] == CUP_WINE 
            || map[i][j] == POISON
            || map[i][j] == CROSS

            || map[i][j] == BIBLE
            || map[i][j] == TABLE_BOTTOM
            || map[i][j] == TABLE_BOTTOM_LEFT
            || map[i][j] == TABLE_BOTTOM_RIGHT 
            || map[i][j] == TABLE_TOP_RIGHT
            || map[i][j] == TABLE_TOP 
            || map[i][j] == TABLE_TOP_LEFT
            || map[i][j] == SEAT) {
                col = collision(*player_position_x, *player_position_y, j * tile_size, i * tile_size, tile_size, tile_size, PROTAGONIST_W, PROTAGONIST_H);
                collision_reaction(col, player_position_x, player_position_y, j * tile_size, i * tile_size, tile_size, tile_size, PROTAGONIST_W, PROTAGONIST_H, PROTAGONIST_SPEED);
            } else if(j == knight.position_x && i == knight.position_y) {
                col = collision(*player_position_x, *player_position_y, j * tile_size, i * tile_size, knight.width, knight.height, PROTAGONIST_W, PROTAGONIST_H);
                collision_reaction(col, player_position_x, player_position_y, j * tile_size, i * tile_size, knight.width, knight.height, PROTAGONIST_W, PROTAGONIST_H, PROTAGONIST_SPEED);
            } else if(j == bishop.position_x && i == bishop.position_y) {
                col = collision(*player_position_x, *player_position_y, j * tile_size, i * tile_size, bishop.width, bishop.height, PROTAGONIST_W, PROTAGONIST_H);
                collision_reaction(col, player_position_x, player_position_y, j * tile_size, i * tile_size, bishop.width, bishop.height, PROTAGONIST_W, PROTAGONIST_H, PROTAGONIST_SPEED);
            } else if(j == tower.position_x && i == tower.position_y) {
                col = collision(*player_position_x, *player_position_y, j * tile_size, i * tile_size, tower.width, tower.height, PROTAGONIST_W, PROTAGONIST_H);
                collision_reaction(col, player_position_x, player_position_y, j * tile_size, i * tile_size, tower.width, tower.height, PROTAGONIST_W, PROTAGONIST_H, PROTAGONIST_SPEED);
            } else if(j == king.position_x && i == king.position_y) {
                col = collision(*player_position_x, *player_position_y, j * tile_size, i * tile_size, king.width, king.height, PROTAGONIST_W, PROTAGONIST_H);
                collision_reaction(col, player_position_x, player_position_y, j * tile_size, i * tile_size, king.width, king.height, PROTAGONIST_W, PROTAGONIST_H, PROTAGONIST_SPEED);
            }
            
           
            //if(col)
            //   printf("Void - x.%d, y.%d Player - %d, %d Colission - %s\n", j*tile_size, i*tile_size, *player_position_x, *player_position_y, col ? "true" : "false");
                    
        }    
    }

    return;
}


void it_table(int min, int max, bool *table) {
    if(player.map > max && *table)
        sc_map.map_it = !sc_map.map_it;
    else
        sc_map.map_it = true;

    if(player.map < min || player.map > max) {
        if(*table)
            player.map = max;
        else
            player.map = min;
    }
                        
    *table = true;

    return;
}


void detect_iteration_map(int *player_position_x, int *player_position_y) {
    bool it;
    tic_tac = time_count();

    for(int i = 0; i < map_lines; i++)
    {   
        for(int j = 0; j < map_columns; j++) 
        {
            if(map[i][j] == DOOR) {
                it = detect_iteration(*player_position_x, *player_position_y, j * 32, i * 32, 32, 32);
                if(it && key[ALLEGRO_KEY_E] && count_timer > 2) {
                    sc_map.map_it = !sc_map.map_it;
                    player.map = 0;
                    map_script(&player.map);
                    restart_time();
                } 
            } else if(map[i][j] == BOOK_TOP
                   || map[i][j] == BOOK_BOTTOM
                   || map[i][j] == BOOK 
                   || map[i][j] == ARROW 
                   || map[i][j] == CUP_WATER
                   || map[i][j] == CUP_WINE 
                   || map[i][j] == POISON
                   || map[i][j] == CROSS
   
                   || map[i][j] == BIBLE
                   || map[i][j] == TABLE_BOTTOM
                   || map[i][j] == TABLE_BOTTOM_LEFT
                   || map[i][j] == TABLE_BOTTOM_RIGHT 
                   || map[i][j] == TABLE_TOP_RIGHT
                   || map[i][j] == TABLE_TOP 
                   || map[i][j] == TABLE_TOP_LEFT
                   || map[i][j] == SEAT) {
                it = detect_iteration(*player_position_x, *player_position_y, j * 32, i * 32, 32, 32);
                if(it && key[ALLEGRO_KEY_E] && count_timer > 2) {
                    if(j < map_columns/4) {
                        it_table(1, 2, &table_horse);
                        map_script(&player.map);
                        restart_time();
                    } else if(j < 2 * map_columns/4) {
                        it_table(3, 4, &table_bishop);
                        map_script(&player.map);
                        restart_time();
                    } else if(j < 3 * map_columns/4) {
                        it_table(5, 6, &table_tower);
                        map_script(&player.map);
                        restart_time();
                    }
                }
            } else if(map[i][j] == THRONE) {
                it = detect_iteration(*player_position_x, *player_position_y, j * 32, i * 32, 32, 32);
                if(it && key[ALLEGRO_KEY_E] && count_timer > 2) {
                    sc_map.map_it = !sc_map.map_it;
                    player.map = 7;
                    map_script(&player.map);
                    restart_time();
                }
            }
        }
    }   

    return;
}


void map_update(int *player_position_x, int *player_position_y)
{
    detect_collision(player_position_x, player_position_y);
    detect_iteration_map(player_position_x, player_position_y);

    xOff = -(*player_position_x - (BUFFER_W / 2) + (PROTAGONIST_W/2));
    yOff = -(*player_position_y - (BUFFER_H / 2) + (PROTAGONIST_H/2));  

    return;
}


void map_draw(void)
{
    int count = 0;
    bool col;
    for(int i = 0; i < map_lines; i++)
    {   
        for(int j = 0; j < map_columns; j++) 
        {
            switch (map[i][j])
            {
                case VOIDING:
                    al_draw_bitmap(sprite_map.voiding, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case CORNER_TOP_LEFT:
                    al_draw_bitmap(sprite_map.corner_top_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case CORNER_TOP_RIGHT:
                    al_draw_bitmap(sprite_map.corner_top_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case CORNER_BOTTOM_RIGHT:
                    al_draw_bitmap(sprite_map.corner_bottom_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case CORNER_BOTTOM_LEFT:
                    al_draw_bitmap(sprite_map.corner_bottom_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                    
                case CORNER_LEFT:
                    al_draw_bitmap(sprite_map.corner_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case CORNER_RIGHT:
                    al_draw_bitmap(sprite_map.corner_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;          

                case CORNER_TOP:
                    al_draw_bitmap(sprite_map.corner_top, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case CORNER_BOTTOM:
                    al_draw_bitmap(sprite_map.corner_bottom, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case FLOOR:
                    al_draw_bitmap(sprite_map.checkered_floor, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);          
                    break;

                case WALL:
                    al_draw_bitmap(sprite_map.wall, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case RED_WALL:
                    al_draw_bitmap(sprite_map.red_wall, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case BORDER_TOP_LEFT:
                    al_draw_bitmap(sprite_map.border_top_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case BORDER_TOP_RIGHT:
                    al_draw_bitmap(sprite_map.border_top_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case BORDER_BOTTOM_RIGHT:
                    al_draw_bitmap(sprite_map.border_bottom_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case BORDER_BOTTOM_LEFT:
                    al_draw_bitmap(sprite_map.border_bottom_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case DOOR:
                    al_draw_bitmap(sprite_map.door, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case FLAG:
                    al_draw_bitmap(sprite_map.flag, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);          
                    break;
                case RED_FLAG:
                    al_draw_bitmap(sprite_map.red_flag, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);          
                    break;

                case RUG_TOP_LEFT:
                   al_draw_bitmap(sprite_map.rug_top_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case RUG_TOP_RIGHT:
                   al_draw_bitmap(sprite_map.rug_top_right , xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case RUG_BOTTOM_LEFT:
                    al_draw_bitmap(sprite_map.rug_bottom_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;
                
                case RUG_BOTTOM_RIGHT:
                    al_draw_bitmap(sprite_map.rug_bottom_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case RUG_TOP_CENTER:
                    al_draw_bitmap(sprite_map.rug_top_center, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case RUG_BOTTOM_CENTER:
                    al_draw_bitmap(sprite_map.rug_bottom_center, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case WINDOWS:
                    al_draw_bitmap(sprite_map.windows, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case RED_WINDOWS:
                    al_draw_bitmap(sprite_map.red_windows, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case TABLE_BOTTOM_RIGHT:
                    al_draw_bitmap(sprite_map.table_bottom_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case TABLE_BOTTOM_LEFT:
                    al_draw_bitmap(sprite_map.table_bottom_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);          
                    break;

                case TABLE_BOTTOM:
                    al_draw_bitmap(sprite_map.table_bottom, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case TABLE_TOP_RIGHT:
                    al_draw_bitmap(sprite_map.table_top_right, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case TABLE_TOP_LEFT:
                    al_draw_bitmap(sprite_map.table_top_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case TABLE_TOP:
                    al_draw_bitmap(sprite_map.table_top, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;
                
                case TORCH_CENTER:
                    al_draw_bitmap(sprite_map.torch_center, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case TORCH_LEFT:
                    al_draw_bitmap(sprite_map.torch_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case BLUE_TORCH_CENTER:
                    al_draw_bitmap(sprite_map.blue_torch_center, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case BLUE_TORCH_LEFT:
                    al_draw_bitmap(sprite_map.blue_torch_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case RED_WALL_TORCH_CENTER:
                    al_draw_bitmap(sprite_map.red_wall_torch_center, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case RED_WALL_TORCH_LEFT:
                    al_draw_bitmap(sprite_map.red_wall_torch_left, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case THRONE:
                    al_draw_bitmap(sprite_map.throne, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case RED_FLOOR:
                    al_draw_bitmap(sprite_map.red_floor, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case SEAT:
                    al_draw_bitmap(sprite_map.seat, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case BOOK_TOP:
                    al_draw_bitmap(sprite_map.book_top, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;
                
                case BOOK_BOTTOM:
                    al_draw_bitmap(sprite_map.book_bottom, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;
                
                case BIBLE:
                    al_draw_bitmap(sprite_map.bible, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case CUP_WINE:
                    al_draw_bitmap(sprite_map.cup_wine, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case CUP_WATER:
                    al_draw_bitmap(sprite_map.cup_water, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case BOOK:
                    al_draw_bitmap(sprite_map.book, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case ARROW:
                    al_draw_bitmap(sprite_map.arrow, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case POISON:
                    al_draw_bitmap(sprite_map.poison, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case CROSS:
                    al_draw_bitmap(sprite_map.cross, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);
                    break;

                case ALL_RUG:
                    al_draw_bitmap(sprite_map.all_rug, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case BORDER_RUG_BOTTOM:
                    al_draw_bitmap(sprite_map.border_rug_bottom, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                case RUG_CURVE:
                    al_draw_bitmap(sprite_map.rug_curve, xOff + tile_size * (count % map_columns), yOff + tile_size * (count / map_columns), 0);           
                    break;

                default:
                    printf("ALERT! Número desconhecido no maping.txt\n");
                    break;
            }                

            count++;
        }    
    }
    return;
}


void destroy_sprites_map(void)
{   
    al_destroy_bitmap(sprite_map._sheet);
    al_destroy_bitmap(sprite_map.checkered_floor);
    al_destroy_bitmap(sprite_map.voiding);
    al_destroy_bitmap(sprite_map.corner_top_left);
    al_destroy_bitmap(sprite_map.corner_top_right);
    al_destroy_bitmap(sprite_map.corner_bottom_left);
    al_destroy_bitmap(sprite_map.corner_bottom_right);
    al_destroy_bitmap(sprite_map.corner_left);
    al_destroy_bitmap(sprite_map.corner_right);
    al_destroy_bitmap(sprite_map.corner_top);
    al_destroy_bitmap(sprite_map.corner_bottom);
    al_destroy_bitmap(sprite_map.floor);
    al_destroy_bitmap(sprite_map.wall);
    al_destroy_bitmap(sprite_map.red_wall);
    al_destroy_bitmap(sprite_map.border_top_left);
    al_destroy_bitmap(sprite_map.border_top_right);
    al_destroy_bitmap(sprite_map.border_bottom_left);
    al_destroy_bitmap(sprite_map.border_bottom_right);
    al_destroy_bitmap(sprite_map.door);
    al_destroy_bitmap(sprite_map.flag);
    al_destroy_bitmap(sprite_map.red_flag);
    al_destroy_bitmap(sprite_map.rug_top_left);
    al_destroy_bitmap(sprite_map.rug_top_right);
    al_destroy_bitmap(sprite_map.rug_bottom_left);
    al_destroy_bitmap(sprite_map.rug_bottom_right);
    al_destroy_bitmap(sprite_map.rug_top_center);
    al_destroy_bitmap(sprite_map.rug_bottom_center);
    al_destroy_bitmap(sprite_map.windows);
    al_destroy_bitmap(sprite_map.red_windows);

    al_destroy_bitmap(sprite_map.table_bottom_right);
    al_destroy_bitmap(sprite_map.table_bottom_left);
    al_destroy_bitmap(sprite_map.table_bottom);
    al_destroy_bitmap(sprite_map.table_top_right);
    al_destroy_bitmap(sprite_map.table_top_left);
    al_destroy_bitmap(sprite_map.table_top);
    al_destroy_bitmap(sprite_map.torch_center);
    al_destroy_bitmap(sprite_map.torch_left);
    al_destroy_bitmap(sprite_map.blue_torch_center);
    al_destroy_bitmap(sprite_map.blue_torch_left);
    al_destroy_bitmap(sprite_map.red_wall_torch_center);
    al_destroy_bitmap(sprite_map.red_wall_torch_left);
    al_destroy_bitmap(sprite_map.throne);
    al_destroy_bitmap(sprite_map.red_floor);
    al_destroy_bitmap(sprite_map.seat);
    al_destroy_bitmap(sprite_map.book_top);
    al_destroy_bitmap(sprite_map.book_bottom);
    al_destroy_bitmap(sprite_map.bible);
    al_destroy_bitmap(sprite_map.cup_wine);
    al_destroy_bitmap(sprite_map.cup_water);
    al_destroy_bitmap(sprite_map.book);
    al_destroy_bitmap(sprite_map.arrow);
    al_destroy_bitmap(sprite_map.poison);
    al_destroy_bitmap(sprite_map.cross);
    al_destroy_bitmap(sprite_map.all_rug);
    al_destroy_bitmap(sprite_map.border_rug_bottom);
    al_destroy_bitmap(sprite_map.rug_curve);

    return;
}
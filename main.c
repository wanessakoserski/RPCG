#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h> // writing
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h> // draw 
#include <allegro5/allegro_audio.h> // sounds
#include <allegro5/allegro_acodec.h> // sounds
#include <allegro5/allegro_image.h>

bool collision(int player_x, int player_y, int x, int y, int width, int height, int play_width, int play_height);
void collision_reaction(bool collision, int *player_position_x, int *player_position_y, int x, int y, int width, int height, int play_width, int play_height, int speed);

#include "src/structure.h"
#include "src/player.h"
#include "src/map.h"
#include "src/npc.h"
#include "src/parallel_game.h"
#include "src/screenplay.h"
#include "src/stand_screen.h"


enum play_what
    {
        MENU = 0,
        PLAYING = 1,
        MAIN_GAME = 2,
        BISHOP_GAME = 3,
        KING_GAME = 4,
        KNIGHT_GAME = 5,
        TOWER_GAME = 6,
        GAME_OVER = 7,
        END_GAME = 8
    };

void start(int *play) {
    *play = MENU;

    init_structure_all();
    init_map();
    init_sprites_map();
    init_script_file();
    init_player(); 
    init_parallel_bool();
    init_npc(tile_size);
    al_set_window_title(display, "[ RPCG ]  Role Playing Chess Game");

    return;
}

int main()
{
    int play;

    start(&play);


    while(PLAYING) 
    {
        
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                switch (play)
                {
                    case MENU:
                        if(key[ALLEGRO_KEY_ENTER])
                            play = 2;
                        break;

                    case MAIN_GAME:
                        if((!sc_kni.map_it || sc_bis.map_it || sc_tow.map_it || sc_kin.map_it)
                        || (!sc_kni.map_it || sc_bis.map_it || sc_tow.map_it || sc_kin.map_it)
                        || (!sc_kni.map_it || sc_bis.map_it || sc_tow.map_it || sc_kin.map_it)
                        || (!sc_kni.map_it || sc_bis.map_it || sc_tow.map_it || sc_kin.map_it))
                            player_update();       
                        map_update(&player.position_x, &player.position_y);
                        npc_update(player.position_x, player.position_y, &play);
                        break;
                    
                    case KNIGHT_GAME:
                        knight_update(&play, &player.knight);              
                        break;

                    case BISHOP_GAME:
                        parallel_player_update();
                        enemy_update(parallel_player.x, parallel_player.y);
                        add_shot(3);
                        shot_update(3);
                        bishop_update(&play);  
                        break; 

                    case TOWER_GAME:
                        parallel_player_update(); 
                        enemy_update(parallel_player.x, parallel_player.y);
                        add_shot(2);
                        shot_update(2);
                        tower_update(&play);  
                        break;

                    case KING_GAME:
                        parallel_player_update();
                        enemy_king_update(parallel_player.x, parallel_player.y);
                        add_shot(1);
                        if(key[ALLEGRO_KEY_X] && count_timer%2 == 0)
                            add_shot_player();
                        shot_update(1);
                        shot_update_player();
                        king_update(&play);  
                        break;

                    case GAME_OVER:
                        break;  

                    case END_GAME:
                        if(key[ALLEGRO_KEY_L])
                            start(&play);
                        break;                    
                }
                if(key[ALLEGRO_KEY_M])
                    play = MAIN_GAME;
                
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;
                redraw = true;
      
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        keyboard_update(&event);

        if(redraw && al_is_event_queue_empty(queue))
        {
            switch (play)
            {
                case MENU:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    menu_draw();
                    // good_ending();
                    // bad_ending();

                    display_post_draw();
                    break;

                case MAIN_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    map_draw();
                    npc_draw(xOff, yOff);
                    if(sc_kni.map_it)
                        script_draw(sc_kni);
                    player_draw(parallel_player.tower_done);
                   
                    display_post_draw();
                    break;
                
                case KNIGHT_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    script_draw(sc_kni);

                    display_post_draw(); 
                    break;

                case BISHOP_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    parallel_player_draw();
                    enemy_draw();
                    shot_draw();
                    time_draw(tic_tac);

                    display_post_draw(); 
                    break; 

                case TOWER_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    parallel_player_draw();
                    enemy_draw();
                    shot_draw();
                    time_draw(tic_tac);

                    display_post_draw(); 
                    break;

                case KING_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(0,0,0));

                    parallel_player_draw();
                    enemy_draw();
                    shot_draw(); 
                    shot_draw_player();
                    if(tic_tac < 6)
                        time_draw(tic_tac);

                    display_post_draw(); 
                    break;   

                case GAME_OVER:
                    display_pre_draw();

                    game_over(&parallel_player.lost, &play);

                    display_post_draw(); 
                    break;

                case END_GAME:
                    display_pre_draw();
                    al_clear_to_color(al_map_rgb(32,21,41));

                    if(parallel_player.king_dead)
                        good_ending();
                    else
                        bad_ending();

                    display_post_draw(); 
                    break; 
            }
            
            redraw = false;
        }
        
    }


    destroy_structure_all();
    destroy_player();
    destroy_npc();
    destroy_sprites_map();
    
    
    return 0;
}
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MAXQTD_obj 50
const int SCREEN_V = 600;
const int SCREEN_H = 800;
//const int MAXQTD_obj = 50;
#define MAXLEN_label 20

ALLEGRO_BITMAP *quadrado[50];
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *fonte = NULL;
int _countObj=-1;
char _objLabel[MAXQTD_obj][MAXLEN_label];
float _objHeight[MAXQTD_obj];
float _objWidth[MAXQTD_obj];
float posx[MAXQTD_obj];
float posy[MAXQTD_obj];
float x = 0;
float y = 0;

enum listObj{btnjogar};
enum listAlign{CENTER=1};

int createObject(int cdobj,char texto[MAXLEN_label],float largura,float altura, float x, float y, int customalign);
int getObject(int cdobj,int posx, int posy);


int main(){

//     int y=SCREEN_V*2/3;
//     int x=SCREEN_H/2 - LARGURA/2;
    int key_up=0,key_down=0,key_left=0,key_right=0;
    int FPS = 10; //modificável para efeitos

    int i=0,j=0; while(i<MAXQTD_obj){ quadrado[i]=NULL; while(j<20){_objLabel[i][j]=0; j++; } i++; }

    if(!al_init()) { printf("failed to initialize allegro!\n"); return -1; }
    timer = al_create_timer(1.0 / FPS);if(!timer) { printf("failed to create timer!\n"); return -1; }
    display = al_create_display(SCREEN_H, SCREEN_V);if(!display) { printf("failed to create display!\n"); return -1; }
    event_queue = al_create_event_queue();if(!event_queue) { printf("failed to create event_queue!\n"); return -1; }

    createObject(btnjogar,"Jogar",100, 40, 0, 0,CENTER);

//     al_set_target_bitmap(al_get_backbuffer(display));
//     al_clear_to_color(al_map_rgb(100,100,100));


    al_init_font_addon();
    if(!al_init_ttf_addon()){fprintf(stderr,"Falha ao inicializar add-on allegro_ttf.\n");return -1;}
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_start_timer(timer);
    
    fonte = al_load_font("arial.TTF", 48, 0);

    //al_clear_to_color(al_map_rgb(255, 255, 255));
    if (!fonte) { fprintf(stderr, "Falha ao carregar fonte.\n"); return -1; }
    ALLEGRO_BITMAP *image = al_load_bitmap("windows.jpg");
    //al_rest(10.0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            switch(ev.mouse.button) {
                case 1:
                    if(ev.mouse.x > posx[btnjogar] && ev.mouse.y > posy[btnjogar] && ev.mouse.x < (posx[btnjogar]+_objWidth[btnjogar]) && ev.mouse.y < (posy[btnjogar]+_objHeight[btnjogar])){
                        printf("Clique no quadrado\n");

                    }
                    //printf("EVENTO MOUSE DOWN - DIREITO(%d)\n",ev.mouse.x);
            }
        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key_up++;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key_down++;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key_left++;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key_right++;
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key_up=0;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key_down=0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key_left=0;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key_right=0;
                    break;
            }
        }

        if(key_up){key_up++;posy[btnjogar]--;}
        if(key_down){key_down++;posy[btnjogar]++;}
        if(key_left){key_left++;posx[btnjogar]--;}
        if(key_right){key_right++;posx[btnjogar]++;}

        if(ev.type == ALLEGRO_EVENT_TIMER) {
            if(posx[btnjogar] < 0) x = 0;
            if(posx[btnjogar] > SCREEN_H - _objWidth[btnjogar]) x = SCREEN_H - _objWidth[btnjogar];
            if(posy[btnjogar] < 0) y = 0;
            if(posy[btnjogar] > SCREEN_V - _objHeight[btnjogar]) y = SCREEN_V - _objHeight[btnjogar];
            al_clear_to_color(al_map_rgb(255,255,255));
            al_draw_bitmap(image, 0, 0, 0);
//            al_draw_bitmap(quadrado, x, y, 0);
            getObject(btnjogar,x,y);
            //al_draw_text(fonte, al_map_rgb(255, 0, 0), x, y, ALLEGRO_ALIGN_LEFT, "Esquerda");
            al_flip_display();
        }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
    }
    
    //al_destroy_bitmap(quadrado);
    //al_destroy_timer(timer);
    al_destroy_display(display);
    //al_destroy_event_queue(event_queue);

    
    //system("PAUSE");
    printf("Execution Finished\n");

}

int createObject(int cdobj,char texto[MAXLEN_label],float largura,float altura, float x, float y, int customalign){
    quadrado[cdobj] = al_create_bitmap(largura, altura);if(!quadrado[0]) { printf("failed to create bitmap!\n"); return -1; }
    _objWidth[cdobj]=largura;
    _objHeight[cdobj]=altura;
    switch(customalign){
        case CENTER:
            posx[cdobj]=SCREEN_V*2/3+y;
            posy[cdobj]=SCREEN_H/2 - largura/2;
            break;
        default:
        posx[cdobj]=x;
        posy[cdobj]=y;
    }
    al_set_target_bitmap(quadrado[cdobj]);
    int a=0;
    while(a<MAXLEN_label){
        if(texto[a]==0)break;
        _objLabel[cdobj][a]=texto[a];
        a++;
    }
    al_clear_to_color(al_map_rgb(0, 0.5, 0.5));
    return cdobj;
}

int getObject(int cdobj,int posx, int posy){
    al_draw_tinted_bitmap(quadrado[cdobj], al_map_rgba_f(1.0, 1.0, 1.0, 0.4), posx, posy, 0);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), posx, posy, ALLEGRO_ALIGN_LEFT, _objLabel[cdobj]);
//    al_draw_bitmap(quadrado[cdobj], posx, posy, 0);
    return 0;
}
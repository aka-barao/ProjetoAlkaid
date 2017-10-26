#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "globais.c"
#include "funcoes.h"
#include "objetos.h"
#include "movimentacao.h"


ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

float _posx[MAXQTD_obj];
float _posy[MAXQTD_obj];

void limparTela(){
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(255,255,255));
}

int inicializarAllegro(int fps){

    if(!al_init()) { printf("failed to initialize allegro!\n"); return -1; }
    timer = al_create_timer(1.0 / fps);if(!timer) { printf("failed to create timer!\n"); return -1; }
    display = al_create_display(SCREEN_H, SCREEN_V);if(!display) { printf("failed to create display!\n"); return -1; }
    event_queue = al_create_event_queue();if(!event_queue) { printf("failed to create event_queue!\n"); return -1; }

    al_init_font_addon();
    if(!al_init_ttf_addon()){fprintf(stderr,"Falha ao inicializar add-on allegro_ttf.\n");return -1;}
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_start_timer(timer);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    return 0;
}

void destruirElementos(){
//al_destroy_bitmap(quadrado);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
int main(){
    FILE *filedebug = fopen("debug.txt","w");
    filedebug=fopen("debug.txt","a");

    int countKeyUp=0,countKeyDown=0,countKeyLeft=0,countKeyRight=0;
    int _telaatual=0;
    int seconds=0;
    int frames=0;


//      int FPS;
//      printf("Frames per Second:");
//      scanf("%d",&FPS);

    struct OBJETO obj[MAXQTD_obj];
    inicializarObjeto(obj);
    struct OBJETO homem[20];
    inicializarObjeto(homem);
    struct LOOP loop[MAXQTD_obj];
    inicializarLoop(loop);

    inicializarAllegro(FPS);
    carregarFontes();

    //sempre adicionar elemento antes na enumObjetos
    criarObjeto(obj,windows,NULL,"windows.jpg",0,0,0,0,0);
    criarObjeto(obj,logo,NULL,"logo.jpg",0,0,0,-100,CENTER);
    criarObjeto(obj,btnjogar," Play",NULL,190, 60, 0, 0,CENTER);
    criarObjeto(obj,btnOpcoes," Options",NULL,190, 60, 0, 60,CENTER);
    criarObjeto(obj,btnCreditos," Credits",NULL,190, 60, 0, 120,CENTER);
    criarObjeto(obj,personagem,"W",NULL,50,50,100,100,0);
    criarObjeto(obj,help,"HEEELP!",NULL,300,60,500,150,TOPRIGHT);
    criarObjeto(obj,mesa,"",NULL,200,200,0,0,CENTER);
    criarObjeto(obj,frontup,"",NULL,SCREEN_H,0,0,0,0);
    criarObjeto(obj,frontright,"",NULL,0,SCREEN_V,SCREEN_H,0,0);
    criarObjeto(obj,frontdown,"",NULL,SCREEN_H,0,0,SCREEN_V,0);
    criarObjeto(obj,frontleft,"",NULL,0,SCREEN_V,0,0,0);
    criarObjeto(obj,btnVoltar," Voltar",NULL,190,60,0,0,TOPLEFT);

    criarSprite(homem,spriteshomem,"homem",6,0,0,BOTTOMLEFT);

    int direcao=0;

     while(1){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
         //capturar eventos do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            switch(ev.mouse.button) {
                case 1://clique botao esquerdo
                    if(itsInside2(obj,btnjogar,ev.mouse.x,ev.mouse.y))
                        _telaatual=Fase1;
                    if(itsInside2(obj,btnOpcoes,ev.mouse.x,ev.mouse.y))
                        _telaatual=TelaOpcoes;
                    if(itsInside2(obj,btnCreditos,ev.mouse.x,ev.mouse.y))
                        _telaatual=TelaCreditos;
                    if(itsInside2(obj,btnVoltar,ev.mouse.x,ev.mouse.y))
                        _telaatual=TelaInicial;
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
             switch(ev.keyboard.keycode) {
                 case ALLEGRO_KEY_UP:
                     countKeyUp++;
                     break;
                 case ALLEGRO_KEY_DOWN:
                     countKeyDown++;
                     break;
                 case ALLEGRO_KEY_LEFT:
                     countKeyLeft++;
                     break;
                case ALLEGRO_KEY_RIGHT:
                    countKeyRight++;
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    countKeyUp=0;
                    break;
                case ALLEGRO_KEY_DOWN:
                    countKeyDown=0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    countKeyLeft=0;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    countKeyRight=0;
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_TIMER) {
             limparTela();
             inicializarObjeto(obj);
             direcao = 0;

             getObject(obj,frontup,0,direcao);
             getObject(obj,frontdown,0,direcao);
             getObject(obj,frontright,0,direcao);
             getObject(obj,frontleft,0,direcao);

            switch(_telaatual){

                case TelaInicial:

                        //getObject(obj,windows,100,direcao);


                        //getObject(obj,logo,100,direcao);
                        {
                        int sprit=0;
                        if(seconds>5){
                            sprit=looping(loop,spriteshomem,1,5,1,20,1,FPS);
                            homem[sprit].x=loop[spriteshomem].loopforward*50;
                        }
                        getObject(homem,sprit,looping(loop,tamanhohomem,49,50,50,1,2,FPS),0);
                        }
                        getObject(obj,logo,looping(loop,logo,30,31,30,2,1,FPS),direcao);
                        if(seconds>1)getObject(obj,btnjogar,0,direcao);
                        if(seconds>2)getObject(obj,btnOpcoes,0,direcao);
                        if(seconds>3)getObject(obj,btnCreditos,0,direcao);


                        break;
                case Fase1:
                        getObject(obj,mesa,0,direcao);
                        getObject(obj,btnVoltar,0,direcao);

//                        if(countKeyUp)checkMovement(sprites,obj,0,key_up);
//                        if(countKeyDown)checkMovement(sprites,obj,0,key_down);
//                        if(countKeyLeft){
//                            if(checkMovement(sprites,obj,0,key_left)){
//                                sprit=looping(loop,personagem,1,5,1,10,FPS);//sprit recebe um loop
//                                sprites[sprit].x=sprites[0].x;
//                                direcao=ALLEGRO_FLIP_HORIZONTAL;
//                            }
//                    }
//                        if(countKeyRight){
//                            if(checkMovement(sprites,obj,0,key_right))
//                                sprit=looping(loop,personagem,1,5,1,10,FPS);
//                                sprites[sprit].x=sprites[0].x;
//                        }
//                    getObject(sprites,sprit,10,direcao);


                    break;
                case TelaOpcoes:
                    getObject(obj,btnVoltar,0,direcao);
                    break;
                case TelaCreditos:
                    getObject(obj,btnVoltar,0,direcao);
                    break;
            }
            frames++;
            if(!(frames%FPS))seconds++;
            if(seconds>60)seconds=0;
            al_flip_display();
            //system("PAUSE");
         }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
             break;
         }
     } //fim while
    destruirElementos();
    fclose(filedebug);
    //system("PAUSE");
    return 0;
}








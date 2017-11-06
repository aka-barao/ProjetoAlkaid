#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "globais.c"
#include "audio.h"
#include "funcoes.h"
#include "objetos.h"
#include "movimentacao.h"
#include "fase1.c"


ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;


ALLEGRO_SAMPLE *menuAudioSample[20];
ALLEGRO_SAMPLE_INSTANCE *menuAudioInstance[20];

int createElements(struct OBJETO *obj){
    //sempre adicionar elemento antes na enumObjetos
    criarObjeto(obj,windows,NULL,"windows.jpg",0,0,0,0,0);
    criarObjeto(obj,logo,NULL,"logo.jpg",0,0,0,-100,CENTER);
    criarObjeto(obj,btnjogar," Play",NULL,190, 60, 0, 0,CENTER);
    criarObjeto(obj,btnOpcoes," Options",NULL,190, 60, 0, 60,CENTER);
    criarObjeto(obj,btnCreditos," Credits",NULL,190, 60, 0, 120,CENTER);
    criarObjeto(obj,btnQuit," QUIT",NULL,190, 60, 0, 120,BOTTOMRIGHT);
    //criarObjeto(obj,personagem,"W",NULL,50,50,100,100,0);
    criarObjeto(obj,help,"HEEELP!",NULL,300,60,500,150,TOPRIGHT);
    criarObjeto(obj,mesa,"",NULL,200,200,0,0,CENTER);
    criarObjeto(obj,quadrado10,"",NULL,10,10,0,0,0);
    //criarObjeto(obj,retangulo5010,"",NULL,50,10,0,0,0);
    criarObjeto(obj,frontup,"",NULL,SCREEN_H,0,0,0,0);
    criarObjeto(obj,frontright,"",NULL,0,SCREEN_V,SCREEN_H,0,0);
    criarObjeto(obj,frontdown,"",NULL,SCREEN_H,0,0,SCREEN_V,0);
    criarObjeto(obj,frontleft,"",NULL,0,SCREEN_V,0,0,0);
    criarObjeto(obj,btnVoltar," Voltar",NULL,190,60,0,0,TOPLEFT);
    criarObjeto(obj,ponte,"Ponte",NULL,100,300,300,150,0);
    criarObjeto(obj,btnaction,"socorrer",NULL,200,60,300,SCREEN_V-70,0);
    criarObjeto(obj,vitima,"vitima","vitima.png",0,0,400,300,0);
    criarObjeto(obj,fundofase1,"","fundofase1.png",0,0,0,0,0);
    return 0;
}


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

    if (!al_install_audio()){
		printf("Falha ao inicializar áudio.\n");
		return false;
	}

	if (!al_init_acodec_addon()){
		printf("Falha ao inicializar codecs de áudio.\n");
		return false;
	}

	if (!al_reserve_samples(1)){
		printf("Falha ao alocar canais de áudio.\n");
		return false;
	}

    return 0;
}

void destruirElementos(){
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}




int main(){
    FILE *filedebug = fopen("debug.txt","w");
    filedebug=fopen("debug.txt","a");

    int _telaatual=TelaInicial;
    int seconds=0;
    int frames=0;
    int countKey[MAXQTD_teclas];{int i=0;while(i<MAXQTD_teclas){countKey[i]=0;i++;}}

    struct OBJETO obj[MAXQTD_obj];
    inicializarObjeto(obj,MAXQTD_obj);
    struct OBJETO invisible[MAXQTD_invisible];
    inicializarObjeto(invisible,MAXQTD_invisible);
    struct OBJETO homem[MAXQTD_sprites];
    inicializarObjeto(homem,MAXQTD_sprites);
    struct LOOP loop[MAXQTD_obj];
    inicializarLoop(loop);
    struct AUDIO audio[MAXQTD_audio];
    inicializarAudio(audio,MAXQTD_audio);

    inicializarAllegro(FPS);

    carregarFontes();
    criarSprite(homem,cdhomemlado,"homem",6,10,10,0);
    createElements(obj);
    createSound(audio,oggTelaInicial,"audio_tela.ogg");
    createSound(audio,oggParque,"parque.ogg");

    //teste audio

    while(1){



        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
         //capturar eventos do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            switch(ev.mouse.button) {
                case 1://clique botao esquerdo
                    if(itsInsideMouse(obj,btnjogar,ev.mouse.x,ev.mouse.y)){
                        _telaatual=Fase1;
                        al_stop_samples();
                    }
                    if(itsInsideMouse(obj,btnOpcoes,ev.mouse.x,ev.mouse.y)){
                        _telaatual=TelaOpcoes;
                        al_stop_samples();
                    }
                    if(itsInsideMouse(obj,btnCreditos,ev.mouse.x,ev.mouse.y)){
                        _telaatual=TelaCreditos;
                        al_stop_samples();
                    }
                    if(itsInsideMouse(obj,btnVoltar,ev.mouse.x,ev.mouse.y)){
                        _telaatual=TelaInicial;
                        al_stop_samples();
                    }
                    printf("Coordenadas do clique = (%d,%d)\n",ev.mouse.x,ev.mouse.y);
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
             switch(ev.keyboard.keycode) {
                 case ALLEGRO_KEY_UP:
                     countKey[key_up]++;
                     break;
                 case ALLEGRO_KEY_DOWN:
                     countKey[key_down]++;
                     break;
                 case ALLEGRO_KEY_LEFT:
                     countKey[key_left]++;
                     break;
                case ALLEGRO_KEY_RIGHT:
                    countKey[key_right]++;
                    break;
            }
        }
        if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    countKey[key_up]=0;
                    break;
                case ALLEGRO_KEY_DOWN:
                    countKey[key_down]=0;
                    break;
                case ALLEGRO_KEY_LEFT:
                    countKey[key_left]=0;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    countKey[key_right]=0;
                    break;
            }
        }
        if(countKey[key_up])countKey[key_up]++;
        if(countKey[key_left])countKey[key_left]++;
        if(countKey[key_down])countKey[key_down]++;
        if(countKey[key_right])countKey[key_right]++;
        //printf("MOVIMENTO = %d/%d/%d/%d\n",countKey[key_up],countKey[key_right],countKey[key_down],countKey[key_left]);
        if(ev.type == ALLEGRO_EVENT_TIMER) {

             limparTela();
             inicializarObjeto(obj,MAXQTD_obj);
             inicializarObjeto(invisible,MAXQTD_invisible);
             int direcao = 0;
             getObject(obj,frontup,100,direcao);
             getObject(obj,frontdown,100,direcao);
             getObject(obj,frontright,100,direcao);
             getObject(obj,frontleft,100,direcao);

            switch(_telaatual){

                case TelaInicial:

                        getSound(audio,oggTelaInicial);
                        {
                        int sprit=0;
                        if(seconds>5){
                            sprit=looping(loop,loophomemleft,1,5,1,10,1,FPS);
                            homem[sprit].x=loop[loophomemleft].loopforward*50;
                        }
                        getObject(homem,sprit,looping(loop,loophomemtamanho,49,50,50,1,2,FPS),0);
                        }
                        getObject(obj,logo,looping(loop,looplogotamanho,30,31,30,2,1,FPS),direcao);
                        if(seconds>1)getObject(obj,btnjogar,0,direcao);
                        if(seconds>2)getObject(obj,btnOpcoes,0,direcao);
                        if(seconds>3)getObject(obj,btnCreditos,0,direcao);


                        break;
                case Fase1:
                    fase1(obj,homem,loop,audio,countKey,invisible);
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








#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define MAXQTD_obj 50   //Maxima quantidade de Objetos para criacao dos vetores
#define MAXLEN_label 20 //Maximo de texto por objeto
const int SCREEN_V = 600;
const int SCREEN_H = 800;

ALLEGRO_BITMAP *quadrado[MAXQTD_obj];
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *fonte = NULL;

//Variaveis Globais começam com "_"
int FPS = 600; //modificável para efeitos
char _objLabel[MAXQTD_obj][MAXLEN_label];
float _objHeight[MAXQTD_obj];
float _objWidth[MAXQTD_obj];
float _posx[MAXQTD_obj];
float _posy[MAXQTD_obj];
int _telaatual=0;

//Enumeracoes
enum listObj{
            //Botoes
            btnjogar
            ,btnOpcoes
            ,btnCreditos
            ,personagem
            ,mesa
            ,help
            //Limites da tela
            ,frontup
            ,frontright
            ,frontdown
            ,frontleft
            };
enum listAlign{CENTER=1};
enum telas{TelaInicial,Fase1};
enum teclas{key_up,key_down,key_right,key_left};

//Prototipos
void InicializarVetores();
int InicializarAllegro();
int createObject(int cdobj,char texto[MAXLEN_label],float largura,float altura, float x, float y, int customalign);
int getObject(int cdobj);
void movimentacao(int cdobj);
int itsInside(int cdobj,int cdelemento);
int checkMovement(int cdobj,int tecla);
char *itoa(int value,char *p);
void limparTela();
void destruirElementos();

int main(){
    int i=0;
    int countKeyUp=0,countKeyDown=0,countKeyLeft=0,countKeyRight=0;

    InicializarVetores();
    InicializarAllegro();

    //sempre adicionar elemento antes na enumObjetos
    createObject(btnjogar," Play",190, 60, 0, 0,CENTER);
    createObject(btnOpcoes," Options",190, 60, 0, 60,CENTER);
    createObject(btnCreditos," Credits",190, 60, 0, 120,CENTER);
    createObject(personagem,"Kaidwal",50,50,100,100,0);
    createObject(help,"HEEELP!",300,60,500,150,0);
    createObject(mesa,"",50,50,200,100,0);
    createObject(frontup,"",SCREEN_H,0,0,0,0);
    createObject(frontright,"",0,SCREEN_V,SCREEN_H,0,0);
    createObject(frontdown,"",SCREEN_H,0,0,SCREEN_V,0);
    createObject(frontleft,"",0,SCREEN_V,0,0,0);
    //fundo branco
    limparTela();
    //carregar imagens
    ALLEGRO_BITMAP *image = al_load_bitmap("logo.jpg");
    ALLEGRO_BITMAP *image2 = al_load_bitmap("windows.jpg");
    ALLEGRO_BITMAP *imagens[10];

    i=0;
    int qtdimagens=7;
    while(i<qtdimagens){
        char convert[10];
        char string[80]="Sprites/homem";
        strcat(strcat(string,itoa(i+1,convert)),".png");
        //printf(string);
        imagens[i]=al_load_bitmap(string);
        i++;
    }
    //system("PAUSE");
    //exit(0);

    int time=0;
    int delay=30;
    int posicao=0;

    while(1){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        //capturar eventos do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
             switch(ev.mouse.button) {
                 case 1:
                    if(ev.mouse.x > _posx[btnjogar] && ev.mouse.y > _posy[btnjogar] && ev.mouse.x < (_posx[btnjogar]+_objWidth[btnjogar]) && ev.mouse.y < (_posy[btnjogar]+_objHeight[btnjogar])){
                         printf("Clique Jogar\n");
                         _telaatual=Fase1;
                     }else if(ev.mouse.x > _posx[btnOpcoes] && ev.mouse.y > _posy[btnOpcoes] && ev.mouse.x < (_posx[btnOpcoes]+_objWidth[btnOpcoes]) && ev.mouse.y < (_posy[btnOpcoes]+_objHeight[btnOpcoes])){
                         printf("Clique Opçoes\n");
                     }else if(ev.mouse.x > _posx[btnCreditos] && ev.mouse.y > _posy[btnCreditos] && ev.mouse.x < (_posx[btnCreditos]+_objWidth[btnCreditos]) && ev.mouse.y < (_posy[btnCreditos]+_objHeight[btnCreditos])){
                         printf("Clique no Creditos\n");
                     }
             }
         }
         //capturar eventos do teclado
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
        //atualizacao da tela (constante)
        if(ev.type == ALLEGRO_EVENT_TIMER) {

            //cronometro++;

            limparTela();
            //Criar objetos presentes em todas as telas
            //Sempre adicionar o objeto na checagem de CheckMovement
            getObject(frontup);
            getObject(frontdown);
            getObject(frontright);
            getObject(frontleft);

            //Criar Objetos de acordo com a tela atual
            switch(_telaatual){
                case TelaInicial:
                    al_draw_bitmap(image, 150, 0, 0);

                    if(time==50){
                        delay=30;
                        time=0;
                    }

                    if(delay<20&&(delay>0))
                        getObject(help);
                    if(time)
                        posicao=(time-1)*100;
                    else
                        posicao=0;
                    if(time<qtdimagens)
                        al_draw_bitmap(imagens[time], posicao-120, 0, 0);
                    if(time>10)getObject(btnjogar);
                    if(time>20)getObject(btnOpcoes);
                    if(time>30)getObject(btnCreditos);

                    if((!time)&&(delay))delay--;
                    else time++;
                    printf("time = %d / delay = %d\n",time,delay);
                    break;
                case Fase1:
                    if(countKeyUp)checkMovement(personagem,key_up);
                    if(countKeyDown)checkMovement(personagem,key_down);
                    if(countKeyLeft)checkMovement(personagem,key_left);
                    if(countKeyRight)checkMovement(personagem,key_right);
                    al_draw_bitmap(image2, 0, 0, 0);
                    getObject(personagem);
                    getObject(mesa);
                    break;
            }
            al_flip_display();
         }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
             break;
         }
    }
    destruirElementos();
    return 0;
}

int createObject(int cdobj,char texto[MAXLEN_label],float largura,float altura, float x, float y, int customalign){
    quadrado[cdobj] = al_create_bitmap(largura, altura);if(!quadrado[0]) { printf("failed to create bitmap!\n"); return -1; }
    _objWidth[cdobj]=largura;
    _objHeight[cdobj]=altura;
    switch(customalign){
        case CENTER:
            _posx[cdobj]=SCREEN_H/2 - largura/2;
            _posy[cdobj]=SCREEN_V*2/3+y;
            break;
        default:
        _posx[cdobj]=x;
        _posy[cdobj]=y;
    }
    al_set_target_bitmap(quadrado[cdobj]);
    int a=0;
    while(a<MAXLEN_label){
        if(texto[a]==0)break;
        _objLabel[cdobj][a]=texto[a];
        a++;
    }
    al_clear_to_color(al_map_rgb(100, 0, 0));
    return cdobj;
}

int getObject(int cdobj){
    //al_set_target_bitmap(quadrado[cdobj]);
    if(!quadrado[cdobj]){
        printf("getObject(%d)Objeto nao encontrado\n",cdobj);
        return -1;
    }
    al_draw_tinted_bitmap(quadrado[cdobj], al_map_rgba_f(1.0, 1.0, 1.0, 0.5), _posx[cdobj], _posy[cdobj], 0);
    al_draw_text(fonte, al_map_rgb(255, 255, 255), _posx[cdobj], _posy[cdobj], ALLEGRO_ALIGN_LEFT, _objLabel[cdobj]);
//    al_draw_bitmap(quadrado[cdobj], _posx, _posy, 0);
    return 0;
}

int InicializarAllegro(){

    if(!al_init()) { printf("failed to initialize allegro!\n"); return -1; }
    timer = al_create_timer(1.0 / FPS);if(!timer) { printf("failed to create timer!\n"); return -1; }
    display = al_create_display(SCREEN_H, SCREEN_V);if(!display) { printf("failed to create display!\n"); return -1; }
    event_queue = al_create_event_queue();if(!event_queue) { printf("failed to create event_queue!\n"); return -1; }

    al_init_font_addon();
    if(!al_init_ttf_addon()){fprintf(stderr,"Falha ao inicializar add-on allegro_ttf.\n");return -1;}
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_start_timer(timer);
    fonte = al_load_font("arial.TTF", 48, 0);
    if (!fonte) { fprintf(stderr, "Falha ao carregar fonte.\n"); return -1; }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());


    return 0;


}

void InicializarVetores(){
    int i=0,j=0;
    while(i<MAXQTD_obj){
        quadrado[i]=NULL;
        while(j<20){
            _objLabel[i][j]=0;
            j++;
        }
        i++;
    }
}

void movimentacao(int cdobj){
    if(_posx[cdobj] < 0) _posx[cdobj] = 0;
    if(_posx[cdobj] > SCREEN_H - _objWidth[cdobj]) _posx[cdobj] = SCREEN_H - _objWidth[cdobj];
    if(_posy[cdobj] < 0) _posy[cdobj] = 0;
    if(_posy[cdobj] > SCREEN_V - _objHeight[cdobj]) _posy[cdobj] = SCREEN_V - _objHeight[cdobj];
    if((_posx[cdobj]+_objWidth[cdobj]) == _posx[mesa])_posx[cdobj]=0;
}

int checkMovement(int cdobj,int tecla){
    switch(tecla){
        case key_up:
            _posy[cdobj]--;
            if(itsInside(cdobj,mesa))_posy[cdobj]++;
            if(itsInside(cdobj,frontup))_posy[cdobj]++;
            break;
        case key_down:
            _posy[cdobj]++;
            if(itsInside(cdobj,mesa))_posy[cdobj]--;
            if(itsInside(cdobj,frontdown))_posy[cdobj]--;
            break;
        case key_right:
            _posx[cdobj]++;
            if(itsInside(cdobj,mesa))_posx[cdobj]--;
            if(itsInside(cdobj,frontright))_posx[cdobj]--;
            break;
        case key_left:
            _posx[cdobj]--;
            if(itsInside(cdobj,mesa))_posx[cdobj]++;
            if(itsInside(cdobj,frontleft))_posx[cdobj]++;
            break;
    }
    return 0;
}

int itsInside(int cdobj,int cdelemento){
    //Retorna 1 se estiver dentro dos limites de algum elemento
    //Retorna 0 se NAO estiver
//    printf("Personagem(%.0f,%.0f)\n",_posx[cdobj],_posy[cdobj]);
//    printf("Elemento(%.0f,%.0f)\n",_posx[cdelemento],_posy[cdelemento]);
    if((_posx[cdobj]+_objWidth[cdobj] > _posx[cdelemento])
    &&(_posy[cdobj]+_objHeight[cdobj] > _posy[cdelemento])
    &&(_posx[cdobj] < _posx[cdelemento]+_objWidth[cdelemento])
    &&(_posy[cdobj] < _posy[cdelemento]+_objHeight[cdelemento]))
        return 1;
    return 0;
}

char *itoa(int value,char *p){
    char* ptr = p, *ptr1 = p, temp;
    int temp_value;
    do{
        temp_value=value;
        value /= 10;
        *ptr++=(temp_value-value*10)+48;
    }while(value);
    *ptr--='\0';
    while(ptr1<ptr){
        temp=*ptr;
        *ptr--=*ptr1;
        *ptr1++=temp;
    }
    return p;
}

void limparTela(){
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(255,255,255));
}
void destruirElementos(){
//al_destroy_bitmap(quadrado);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}

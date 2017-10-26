#include <allegro5/allegro.h>
#define MAXQTD_obj 100   //Maxima quantidade de Objetos para criacao dos vetores
#define MAXLEN_label 20 //Maximo de texto por objeto
#define MAXLEN_path 100
#define SCREEN_V 600
#define SCREEN_H 800
#define FPS 60

enum listAlign{
                CENTER=1
                ,TOPLEFT
                ,TOPRIGHT
                ,BOTTOMLEFT
                ,BOTTOMRIGHT
};

enum teclas{key_up=1,key_down,key_right,key_left};
enum listObj{
            //Botoes
            btnjogar
            ,btnOpcoes
            ,btnCreditos
            ,btnVoltar
            ,personagem
            ,posicaopersonagem
            ,mesa
            ,help
            //Limites da tela
            ,frontup
            ,frontright
            ,frontdown
            ,frontleft
            ,logo
            ,windows
            ,spriteshomem
            ,tamanhohomem
            };
enum telas{TelaInicial,Fase1,TelaOpcoes,TelaCreditos};

struct OBJETO{
    ALLEGRO_BITMAP *bmp;
    float h;
    float w;
    float x;
    float y;
    char label[MAXLEN_label];
    char path[MAXLEN_path];
    bool imagem;
    int align;
    bool active;
};

struct LOOP{
    int loop;
    int loopforward;
    int inverse;
    int maxloop;
    int minloop;
    int inicializado;
    int contadorfreq;
};

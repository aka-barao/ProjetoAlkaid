#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "globais.c"
#include "funcoes.h"

ALLEGRO_BITMAP *quadrado[MAXQTD_obj];
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_FONT *fonte20 = NULL;
float _objWidth[MAXQTD_obj];
float _objHeight[MAXQTD_obj];



int carregarFontes(){
    fonte = al_load_font("arial.TTF", 48, 0);
    if (!fonte) { fprintf(stderr, "Falha ao carregar fonte.\n"); return -1; }

    fonte20 = al_load_font("arial.TTF", 20, 0);
    if (!fonte) { fprintf(stderr, "Falha ao carregar fonte.\n"); return -1; }
    return 0;
}

int criarObjeto(struct OBJETO *obj,int cdobj,char texto[],char path[],float largura,float altura, float x, float y, int customalign){
//     printf("\nPrimeiro Objeto: %c\n",p->text[0]);
//     printf("\nSegundo Objeto: %c\n",(p+10)->text[0]);

    //quadrado[cdobj] = al_create_bitmap(largura, altura);if(!quadrado[0]) { printf("failed to create bitmap!\n"); return -1; }
    struct OBJETO *p;
    p=obj+cdobj;


    if(!path){
        p->bmp = al_create_bitmap(largura, altura);
        if(!(p->bmp)){printf("failed to create bitmap!\n");return -1;}
        p->imagem = false;
        p->h=altura;
        p->w=largura;
        al_set_target_bitmap(p->bmp);
        al_clear_to_color(al_map_rgb(200, 200, 200));
    }else{
        char caminhodoarquivo[50]="images/";
        p->imagem = true;
        strcat(caminhodoarquivo,path);
        p->bmp = al_load_bitmap(caminhodoarquivo);
        if(!(p->bmp)){printf("failed to create bitmap Imagem %d!\n",cdobj);return -1;}
        p->h=al_get_bitmap_height(p->bmp);
        p->w=al_get_bitmap_width(p->bmp);
    }



    p->align=customalign;
    switch(customalign){
        case CENTER:
            p->x=SCREEN_H/2 - p->w/2;
            p->y=SCREEN_V/2 - p->h/2+y;
            break;
        case TOPLEFT:
            p->x=10;
            p->y=10;
            break;
        case TOPRIGHT:
            p->x=SCREEN_H-10;
            p->y=10;
            break;
        case BOTTOMLEFT:
            p->x=10;
            p->y=SCREEN_V-10-p->h;
            break;
        case BOTTOMRIGHT:
            p->x=SCREEN_H-10;
            p->y=SCREEN_V-10;
            break;
        default:
        p->align=0;
        p->x=x;
        p->y=y;
    }

    if(texto){
        int a=0;
        while(a<MAXLEN_label){
            if(texto[a])
                p->label[a]=texto[a];
            else{
                p->label[a]='\0';
                break;
            }
            a++;
        }
    }else{
        p->label[0]='\0';
    }

    return cdobj;
}
void alinhamentoPersonalizado(struct OBJETO *p,int customalign, float x,float y, float width, float height){

//    printf("alinhamento = %d\n",customalign);
    switch(customalign){
        case CENTER:
            p->x=SCREEN_H/2 - p->w/2;
            p->y=SCREEN_V/2 - p->h/2+y;
            break;
        case TOPLEFT:
            p->x=10;
            p->y=10;
            break;
        case TOPRIGHT:
            p->x=SCREEN_H-10-width;
            p->y=10;
            break;
        case BOTTOMLEFT:
            //printf("Alinhamento Bootom Left height = %f\n ",height);
            p->x=10;
            p->y=SCREEN_V-10-height;
            break;
        case BOTTOMRIGHT:
            p->x=SCREEN_H-10-width;
            p->y=SCREEN_V-10-height;
            break;
        default:
        p->align=0;
        p->x=x;
        p->y=y;
    }


}
int criarSprite(struct OBJETO *spr,int cdsprite,char nomesprite[],int qtdimagens,float x, float y, int customalign){
    struct OBJETO *p;
    int i=0;
    int imagenscarregadas=0;
    while(i<qtdimagens){
        p=spr+i;
        char convert[10];
        char string[80]="sprites/";
        strcat(string,nomesprite);
        strcat(strcat(string,iToChar(i,convert)),".png");
        p->bmp = al_load_bitmap(string);
        if(!(p->bmp)){printf("failed to create sprite %d.%d!\n",cdsprite,i);i++;continue;}
        imagenscarregadas++;
        p->imagem = true;
        p->h=al_get_bitmap_height(p->bmp);
        p->w=al_get_bitmap_width(p->bmp);
        alinhamentoPersonalizado(p,customalign,x,y,p->w,p->h);
        p->align=customalign;
        i++;
    }
    return imagenscarregadas;
}

int getObject(struct OBJETO *obj,int cdobj,int escala,int direcao){
    struct OBJETO *p;
    p=obj+cdobj;

    if(!(p->bmp)){
       printf("getObject(%d)Objeto nao encontrado\n",cdobj);
       return -1;
    }


    if(p->imagem){
        float resize = escala/100.0;
        int larguraoriginal=al_get_bitmap_width(p->bmp);
        int alturaoriginal= al_get_bitmap_height(p->bmp);

//         printf("\nVai Alinhar Logo\n");
//        alinhamentoPersonalizado(p,p->align, p->x,p->y,p->w,p->h);
//         printf("Alinhou x=%f y=%f\n",p->x,p->y);

        float posx=p->x;
        float posy=p->y;
        switch(p->align){
           case CENTER:
               posx=p->x+((larguraoriginal-(larguraoriginal*resize))/2);
               posy=p->y+((alturaoriginal-(alturaoriginal*resize))/2);
               break;
           case BOTTOMRIGHT:
               posx=p->x+((larguraoriginal-(larguraoriginal*resize)));
               posy=p->y+((alturaoriginal-(alturaoriginal*resize)));
               break;
           case BOTTOMLEFT:

               posx=p->x;
               posy=p->y+((alturaoriginal-(alturaoriginal*resize)));
               //posy=p->y;
               //printf("BOTTOM LEFT %f\n",p->y+(alturaoriginal - (alturaoriginal*resize)));
               //printf("\n1 posy = %f\n",posy);
               break;
           default:
               posx=p->x;
               posy=p->y;
               break;

       }
        //printf("2 posy = %f\n",posy);
        p->w=larguraoriginal*resize;
        p->h=alturaoriginal*resize;

        al_draw_scaled_bitmap(p->bmp,0,0,larguraoriginal,alturaoriginal,posx,posy,p->w,p->h,direcao);
        if(p->label[0])al_draw_text(fonte20, al_map_rgb(255, 0, 0), posx, posy+20, ALLEGRO_ALIGN_LEFT, p->label);
        //printf("\n3 posy = %f\n",posy);

    }else{
        //printf("Criacao do botao");
        al_draw_tinted_bitmap(p->bmp, al_map_rgba_f(1.0, 1.0, 0, 0.5), p->x, p->y,0);
        if(p->label[0])al_draw_text(fonte, al_map_rgb(255, 0, 0), p->x, p->y, ALLEGRO_ALIGN_LEFT, p->label);
    }

    p->active=true;
    return 0;

}
int getInvisible(struct OBJETO *obj,struct OBJETO *invisible,int cdinvisible,int tipo,float x,float y){
    struct OBJETO *p;
    struct OBJETO *i;
    p=obj+tipo;
    if(!(p->bmp)){
       printf("getInvisible(%d)Objeto nao encontrado\n",tipo);
       return -1;
    }
    i=invisible+cdinvisible;
    i->x=x;
    i->y=y;
    i->w=10;
    i->h=10;
    //printf("x=%f / y=%f\n",x,y);
    al_draw_tinted_bitmap(p->bmp, al_map_rgba_f(0.0, 0.0, 1.0, 0.5),x,y,0);

    p->active=true;
    return 0;
}

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "globais.c"

int itsInside(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int cdelemento){
    struct OBJETO *p;
    p=obj+cdobj;
    struct OBJETO *e;
    e=elemento+cdelemento;
    if(((p->x+p->w) > e->x)
    &&((p->y+p->h) > e->y)
    &&(p->x < e->x+e->w)
    &&(p->y < e->y+e->h)){
        return 1;
    }
    return 0;
}

int itsInside2(struct OBJETO *obj,int cdobj,int x, int y){
    struct OBJETO *e;
    e=obj+cdobj;
    if(!e->active)return 0;
    
    if((x > e->x)
    &&(y > e->y)
    &&(x < e->x+e->w)
    &&(y < e->y+e->h))
        return 1;
    return 0;
}

int checkMovement(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int tecla){
    struct OBJETO *p;
    p=obj+cdobj;
    switch(tecla){
        case key_up:
            p->y--;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontup))){
                p->y++;
                return 0;
            }
            break;
        case key_down:
            p->y++;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontdown))){
                p->y--;
                return 0;
            }
            break;
        case key_right:
            p->x++;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontright))){
                p->x--;
                return 0;
            }
            break;
        case key_left:
            p->x--;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontleft))){
                p->x++;
                return 0;
            }
            break;
    }
    return tecla;
}

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "globais.c"

int itsInside(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int cdelemento){
    struct OBJETO *p;
    p=obj+cdobj;
    struct OBJETO *e;
    e=elemento+cdelemento;
    if(!e->active||(!p->active))return 0;
//     printf("px+pw=%.1f > ex=%.1f\n",p->x+p->w,e->x);
//     printf("py+ph=%.1f > ey%.1f\n",p->y+p->h,e->y);
//     printf("px=%.1f < ex+ew=%.1f\n",p->x,e->x+e->w);
//     printf("py=%.1f < ey+eh=%.1f\n",p->y,e->y+e->h);
    if(((p->x+p->w) > e->x) //pela esquerda
    &&((p->y+p->h) > e->y) //por cima
    &&(p->x < e->x+e->w) //pela direita
    &&(p->y < e->y+e->h)){ //por baixo
        return 1;
    }
    return 0;
}
int inside(struct OBJETO *p,struct OBJETO *e){
    if(((p->x+p->w) > e->x)&&((p->y+p->h) > e->y)&&(p->x < e->x+e->w)&&(p->y < e->y+e->h))
        return 1;
    return 0;
}


int itsInsideInvisible(struct OBJETO *obj,int cdobj,struct OBJETO *invisible,int key){
    struct OBJETO *p;
    struct OBJETO *e;
    p=obj+cdobj;
    int i=0;
    int diagonal=0;
    int invertida=0;
    while(i<60){
        e=invisible+i;
        if(inside(p,e)){
            //printf("ENCONTROU OBJETO\n");
            if(inside(p,e+1)||inside(p,e-1)){
                //printf("TAMBEM ESTA DENTRO DO OBJETO ADJACENTE\n");
                return 0;
            }else{
                //printf("NAO ESTA DENTRO DO OBJETO ADJACENTE\n");
            }
            if((((e+1)->x==(e->x)-10)&&((e+1)->y==(e->y)+10))
            ||(((e-1)->x==((e->x)-10))&&((e-1)->y==((e->y)+10)))){
                printf("DIAGONAL / \n");
                diagonal=1;
            }else if((((e+1)->x==(e->x)+10)&&((e+1)->y==(e->y)+10))
            ||(((e-1)->x==((e->x)+10))&&((e-1)->y==((e->y)+10)))){
                invertida=1;
                printf("DIAGONAL \\\n");
            }else{
                printf("NAO E DIAGONAL");
            }
            switch(key){
                case key_right:
                    if(diagonal)return -1;
                    if(invertida)return +1;
                    break;
                case key_down:
                    if(diagonal)return -1;
                    if(invertida)return +1;
                    break;
                case key_left:
                    if(diagonal)return +1;
                    if(invertida)return -1;
                    break;
                case key_up:
                    if(diagonal)return +1;
                    if(invertida)return -1;
                    break;

            }
        }
        i++;
    }
    return -20;
}

int itsInsideMouse(struct OBJETO *obj,int cdobj,int x, int y){
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

int checkMovement(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int tecla, struct OBJETO *invisible){
    struct OBJETO *p;
    p=obj+cdobj;
    int r=0;
    switch(tecla){
        case key_up:
            p->y--;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontright))
            ||(itsInside(obj,elemento,cdobj,frontleft))
            ||(!(r=itsInsideInvisible(obj,cdobj,invisible,key_up)))
            ||(itsInside(obj,elemento,cdobj,frontup))){
                p->y++;
                return 0;
            }else if(r>-20)
                p->x+=r;
            //if(itsInsideInvisible(obj,cdobj,invisible,key_up)==2)p->x--;
            break;
        case key_down:
            p->y++;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontright))
            ||(itsInside(obj,elemento,cdobj,frontleft))
            ||(!(r=itsInsideInvisible(obj,cdobj,invisible,key_down)))
            ||(itsInside(obj,elemento,cdobj,frontdown))){
                p->y--;
                return 0;
            }else if(r>-20)
                p->x+=r;
            //if(itsInsideInvisible(obj,cdobj,invisible,key_down)==2)p->x--;
            break;
        case key_right:
            p->x++;

            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontright))
            ||(itsInside(obj,elemento,cdobj,frontdown))
            ||(itsInside(obj,elemento,cdobj,frontup))
            ||(!(r=itsInsideInvisible(obj,cdobj,invisible,key_right)))
            ){
                //printf("Movimento Cancelado\n");
                p->x--;
                return 0;
            }else if(r>-20){
                //printf("Movimento Diagonal\n");
                p->y+=r;
            }
            break;
        case key_left:
            p->x--;
            if(itsInside(obj,elemento,cdobj,mesa)
            ||(itsInside(obj,elemento,cdobj,frontleft))
            ||(itsInside(obj,elemento,cdobj,frontdown))
            ||(itsInside(obj,elemento,cdobj,frontup))
            ||(!(r=itsInsideInvisible(obj,cdobj,invisible,key_left)))){
                p->x++;
                return 0;
            }else if(r>-20)
                p->y+=r;
            break;
    }
    return tecla;
}

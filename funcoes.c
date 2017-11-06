#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "globais.c"

char *iToChar(int value,char *p){
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

int looping(struct LOOP *l,int cdobj,int min, int max, int inicio,int frequenciaporsegundo,int segundoporfrequencia,int fps){
    struct LOOP *p;
    p=l+cdobj;
    if(!(p->active)){
        p->loop=inicio;
        p->loopforward=0;
        p->active=true;
        p->inverse=0;
        p->contadorfreq=0;
        return p->loop;
    }
    p->contadorfreq++;
//    printf("\nloop = %d / contador = %d\n",p->loop,p->contadorfreq);
    if(frequenciaporsegundo>fps)frequenciaporsegundo=fps;
    if(p->contadorfreq%(fps*segundoporfrequencia/frequenciaporsegundo))return p->loop;
    //printf("contador de frequencia = %d", p->contadorfreq);
    p->loopforward++;
    if((p->loop>min)&&!p->inverse){
        p->loop--;
    }else if(p->loop>(max-1)){
            p->inverse=0;
            p->loop--;
    }else{
        p->inverse++;
        p->loop++;
    }
    //printf("\n%d / %d\n",p->loop,p->loopforward);
    return p->loop;
}


void inicializarLoop(struct LOOP *p){
    int i=0;
    struct LOOP *loop;
    while(i<MAXQTD_obj){
        loop=p+i;
        loop->active=false;
        i++;
    }
}

void inicializarObjeto(struct OBJETO *p, int MAX){
    int i=0;
    struct OBJETO *obj;
    while(i<MAX){
        obj=p+i;
        obj->active=false;
        i++;
    }
}

void inicializarAudio(struct AUDIO *p, int MAX){
    int i=0;
    struct AUDIO *audio;
    while(i<MAX){
        audio=p+i;
        audio->printederror=false;
        audio->sample = NULL;
        audio->instance = NULL;
        i++;
    }
}

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "globais.c";

int createSound(struct AUDIO *audio,int cdaudio,char path[]){
    struct AUDIO *p;
    p=audio+cdaudio;
    char caminhodoarquivo[50]="sounds/";
    strcat(caminhodoarquivo,path);
    p->sample = al_load_sample(caminhodoarquivo);
    if(!p->sample){
        printf("Erro ao carregar amostra de audio: %d %s\n",cdaudio,path);
        return -1;
    }
	p->instance = al_create_sample_instance(p->sample);
    if(!p->instance){
        printf("Erro ao carregar instancia de audio: %d %s\n",cdaudio,path);
        return -1;
    }
	al_attach_sample_instance_to_mixer(p->instance, al_get_default_mixer());

    return 0;
}

int getSound(struct AUDIO *audio,int cdaudio){
    struct AUDIO *p;
    p=audio+cdaudio;
    if(!p->instance){
        if(p->printederror==false){
            printf("Erro ao tocar instancia de audio: %d\n",cdaudio);
            p->printederror = true;
        }
        return -1;
    }
    //al_play_sample_instance(p->instance,0.5);
    al_play_sample(p->sample,0.1,ALLEGRO_AUDIO_PAN_NONE,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    return 0;
}

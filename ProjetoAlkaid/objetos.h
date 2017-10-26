#ifndef __OBJETOS_H_
#define __OBJETOS_H_



int carregarFontes();

//recebe ponteiro objeto e codigo de um novo objeto, criando a imagem do objeto
int criarObjeto(struct OBJETO *obj,int cdobj,char texto[],char path[],float largura,float altura, float x, float y, int customalign);

int criarSprite(struct OBJETO *spr,int cdsprite,char nomesprite[],int qtdimagens,float x, float y, int customalign);

void alinhamentoPersonalizado(struct OBJETO *p,int customalign, float x,float y, float width, float height);

int getObject(struct OBJETO *obj,int cdobj,int escala, int direcao);

#endif

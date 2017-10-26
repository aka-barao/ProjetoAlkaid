#ifndef __FUNCOES_H_
#define __FUNCOES_H_

char *iToChar(int value,char *p);
int looping(struct LOOP *l,int cdobj,int min, int max, int inicio,int frequenciaporsegundo,int segundoporfrequencia,int fps);
void inicializarLoop(struct LOOP *p);
void inicializarObjeto(struct OBJETO *p);

#endif
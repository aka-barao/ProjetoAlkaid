#ifndef __MOVIMENTACAO_H_
#define __MOVIMENTACAO_H_

int checkMovement(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int tecla, struct OBJETO *invisible);

/*
    Verifica se as coordenadas x e y estão dentro de um certo cdobj
    O ponteiro obj deve ser passado como parametro para que a funcao tenha
    acesso a matriz OBJETO
    O ponteiro elemento deve ser passado como parametro para que a funcao tenha
    acesso a matriz de elementos para comparacao das posicoes
*/
int itsInside(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int cdelemento);
int itsInsideMouse(struct OBJETO *obj,int cdobj,int x, int y);
int itsInsideInvisible(struct OBJETO *obj,int cdobj,struct OBJETO *invisible,int key);



#endif
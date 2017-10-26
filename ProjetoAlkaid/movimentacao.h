#ifndef __MOVIMENTACAO_H_
#define __MOVIMENTACAO_H_

int itsInside(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int cdelemento);

/*
    Verifica se as coordenadas x e y estão dentro de um certo cdobj
    O ponteiro obj deve ser passado como parametro para que a funcao tenha
    acesso a matriz OBJETO
*/
int itsInside2(struct OBJETO *obj,int cdobj,int x, int y);


int checkMovement(struct OBJETO *obj,struct OBJETO *elemento,int cdobj,int tecla);


#endif
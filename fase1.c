

void fase1(struct OBJETO *obj,struct OBJETO *homem,struct LOOP *loop,struct AUDIO *audio,int countKey[],struct OBJETO *invisible){
    int direcao=0;
    int sprit=0;

//criar fronteiras do cenario
//    {int i=1;
//        int x=0;
//        int y=0;
//        while(i<=10){//reta
//            getInvisible(obj,invisible,i,quadrado10,x=100,y=i*10);
//            i++;
//        }
//        while(i<=20){//diagonal
//
//            getInvisible(obj,invisible,i,quadrado10,x=i*10,y=i*10);
//            i++;
//        }
//        while(i<=30){//invertida
//            getInvisible(obj,invisible,i,quadrado10,x=i*10,y-=10);
//            i++;
//        }
//    }

    //printf("MOVIMENTO = %d/%d/%d/%d\n",countKey[key_up],countKey[key_right],countKey[key_down],countKey[key_right]);
    getSound(audio,oggParque);
    getObject(obj,ponte,100,0);
    getObject(obj,fundofase1,100,0);
    if(countKey[key_up]){
        if(checkMovement(homem,obj,0,key_up,invisible)){
            sprit=0;
            homem[sprit].x=homem[0].x;
            homem[sprit].y=homem[0].y;
        }
    }
    if(countKey[key_down]){
        if(checkMovement(homem,obj,0,key_down,invisible)){
            sprit=0;
            homem[sprit].x=homem[0].x;
            homem[sprit].y=homem[0].y;
        }
    }
    if(countKey[key_left]){
        if(checkMovement(homem,obj,0,key_left,invisible)){
            sprit=looping(loop,loophomemleft,1,5,1,10,1,FPS);
            homem[sprit].x=homem[0].x;
            homem[sprit].y=homem[0].y;
            direcao=ALLEGRO_FLIP_HORIZONTAL;
        }
    }
    if(countKey[key_right]){
        if(checkMovement(homem,obj,0,key_right,invisible)){
            sprit=looping(loop,loophomemright,1,5,1,10,1,FPS);
            homem[sprit].x=homem[0].x;
            homem[sprit].y=homem[0].y;
            direcao=0;
        }
    }
    getObject(homem,sprit,10,direcao);
    if(itsInside(homem,obj,0,ponte)){
            //printf("homem na ponte\n");
        getObject(obj,btnaction,100,0);
            {int i=0;
                while(i*10<obj[ponte].h){//reta
                    getInvisible(obj,invisible,i,quadrado10,obj[ponte].x-10,obj[ponte].y+(i*10));
                    i++;
                }

            }
    }
//    obj[vitima].y=looping(loop,vitimaafogando,250,350,295,10,1,FPS);
//    obj[vitima].x=looping(loop,vitimaafogandox,400,500,400,10,1,FPS);
    getObject(obj,vitima,10,0);

}

#include <STC15F2K60S2.h>

void cls_buzz(){
    P2 = (P2 & 0x1f) | 0xa0;
    P0 = 0xaf;
    P2 &= 0x1f;
}

unsigned int key_press = 0;
unsigned char key(){
    P3 = 0x0f;
    if (!P30 || !P31 || !P32 || !P33){
        key_press++;
    }else{
        key_press = 0;
    }
    if(key_press==3){
        if(!P30) return 1;
        else if (!P31) return 2;
        else if (!P32) return 3;
        else if (!P33) return 4;
        else return 0;
    }
    else return 0;
}

void main(){
    cls_buzz();
    while(1){
        switch(key()){
            case 1:
                P2 = (P2 & 0x1f) | 0x80;
                P0 = 0xfe;
                P2 &= 0x1f;
                break;
            case 2:
                P2 = (P2 & 0x1f) | 0x80;
                P0 = 0xfd;
                P2 &= 0x1f;
                break;
            case 3:
                P2 = (P2 & 0x1f) | 0x80;
                P0 = 0xfb;
                P2 &= 0x1f;
                break;
            case 4:
                P2 = (P2 & 0x1f) | 0x80;
                P0 = 0xf7;
                P2 &= 0x1f;
                break;
        }
    }
}

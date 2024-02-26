#include "muros.h"

void inicia_muro(struct muro M[]){
    char pos_muros[3][22] = {
       "AEC   AEC   AEC   AEC",   
       "B D   B D   B D   B D",
    };
    int r = 0;
    for(int i=0;i<21;i++){
        for(int j=0;j<2;j++){
            if(pos_muros[j][i] != ' '){
                M[r].x=90+i*20;
                M[r].y=450+j*15;
                M[r].dano = 0;
                if(pos_muros[j][i] == 'A') M[r].tipo = 0;
                if(pos_muros[j][i] == 'B') M[r].tipo = 1;
                if(pos_muros[j][i] == 'C') M[r].tipo = 2;
                if(pos_muros[j][i] == 'D') M[r].tipo = 3;
                if(pos_muros[j][i] == 'E') M[r].tipo = 4;
                r++;            
            }
        }
    }
}

void pintar_muros(struct muro M[], ALLEGRO_BITMAP* img_muro, ALLEGRO_BITMAP* buffer) {
    for (int i = 0; i < 20; i++) {
        if (M[i].dano != 3)
            al_draw_bitmap_region(img_muro, M[i].dano * 20, M[i].tipo * 16, 20, 16, M[i].x, M[i].y, 0);
    }
}
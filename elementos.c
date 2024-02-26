#include "elementos.h"

#define LARGURA 600
#define ALTURA  600

void inicia_nave(struct NAVE* nave,char* caminho_nave,char* caminho_bala,int largura_b,int altura_b,int largura_n, int altura_n, int x, int y,int dir_bala, int tipo, int vida,int max_disp){
    nave->x = x;
    nave->y = y;
    nave->n_disp = 0;
    nave->max_disp = max_disp;
    nave->img_nave = al_load_bitmap(caminho_nave);
    nave->img_bala = al_load_bitmap(caminho_bala);
    nave->tick = 0;
    nave->alto_b = altura_b;
    nave->largura_b = largura_b;
    nave->largura_p = largura_n;
    nave->alto_p = altura_n;
    nave->dir_bala = dir_bala;
    nave->tipo = tipo;
    nave->vida = vida;
    nave->img_explosao = al_load_bitmap("explosaoinimigo.bmp");
}

void carregar_nave(struct NAVE* nave,ALLEGRO_BITMAP* buffer,int x, int y){
        al_draw_bitmap_region(nave->img_nave,x*nave->largura_p,y*nave->alto_p,nave->largura_p,nave->alto_p,nave->x,nave->y,0);
}

void disparar(struct NAVE* nave, ListaBalas* lista, ALLEGRO_BITMAP* buffer) {
    //int i = 1;
    if (nave->tipo)
        criar_bala(&nave->n_disp,nave->max_disp,lista, nave->x, nave->y, nave->dir_bala);

    carregar_bala(lista, buffer, nave->img_bala);
    //eliminar quando chegar no fim do mapa
    elimina_bala(lista, LARGURA, ALTURA);
}

int colisao(int x1, int y1, int a1, int h1, int x2, int y2, int a2, int h2){
    if((x1<x2 + a2) && (x2 < x1+a1) && (y1<y2+h2) && (y2<y1+h1)){
        return 0;
    }
    return 1;
}

//Da pra fazer colisao com a nave tbm qnd n tiver o muro, alterar p/ m[i] 
int colisao_inimigo_muro(struct NAVE E[],struct muro m[]){
    for(int i=0;i<55;i++){
        //int colisao(int x1, int y1, int a1, int h1, int x2, int y2, int a2, int h2){
        if(!colisao(m[0].x,m[0].y,20,15,E[i].x,E[i].y,E[i].alto_p,E[i].largura_p)){
            return 0;
        }
    }
    return 1;
}

int eliminar_bala_objeto(struct NAVE* N,struct NAVE* E,ListaBalas* lista){
        NoBala* current = lista->cabeca->prox;

    if (lista->cabeca->prox->bala) {
        while (current != lista->cabeca) {
            if((!colisao(E->x,E->y,E->largura_p,E->alto_p,current->bala->x,current->bala->y,N->largura_b,N->alto_b)) && E->vida > 0){
                elimina_bala(lista,E->largura_p,E->alto_p);
                return 0;
            }
            current = current->prox;
        }      
    }
    return 1;
}

void criar_bala_nave(struct NAVE* N, ListaBalas* lista) {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if ((al_key_down(&keyState, ALLEGRO_KEY_SPACE) && (lista->cabeca->count < 2)) ) {
        criar_bala(&N->n_disp, N->max_disp, lista, N->x, N->y, N->dir_bala);
    }
}

void carregar_inimigos(struct NAVE E[],ALLEGRO_BITMAP* buffer,int mov){
    int indice = -1;
    for(int i=0;i<5;i++){
        for(int j=0;j<11;j++){
            indice++;
            if(E[indice].vida > 0)
                carregar_nave(&E[indice],buffer,mov,E[indice].tipo-1);
        }
    }
}

void criar_bala_inimigo(struct NAVE e[],int *aleatorio){
    if(e[*aleatorio].n_disp == 0) *aleatorio = rand()%55;
    //procura ate achar algum inimigo com vida
    while((e[*aleatorio].vida) == 0) *aleatorio = rand()%55;
}

void acomoda_inimigos(struct NAVE E[]){
    int indice = -1;
    int tipos = 0;
    for(int i=0;i<5;i++){
        tipos++;
        if(tipos == 4) tipos = 1;
        for(int j=0;j<11;j++){
            indice++;
            if(i <= 1 )
                inicia_nave(&E[indice],"enemigos.bmp","BalaE.bmp",6,12,25,20,140+j*30,130+i*24,2,tipos,1,3);
            else if (i <= 3)
                inicia_nave(&E[indice],"enemigos.bmp","BalaE2.bmp",6,12,25,20,140+j*30,130+i*24,2,tipos,1,3);
            else{
                inicia_nave(&E[indice],"enemigos.bmp","BalaE3.bmp",6,12,25,20,140+j*30,130+i*24,2,tipos,1,3);
            }
        }
    }
}

int limites(struct NAVE E[],int* dir){
    for(int i=0;i<55;i++){
        if((E[i].x > 550 || E[i].x < 20) && E[i].vida != 0){
            *dir = -1*(*dir);
            return 0;
        }
    }
    return 1;
}

int limitesNV(struct NAVE E,int* dir){
        if(E.x > 650 && E.vida != 0){
            return 0;
        }
    return 1;
}

void mover_inimigos(struct NAVE E[],int* mov, int *dir){
    for(int i=0;i<55;i++){
        //al_rest(10);
        E[i].x += *dir;
    }
        if (++(*mov) == 2) *mov = 0;
        if(!limites(E,dir)){
            for(int j = 0;j<55 ; j++){
                //al_rest(10);
                E[j].y += 10;
            }
        }
}

void explosao1(struct NAVE E, ALLEGRO_BITMAP* buffer,ALLEGRO_DISPLAY* display) {
    ALLEGRO_BITMAP* parte = al_create_bitmap(30, 20);
    al_set_target_bitmap(parte);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(display));

    al_draw_bitmap(parte, E.x, E.y, 0);
    al_draw_bitmap_region(E.img_explosao, 0, 0, 41, 34, E.x - 10, E.y, 0);

    al_destroy_bitmap(parte);
}

void explosao2(struct NAVE N, ALLEGRO_BITMAP* buffer, ALLEGRO_DISPLAY* display) {
    ALLEGRO_BITMAP* parte = al_create_bitmap(30, 20);
    al_set_target_bitmap(parte);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(al_get_backbuffer(display));

    for (int i = 0; i < 6; i++) {
        for (int j = 1; j < 3; j++) {
            al_draw_bitmap(parte, N.x, N.y, 0);
            al_draw_bitmap_region(N.img_nave, i * 30, 0, 30, 20, N.x, N.y, 0);
            //imprimir_fundo(fundo, buffer);
            al_flip_display();
            al_rest(0.5);
        }
    }

    al_destroy_bitmap(parte);
}

void eliminar_bala_muro(struct NAVE* N,struct muro E[],ListaBalas* lista){
        NoBala* current = lista->cabeca->prox;

        if (lista->cabeca->prox->bala) {
            while (current != lista->cabeca) {        
                for(int i = 0;i<20;i++){
                    if((!colisao(E[i].x,E[i].y,20,16,current->bala->x,current->bala->y,N->largura_b,N->alto_b) && E[i].dano < 3)){
                        elimina_bala(lista,E[i].x,E[i].y);
                        E[i].dano++;
                        //break;               
                    }
                }
                current = current->prox;
            }
        }
}

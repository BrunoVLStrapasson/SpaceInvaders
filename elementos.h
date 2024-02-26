#include <allegro5/allegro5.h>				
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>																																			
#include <allegro5/allegro_primitives.h>

#include "tiros.h"
#include "muros.h"

struct NAVE{
    int x,y;
    int n_disp;
    int max_disp;
    int tick;
    int largura_b, alto_b;
    int largura_p, alto_p;
    int dir_bala;
    int tipo;
    int vida;

    ALLEGRO_BITMAP* img_nave;
    ALLEGRO_BITMAP* img_bala;
    ALLEGRO_BITMAP* img_explosao;
};

void inicia_nave(struct NAVE* nave,char* caminho_nave,char* caminho_bala,int largura_b,int altura_b,int largura_n, int altura_n, int x, int y,int dir_bala, int tipo, int vida,int max_disp);

void carregar_nave(struct NAVE* nave,ALLEGRO_BITMAP* buffer,int x, int y);

void disparar(struct NAVE* nave, ListaBalas* lista, ALLEGRO_BITMAP* buffer);

int colisao(int x1, int y1, int a1, int h1, int x2, int y2, int a2, int h2);

int colisao_inimigo_muro(struct NAVE E[],struct muro m[]);

int eliminar_bala_objeto(struct NAVE* N,struct NAVE* E,ListaBalas* lista);

void criar_bala_nave(struct NAVE* N, ListaBalas* lista);

void carregar_inimigos(struct NAVE E[],ALLEGRO_BITMAP* buffer,int mov);

void criar_bala_inimigo(struct NAVE e[],int *aleatorio);

void acomoda_inimigos(struct NAVE E[]);

int limites(struct NAVE E[],int* dir);

int limitesNV(struct NAVE E,int* dir);

void mover_inimigos(struct NAVE E[],int* mov, int *dir);

void explosao1(struct NAVE E, ALLEGRO_BITMAP* buffer,ALLEGRO_DISPLAY* display);

void explosao2(struct NAVE N, ALLEGRO_BITMAP* buffer, ALLEGRO_DISPLAY* display);

void eliminar_bala_muro(struct NAVE* N,struct muro E[],ListaBalas* lista);
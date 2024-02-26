#include <allegro5/allegro5.h>				
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>																																			
#include <allegro5/allegro_primitives.h>

typedef struct Balas{
    int x , y;
    int dx , dy;
}Bala;

// Definição da estrutura do nó da lista de balas
typedef struct NoBala {
    struct NoBala* ant;
    struct NoBala* prox;
	int count;
    Bala* bala;
} NoBala;

// Definição da estrutura da lista de balas
typedef struct {
    NoBala* cabeca;
} ListaBalas;

ListaBalas* InicializarListaBalas();

void criar_bala(int* n_disparos, const int max_disparos,ListaBalas* lista, int X, int Y, int dy);

void carregar_bala(ListaBalas* lista, ALLEGRO_BITMAP* buffer, ALLEGRO_BITMAP* bala);

void eliminar(ListaBalas* lista, NoBala* no);

void elimina_bala(ListaBalas* lista, const int largura, const int altura);

void DestruirListaBalas(ListaBalas* listaBalas);
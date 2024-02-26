#include <allegro5/allegro5.h>				
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>																																			
#include <allegro5/allegro_primitives.h>
#include "tiros.h"

#define LARGURA 600
#define ALTURA  600

// Função para inicializar a lista de balas
ListaBalas* InicializarListaBalas() {
    ListaBalas* listaBalas = (ListaBalas*)malloc(sizeof(ListaBalas));

    if (listaBalas != NULL) {
        listaBalas->cabeca = (NoBala*)malloc(sizeof(NoBala));
        if (listaBalas->cabeca != NULL) {
            listaBalas->cabeca->prox = listaBalas->cabeca;
            listaBalas->cabeca->ant = listaBalas->cabeca;
            listaBalas->cabeca->bala = NULL;
            listaBalas->cabeca->count = 0;
        } else {
            //erro de alocação de memória para o no da cabeça
            free(listaBalas);
            listaBalas = NULL;
        }
    }

    return listaBalas;
}

void criar_bala(int* n_disparos, const int max_disparos,ListaBalas* lista, int X, int Y, int dy) {
    if (lista->cabeca->count < max_disparos - 1) {
        // Alocar memoria para a nova bala
        Bala* novaBala = (Bala*)malloc(sizeof(Bala));
        if (novaBala == NULL) {
            return;
        }

        // Preencher os dados da nova bala
        novaBala->x = X + 11;
        novaBala->y = Y;
        novaBala->dx = 0;
        novaBala->dy = dy;

        // Alocar memoria para o novo no da lista
        NoBala* novoNode = (NoBala*)malloc(sizeof(NoBala));
        if (novoNode == NULL) {
            free(novaBala);
            return;
        }

        novoNode->bala = novaBala;

        // Adicionar o novo no na lista
        novoNode->prox = lista->cabeca->prox;
        novoNode->ant = lista->cabeca;
        lista->cabeca->prox->ant = novoNode;
        lista->cabeca->prox = novoNode;

        lista->cabeca->count++;
    }
}

void carregar_bala(ListaBalas* lista, ALLEGRO_BITMAP* buffer, ALLEGRO_BITMAP* bala) {
    NoBala* current = lista->cabeca->prox;

    while (current != lista->cabeca) {
        current->bala->x += current->bala->dx;
        current->bala->y += current->bala->dy;
        al_draw_bitmap(bala, current->bala->x, current->bala->y, 0);
        current = current->prox;
    }
}

void eliminar(ListaBalas* lista, NoBala* no) {
    if (no != NULL) {
        NoBala* anterior = no->ant;
        NoBala* proximo = no->prox;

        if (anterior != NULL) {
            anterior->prox = proximo;
        }

        if (proximo != NULL) {
            proximo->ant = anterior;
        }

        if (lista->cabeca->prox == no) {
            lista->cabeca->prox = proximo;
        }

        free(no->bala);  // Liberar a bala associada ao nó
        free(no);

        lista->cabeca->count--;
    }
}

void elimina_bala(ListaBalas* lista, const int largura, const int altura) {
    NoBala* current = lista->cabeca->prox;
    NoBala* previous = lista->cabeca;

    while (current != lista->cabeca) {
        if (current->bala->y > altura || current->bala->y < 0 || current->bala->x > largura || current->bala->x < 0) {
            //Vazando memoria
            //NoBala* temp = current;
            previous->prox = current->prox;
            current = current->prox;
            //free(temp->bala);  // Liberar a bala associada ao nó
            //free(temp);
            lista->cabeca->count--;
        } else {
            previous = current;
            current = current->prox;
        }
    }
}
// Função para destruir a lista de balas
void DestruirListaBalas(ListaBalas* listaBalas) {
    if (listaBalas != NULL) {
        NoBala* atual = listaBalas->cabeca->prox;
        while (atual != listaBalas->cabeca) {
            NoBala* proximo = atual->prox;
            free(atual->bala);  // Liberar a bala associada ao nó
            free(atual);
            atual = proximo;
        }

        free(listaBalas->cabeca);
        free(listaBalas);
    }
}
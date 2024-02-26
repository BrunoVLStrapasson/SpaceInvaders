#include <allegro5/allegro5.h>				
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>																																			
#include <allegro5/allegro_primitives.h>

struct muro{
    int x,y;
    int dano;
    int tipo;
};

void inicia_muro(struct muro M[]);

void pintar_muros(struct muro M[], ALLEGRO_BITMAP* img_muro, ALLEGRO_BITMAP* buffer);
#include "entradas.h"

void inicia_allegro(int largura, int altura){

    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    //set_color_depth(32);
}

void Entrada(ALLEGRO_BITMAP* p) {
    int cont = 0;
    int saida = 0;
    int apertou = 0;

    while (!saida) {
        al_draw_bitmap_region(p, 0, 0, 600, 600, 0, 0, 0);

        al_flip_display();
    
        ALLEGRO_KEYBOARD_STATE keyState;
        al_get_keyboard_state(&keyState);

        if (al_key_down(&keyState, ALLEGRO_KEY_ENTER) || al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
            apertou = 1;
        }

        if (apertou) cont++;

        if (cont > 50) saida = 1;

    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
}
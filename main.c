#include <allegro5/allegro5.h>				
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>																																			
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entradas.h"
#include "elementos.h"

#define LARGURA 600
#define ALTURA  600

int main(){

    inicia_allegro(LARGURA,ALTURA); 

    srand(time(NULL));

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);		
    ALLEGRO_EVENT_QUEUE* eventos = al_create_event_queue();
    ALLEGRO_BITMAP *entrada = al_load_bitmap("entrada.bmp");
    ALLEGRO_DISPLAY* buf = al_create_display(LARGURA,ALTURA);
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_BITMAP *buffer = al_create_bitmap(LARGURA, ALTURA);

    al_register_event_source(eventos, al_get_keyboard_event_source());																																		
	al_register_event_source(eventos, al_get_display_event_source(buf));																															
	al_register_event_source(eventos, al_get_timer_event_source(timer));
    
    ALLEGRO_EVENT evento;
    al_start_timer(timer);
    
    struct NAVE n;
    inicia_nave(&n,"nave.bmp","Bala2.bmp",6,12,30,20,LARGURA/2,ALTURA-70,-4,0,3,2);

    struct NAVE e[60];
    inicia_nave(&e[0],"enemigos.bmp","BalaE.bmp",6,12,25,20,50,80,2,1,1,2);
    acomoda_inimigos(e);

    struct NAVE nv;
    inicia_nave(&nv,"naveV.bmp","BalaE.bmp",6,12,55,20,-100,50,2,4,1,0);

    struct muro m[30];

    inicia_muro(m);
    ALLEGRO_BITMAP *img_muro = al_load_bitmap("muros.bmp");

    //carrega o fundo "Space invaders"
    Entrada(entrada);

    ListaBalas* listaBalas_n = InicializarListaBalas();
    ListaBalas* listaBalas_e = InicializarListaBalas();
    
    int mov = 0;
    //passo do inimigo
    int dir = -5;
    int dir2 = 5;
    //int vel_jogo = 10;
    int aleatorio = rand()%55;
    int cont_Enem = 0;
    int contV = 0;
    int contN = 0;
    int score = 0;

        while(1){
            //contador p/ movimentar inimigos
            cont_Enem++;
            if(contN != 1000){
                contN++;
            }
            al_wait_for_event(eventos,&evento);
            ALLEGRO_KEYBOARD_STATE keyState;
            al_get_keyboard_state(&keyState);

            //limpa o fundo
            al_clear_to_color(al_map_rgb(0, 0, 0));

            //Carrega o score
            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "SCORE: %d",score);
            al_draw_text(font, al_map_rgb(255, 255, 255), 450, 20, 0, "LIVES");
            //carrega os muros
            pintar_muros(m,img_muro,buffer);
            //carrega a nave 
            carregar_nave(&n,0,0,0);
            //Nave vermelha e suas configs.
            carregar_nave(&nv,0,0,0);
            if(contN == 1000){
                nv.x+=1;
                al_draw_bitmap_region(nv.img_nave,0,0,55,20,nv.x,50,0);
                if(!eliminar_bala_objeto(&n,&nv,listaBalas_n)){
                    explosao1(nv,buffer,buf);
                    contN = 0;
                    score+=100;
                    nv.x = -100;
                    carregar_nave(&nv,0,0,0);
                }
                else if(!limitesNV(nv,&dir2)){
                    contN = 0;
                    nv.x = -100;
                    carregar_nave(&nv,0,0,0);
                }
            }
            //Contador de vidas na Tela
            if(n.vida > 0 && n.vida < 5){
                for(int i = 0;i<n.vida;i++){
                    al_draw_bitmap_region(n.img_nave,0,0,30,20,(LARGURA-40)-(i*30),10,0);
                }
            }
            //game over
            if(n.vida == 0){
                break;
            }
            //controles da nave principal
            if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
                if(n.x == 0){
                    al_draw_bitmap_region(n.img_nave,0,0,30,20,n.x,ALTURA-70,0);
                }else{
                    n.x -= 2;
                    al_draw_bitmap_region(n.img_nave,0,0,30,20,n.x,ALTURA-70,0);
                }
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
                if(n.x == 562){
                    al_draw_bitmap_region(n.img_nave,0,0,30,20,n.x,ALTURA-70,0);

                }else{
                    n.x += 2;
                    al_draw_bitmap_region(n.img_nave,0,0,30,20,n.x,ALTURA-70,0);
                }
            }
            //funcoes de disparo
            criar_bala_nave(&n,listaBalas_n);
            disparar(&n,listaBalas_n,buffer);
            
            //funcoes do primeiro disparo dos inimigos
            carregar_inimigos(e,buffer,mov);
            criar_bala_inimigo(e,&aleatorio);
            disparar(&e[aleatorio],listaBalas_e, buffer);
            
            //percorre todos os inimigos e verifica se o tiro da nave acertou algum,
            //no mesmo loop verifica se algum muro foi atingido pelo tiro da nave
            for(int i=0; i<55 ; i++){
                //Todos os inimigos foram mortos reiniciar a proxima fase.
                if(contV == 55){
                    //REINICIAR O JOGO NUMA PROXIMA FASE
                    contV = 0;
                    al_flip_display();
                    //inimigos voltam pra posicao inicial
                    acomoda_inimigos(e);
                    //Nave ganha uma vida
                    n.vida++;
                    al_rest(2);
                    break;
                }
                if(!eliminar_bala_objeto(&n,&e[i],listaBalas_n)){
                    contV++;
                    e[i].vida--;
                    if(e[i].tipo == 2)score+=10;
                    else if (e[i].tipo == 1) score+=20;
                    else score+=40;
                    explosao1(e[i],buffer,buf);
                }
                //verifica se algum tiro atingiu o muro
                eliminar_bala_muro(&n,m,listaBalas_n);
            }

            //Define a veloidade dos oponentes
            if(cont_Enem == 10){
                    cont_Enem = 0;
                    mover_inimigos(e,&mov,&dir);

            }
            
            //verifica colisao entre inimigos e o muro
            //se os inimigos chegarem eh fim de jogo
            if(!colisao_inimigo_muro(e,m)){
                //Game Over!
                break;
            }
    
            //tiro inigimo acertou a nave
            if(!eliminar_bala_objeto(&e[aleatorio],&n,listaBalas_e)){
                explosao2(n,buffer,buf);
                // decrementa a vida
                n.vida--;
                carregar_nave(&n,0,0,0);
            }

            //segundo tiro do inimigo
            int x = rand()%55;
            criar_bala_inimigo(e,&x);
            disparar(&e[x],listaBalas_e,buffer);

            if(!eliminar_bala_objeto(&e[x],&n,listaBalas_e)){
                explosao2(n,buffer,buf);
                // decrementa a vida
                n.vida--;
                carregar_nave(&n,0,0,0);
            }

            //verifica se a bala dos inimigos atingiu os muros
            eliminar_bala_muro(&e[aleatorio],m,listaBalas_e);

            al_flip_display();
            
            if(evento.type == 42 || al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) break;
        }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), ALTURA/2-30 , LARGURA/2, 0, "GAME OVER!");
    al_flip_display();
    al_rest(1);

    al_destroy_font(font);																																													//Destrutor da fonte padrão
	al_destroy_display(buf);																																												//Destrutor da tela
	al_destroy_timer(timer);																																												//Destrutor do relógio
	al_destroy_event_queue(eventos);		

    DestruirListaBalas(listaBalas_n);
    DestruirListaBalas(listaBalas_e);

	return 0;
}

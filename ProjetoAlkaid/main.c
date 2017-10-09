#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

const int SCREEN_V = 600;
const int SCREEN_H = 800;
const int PASSO = 10;

// Comentário de teste

int main() {

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *quadrado = NULL;
	int x = 0;
	int y = 0;
	int key_up = 0, key_down = 0, key_left = 0, key_right = 0;
	int FPS = 60; //modificável para efeitos
	int ALTURA = 40;
	int LARGURA = 20;

	//inicializacao do allegro
	if (!al_init()) {
		printf("failed to initialize allegro!\n");
		return -1;
	}
	else {
		printf("Success to initialize allegro\n");
	}
	//inicializa timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		printf("failed to create timer!\n");
		return -1;
	}
	else {
		printf("Success to create timer\n");
	}
	//inicializa display
	display = al_create_display(SCREEN_H, SCREEN_V);
	if (!display) {
		printf("failed to create display!\n");
		return -1;
	}
	else {
		printf("Success to create display\n");
	}
	//inicializa quadrado
	quadrado = al_create_bitmap(LARGURA, ALTURA);
	if (!quadrado) {
		printf("failed to create bitmap!\n");
		return -1;
	}
	else {
		printf("Success to create bitmap\n");
	}

	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if (!event_queue) {
		printf("failed to create event_queue!\n");
		return -1;
	}
	else {
		printf("Success to create event_queue!\n");
	}

	al_set_target_bitmap(quadrado);
	al_clear_to_color(al_map_rgb(0, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(100, 100, 100));

	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_start_timer(timer);
	al_draw_bitmap(quadrado, x, y, 0);
	ALLEGRO_BITMAP *image = al_load_bitmap("windows.jpg");
	al_draw_bitmap(image, 0, 0, 0);
	al_flip_display();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

			switch (ev.mouse.button) {
			case 1:
				if (ev.mouse.x > x && ev.mouse.y > y && ev.mouse.x < (x + LARGURA) && ev.mouse.y < (y + ALTURA)) {
					LARGURA++;
					ALTURA++;
					printf("Clique no quadrado\n");
					al_destroy_bitmap(quadrado);
					quadrado = al_create_bitmap(LARGURA, ALTURA);
				}
				//printf("EVENTO MOUSE DOWN - DIREITO(%d)\n",ev.mouse.x);
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key_up++;
				break;
			case ALLEGRO_KEY_DOWN:
				key_down++;
				break;
			case ALLEGRO_KEY_LEFT:
				key_left++;
				break;
			case ALLEGRO_KEY_RIGHT:
				key_right++;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key_up = 0;
				break;
			case ALLEGRO_KEY_DOWN:
				key_down = 0;
				break;
			case ALLEGRO_KEY_LEFT:
				key_left = 0;
				break;
			case ALLEGRO_KEY_RIGHT:
				key_right = 0;
				break;
			}
		}

		if (key_up)y--;
		if (key_down)y++;
		if (key_left)x--;
		if (key_right) {
			key_right++;
			if (key_right < 10) {
				x += 6;
			}
			else {
				x++;
			}
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (x < 0) x = 0;
			if (x > SCREEN_H - LARGURA) x = SCREEN_H - LARGURA;
			if (y < 0) y = 0;
			if (y > SCREEN_V - ALTURA) y = SCREEN_V - ALTURA;
			al_clear_to_color(al_map_rgb(100, 100, 100));
			al_draw_bitmap(image, 0, 0, 0);
			al_draw_bitmap(quadrado, x, y, 0);
			al_flip_display();
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
	}

	//al_destroy_bitmap(quadrado);
	//al_destroy_timer(timer);
	al_destroy_display(display);
	//al_destroy_event_queue(event_queue);


	system("PAUSE");
	printf("Execution Finished\n");

}

//teste commit

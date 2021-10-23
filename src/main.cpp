#include <stdio.h> // printf

// ↓ deve ser movido para outro arquivo
#include <SDL2/SDL.h>

void iniciaSDL();
SDL_Window* novaJanela();

int main() {
	printf("Olá mundo!\n");
	SDL_Log("Olá SDL2");

	iniciaSDL();
	SDL_Window *J 	= novaJanela();
	SDL_Renderer *R	=	NULL;


	return 0;
}

void iniciaSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR: SDL2 couldn't init: %s", SDL_GetError());
	}
}

SDL_Window* novaJanela() {
	return SDL_CreateWindow( "Janela", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640,480, SDL_WINDOW_SHOWN);
}

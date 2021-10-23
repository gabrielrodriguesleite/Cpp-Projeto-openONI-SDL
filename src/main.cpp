#include <stdio.h> // printf

// ↓ deve ser movido para outro arquivo
#include <SDL2/SDL.h>
// http://wiki.libsdl.org/CategoryAPI

#include "SDL_FontCache.h"

void iniciaSDL();
SDL_Window* novaJanela();
SDL_Renderer* novoRender(SDL_Window* janela);
void limpaTela(SDL_Renderer* R, SDL_Color = SDL_Color{128, 128, 128, 255});

int main() {
	printf("Olá mundo!\n");
	SDL_Log("Olá SDL2");

	iniciaSDL();
	SDL_Window *J 	= novaJanela();
	SDL_Renderer *R	=	novoRender(J);

	SDL_Texture *bitmap = SDL_CreateTextureFromSurface(R, SDL_LoadBMP("assets/Icon.1_24.bmp"));
	FC_Font* fonte = FC_CreateFont();
	FC_LoadFont(fonte, R, "assets/Mini Story.ttf", 20,
		FC_MakeColor(255, 0, 0, 255), TTF_STYLE_NORMAL);

	int dFPS = 60;
	int dDelta = 1000/dFPS; // desired time b/w frames

	SDL_Event E;
	SDL_bool rodar = SDL_TRUE;
	while(rodar) {
		int starttick = SDL_GetTicks();

		while(SDL_PollEvent(&E)){
			switch(E.type) {
				case SDL_QUIT: rodar = SDL_FALSE; break;
			}
		}

		SDL_RenderClear(R);
		SDL_RenderCopy(R, bitmap, NULL, NULL);

		int delta = SDL_GetTicks() - starttick;
		int FPS = 1000/(dDelta - delta);
		FC_Draw(fonte, R, 0, 0, "FPS: %d", FPS);

		SDL_RenderPresent(R);

		if (delta < dDelta) SDL_Delay(dDelta - delta);

//		fpsDelay = ;
//		SDL_Delay(fpsDelay);
		//SDL_Delay(50/3); //1000/60


	}

	SDL_DestroyRenderer(R);
	SDL_DestroyWindow(J);
	SDL_Quit();
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

SDL_Renderer* novoRender(SDL_Window* janela) {
	if(janela == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR: SDL2 couldn't create window: %s", SDL_GetError());
	}
	return SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
}

void limpaTela(SDL_Renderer* R, SDL_Color cor) {
	SDL_SetRenderDrawColor(R, cor.r, cor.g, cor.b, 255);
	SDL_RenderClear(R);
	SDL_RenderPresent(R);
}






// https://opengameart.org/
// http://wiki.libsdl.org/SDL_CreateRenderer
// https://dotnettutorials.net/lesson/references/
// https://www.programiz.com/cpp-programming/default-argument
// https://klebermota.eti.br/2017/06/10/tutorial-de-sdl-parte-25-definindo-o-frame-rate-manualmente/
































//

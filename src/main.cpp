#include <stdio.h> // printf

// ↓ deve ser movido para outro arquivo
#include <SDL2/SDL.h>
// http://wiki.libsdl.org/CategoryAPI

#include "SDL_FontCache.h"

void iniciaSDL();
SDL_Window* novaJanela();
SDL_Renderer* novoRender(SDL_Window* janela);
void limpaTela(SDL_Renderer* R, SDL_Color = SDL_Color{128, 128, 128, 255});
float controleFPS(Uint32& inicioT);

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

	SDL_Event E;
	SDL_bool rodar = SDL_TRUE;

	Uint32 frames = 0;
	Uint32 deltaT60F = SDL_GetTicks();
	float FPS = 60;

	Uint32 inicioT = SDL_GetTicks();

	while(rodar) {

		while(SDL_PollEvent(&E)){
			switch(E.type) {
				case SDL_QUIT: rodar = SDL_FALSE; break;
			}
		}

		SDL_RenderClear(R);
		SDL_RenderCopy(R, bitmap, NULL, NULL);

		// display FPS
		frames++;
		if (frames >= 60) {
			Uint32 tempoTotalMS = SDL_GetTicks() - deltaT60F;
			FPS = 60000.0f / tempoTotalMS;
			frames -= 60;
			deltaT60F = SDL_GetTicks();
		}
//
//		Uint32 fimT = (SDL_GetTicks()-inicioT);
//		float delay = 50/3 - fimT;
//		if (delay < 0) delay = 0;
//		SDL_Delay(delay);
//		inicioT = SDL_GetTicks();

//		controleFPS(inicioT);

		FC_Draw(fonte, R, 0, 0, "FPS: %.2f, Delay: %.2f", FPS, controleFPS(inicioT));
		SDL_RenderPresent(R);

		SDL_Delay(14);

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

float controleFPS(Uint32& inicioT) {
		Uint32 fimT = (SDL_GetTicks()-inicioT);
		float delay = 50/3.0f - fimT;
		if (delay < 0) delay = 0;
		if (delay > 50/3.0f) delay = 50/3.0f;
		SDL_Delay(delay);
		inicioT = SDL_GetTicks();
		return delay;
}




// https://opengameart.org/
// http://wiki.libsdl.org/SDL_CreateRenderer
// https://dotnettutorials.net/lesson/references/
// https://www.programiz.com/cpp-programming/default-argument
// https://klebermota.eti.br/2017/06/10/tutorial-de-sdl-parte-25-definindo-o-frame-rate-manualmente/
































//

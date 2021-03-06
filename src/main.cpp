#include <stdio.h> // printf

// ↓ deve ser movido para outro arquivo	 
#include <SDL2/SDL.h>
// http://wiki.libsdl.org/CategoryAPI

#include "SDL_FontCache.h"

#include "FPS.h"

void iniciaSDL();
SDL_Window* novaJanela();
SDL_Renderer* novoRender(SDL_Window* janela);
void limpaTela(SDL_Renderer* R, SDL_Color = SDL_Color{128, 128, 128, 255});
float controleFPS(Uint32& inicioT);

int main(int argc, char const *argv[]) {
	printf("Olá mundo!\n");
	SDL_Log("Olá SDL2.\n argc: %d, argv: %s", argc, argv[argc-1] ); // para ser usado quando tentar abrir arquivo pela linha de programa

	iniciaSDL();
	SDL_Window *J 	= novaJanela();
	SDL_Renderer *R	=	novoRender(J);

	// FPS CLASSE:
	FPS fps(SDL_GetTicks(), 60);

	// assets management
	// configs

	// textures
	SDL_Texture *bitmap = SDL_CreateTextureFromSurface(R, SDL_LoadBMP("assets/Icon.1_24.bmp"));
	// fonts
	FC_Font* fonte = FC_CreateFont();
	FC_LoadFont(fonte, R, "assets/Mini Story.ttf", 20,
		FC_MakeColor(255, 0, 0, 255), TTF_STYLE_NORMAL);

	// sounds

	// saves

	// visualizador imagens
	float nivelZoom = 1.0;
	
	SDL_Rect textureRect;
	SDL_QueryTexture(bitmap, NULL, NULL, &textureRect.w, &textureRect.h);

	SDL_Rect projecao;
	SDL_Point projPos = {0, 0};

	// main loop
	SDL_bool rodar = SDL_TRUE;
	while(rodar) {
		SDL_Event E;

		while(SDL_PollEvent(&E)){
			switch(E.type) {
				case SDL_QUIT: rodar = SDL_FALSE; break;
				case SDL_MOUSEWHEEL:
					if(E.wheel.y > 0) nivelZoom += .1f * nivelZoom;
					else if(E.wheel.y < 0) nivelZoom -= .1f * nivelZoom;
					break;
				case SDL_KEYDOWN:
					switch(E.key.keysym.sym) {
						case SDLK_UP:			projPos.y -= .1 * projecao.h; break;
						case SDLK_DOWN:		projPos.y += .1 * projecao.h; break;
						case SDLK_LEFT:		projPos.x -= .1 * projecao.w; break;
						case SDLK_RIGHT:	projPos.x += .1 * projecao.w; break;
					}
			}
		}

		// Lógica

		// Controle FPS
		// atualiza contagem de frames
		SDL_Delay(fps.update(SDL_GetTicks()));

		// Desenhar
		SDL_GetWindowSize(J, &projecao.x, &projecao.y);
		projecao.x = projecao.x / 2 - textureRect.w / 2 * nivelZoom + projPos.x;
		projecao.y = projecao.y / 2 - textureRect.h / 2 * nivelZoom + projPos.y;
		projecao.w = textureRect.w * nivelZoom;
		projecao.h = textureRect.h * nivelZoom;

		SDL_RenderClear(R);
		SDL_RenderCopy(R, bitmap, NULL, &projecao);

		// display FPS
		FC_Draw(fonte, R, 0, 0, "FPS: %.2f", fps.get());
		SDL_RenderPresent(R);
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
// https://thenumbat.github.io/cpp-course/index.html
// https://dotnettutorials.net/lesson/references/
// https://www.programiz.com/cpp-programming/default-argument
// https://klebermota.eti.br/2017/06/10/tutorial-de-sdl-parte-25-definindo-o-frame-rate-manualmente/
// https://thenumbat.github.io/cpp-course/sdl2/08/08.html // fps vsync perf physics & animation times
// https://linux.m2osw.com/creating-new-git-repository

// https://wiki.libsdl.org/SDL_atomic_t // fps de verdade































//

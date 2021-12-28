#include <stdio.h> // printf

// ↓ deve ser movido para outro arquivo	 
#include <SDL2/SDL.h>
// http://wiki.libsdl.org/CategoryAPI

#include "SDL_FontCache.h"

// TRANSFORMAR O FPS EM CLASSE:
// O metodo update é chamado cada vez que desenha a tela - ele atualiza os valores e devolve o delay necessario
// O metodo get devolve o valor do FPS calculado
class FPS
{
private:
	/* data */
	float fps_calculado;
	int fps_desejado;
	int frames;
	Uint32 tick_antigo;
	Uint32 ticks_60f;
public:
	FPS(Uint32, int);
	~FPS();
	float update(Uint32);
	float get();
};

FPS::FPS(Uint32 tick, int _fps_desejado) {
	fps_calculado = 60.0;
	frames = 0;
	tick_antigo = tick;
	fps_desejado = _fps_desejado;
	ticks_60f = 0;
}

FPS::~FPS()
{
}

float FPS::update(Uint32 tick_atual) {
	// essa função devolve o delay que deve haver até que este quadro seja desenhado
	// deve ficar antes de desenhar o quadro mas logo após a execução da lógica

	// 1000 / 60 = tempo de 1 frame em ms para um fps de 60
	// if (frames % 60) { SDL_Log("1 frame = %dms" , tick_atual - tick_antigo); }
	float delay_d = 1000.0 / fps_desejado;
	int delay_m = tick_atual - tick_antigo;

	++frames;
	if( frames >= fps_desejado) { // atualiza ~ 1 / seg
		frames -= fps_desejado;
		fps_calculado = 1000.0 / delay_m; // quantas vezes o frame atual cabe em 1s
	}
	
	tick_antigo = tick_atual;
	float delay = delay_d;
	// demorou demais
	if ( delay_m > delay_d ) {
		delay = delay_d - (delay_m - delay_d);
		if (delay < 0){ return 1.0; }
	}
	return delay;
}

float FPS::get() { return fps_calculado; }

// --- FIM DA CLASSE FPS ---

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

	// FPS display
	Uint32 frames = 0;
	Uint32 deltaT60F = SDL_GetTicks();
	float FPSv = 60;

	// FPS control
	Uint32 inicioT = SDL_GetTicks();

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
		frames++;
		if (frames >= 60) {
			Uint32 tempoTotalMS = SDL_GetTicks() - deltaT60F;
			FPSv = 60000.0f / tempoTotalMS;
			frames -= 60;
			deltaT60F = SDL_GetTicks();
		}
		// FC_Draw(fonte, R, 0, 0, "FPS: %.2f, Delay: %.2f", FPSv, controleFPS(inicioT));
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
// https://thenumbat.github.io/cpp-course/index.html
// https://dotnettutorials.net/lesson/references/
// https://www.programiz.com/cpp-programming/default-argument
// https://klebermota.eti.br/2017/06/10/tutorial-de-sdl-parte-25-definindo-o-frame-rate-manualmente/
// https://thenumbat.github.io/cpp-course/sdl2/08/08.html // fps vsync perf physics & animation times
// https://linux.m2osw.com/creating-new-git-repository

// https://wiki.libsdl.org/SDL_atomic_t // fps de verdade































//

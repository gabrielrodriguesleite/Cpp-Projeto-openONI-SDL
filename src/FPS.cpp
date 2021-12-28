#include "FPS.h"

FPS::FPS(Uint32 tick, int _fps_desejado) {
	fps_calculado = float(_fps_desejado);
	frames = 0;
	tick_antigo = tick;
	fps_desejado = _fps_desejado;
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
/*
 TRANSFORMAR O FPS EM CLASSE:
 O metodo update é chamado cada vez que desenha a tela -- ele atualiza os valores e devolve o delay necessario
 O metodo get devolve o valor do FPS calculado
	Uso:
	INICIALIZAÇÃO - Crie um novo objeto no com:
		FPS fps(SDL_GetTicks(), 60);
		sendo 60 o fps desejado.

	ATUALIZAÇÃO - Dentro do loop principal:
	logica();
	SDL_Delay(fps.update(SDL_GetTicks));
	desenho();

	DADOS - A qualquer momento chame fps.get() para receber o valor aproximado em float do último calculo de fps
*/
#include <SDL2/SDL.h>

class FPS {
private:
	float fps_calculado;
	int fps_desejado;
	int frames;
	Uint32 tick_antigo;
public:
	FPS(Uint32, int); // recebe os ticks atualizados do SDL e um valor para o fps desejado
	~FPS();
	float update(Uint32); // recebe os ticks atualizados do SDL e devolve o delay para o próximo quadro
	float get(); // devolve um float com fps aproximado do último cálculo
};
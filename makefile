# $make app

FONTES			= src/*
BINARIO			= bin/linux/openONI
COMPILADOR	= g++
COMP_OP			= -w -no-pie
LINK_OP			= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_gfx
app: $(FONTES)
	mkdir -p bin/linux/
	clear
	$(COMPILADOR) $(FONTES) $(COMP_OP) $(LINK_OP) -o $(BINARIO)
	du -h $(BINARIO)
	./$(BINARIO)


# fim do MAKEFILE

# http://wiki.libsdl.org/Installation
# gcc -o myprogram myprogram.c `sdl2-config --cflags --libs`
# https://github.com/libsdl-org/SDL/blob/main/docs/README-linux.md

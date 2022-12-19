.PHONY: zedit
zedit: src/main.cpp
	g++ -std=c++17 src/main.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -o out/zedit


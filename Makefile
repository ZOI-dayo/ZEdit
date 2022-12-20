.PHONY: zedit
zedit: src/main.cpp
	g++ -std=c++17 src/main.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -o out/zedit
debug: src/main.cpp
	g++ -std=c++17 src/main.cpp -g -O0 `sdl2-config --cflags --libs` -lSDL2_ttf -o out/zedit_debug

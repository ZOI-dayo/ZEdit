.PHONY: zedit
zedit: src/main.cpp
	g++ src/main.cpp `sdl2-config --cflags --libs` -o out/zedit

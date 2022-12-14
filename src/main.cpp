#include <stdlib.h>
#include <SDL.h>

int main(int argc, char * args[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *win = SDL_CreateWindow("ZEdit", 0, 0, 1280, 720, SDL_WINDOW_MAXIMIZED);
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(ren, 128, 0, 0, 255);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);
  bool quit = false;

  SDL_Event e;

  while( !quit ) {
    while( SDL_PollEvent( &e ) != 0 ) {
      if( e.type == SDL_QUIT ) {
        quit = true;
      }
    }
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

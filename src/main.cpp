#include <SDL.h>
#include <SDL_ttf.h>
#include <algorithm>
#include <iostream>

#include "space/textspace.cpp"
#include "util/fontloader.cpp"

#define FONT_PATH "/Users/zoi/Library/Fonts/Cica-Regular.ttf"

int main(int, char **const) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_Window *window = SDL_CreateWindow("ZEdit",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Event ev;
  PixelSize::init(window);

  FontLoader::load(FONT_PATH);
  TextSpace textspace_test(renderer, "Hello World!aaaaaaaaaaa𠮷aaaaああああああああaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", FontLoader::getFont("Cica-Regular.ttf", 14), (SDL_Color){255,255,255,255});
  /* TTF_SetFontOutline(font, 1); // 縁取り文字*/

  // surface = TTF_RenderUTF8_Blended(font, "Hello World!", (SDL_Color){255,255,255,255});

  // texture = SDL_CreateTextureFromSurface(renderer, surface);

  bool isRunning = true;
  while(isRunning){
    SDL_SetRenderDrawColor(renderer, 23, 24, 34, 255);
    SDL_RenderClear(renderer);
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) {
        isRunning = false;
      }
    }
    /*
       int iw,ih;
    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
    SDL_Rect txtRect = (SDL_Rect){0, 0, iw, ih};
    SDL_Rect pasteRect = (SDL_Rect){100, 100, iw, ih};
    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);*/
    textspace_test.render();
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  FontLoader::unload();
  TTF_Quit();
  return 0;
}

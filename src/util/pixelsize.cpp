#ifndef ZEDIT_CLASS_PIXELSIZE_DEFINED

#define ZEDIT_CLASS_PIXELSIZE_DEFINED

#include <SDL.h>
#include <iostream>
#include <exception>
#include <stdexcept>

class PixelSize {
  private:
    static float dpi_rate;
  public:
    PixelSize();
    PixelSize(int value);
    static void init(SDL_Window *window);
    int value;
};

float PixelSize::dpi_rate = -1;

PixelSize::PixelSize() {
  value = 0;
}
PixelSize::PixelSize(int value) {
  if(dpi_rate < 0) throw std::runtime_error("PixelSize is not initialized.");
  this->value = value * dpi_rate;
}
void PixelSize::init(SDL_Window *window) {
  if(dpi_rate > 0) {
    std::cerr << "[Warning] PixelSize is already initialized. (L" << __LINE__ << ")" << std::endl;
    return;
  }
  int w, pw;
  SDL_GetWindowSize(window, &w, NULL);
  SDL_GetWindowSizeInPixels(window, &pw, NULL);
  dpi_rate = ((float)pw) / w;
}

#endif

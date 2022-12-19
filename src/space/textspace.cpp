#ifndef ZEDIT_CLASS_TEXTSPACE_DEFINED

#define ZEDIT_CLASS_TEXTSPACE_DEFINED

#include "space.cpp"
#include "../util/pixelsize.cpp"
#include <string>
#include <SDL_ttf.h>

class TextSpace : public Space {
  private:
    std::string text;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    PixelSize outline;
  public:
    TextSpace(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color color, PixelSize outline);
    ~TextSpace();
    void render();
};

TextSpace::TextSpace(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color color, PixelSize outline) {
  this->renderer = renderer;
  this->text = text;
  this->font = font;
  this->outline = outline;

  if(TTF_GetFontOutline(font) != outline.value) TTF_SetFontOutline(font, outline.value);
  surface = TTF_RenderUTF8_Blended(font, text.data(), color);

  texture = SDL_CreateTextureFromSurface(renderer, surface);
}

TextSpace::~TextSpace() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void TextSpace::render() {
  int iw,ih;
  SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
  SDL_Rect txtRect = (SDL_Rect){0, 0, iw, ih};
  SDL_Rect pasteRect = (SDL_Rect){100, 100, iw, ih};
  SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
}

#endif

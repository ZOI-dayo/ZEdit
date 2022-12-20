#ifndef ZEDIT_CLASS_TEXTSPACE_DEFINED

#define ZEDIT_CLASS_TEXTSPACE_DEFINED

#include "space.cpp"
#include "../util/pixelsize.cpp"
#include "../util/textconverter.cpp"
#include <SDL_ttf.h>

class TextSpace : public Space {
  private:
    std::vector<std::vector<char32_t>> text = std::vector<std::vector<char32_t>>({{}});
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    PixelSize outline;
    std::pair<int, int> cursorLoc;
  public:
    TextSpace(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color color): TextSpace(renderer, text, font, color, PixelSize()){};
    TextSpace(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color color, PixelSize outline);
    ~TextSpace();
    void render();
    void insertText(std::string value);
};


TextSpace::TextSpace(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color color, PixelSize outline) {
  this->renderer = renderer;
  this->font = font;
  this->outline = outline;

  std::vector<char32_t> u32str = TextConverter::u8to32(text);
  for(const char32_t c : u32str) {
    this->text.back().emplace_back(c);
    if(c == '\n') this->text.emplace_back();
  }

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

// TODO カーソル位置の考慮をする
void TextSpace::insertText(std::string value) {
  std::vector<char32_t> u32str = TextConverter::u8to32(value);
  for(const char32_t c : u32str) {
    this->text.back().emplace_back(c);
    if(c == '\n') this->text.emplace_back();
  }
}

#endif

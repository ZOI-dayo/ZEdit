#ifndef ZEDIT_CLASS_FONTLOADER_DEFINED

#define ZEDIT_CLASS_FONTLOADER_DEFINED

#include <map>
#include <string>
#include <filesystem>
#include <SDL_ttf.h>
#include <iostream>
#include <stdexcept>

#include "pixelsize.cpp"

class FontLoader {
  private:
    static std::map<std::string, std::string> font_path;
    static std::map<std::string, std::map<int, TTF_Font*>> font_data;
  public:
    ~FontLoader();
    static void load(std::string file_path);
    static void load(std::string file_path, std::string name);
    static TTF_Font* getFont(std::string name, int size);
    static void unload();
    static void unload(std::string name);
};

std::map<std::string, std::string> FontLoader::font_path = std::map<std::string, std::string>();
std::map<std::string, std::map<int, TTF_Font*>> FontLoader::font_data = std::map<std::string, std::map<int, TTF_Font*>>();

FontLoader::~FontLoader() {
  unload();
}

void FontLoader::load(std::string file_path) {
  load(file_path, file_path.substr(file_path.find_last_of('/') + 1));
}

void FontLoader::load(std::string file_path, std::string name) {
  if(font_path.count(name) != 0) {
    std::cerr << "[Warning] Font \"" << name << "\" already loaded." << std::endl;
    return;
  }
  font_path[name] = file_path;
  // font_data[name] = std::map<int, TTF_Font *>({});
}

TTF_Font* FontLoader::getFont(std::string name, int size) {
  if(font_path.count(name) == 0) {
    throw std::runtime_error("Font named \"" + name + "\" is not added.");
  }
  if(font_data[name].count(size) == 0) {
    font_data[name][size] = TTF_OpenFont(font_path[name].data(), PixelSize(size).value);
  }
  return font_data[name][size];
}

void FontLoader::unload() {
  auto saved_font_path = font_path;
  for(std::pair<std::string, std::string> p : saved_font_path) {
    unload(p.first);
  }
}

void FontLoader::unload(std::string name) {
  if(font_path.count(name) == 0) {
    std::cerr << "[Warning] Try to unload Font \"" << name << "\", but not loaded." << std::endl;
    return;
  }
  for(std::pair<int, TTF_Font*> p : font_data[name]) {
    TTF_CloseFont(p.second);
  }
  font_path.erase(name);
  font_data.erase(name);
}

#endif

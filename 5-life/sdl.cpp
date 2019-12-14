#include "sdl.hpp"
#include "window.hpp"

#include <cassert>

Sdl::Sdl() {
  assert(!SDL_Init(SDL_INIT_VIDEO));
}

Sdl::~Sdl() {
  SDL_Quit();
}

Window Sdl::create_window(const char* title, int width, int height, int texture_width, int texture_height) {
  SDL_Window* window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    width, height,
    0
  );

  return Window(window, texture_width, texture_height);
}

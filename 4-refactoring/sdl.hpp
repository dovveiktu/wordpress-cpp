#pragma once

#include <SDL2/SDL.h>
#include "window.hpp"

class Sdl {
public:
  Sdl();
  ~Sdl();

  Window create_window(const char* title, int width, int height, int texture_width, int texture_height);
};

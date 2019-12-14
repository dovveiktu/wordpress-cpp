#pragma once

#include <vector>
#include <cstdint>

#include <SDL2/SDL.h>

struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};

class Window {
private:
  int w;
  int h;
  bool running;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;

  std::vector<int> pixel_data;

public:
  Window(SDL_Window* window, int texture_width, int texture_height);
  ~Window();

  int width() const;
  int height() const;
  bool is_running() const;

  void update();
  void set_pixel(int x, int y, const Pixel& pixel);
  void render();
};

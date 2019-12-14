#include "window.hpp"

#include <cassert>
#include <iostream>

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
  r(r),g(g), b(b), a(a) {}

Window::Window(SDL_Window* window, int texture_width, int texture_height):
  w(texture_width), h(texture_height),
  running(true),
  window(window),
  pixel_data(texture_width * texture_height * sizeof(int), 0)
{
  renderer = SDL_CreateRenderer(window, -1, 0);

  assert(renderer != nullptr);

  texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
    w, h
  );

  assert(texture != nullptr);
}

Window::~Window() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

int Window::width() const {
  return w;
}

int Window::height() const {
  return h;
}

bool Window::is_running() const {
  return running;
}

void Window::update() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        running = false;
        break;
    }
  }
}

void Window::set_pixel(int x, int y, const Pixel& pixel) {
  int* ptr = pixel_data.data() + (y * w + x);

  *ptr = pixel.a << 24 |
         pixel.r << 16 |
         pixel.g <<  8 |
         pixel.b;
}

void Window::render() {
  SDL_UpdateTexture(texture, nullptr, pixel_data.data(), w * sizeof(int));
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
}

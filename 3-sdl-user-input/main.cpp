#include <SDL2/SDL.h>
#include <cstring>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow(
    "SDL Window",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    640, 480,
    0
  );

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

  unsigned int* pixels = new unsigned int[640 * 480 * sizeof(unsigned int)];
  std::memset(pixels, 255, 640 * 480 * sizeof(unsigned int));

  bool should_quit = false;
  SDL_Event event;
  bool mouse_down = false;

  while(!should_quit) {
    SDL_UpdateTexture(texture, nullptr, pixels, 640 * sizeof(unsigned int));

    SDL_WaitEvent(&event);

    switch(event.type) {
      case SDL_QUIT:
        should_quit = true;
        break;
      case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = false;
          break;
        }
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = true;
        }
      case SDL_MOUSEMOTION:
        if (mouse_down) {
          int x = event.motion.x;
          int y = event.motion.y;

          for(int x_offset = -5; x_offset < 5; x_offset++) {
            for(int y_offset = -5; y_offset < 5; y_offset++) {
              int pixel_x = x + x_offset;
              int pixel_y = y + y_offset;

              if(pixel_x >= 0 && pixel_x < 640 && pixel_y >= 0 && pixel_y < 480) {
                pixels[pixel_y * 640 + pixel_x] = 0;
              }
            }
          }
        }
        break;
    }

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
  }

  delete[] pixels;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

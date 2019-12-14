#include <SDL2/SDL.h>

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow(
    "SDL Window",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    320, 240,
    0
  );

  bool should_quit = false;
  SDL_Event event;

  while(!should_quit) {
    SDL_WaitEvent(&event);

    switch(event.type) {
      case SDL_QUIT:
        should_quit = true;
        break;
    }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();
}

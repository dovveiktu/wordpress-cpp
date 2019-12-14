#include "sdl.hpp"
#include "window.hpp"

#include <random>

int main() {
  Sdl sdl;

  Window window = sdl.create_window("Random pixels", 300, 200, 300, 200);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);

  for(int x = 0; x < window.width(); x++) {
    for(int y = 0; y < window.height(); y++) {
      int r = dis(gen);
      int g = dis(gen);
      int b = dis(gen);
      Pixel random(r, g, b, 255);
      window.set_pixel(x, y, random);
    }
  }

  window.render();

  while(window.is_running()) {
    window.update();
  }
}

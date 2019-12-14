#include "sdl.hpp"
#include "window.hpp"

#include <random>
#include <vector>
#include <functional>



int count_neighbours(int x, int y, const std::vector<bool>& grid, int width, int height) {
  int count = 0;

  for(int x_pos = x - 1; x_pos <= x + 1; x_pos++) {
    for(int y_pos = y - 1; y_pos <= y + 1; y_pos++) {
      if(x_pos >= 0 && x_pos < width && y_pos >= 0 && y_pos < height) {
        if(grid[y_pos * width + x_pos]) {
          count++;
        }
      }
    }
  }

  if(grid[y * width + x]) {
    count--;
  }

  return count;
}

void next_generation(std::vector<bool>& current, std::vector<bool>& next, int width, int height) {
  for(int x = 0; x < width; x++) {
    for(int y = 0; y < height; y++) {
      int neighbours = count_neighbours(x, y, current, width, height);

      int idx = y * width + x;

      if(neighbours == 3) {
        next[idx] = true;
      } else if(neighbours == 2) {
        next[idx] = current[idx];
      } else {
        next[idx] = false;
      }
    }
  }

  current.swap(next);
}

int main() {
  Sdl sdl;

  int window_width = 512;
  int window_height = 512;
  int grid_width = 64;
  int grid_height = 64;

  Window window = sdl.create_window("Game of Life", window_width, window_height, grid_width, grid_height);

  Pixel alive(255, 255, 255, 255);
  Pixel dead(0, 0, 0, 255);

  int size = grid_width * grid_height;

  std::vector<bool> current(size);
  std::vector<bool> next(size);

  auto rand_bool = std::bind(
    std::uniform_int_distribution<>(0, 1),
    std::default_random_engine()
  );

  for(int i = 0; i < current.size(); i++) {
      current[i] = rand_bool();
  }

  while(window.is_running()) {
    window.update();

    for(int x = 0; x < grid_width; x++) {
      for(int y = 0; y < grid_height; y++) {
        int idx = y * grid_width + x;

        if(current[idx]) {
          window.set_pixel(x, y, alive);
        } else {
          window.set_pixel(x, y, dead);
        }
      }
    }

    window.render();
    next_generation(current, next, grid_width, grid_height);

    SDL_Delay(100);
  }
}

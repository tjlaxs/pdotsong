#include "SDL.h" 

void Pong_GenerateOutput(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(r);

  SDL_SetRenderDrawColor(r, 255, 255, 0, SDL_ALPHA_OPAQUE);

  SDL_Rect top_wall {
    0,
    0,
    1024,
    15
  };
  SDL_RenderFillRect(r, &top_wall);

  SDL_Rect bottom_wall {
    0,
    749,
    1024,
    15
  };
  SDL_RenderFillRect(r, &bottom_wall);

  SDL_RenderPresent(r);
}

void Pong_UpdateGame() {}

void Pong_ProcessInput(bool *run) {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
      case SDL_QUIT:
        (*run) = false;
        break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    (*run) = false;
  }
}

void Pong_GameLoop(bool pong_running, SDL_Renderer *r) {
  while (pong_running) {
    Pong_ProcessInput(&pong_running);
    Pong_UpdateGame();
    Pong_GenerateOutput(r);
  }
}

int main(int argc, char *argv[])
{
  bool pong_running = true;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1024,
    768,
    0
  );

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  Pong_GameLoop(pong_running, renderer);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}


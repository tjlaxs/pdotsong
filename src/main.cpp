#include "SDL.h" 

class Pong {
  public:
    bool running;
    SDL_Renderer *renderer;
    int thickness = 15;
};

void Pong_GenerateOutput(Pong *p) {
  SDL_SetRenderDrawColor(p->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(p->renderer);

  SDL_SetRenderDrawColor(p->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

  SDL_Rect top_wall {
    0,
    0,
    1024,
    p->thickness
  };
  SDL_RenderFillRect(p->renderer, &top_wall);

  SDL_Rect bottom_wall {
    0,
    768 - p->thickness,
    1024,
    p->thickness
  };
  SDL_RenderFillRect(p->renderer, &bottom_wall);

  SDL_RenderPresent(p->renderer);
}

void Pong_UpdateGame() {}

void Pong_ProcessInput(Pong *p) {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
      case SDL_QUIT:
        p->running = false;
        break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    p->running = false;
  }
}

void Pong_GameLoop(Pong *p) {
  while (p->running) {
    Pong_ProcessInput(p);
    Pong_UpdateGame();
    Pong_GenerateOutput(p);
  }
}

int main(int argc, char *argv[])
{
  Pong p;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1024,
    768,
    0
  );

  p.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  Pong_GameLoop(&p);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}


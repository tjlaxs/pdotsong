#include "SDL.h" 

class Pong {
  public:
    bool running = true;
    SDL_Renderer *renderer = NULL;
    int thickness = 15;
    
    void GenerateOutput();
    void UpdateGame();
    void ProcessInput();
};

void Pong::GenerateOutput() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);

  SDL_SetRenderDrawColor(this->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

  SDL_Rect top_wall {
    0,
    0,
    1024,
    this->thickness
  };
  SDL_RenderFillRect(this->renderer, &top_wall);

  SDL_Rect bottom_wall {
    0,
    768 - this->thickness,
    1024,
    this->thickness
  };
  SDL_RenderFillRect(this->renderer, &bottom_wall);

  SDL_RenderPresent(this->renderer);
}

void Pong::UpdateGame() {}

void Pong::ProcessInput(void) {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
      case SDL_QUIT:
        this->running = false;
        break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    this->running = false;
  }
}

void Pong_GameLoop(Pong *p) {
  while (p->running) {
    p->ProcessInput();
    p->UpdateGame();
    p->GenerateOutput();
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


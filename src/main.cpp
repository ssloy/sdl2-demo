#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "fps_counter.h"
#include "sprite.h"

int main() {
    SDL_SetMainReady(); // tell SDL that we handle main function ourselves, comes with the SDL_MAIN_HANDLED macro
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window   *window   = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        std::cerr << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_SetWindowTitle(window, "SDL2 game blank");
    SDL_SetRenderDrawColor(renderer, 210, 255, 179, 255);

    {
        TimeStamp timestamp = Clock::now();
        FPS_Counter fps_counter(renderer);
        while (1) { // main game loop
            SDL_Event event; // handle window closing
            if (SDL_PollEvent(&event) && (SDL_QUIT == event.type || (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym)))
                break; // quit

            SDL_RenderClear(renderer); // re-draw the window
            fps_counter.draw();
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


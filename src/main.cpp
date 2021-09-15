#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "fps_counter.h"
#include "map.h"
#include "player.h"

void main_loop(SDL_Renderer *renderer) {
    FPS_Counter fps_counter(renderer);
    Map map(renderer);
    Player player(renderer);
    TimeStamp timestamp = Clock::now();
    while (1) { // main game loop
        SDL_Event event; // handle window closing
        if (SDL_PollEvent(&event) && (SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym)))
            break; // quit
        player.handle_keyboard(); // no need for the event variable, direct keyboard state polling

        double dt = std::chrono::duration<double>(Clock::now() - timestamp).count();
        if (dt<.02) { // 50 FPS regulation
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        timestamp = Clock::now();

        player.update_state(dt, map); // gravity, movements, collision detection etc

        SDL_RenderClear(renderer); // re-draw the window
        fps_counter.draw();
        player.draw();
        map.draw();
        SDL_RenderPresent(renderer);
    }
} // N.B. fps_counter, map and player objects call their destructors here, thus destroying allocated textures, it must be done prior to destroying the renderer

int main() {
    SDL_SetMainReady(); // tell SDL that we handle main() function ourselves, comes with the SDL_MAIN_HANDLED macro
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

    main_loop(renderer); // all interesting things happen here

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


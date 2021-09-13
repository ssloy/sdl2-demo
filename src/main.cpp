#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "fps_counter.h"
#include "sprite.h"
#include "map.h"
#include "player.h"

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

    { // main loop
        TimeStamp timestamp = Clock::now();
        FPS_Counter fps_counter(renderer);
        Map map(renderer);
        Player player(renderer);
        while (1) { // main game loop
            SDL_Event event; // handle window closing
            if (SDL_PollEvent(&event) && (SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym)))
                break; // quit

            double dt = std::chrono::duration<double>(Clock::now() - timestamp).count();
            if (dt<.02) { // 50 FPS regulation
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }
            timestamp = Clock::now();

            SDL_RenderClear(renderer); // re-draw the window
            fps_counter.draw();
            player.draw();
            map.draw();
            SDL_RenderPresent(renderer);
        }
    } // N.B. these brackets are needed to destroy textures before destroying the renderer

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


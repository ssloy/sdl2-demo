#pragma once
#include "sprite.h"

namespace {
    static const std::chrono::milliseconds UPTADE_CURRENT_FPS{300};
}

struct FPS_Counter {
    FPS_Counter(SDL_Renderer *renderer) : renderer(renderer), numbers(renderer, "numbers.bmp", 24) {}

    void draw() {
        using namespace std::chrono;
        fps_cur++;
        auto dt = duration_cast<milliseconds>(Clock::now() - timestamp);
        if (dt >= UPTADE_CURRENT_FPS) { // every 300 ms update current FPS reading
            fps_prev = static_cast<int>(fps_cur / duration<double>(dt).count() );
            fps_cur = 0;
            timestamp = Clock::now();
        }
        SDL_Rect dst = {4, 16, numbers.m_params.width, numbers.m_params.height}; // first character will be drawn here
        for (const char c : std::to_string(fps_prev)) { // extract individual digits of fps_prev
            SDL_Rect src = numbers.rect(c-'0'); // crude conversion of numeric characters to int: '7'-'0'=7
            SDL_RenderCopy(renderer, numbers.texture, &src, &dst); // draw current digit
            dst.x += numbers.m_params.width + 4; // draw characters left-to-right, +4 for letter spacing (TODO: add padding directly to the .bmp file)
        }
    }

    int fps_cur  = 0; // the FPS readings are updated once in a while; fps_cur is the number of draw() calls since the last reading
    int fps_prev = 0; // and here is the last fps reading
    TimeStamp timestamp = Clock::now(); // last time fps_prev was updated
    SDL_Renderer *renderer; // draw here
    const Sprite numbers;   // "font" file
};


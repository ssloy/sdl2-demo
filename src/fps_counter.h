#include "sprite.h"

struct FPS_Counter {
    FPS_Counter(SDL_Renderer *renderer) : renderer(renderer), numbers(renderer, "numbers.bmp", 24) {}

    void draw() {
        fps_cur++;
        double dt = std::chrono::duration<double>(Clock::now() - timestamp).count();
        if (dt>=.3) { // every 300 ms update current FPS reading
            fps_prev = fps_cur/dt;
            fps_cur = 0;
            timestamp = Clock::now();
        }
        SDL_Rect dst = {4, 16, numbers.width, numbers.height}; // first character will be drawn here
        for (const char c : std::to_string(fps_prev)) { // extract individual digits of fps_prev
            SDL_Rect src = numbers.rect(c-'0'); // crude conversion of numeric characters to int: '7'-'0'=7
            SDL_RenderCopy(renderer, numbers.texture, &src, &dst); // draw current digit
            dst.x += numbers.width + 4; // draw characters left-to-right, +4 for letter spacing (TODO: add padding directly to the .bmp file)
        }
    }

    int fps_cur  = 0; // the FPS readings are updated once in a while; fps_cur is the number of draw() calls since the last reading
    int fps_prev = 0; // and here is the last fps reading
    TimeStamp timestamp = Clock::now(); // last time fps_prev was updated
    SDL_Renderer *renderer; // draw here
    const Sprite numbers;   // "font" file
};


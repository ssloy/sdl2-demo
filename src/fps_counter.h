using Clock = std::chrono::high_resolution_clock;
using TimeStamp = std::chrono::time_point<Clock>;

#include "sprite.h"

struct FPS_Counter {
    FPS_Counter(SDL_Renderer *renderer) : numbers(renderer, std::string(RESOURCES_DIR) + "numbers.bmp", 24), renderer(renderer) {
    }

    void draw() {
        cnt1++;
        double dt = std::chrono::duration<double>(Clock::now() - timestamp).count();
        if (dt>=.3) { // every 300 ms update current FPS reading
            cnt2 = cnt1/dt;
            cnt1 = 0;
            timestamp  = Clock::now();
        }
        std::string str = std::to_string(cnt2); // extract individual digits
        SDL_Rect dst = {4, 4, numbers.width, numbers.height};
        for (const char c : str) { // iterate through the digits
            SDL_Rect src = numbers.rect(c-'0');
            SDL_RenderCopy(renderer, numbers.texture, &src, &dst); // draw current digit
            dst.x += numbers.width + 4;
        }
    }

    int cnt1 = 0, cnt2 = 0;
    Sprite numbers;
    SDL_Renderer *renderer;   // draw here
    TimeStamp timestamp = Clock::now();
};


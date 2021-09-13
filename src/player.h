#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <cmath>
#include "map.h"

struct Player {
    enum States {
        REST=0, TAKEOFF=1, FLIGHT=2, LANDING=3, WALK=4, FALL=5
    };

    Player(SDL_Renderer *renderer) :
        renderer(renderer),
        sprites{Animation(renderer, "../resources/rest.bmp",    256, 1.0, true ),
                Animation(renderer, "../resources/takeoff.bmp", 256, 0.3, false),
                Animation(renderer, "../resources/flight.bmp",  256, 1.3, false),
                Animation(renderer, "../resources/landing.bmp", 256, 0.3, false),
                Animation(renderer, "../resources/walk.bmp",    256, 1.0, true ),
                Animation(renderer, "../resources/fall.bmp",    256, 1.0, true )} {
    }

    void draw() {
        SDL_Rect src = sprites[state].rect(timestamp);
        SDL_Rect dest = { int(x)-sprite_w/2, int(y)-sprite_h, sprite_w, sprite_h };
        SDL_RenderCopyEx(renderer, sprites[state].texture, &src, &dest, 0, nullptr, backwards ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    double x = 150, y = 200; // coordinates of the player
    bool backwards = false;  // left or right

    int state = WALK;
    TimeStamp timestamp = Clock::now();

    const int sprite_w = 256; // size of the sprite on the screen
    const int sprite_h = 128;

    SDL_Renderer *renderer;   // draw here
    std::array<Animation,6> sprites; // sprite sequences to be drawn
};

#endif


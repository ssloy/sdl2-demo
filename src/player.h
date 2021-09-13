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

    void set_state(int s) {
        timestamp = Clock::now();
        state = s;
        if (state==REST)
            vx = 0;
        if (state==WALK)
            vx = backwards ? -150 : 150;
    }

    void handle_keyboard() {
        const Uint8 *kbstate = SDL_GetKeyboardState(NULL);
        if (state==WALK && !kbstate[SDL_SCANCODE_RIGHT] && !kbstate[SDL_SCANCODE_LEFT])
            set_state(REST);
        if (state==REST && (kbstate[SDL_SCANCODE_LEFT] || kbstate[SDL_SCANCODE_RIGHT])) {
            backwards = kbstate[SDL_SCANCODE_LEFT];
            set_state(WALK);
        }
    }

    void update_state(const double dt, const Map &map) {
        double cand_x = x + dt*vx; // candidate coordinates prior to collision detection

        if (!map.is_empty(cand_x/map.tile_w, y/map.tile_h)) { // horizontal collision detection
            int snap = std::round(cand_x/map.tile_w)*map.tile_w; // snap the coorinate to the boundary of last free tile
            cand_x = snap + (snap>cand_x ? 1 : -1);              // be careful to snap to the left or to the right side of the free tile
            vx = 0; // stop
        }

        x = cand_x; // final coordinates post-collision detection
    }

    void draw() {
        SDL_Rect src = sprites[state].rect(timestamp);
        SDL_Rect dest = { int(x)-sprite_w/2, int(y)-sprite_h, sprite_w, sprite_h };
        SDL_RenderCopyEx(renderer, sprites[state].texture, &src, &dest, 0, nullptr, backwards ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }

    double x = 150, y = 200; // coordinates of the player
    double vx = 0, vy = 0;   // speed
    bool backwards = false;  // left or right

    int state = REST;
    TimeStamp timestamp = Clock::now();

    const int sprite_w = 256; // size of the sprite on the screen
    const int sprite_h = 128;

    SDL_Renderer *renderer;   // draw here
    std::array<Animation,6> sprites; // sprite sequences to be drawn
};

#endif


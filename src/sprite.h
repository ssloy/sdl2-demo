#pragma once
#include <string>
#include <chrono>
#include <algorithm>
#include <iostream>

struct Sprite {
    
    struct SpriteParameters
    {
        int width = 0; // single sprite width (texture width = width * nframes)
        int height = 0; // sprite height
        int nframes = 0; // number of frames in the animation sequence
    };


    Sprite(SDL_Renderer *renderer, const std::string& filename, const int width) 
        : m_params{ width, 0, 0 }
    {
        SDL_Surface *surface = SDL_LoadBMP((std::string(RESOURCES_DIR) + filename).c_str());
        if (surface == nullptr) {
            std::cerr << "Error in SDL_LoadBMP: " << SDL_GetError() << std::endl;
            return;
        }
        if ((surface->w % width) == 0 && surface->w / width) { // image width must be a multiple of sprite width
            m_params.height  = surface->h;
            m_params.nframes = surface->w / width;
            texture = SDL_CreateTextureFromSurface(renderer, surface);
        }
        else {
            std::cerr << "Incorrect sprite size" << std::endl;
            return;
        }
        SDL_FreeSurface(surface);
    }

    SDL_Rect rect(const int idx) const { // choose the sprite number idx from the texture
        // how should (idx * width) work in case of int overflow?
        return { idx * m_params.width, 0, m_params.width, m_params.height };
    }

    ~Sprite() { // do not forget to free the memory!
        if (texture != nullptr) 
            SDL_DestroyTexture(texture);
    }


    SpriteParameters m_params;
    SDL_Texture* texture; // the image is to be stored here
};

using Clock = std::chrono::steady_clock;
using TimeStamp = std::chrono::time_point<Clock>;

struct Animation {
    Animation(const std::chrono::milliseconds duration, const bool repeat, const Sprite::SpriteParameters& params)
        : duration(duration)
        , repeat(repeat) 
        , spriteParams(params)
    {}

    bool animation_ended(const TimeStamp& timestamp) const { // is the animation sequence still playing?
        using namespace std::chrono;
        const auto elapsed = duration_cast<milliseconds>(Clock::now() - timestamp); // seconds from timestamp to now
        return !repeat && (elapsed >= duration);
    }

    int frame(const TimeStamp timestamp) const { // compute the frame number at current time for the the animation started at timestamp
        using namespace std::chrono;
        auto elapsed = duration_cast<milliseconds>(Clock::now() - timestamp); // seconds from timestamp to now
        int idx = static_cast<int>(spriteParams.nframes * elapsed.count() / duration.count());
        return repeat ? idx % spriteParams.nframes : std::min(idx, spriteParams.nframes -1);
    }

    SDL_Rect rect(const TimeStamp timestamp) const { // choose the right frame from the texture
        return { frame(timestamp) * spriteParams.width, 0, spriteParams.width, spriteParams.height };
    }

    const std::chrono::milliseconds duration; // duration of the animation sequence
    const bool repeat; // should we repeat the animation?
    const Sprite::SpriteParameters& spriteParams;   // What are we going to animate, no inheritance is needed, cause Animation is not a Sprite.
};


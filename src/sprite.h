#ifndef SPRITE_H
#define SPRITE_H

struct Sprite {
    Sprite(SDL_Renderer *renderer, const std::string filename, const int width) : width(width) {
        SDL_Surface *surface = SDL_LoadBMP(filename.c_str());
        if (!surface) {
            std::cerr << "Error in SDL_LoadBMP: " << SDL_GetError() << std::endl;
            return;
        }
        if (surface->w%width || !surface->w/width) {
            std::cerr << "Incorrect sprite size" << std::endl;
            return;
        }
        height  = surface->h;
        nframes = surface->w/width;
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    SDL_Rect rect(const int idx) const { // choose the right texture
        return { idx*width, 0, width, height };
    }

    ~Sprite() {
        if (texture) SDL_DestroyTexture(texture);
    }

    SDL_Texture *texture = nullptr; // well duh
    int width   = 0; // single sprite width (texture width = width * nframes)
    int height  = 0; // sprite height
    int nframes = 0; // number of frames in the animation sequence
};

struct Animation : public Sprite {
    Animation(SDL_Renderer *renderer, const std::string filename, const int width, const double duration, const bool repeat) :
        Sprite(renderer, filename, width), duration(duration), repeat(repeat) {}

    double time_elapsed(const TimeStamp timestamp) const { // seconds from timestamp to now
        return std::chrono::duration<double>(Clock::now() - timestamp).count();
    }

    bool animation_ended(const TimeStamp timestamp) const { // is the animation sequence still playing?
        return !repeat && time_elapsed(timestamp) >= duration;
    }

    int frame(const TimeStamp timestamp) const { // compute the frame number at current time for the the animation started at timestamp
        int idx = static_cast<int>(nframes*time_elapsed(timestamp)/duration);
        return repeat ? idx % nframes : std::min(idx, nframes-1);
    }

    SDL_Rect rect(const TimeStamp timestamp) const { // choose the right frame from the texture
        return {frame(timestamp)*width, 0, width, height};
    }

    double duration = 0; // duration of the animation sequence in seconds
    bool repeat = false; // should we repeat the animation?
};

#endif // SPRITE_H


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

#endif // SPRITE_H


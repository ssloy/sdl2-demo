#ifndef MAP_H
#define MAP_H

#include <cassert>

struct Map {
    Map(SDL_Renderer *renderer) :
            renderer(renderer),
            sprite(renderer, "../resources/ground.bmp", 128) {
        assert(sizeof(level) == w*h+1); // +1 for the null terminated string
        int window_w, window_h;
        if (SDL_GetRendererOutputSize(renderer, &window_w, &window_h)) {
            std::cerr << "Failed to get renderer size: " << SDL_GetError() << std::endl;
            return;
        }
        tile_w = window_w/w;
        tile_h = window_h/h;
    }

    void draw() { // draw the level in the renderer window
        for (int j=0; j<h; j++)
            for (int i=0; i<w; i++) {
                if (is_empty(i, j)) continue;
                SDL_Rect dest = {tile_w*i, tile_h*j, tile_w, tile_h};
                SDL_Rect src = sprite.rect(get(i,j));
                SDL_RenderCopy(renderer, sprite.texture, &src, &dest);
            }
    }

    int get(const int i, const int j) const { // retreive the cell, transform character to texture index
        assert(i>=0 && j>=0 && i<w && j<h);
        return level[i+j*w] - '0';
    }

    bool is_empty(const int i, const int j) const {
        assert(i>=0 && j>=0 && i<w && j<h);
        return level[i+j*w] == ' ';
    }

    SDL_Renderer *renderer;   // draw here
    Sprite sprite;            // textures to be drawn
    int tile_w=-1, tile_h=-1; // tile size in the renderer window

    static constexpr int w = 16; // overall map dimensions
    static constexpr int h = 12;
    static constexpr char level[w*h+1] = " 123451234012340"\
                                         "5              5"\
                                         "0              0"\
                                         "5          5   5"\
                                         "0          0   0"\
                                         "512340   12345 5"\
                                         "0              0"\
                                         "5             51"\
                                         "0     50      12"\
                                         "5          51234"\
                                         "0          12345"\
                                         "1234012345052500";
};

#endif // MAP_H


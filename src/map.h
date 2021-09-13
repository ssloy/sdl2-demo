#include <cassert>

struct Map {
    Map(SDL_Renderer *renderer) : renderer(renderer), textures(renderer, "ground.bmp", 128) {
        assert(sizeof(level) == w*h+1); // +1 for the null terminated string
        int window_w, window_h;
        if (!SDL_GetRendererOutputSize(renderer, &window_w, &window_h)) {
            tile_w = window_w/w;
            tile_h = window_h/h;
        } else
            std::cerr << "Failed to get renderer size: " << SDL_GetError() << std::endl;
    }

    void draw() { // draw the level in the renderer window
        for (int j=0; j<h; j++)
            for (int i=0; i<w; i++) {
                if (is_empty(i, j)) continue;
                SDL_Rect dst = { tile_w*i, tile_h*j, tile_w, tile_h };
                SDL_Rect src = textures.rect(get(i,j));
                SDL_RenderCopy(renderer, textures.texture, &src, &dst);
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

    SDL_Renderer *renderer; // draw here
    int tile_w = 0, tile_h = 0; // tile size in the renderer window

    const Sprite textures;         // textures to be drawn
    static constexpr int w = 16; // overall map dimensions, the array level[] has the length w*h+1 (+1 for the null character)
    static constexpr int h = 12; // space character for empty tiles, digits indicate the texture index to be used per tile
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


using Clock = std::chrono::high_resolution_clock;
using TimeStamp = std::chrono::time_point<Clock>;

struct FPS_Counter {
    FPS_Counter(const std::string filename) {
        font = TTF_OpenFont(filename.c_str(), 24);
        if (!font)
            std::cerr << "Error in TTF_OpenFont: " << TTF_GetError() << std::endl;
    }

    void draw(SDL_Renderer *renderer) {
        if (!font) return;
        cnt1++;
        double dt = std::chrono::duration<double>(Clock::now() - timestamp).count();
        if (dt>=.3) {
            cnt2 = cnt1/dt;
            cnt1 = 0;
            timestamp  = Clock::now();
        }
        SDL_Surface* msg = TTF_RenderText_Solid(font, std::to_string(cnt2).c_str(), {0, 0, 0, 0});
        if (!msg) return;
        SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, msg);
        SDL_FreeSurface(msg);
        int w, h;
        SDL_QueryTexture(txt, nullptr, nullptr, &w, &h);
        SDL_Rect rect = {0, 0, w, h};
        SDL_RenderCopy(renderer, txt, nullptr, &rect);
        SDL_DestroyTexture(txt);
    }

    ~FPS_Counter() {
        if (font) TTF_CloseFont(font);
    }

    int cnt1 = 0, cnt2 = 0;
    TTF_Font *font = nullptr;
    TimeStamp timestamp = Clock::now();
};


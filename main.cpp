#include <iostream>
#include <string>
#include <SDL.h>

constexpr char window_name[] = "My Game";
constexpr uint32_t window_size_x = 800;
constexpr uint32_t window_size_y = 600;
constexpr uint32_t window_background_color_r = 0;
constexpr uint32_t window_background_color_g = 0;
constexpr uint32_t window_background_color_b = 0;
constexpr uint32_t window_background_color_a = 255;
constexpr uint32_t player_start_position_x = 400;
constexpr uint32_t player_start_position_y = 300;
constexpr uint32_t player_size_width = 20;
constexpr uint32_t player_size_height = 20;
constexpr uint32_t player_color_r = 255;
constexpr uint32_t player_color_g = 0;
constexpr uint32_t player_color_b = 0;
constexpr uint32_t player_color_a = 255;
constexpr uint32_t player_step = 5;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "failed to initialize SDL, err: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_x, window_size_y, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "failed to initialize SDL window, err: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    uint32_t x = player_start_position_x;
    uint32_t y = player_start_position_y;

    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {

            //User requests quit
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            //User presses a key
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP)
                {
                    y -= player_step;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    y += player_step;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    x -= player_step;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    x += player_step;
                }
            }
        }

        // background
        SDL_SetRenderDrawColor(renderer, window_background_color_r, window_background_color_g, window_background_color_b, window_background_color_a);
        SDL_RenderClear(renderer);

        // player
        SDL_SetRenderDrawColor(renderer, player_color_r, player_color_g, player_color_b, player_color_a);
        SDL_Rect player = { x, y, player_size_width, player_size_height };
        SDL_RenderFillRect(renderer, &player);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#include <SDL.h>

int main(int argc, char* argv[]) {
    SDL_Log("hypnitro version 0.0.0\n");

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_Log("Cannot initialize SDL2! Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow(
            "hypNITRO", /* title */
            SDL_WINDOWPOS_UNDEFINED, /* x */
            SDL_WINDOWPOS_UNDEFINED, /* y */
            640, /* width */
            480, /* height */
            SDL_WINDOW_VULKAN); /* flags */
    if (!window) {
        SDL_Log("Cannot create window! Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Delay(3000);
        
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

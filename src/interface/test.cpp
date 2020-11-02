#include <SDL.h>

int main(int argc, char* argv[]) {
    return SDL_RWFromFile("test.nds", "rb") ? 0 : 1;
}

#include <SDL.h>
#include "SDL_include.h"
#include "Game.h"
#include "Log.h"

int main(int argc, char ** argv) {
    int Height = DEFAULT_GAME_HEIGHT;
    int Width = DEFAULT_GAME_WIDTH

    Game* game = new Game("João Viktor 16/0127823",Width,Height);
    game->Run();

    delete game;

    return 0;
}
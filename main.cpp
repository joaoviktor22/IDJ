#include <SDL.h>
#include "SDL_include.h"
#include "Game.h"
#include "Log.h"
#include "TitleState.h"

int main(int argc, char ** argv) {
    int Height = DEFAULT_GAME_HEIGHT;
    int Width = DEFAULT_GAME_WIDTH;

    auto &game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();

    return 0;
}
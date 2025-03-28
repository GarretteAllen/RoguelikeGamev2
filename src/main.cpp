#include "../includes/core/Game.h"
#include "../includes/common/Constants.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    Game game;
    if (!game.init("Rogue Cards", Constants::DEFAULT_WINDOW_WIDTH, Constants::DEFAULT_WINDOW_HEIGHT)) {
        return 1;
    }

    while (game.running()) {
        game.handleEvents();
        game.render();
        SDL_Delay(16);
    }

    return 0;
}

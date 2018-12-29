//
// Created by aleca on 11/17/2018.
//

#include "game.h"


Game::Game(SDL_Renderer *renderer) : player() {
    player.loadMedia(renderer);
}

bool Game::update(const double deltaTime, SDL_GameController* gameController) {
    //Event handler
    SDL_Event e;

    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT) {
            //Quit
            return true;
        } else {
            player.handleEvent(e);
        }
    }

    player.readInput(gameController);
    player.update(deltaTime);

    //Don't quit
    return false;
}

void Game::render(SDL_Renderer *renderer) {
    player.render(renderer);
}



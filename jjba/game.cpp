//
// Created by aleca on 11/17/2018.
//

#include "game.h"


Game::Game(SDL_Renderer *renderer) : player(), level({Hitbox(400, 400, 500, 50),
                                                      Hitbox(900, 200, 50, 250),
                                                      Hitbox(0, 600, 1500, 50)}) {
    player.loadMedia(renderer);
}

bool Game::update(const double deltaTime, SDL_GameController *gameController) {
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

//Player updates
    player.
            readInput(gameController);
    player.
            update(deltaTime);

//Collision checks
    collisionChecks();

//Don't quit
    return false;
}

void Game::render(SDL_Renderer *renderer) {
    level.render(renderer);
    player.render(renderer);
}

void Game::collisionChecks() {
    player.staticCollisionCheck(level);
}
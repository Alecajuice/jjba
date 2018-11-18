//
// Created by aleca on 11/17/2018.
//

#include "game.h"

Game::Game(SDL_Renderer* renderer) : temp() {
    temp.loadMedia(renderer);
}

void Game::update() {

}

void Game::render(SDL_Renderer* renderer) {
    temp.render(renderer);
}



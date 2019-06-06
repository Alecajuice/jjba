//
// Created by aleca on 11/17/2018.
//

#include <cstdio>
#include <math.h>
#include "hitbox.h"

Hitbox::Hitbox(const SDL_Rect &bounds) : position({(double) bounds.x, (double) bounds.y}),
                                         size({(double) bounds.w, (double) bounds.h}) {}

Hitbox::Hitbox(double x, double y, double width, double height) : position({x, y}), size({width, height}) {}

Hitbox::Hitbox(Vector position, Vector size) : position(position), size(size) {}

const SDL_Rect Hitbox::getSDL_Rect() const {
    return {(int) std::round(position.x), (int) std::round(position.y), (int) std::round(size.x), (int) std::round(size.y)};
}

Hitbox Hitbox::translate(double x, double y) {
//    Hitbox::position.x += x;
//    Hitbox::position.y += y;
    return {position.x + x, position.y + y, size.x, size.y};
}

Hitbox Hitbox::translate(Vector v) {
    return translate(v.x, v.y);
}

const Vector &Hitbox::getPosition() const {
    return position;
}

void Hitbox::setPosition(double x, double y) {
    Hitbox::position = {x, y};
}

void Hitbox::setPosition(Vector position) {
    Hitbox::position = position;
}

const Vector &Hitbox::getSize() const {
    return size;
}

void Hitbox::setBounds(const SDL_Rect &bounds) {
    position = {(double) bounds.x, (double) bounds.y};
    size = {(double) bounds.w, (double) bounds.h};
}

void Hitbox::setBounds(double x, double y, double width, double height) {
    position = {x, y};
    size = {width, height};
}

void Hitbox::setBounds(Vector position, Vector size) {
    Hitbox::position = position;
    Hitbox::size = size;
}

double Hitbox::getX() const {
    return position.x;
}

void Hitbox::setX(double x) {
    position.x = x;
}

double Hitbox::getY() const {
    return position.y;
}

void Hitbox::setY(double y) {
    position.y = y;
}

double Hitbox::getW() const {
    return size.x;
}

void Hitbox::setW(double w) {
    size.x = w;
}

double Hitbox::getH() const {
    return size.y;
}

void Hitbox::setH(double h) {
    size.y = h;
}

Hitbox getBoundingHitbox(std::vector<Hitbox> hitboxes) {
    if (hitboxes.empty()) {
        printf("shit\n");
        return {0, 0, 0, 0};
    }
    double minx = hitboxes.front().getX();
    double miny = hitboxes.front().getY();
    double maxx = minx + hitboxes.front().getW();
    double maxy = miny + hitboxes.front().getH();
//    printf("%lf\n", hitboxes.front().getW());
//    printf("minx: %lf, miny: %lf, maxx: %lf, maxy: %lf\n", minx, miny, maxx, maxy);
    for (int i = 1; i < hitboxes.size(); i++) {
        if (minx > hitboxes[i].getX()) minx = hitboxes[i].getX();
        if (miny > hitboxes[i].getY()) miny = hitboxes[i].getY();
        if (maxx < hitboxes[i].getX() + hitboxes[i].getW()) maxx = hitboxes[i].getX() + hitboxes[i].getW();
        if (maxy < hitboxes[i].getY() + hitboxes[i].getH()) maxy = hitboxes[i].getY() + hitboxes[i].getH();
    }
    return {minx, miny, maxx - minx, maxy - miny};
}

bool oneDimOverlap(double x1, double w1, double x2, double w2) {
    return x1 < x2 + w2 && x2 < x1 + w1;
}

bool checkCollision(Hitbox h1, Hitbox h2, Vector *overlap) {
    if (overlap == nullptr) {
        printf("Attempt to check collision with null output\n");
        return false;
    }
    //If hitboxes have 0 thickness
    if (h1.getW() == 0 || h1.getH() == 0 || h2.getW() == 0 || h2.getH() == 0) {
        return false;
    }
    if (!oneDimOverlap(h1.getX(), h1.getW(), h2.getX(), h2.getW()) ||
        !oneDimOverlap(h1.getY(), h1.getH(), h2.getY(), h2.getH())) {
        return false;
    }
    int xSign = ((h1.getX() - h2.getX()) > 0) - ((h1.getX() - h2.getX()) < 0);
    int ySign = ((h1.getY() - h2.getY()) > 0) - ((h1.getY() - h2.getY()) < 0);
    double x = fmin(h1.getX() + h1.getW(), h2.getX() + h2.getW()) - fmax(h1.getX(), h2.getX());
    double y = fmin(h1.getY() + h1.getH(), h2.getY() + h2.getH()) - fmax(h1.getY(), h2.getY());
    *overlap = {xSign * x, ySign * y};
    return true;
}
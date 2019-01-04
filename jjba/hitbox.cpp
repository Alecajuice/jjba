//
// Created by aleca on 11/17/2018.
//

#include <cstdio>
#include "hitbox.h"

Hitbox::Hitbox(const SDL_Rect &bounds) : position({static_cast<double>(bounds.x), static_cast<double>(bounds.y)}),
                                         size({static_cast<double>(bounds.w), static_cast<double>(bounds.h)}) {}

Hitbox::Hitbox(double x, double y, double width, double height) : position({x, y}), size({width, height}) {}

Hitbox::Hitbox(Vector position, Vector size) : position(position), size(size) {}

const SDL_Rect Hitbox::getSDL_Rect() const {
    return {static_cast<int>(position.x - size.x / 2), static_cast<int>(position.y - size.y / 2),
            static_cast<int>(size.x), static_cast<int>(size.y)};
}

Hitbox Hitbox::translate(double x, double y) {
    Hitbox::position.x += x;
    Hitbox::position.y += y;
    return *this;
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
    position = {bounds.x + static_cast<double>(bounds.w) / 2, bounds.y + static_cast<double>(bounds.h) / 2};
    size = {static_cast<double>(bounds.w), static_cast<double>(bounds.h)};
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



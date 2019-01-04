//
// Created by aleca on 11/17/2018.
//

#ifndef JJBA_HITBOX_H
#define JJBA_HITBOX_H

#include <SDL_rect.h>
#include <vector>

struct Vector {
    double x, y;
};

class Hitbox {
private:
    Vector position;
    Vector size;

public:
    //Constructors
    explicit Hitbox(const SDL_Rect &bounds);

    Hitbox(double x, double y, double width, double height);

    Hitbox(Vector position, Vector size);

    //Member functions
    Hitbox translate(double x, double y);
    Hitbox translate(Vector v);

    //Getters and setters
    const SDL_Rect getSDL_Rect() const;

    const Vector &getPosition() const;

    void setPosition(double x, double y);

    void setPosition(Vector position);

    const Vector &getSize() const;

    void setBounds(const SDL_Rect &bounds);

    void setBounds(double x, double y, double width, double height);

    void setBounds(Vector position, Vector size);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getW() const;

    void setW(double w);

    double getH() const;

    void setH(double h);
};

Hitbox getBoundingHitbox(std::vector<Hitbox> hitboxes);

#endif //JJBA_HITBOX_H

#include "Fish.h"

Fish::Fish(float x, float y, float dx, float dy, std::vector<Fish*>* otherFish)
            : Triangle::Triangle(x, y)
{
    this->dx = dx;
    this->dy = dy;
    this->otherFishes = otherFish;
}
Fish::Fish(float xSize, float ySize, std::vector<Fish*>* otherFishes) 
            : Triangle::Triangle(xSize, ySize)
{
    this->setPosition((rand() % 3 - 1) * (rand() % 100) / 100.0f, 
                      (rand() % 3 - 1) * (rand() % 100) / 100.0f);
    this->dx = (rand() % 3 - 1) * (rand() % 100) / 100.0f;
    this->dy = (rand() % 3 - 1) * (rand() % 100) / 100.0f;
    this->otherFishes = otherFishes;
    limitSpeed();
}

void Fish::processMovement() {
    calculateAvoidance();
    avoidWall(x + dx, y + dy);
    limitSpeed();
    setPosition(x + dx, y + dy);
    float rotationAngle = 3 * M_PI_2 - atan2f(-dy, dx);
    setRotation(rotationAngle);
}

void Fish::setPosition(float x, float y) {
    Triangle::setPosition(x, y);
}

void Fish::avoidWall(float x, float y) {
    float wall = 0.97;
    if ( x < -wall + sizeX * scaleX) {
        dx += AVOID_WALL_STRENGTH;
    }
    else if (x > wall - sizeX * scaleX) {
        dx -= AVOID_WALL_STRENGTH;
    }
    if (y < -wall + sizeY * scaleY) {
        dy += AVOID_WALL_STRENGTH;
    }
    else if (y > wall - sizeY * scaleY) {
        dy -= AVOID_WALL_STRENGTH;
    }
}

void Fish::limitSpeed() { 
    float speed = sqrtf(dx * dx + dy * dy);
    if (speed > MAX_SPEED) {
        dx = (dx / speed) * MAX_SPEED;
        dy = (dy / speed) * MAX_SPEED;
    } else if (speed < MIN_SPEED) {
        dx = dx * (MIN_SPEED / speed);
        dy = dy * (MIN_SPEED / speed);
    }
}

void Fish::calculateAvoidance() {
    float moveX = 0.0f;
    float moveY = 0.0f;
    for (Fish* f : *otherFishes) {
        float distance = sqrtf((f->x-x)*(f->x-x) + (f->y-y)*(f->y-y));
        if (distance < AVOID_DIST_THRESHOLD) {
            moveX += x - f->x;
            moveY += y - f->y;
        }
    }
    dx += moveX * AVOID_STRENGTH;
    dy += moveY * AVOID_STRENGTH;
}
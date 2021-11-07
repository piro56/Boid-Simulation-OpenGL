#include "Fish.h"

//  REFERENCES FROM https://github.com/beneater/boids/blob/master/boids.js

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


void Fish::setPosition(float x, float y) {
    Triangle::setPosition(x, y);
}

void Fish::avoidWall(float x, float y) {
    float wall = 0.95;
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

    if (abs(x) > 1.1 || abs(y) > 1.1) {
        x = 0.0;
        y = 0.0;
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
void Fish::draw() {
    float absX = abs(dx);   
    float absY = abs(dy);
    // can move this into the fragment shader!
    setColor(0.2, 0.0, 0.6);

    //setColor(absX * 30 + dx * dy + 0.5, absX * absY + x, absY * 30 + y);
    Triangle::draw();
}

void Fish::processMovement() {
    calculateAvoidance();
    limitSpeed();
    avoidWall(x, y);
    setPosition(x + dx, y + dy);
    float rotationAngle = 3 * M_PI_2 - atan2f(-dy, dx);
    setRotation(rotationAngle);
}

void Fish::calculateCentering() {
    float centerX = 0.0f;
    float centerY = 0.0f;
    unsigned int nearbyFish = 0;
    for (Fish* f : *otherFishes) {
        float distance = sqrtf((f->x-x)*(f->x-x) + (f->y-y)*(f->y-y));
        if (distance < CENTERING_RANGE) {
            centerX += f->x;
            centerX += f->y;
            nearbyFish++;
        }
    }
    if (nearbyFish > 0) {
        centerX /= nearbyFish;
        centerY /= nearbyFish;

        dx += (centerX - x) * CENTERING_STRENGTH;
        dy += (centerY - y) * CENTERING_STRENGTH;
    }
}

void Fish::calculateAvoidance() {
    // match heading
    float averagedX;
    float averagedY;

    // centering
    float centerX = 0.0f;
    float centerY = 0.0f;
    unsigned int nearbyFish = 0;

    // avoidance
    float moveX = 0.0f;
    float moveY = 0.0f;

    for (Fish* f : *otherFishes) {
        float distance = sqrtf((f->x-x)*(f->x-x) + (f->y-y)*(f->y-y));
        // avoidance
        if (distance < AVOID_DIST_THRESHOLD * (sizeX + sizeY)) {
            moveX += x - f->x;
            moveY += y - f->y;
        }
        // CENTERING & HEADING CODE
        if (distance < CENTERING_RANGE) {
            averagedX += f->dx;
            averagedY += f->dy;
            centerX += f->x;
            centerX += f->y;
            nearbyFish++;
        }
    }
    // centering
    if (nearbyFish > 0) {
        centerX /= nearbyFish;
        centerY /= nearbyFish;
        averagedX /= nearbyFish;
        averagedY /= nearbyFish;
        dx += (centerX - x) * CENTERING_STRENGTH;
        dy += (centerY - y) * CENTERING_STRENGTH;
        
        // Heading
        if (dx < MAX_SPEED && dy < MAX_SPEED) {
        dx += ((averagedX - dx) * FOLLOW_STRENGTH);
        dy += ((averagedY - dy) * FOLLOW_STRENGTH);
        }
    }
    // avoidance
    dx += moveX * AVOID_STRENGTH;
    dy += moveY * AVOID_STRENGTH;
}
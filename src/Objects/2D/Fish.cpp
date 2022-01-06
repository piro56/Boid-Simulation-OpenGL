#include "Fish.h"

//  REFERENCES FROM https://github.com/beneater/boids/blob/master/boids.js

Fish::Fish(float x, float y, float dx, float dy, std::vector<Fish*>* otherFish, 
            std::vector<std::unique_ptr<std::set<Fish*>>>* segmentedFish, FishSettings& fsp, ShaderProgram* sp)
            : Triangle::Triangle(x, y, sp)
{
    this->segmentedFish = segmentedFish;
    this->dx = dx;
    this->dy = dy;
    this->otherFishes = otherFish;
    this->FISH_SETTINGS = &fsp;
}
Fish::Fish(float xSize, float ySize, std::vector<Fish*>* otherFishes, FishSettings& fsp, ShaderProgram* sp) 
            : Triangle::Triangle(xSize, ySize, sp)
{
    this->setPosition((rand() % 3 - 1) * (rand() % 75) / 100.0f, 
                      (rand() % 3 - 1) * (rand() % 75) / 100.0f);
    this->dx = (rand() % 3 - 1) * (rand() % 100) / 100.0f;
    this->dy = (rand() % 3 - 1) * (rand() % 100) / 100.0f;
    this->otherFishes = otherFishes;
    this->FISH_SETTINGS = &fsp;
    this->scale(FISH_SETTINGS->SIZE, FISH_SETTINGS->SIZE, 1.0f);
    limitSpeed();
}


void Fish::setPosition(float x, float y) {
    Triangle::setPosition(x, y);
}

void Fish::avoidWall(float x, float y) {
    float wall = 0.97;
    if ( x < -wall) {
        dx += FISH_SETTINGS->AVOID_WALL_STRENGTH;
    }
    else if (x > wall) {
        dx -= FISH_SETTINGS->AVOID_WALL_STRENGTH;
    }
    if (y < -wall) {
        dy += FISH_SETTINGS->AVOID_WALL_STRENGTH;
    }
    else if (y > wall) {
        dy -= FISH_SETTINGS->AVOID_WALL_STRENGTH;
    }

    if (abs(x) > 1.2 || abs(y) > 1.2) {
        this->x = 0.0;
        this->y = 0.0;
    }
}

void Fish::limitSpeed() { 
    float speed = sqrtf(dx * dx + dy * dy);
    if (speed > FISH_SETTINGS->MAX_SPEED) {
        dx = (dx / speed) * FISH_SETTINGS->MAX_SPEED;
        dy = (dy / speed) * FISH_SETTINGS->MAX_SPEED;
    } else if (speed < FISH_SETTINGS->MIN_SPEED) {
        dx = dx * (FISH_SETTINGS->MIN_SPEED / speed);
        dy = dy * (FISH_SETTINGS->MIN_SPEED / speed);
    }
}
void Fish::draw() {
    float absX = abs(dx);   
    float absY = abs(dy);
    // can move this into the fragment shader!
    //setColor(0.2, 0.0, 0.6);
    this->scale(FISH_SETTINGS->SIZE, FISH_SETTINGS->SIZE, 1.0f);
    setColor(absX * 30 + dx * dy + 0.5, absX * absY + x, absY * 30 + y);
    Triangle::draw();
}

void Fish::processMovement() {
    calculateAvoidance();
    limitSpeed();
    avoidWall(x, y);
    setPosition(x + dx, y + dy);
    //updateSegment();
    float rotationAngle = 3 * M_PI_2 - atan2f(-dy, dx);
    setRotation(rotationAngle);
}
void Fish::updateSegment() {
    double boundary = 0.5;
    int xGrid = -1;
    int yGrid = -1;
    if (abs(x) < boundary) {
        // 0 -> 1, 1 -> 2
        xGrid = 1 + signbit(x);
    } else {
        // 0 -> 0, 1 -> 3
        xGrid = 3 * signbit(x);
    }
    if (abs(y) < boundary) {
        yGrid = 1 +  signbit(y);
    } else {
        yGrid = 3 *  signbit(y);
    }
    xGrid = (yGrid * 4) + xGrid; 
    // if new position
    if (vectorPosition == -1) {
        (*segmentedFish)[xGrid].get()->insert(this);
        vectorPosition = xGrid;
    }
    // if (vectorPosition != xGrid) {
    //     (*segmentedFish)[vectorPosition].get()->erase(this);
    //     (*segmentedFish)[xGrid].get()->insert(this);
    //     vectorPosition = xGrid;
    // }
}
void Fish::calculateCentering() {
    float centerX = 0.0f;
    float centerY = 0.0f;
    unsigned int nearbyFish = 0;
    for (Fish* f : *otherFishes) {
        float distance = sqrtf((f->x-x)*(f->x-x) + (f->y-y)*(f->y-y));
        if (distance < FISH_SETTINGS->CENTERING_RANGE) {
            centerX += f->x;
            centerX += f->y;
            nearbyFish++;
        }
    }
    if (nearbyFish > 0) {
        centerX /= nearbyFish;
        centerY /= nearbyFish;

        dx += (centerX - x) * FISH_SETTINGS->CENTERING_STRENGTH;
        dy += (centerY - y) * FISH_SETTINGS->CENTERING_STRENGTH;
    }
}

void Fish::calculateAvoidance() {
    // match heading
    float averagedX = 0.0f;
    float averagedY = 0.0f;

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
        if (distance < FISH_SETTINGS->AVOID_DIST_THRESHOLD) {
            moveX += x - f->x;
            moveY += y - f->y;
        }
        // CENTERING & HEADING CODE
        if (distance < FISH_SETTINGS->CENTERING_RANGE) {
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
        dx += (centerX - x) * FISH_SETTINGS->CENTERING_STRENGTH;
        dy += (centerY - y) * FISH_SETTINGS->CENTERING_STRENGTH;
        
        // Heading
        dx += ((averagedX - dx) * FISH_SETTINGS->FOLLOW_STRENGTH);
        dy += ((averagedY - dy) * FISH_SETTINGS->FOLLOW_STRENGTH);
    }
    // avoidance
    dx += moveX * FISH_SETTINGS->AVOID_STRENGTH;
    dy += moveY * FISH_SETTINGS->AVOID_STRENGTH;
}
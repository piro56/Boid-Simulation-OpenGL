#include <Circle.h>
Circle::Circle() {
    x = 0;
    y = 0;
    radius = 0.1;
    randomColor();
    numSegments = DEFAULT_CIRCLE_SEGMENTS;
    
}

void Circle::randomColor() {
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;
}

void Circle::initializePoints() {
    pts.resize(numSegments);
    for (int i = 0; i < numSegments; i++) {
        std::pair<float, float> p = std::make_pair(
            (radius * cos(i * M_PI / 10)), 
            (radius * sin(i * M_PI / 10))
        );
        pts.push_back(p);
    }
}
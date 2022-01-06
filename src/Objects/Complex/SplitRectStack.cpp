#include <SplitRectStack.h>

SplitRectStack::SplitRectStack(int num_shape, int num_segments, ShaderProgram* sp) {
    this->boids_vec = new std::vector<BOID>[num_segments];
}

SplitRectStack::~SplitRectStack() {
    delete[] boids_vec;
    
}
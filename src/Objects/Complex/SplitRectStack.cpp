#include <SplitRectStack.h>

SplitRectStack::SplitRectStack(int num_shape, int num_segments, ShaderProgram* sp) {
    this->boids_vec = new std::vector<BOID>[num_segments];
    int shape_idx = 0;
    for (int i = 0; i < num_segments; i++) {
        for (auto j = 0; j < shape_idx; j++) {
            
        }
    }
}

SplitRectStack::~SplitRectStack() {
    delete[] boids_vec;
}
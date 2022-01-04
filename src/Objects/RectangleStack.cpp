#include <RectangleStack.h>
#define COL_SIZE (num_rect * 3 * sizeof(float))
RectangleStack::RectangleStack(int num_rect, ShaderProgram* sp) {
    this->num_rect = num_rect;
    this->points_size = num_rect * 18;  // 18 floats per rect
    this->sp = sp;
    this->vertices = new float[points_size];
    this->colors = new float[points_size];
    this->positions = new float[points_size];
    this->trans = new float[num_rect * 16];
    this->vao.bind();

}

RectangleStack::~RectangleStack() {
    delete vertices;
    delete colors;
    delete positions;
}

void RectangleStack::draw() {
    this->sp->use();
    this->vao.bind();
    verticesBuf.bind();
    verticesBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), this->vertices, GL_STATIC_DRAW);

    colorBuf.bind();
    colorBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0,  points_size * sizeof(float), this->colors);
    posBuf.bind();
    posBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, points_size * sizeof(float), this->positions);

    // transformation update


    glDrawArrays(GL_TRIANGLES, 0, 6 * num_rect);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RectangleStack::initialize(float xWidth, float yLength) {
    /*
    float halfX = xLength / 2.0f;
    float halfY = yLength / 2.0f;
    // we translate this later.
    float vertices[12] = { halfX,  halfY, 0.0f, // TR
                           halfX, -halfY, 0.0f, // BR
                          -halfX, -halfY, 0.0f, // BL 
                          -halfX,  halfY, 0.0f, // TL
                         };
                         */
    //unsigned int indices[6] = {0, 1, 3, 1, 2, 3};
    float halfX = xWidth / 2.0f;
    float halfY = yLength / 2.0f;
    float initVert[18] = {
        halfX, halfY, 0.0f,
        halfX, -halfY, 0.0f,
        -halfX, halfY, 0.0f,
        halfX, -halfY, 0.0f,
        -halfX, -halfY, 0.0f,
        -halfX, halfY, 0.0f
    };
    for (auto i = 0; i < num_rect; i++) {
        float r = norm_randf();
        float g = norm_randf();
        float b = norm_randf();
        glm::mat4 idenmtx = glm::mat4(1.0f);

        // im scared what is this memory copying jarble i am doing D:
        // SHOULD copy matrix data kinda like float[16] into trans... hopefully.
        std::memcpy(&trans[i * 16], glm::value_ptr(idenmtx), sizeof(glm::value_ptr(idenmtx)));
        for (int j = 0; j < 6; j++) {
            this->vertices[i*18 + j*3] = initVert[(i*18 + j*3) % 18];
            this->vertices[i*18 + j*3 + 1] = initVert[(i*18 + j*3 + 1) % 18];
            this->vertices[i*18 + j*3 + 2] = initVert[(i*18 + j*3 + 2) % 18];
            this->positions[i*18 + j*3] = 0.0f;
            this->positions[i*18 + j*3 + 1] = 0.0f;
            this->positions[i*18 + j*3 + 2] = 0.0f;

            this->colors[i*18 + j*3] = r;
            this->colors[i*18 + j*3 + 1] = g;
            this->colors[i*18 + j*3 + 2] = b;
        }
    }
    this->vao.bind();

    // init vertices, colors, and position buffers
    verticesBuf.bind();
    this->verticesBuf.setVertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float));
    this->verticesBuf.enableAttribArray(0);

    this->colorBuf.bind();
    this->colorBuf.setVertexAttributePointer(1, 3, GL_FLOAT, 3 * sizeof(float));
    this->colorBuf.enableAttribArray(1);

    this->posBuf.bind();
    posBuf.setVertexAttributePointer(2, 3, GL_FLOAT, 3 * sizeof(float));
    posBuf.enableAttribArray(2);

    // shader storage buffer
    this->tranSSbuf.bind(GL_SHADER_STORAGE_BUFFER);
    this->tranSSbuf.setBufferData(GL_SHADER_STORAGE_BUFFER, 16 * sizeof(float), this->trans, GL_DYNAMIC_COPY);





}

void RectangleStack::randomizeLocations() {
    // for -> rectangle -> for each of its 6 vertices
    for (int i = 0; i < num_rect; i++) {
        float xOff = neg_randf();
        float yOff = neg_randf();
        for (int j = 0; j < 6; j++) {
            positions[18*i + j * 3] = xOff;
            positions[18*i + j * 3 + 1] = yOff;
        }
    }
}
void RectangleStack::setPosition(int rect_idx, float x, float y, float z) {
    for (int i = 0; i < 6; i++) {
        positions[18*rect_idx + i * 3] = x;
        positions[18*rect_idx  + i * 3 + 1] = y;
        positions[18*rect_idx  + i * 3 + 2] = z;
    }
}
void RectangleStack::setColor(int rect_idx, float r, float g, float b) {
    int offset = 18 * rect_idx;
    for (int i = 0; i < 6; i++) {
        colors[offset + i * 3] = r;
        colors[offset + i * 3 + 1] = g;
        colors[offset + i * 3 + 2] = b;
    }
}
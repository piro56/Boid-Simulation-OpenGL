#include <TriangleStack.h>
TriangleStack::TriangleStack(int num_tri, ShaderProgram* sp) {
    this->num_tri = num_tri;
    this->points_size = num_tri * 9;  // 3 floats per point
    this->sp = sp;
    this->vertices = new float[points_size];
    this->colors = new float[points_size];
    this->positions = new float[points_size];
    this->trans_data = new TransformData[num_tri];
    this->vao.bind();

}

TriangleStack::~TriangleStack() {
    delete[] vertices;
    delete[] colors;
    delete[] positions;
    delete[] trans_data;
}

void TriangleStack::draw() {
    this->sp->use();
    this->vao.bind();
    verticesBuf.bind();
    verticesBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), this->vertices, GL_STATIC_DRAW);
    verticesBuf.unbind();
    colorBuf.bind();
    colorBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0,  points_size * sizeof(float), this->colors);
    colorBuf.unbind();
    posBuf.bind();
    posBuf.setBufferData(GL_ARRAY_BUFFER, points_size * sizeof(float), NULL, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, points_size * sizeof(float), this->positions);

    // transformation update
    this->transformSSB.bind(GL_SHADER_STORAGE_BUFFER);
    // buffer orphan
    this->transformSSB.setBufferData(GL_SHADER_STORAGE_BUFFER, num_tri * sizeof(TransformData), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, num_tri * sizeof(TransformData), this->trans_data);
    // unbind
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    //glDrawArraysInstanced(GL_TRIANGLES, 0, 3 * num_tri, 1);
    glDrawArrays(GL_TRIANGLES, 0, 3 * num_tri);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/*
 * Fills vertices with given width and length
 * Default initializes positions to 0.0f
 * Also initializes to random colors
 * Default initializes transformation data
 * Initalize buffers, and fill them.
 * 3 vertex Buffers, position, color, translation
 * 1 shader storage buffer: transformation
 */

void TriangleStack::initialize(float xWidth, float yLength) {
    float halfX = xWidth / 2.0f;
    float halfY = yLength / 2.0f;
    float initVert[9] = {
        -halfX, -halfY, 0.0f,
        halfX, -halfY, 0.0f,
        0.0f, halfY, 0.0f
    };
    for (auto i = 0; i < num_tri; i++) {
        float r = norm_randf();
        float g = norm_randf();
        float b = norm_randf();

        // load in transformation data
        // vec4 position offset, vec3 scale, float rotation
        trans_data[i] = {{0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 0.0f};
        for (int j = 0; j < 9; j++) {
            this->vertices[i*9 + j] = initVert[(i*9 + j) % 9];
            this->positions[i*9 + j] = 0.0f;
            
            if (j % 3 == 0) colors[i*9 + j] = r;
            else if ((j - 1) % 3 == 0) colors[i*9+j] = g;
            else colors[i*9+j] = b;

        }
    }

    this->vao.bind();

    // init vertices, colors, and position buffers
    verticesBuf.bind();
    this->verticesBuf.setVertexAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(float));
    this->verticesBuf.enableAttribArray(0);
    verticesBuf.unbind();
    this->colorBuf.bind();
    this->colorBuf.setVertexAttributePointer(1, 3, GL_FLOAT, 3 * sizeof(float));
    this->colorBuf.enableAttribArray(1);
    colorBuf.unbind();
    this->posBuf.bind();
    posBuf.setVertexAttributePointer(2, 3, GL_FLOAT, 3 * sizeof(float));
    posBuf.enableAttribArray(2);
    posBuf.unbind();

    this->transformSSB.bind(GL_SHADER_STORAGE_BUFFER);
    this->transformSSB.setBufferData(GL_SHADER_STORAGE_BUFFER, num_tri * sizeof(TransformData), 
    this->trans_data, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, transformSSB.getBuffer());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);



}

void TriangleStack::randomizeLocations() {
    // for -> rectangle -> for each of its 6 vertices
    for (int i = 0; i < num_tri; i++) {
        float xOff = neg_randf();
        float yOff = neg_randf();
        setPosition(i, xOff, yOff, 0.0f);
    }
}
void TriangleStack::setPosition(int tri_idx, float x, float y, float z) {
    this->trans_data[tri_idx].xyz_offset[0] = x;
    this->trans_data[tri_idx].xyz_offset[1] = y;
    this->trans_data[tri_idx].xyz_offset[2] = z;
}
void TriangleStack::setColor(int tri_idx, float r, float g, float b) {
    int offset = 18 * tri_idx;
    for (int i = 0; i < 6; i++) {
        colors[offset + i * 3] = r;
        colors[offset + i * 3 + 1] = g;
        colors[offset + i * 3 + 2] = b;
    }
}

void TriangleStack::setRotation(int tri_idx, float angle_radians) {
    this->trans_data[tri_idx].rotation = angle_radians;
}
#include "ring.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 600;
    for (i = n / 2; i < n; i++)
    {
        vertex_buffer_data[9 * i] = 0.0f;
        vertex_buffer_data[9 * i + 1] = 0.0f;
        vertex_buffer_data[9 * i + 2] = 1.0f;

        vertex_buffer_data[9 * i + 3] = 5 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 4] = 5 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 5] = 1.0f;
        
        vertex_buffer_data[9 * i + 6] = 5 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 7] = 5 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 8] = 1.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n * 3, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    // this->position.x -= 0.1;    
}

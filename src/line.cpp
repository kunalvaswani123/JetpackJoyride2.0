#include "line.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Line::Line(float x, float y, double size, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rand() % 361;
    this->flag = true;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 600;
    for (i = 0; i < n / 2; i++)
    {
        vertex_buffer_data[9 * i] = -size + 0.0f;
        vertex_buffer_data[9 * i + 1] = 0.0f;
        vertex_buffer_data[9 * i + 2] = 2.0f;

        vertex_buffer_data[9 * i + 3] = -size + 0.65 * (double)cos((4 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 4] = 0.65 * (double)sin((4 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 5] = 2.0f;
        
        vertex_buffer_data[9 * i + 6] = -size + 0.65 * (double)cos((4 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 7] = 0.65 * (double)sin((4 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 8] = 2.0f;
    }
    for (; i < n; i++)
    {
        vertex_buffer_data[9 * i] = size + 0.0f;
        vertex_buffer_data[9 * i + 1] = 0.0f;
        vertex_buffer_data[9 * i + 2] = 2.0f;

        vertex_buffer_data[9 * i + 3] = size + 0.65 * (double)cos((4 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 4] = 0.65 * (double)sin((4 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 5] = 2.0f;
        
        vertex_buffer_data[9 * i + 6] = size + 0.65 * (double)cos((4 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 7] = 0.65 * (double)sin((4 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 8] = 2.0f;
    }
    vertex_buffer_data[9 * i] = -size;
    vertex_buffer_data[9 * i + 1] = 0.2f;
    vertex_buffer_data[9 * i + 2] = 2.0f;

    vertex_buffer_data[9 * i + 3] = -size;
    vertex_buffer_data[9 * i + 4] = -0.2f;
    vertex_buffer_data[9 * i + 5] = 2.0f;

    vertex_buffer_data[9 * i + 6] = size;
    vertex_buffer_data[9 * i + 7] = 0.2f;
    vertex_buffer_data[9 * i + 8] = 2.0f;

    i++;
        
    vertex_buffer_data[9 * i] = size;
    vertex_buffer_data[9 * i + 1] = 0.2f;
    vertex_buffer_data[9 * i + 2] = 2.0f;

    vertex_buffer_data[9 * i + 3] = size;
    vertex_buffer_data[9 * i + 4] = -0.2f;
    vertex_buffer_data[9 * i + 5] = 2.0f;
    
    vertex_buffer_data[9 * i + 6] = -size;
    vertex_buffer_data[9 * i + 7] = -0.2f;
    vertex_buffer_data[9 * i + 8] = 2.0f;

    this->object = create3DObject(GL_TRIANGLES, 2 * (n + 3) * 3, vertex_buffer_data, color, GL_FILL);
}

void Line::draw(glm::mat4 VP) {
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

void Line::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Line::tick() {
    // this->position.x -= 0.1;    
}

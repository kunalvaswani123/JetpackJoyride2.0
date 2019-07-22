#include "beam.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Beam::Beam(float x, float y, double rand_y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->size=0;
    this->rand_y=rand_y;
    this->color=color;
    this->flag = true;
    this->count = 0;
    this->move = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Beam::draw(glm::mat4 VP) {
    if (this->size < 18)
    {
        GLfloat vertex_buffer_data[L];
        int j = 0;
        vertex_buffer_data[j++] = -15.0f;
        vertex_buffer_data[j++] = this->rand_y + 0.5;
        vertex_buffer_data[j++] = 2.0f;
        vertex_buffer_data[j++] = -15.0f;
        vertex_buffer_data[j++] = this->rand_y - 0.5;
        vertex_buffer_data[j++] = 2.0f;
        vertex_buffer_data[j++] = -15.0f + this->size;
        vertex_buffer_data[j++] = this->rand_y - 0.5;
        vertex_buffer_data[j++] = 2.0f;
        vertex_buffer_data[j++] = -15.0f + this->size;
        vertex_buffer_data[j++] =  this->rand_y + 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = -15.0f + this->size;
        vertex_buffer_data[j++] =  this->rand_y - 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = -15.0f;
        vertex_buffer_data[j++] =  this->rand_y + 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f;
        vertex_buffer_data[j++] =  this->rand_y + 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f;
        vertex_buffer_data[j++] =  this->rand_y - 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f - this->size;
        vertex_buffer_data[j++] =  this->rand_y - 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f - this->size;
        vertex_buffer_data[j++] =  this->rand_y + 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f - this->size;
        vertex_buffer_data[j++] =  this->rand_y - 0.5;
        vertex_buffer_data[j++] =  2.0f;
        vertex_buffer_data[j++] = 15.0f;
        vertex_buffer_data[j++] =  this->rand_y + 0.5;
        vertex_buffer_data[j++] =  2.0f;  
        
        int i, n = 600;
        for (i = 4; i < n / 2 + 4; i++)
        {
            vertex_buffer_data[9 * i] = -15.0f;
            vertex_buffer_data[9 * i + 1] = this->rand_y;
            vertex_buffer_data[9 * i + 2] = 2.0f;

            vertex_buffer_data[9 * i + 3] = -15.0f + (double)cos((4 * M_PI * i)/n);
            vertex_buffer_data[9 * i + 4] = this->rand_y +  (double)sin((4 * M_PI * i)/n);
            vertex_buffer_data[9 * i + 5] = 2.0f;
            
            vertex_buffer_data[9 * i + 6] = -15.0f + (double)cos((4 * M_PI * (i + 1))/n);
            vertex_buffer_data[9 * i + 7] = this->rand_y + (double)sin((4 * M_PI * (i + 1))/n);
            vertex_buffer_data[9 * i + 8] = 2.0f;
        }
        for (; i < n + 4; i++)
        {
            vertex_buffer_data[9 * i] = 15.0f;
            vertex_buffer_data[9 * i + 1] = this->rand_y;
            vertex_buffer_data[9 * i + 2] = 2.0f;

            vertex_buffer_data[9 * i + 3] = 15.0f + (double)cos((4 * M_PI * i)/n);
            vertex_buffer_data[9 * i + 4] = this->rand_y + (double)sin((4 * M_PI * i)/n);
            vertex_buffer_data[9 * i + 5] = 2.0f;
            
            vertex_buffer_data[9 * i + 6] = 15.0f + (double)cos((4 * M_PI * (i + 1))/n);
            vertex_buffer_data[9 * i + 7] = this->rand_y + (double)sin((4 * M_PI * (i + 1))/n);
            vertex_buffer_data[9 * i + 8] = 2.0f;
        }
        this->object = create3DObject(GL_TRIANGLES, (n + 4) * 3, vertex_buffer_data, this->color, GL_FILL);
    }
    else
    {
        GLfloat vertex_buffer_data[]={};
        this->object = create3DObject(GL_TRIANGLES, 0, vertex_buffer_data, this->color, GL_FILL);   
    }
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

void Beam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Beam::tick() {
    if(this->size<=18 && this->flag)
        this->size += 0.1;
    else if (this->count <= 5)
        this->count += 0.1;
    else
    {
        this->flag = false;
        this->size = 20;
    }
    if (abs(this->position.y) > 5)
        this->move = 1 - this->move;
    if (this->move == 0)
        this->position.y -= 0.1;
    else
        this->position.y += 0.1;
}

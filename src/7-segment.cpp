#include "7-segment.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Seven::Seven(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->score = 0;
    this->lives = 15;
    this->level = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Seven::draw(glm::mat4 VP) {
    static GLfloat vertex_buffer_data[L];
    
    int display[14][7] = {
        {1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0},
        {1, 0, 1, 1, 0, 1, 1},
        {1, 0, 0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 0, 1},
        {0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 1, 1}    
    };
    //H-13, S-10, L-11 dash -12
    int size = 0;
    int arr[100];
    int i = 0;
    double distx = 0;
    double disty = 0;
    int c = 0;

    int temp = this->lives;
    if (temp == 0)
        arr[size++] = 0;
    while(temp > 0)
    {
        arr[size++] = temp % 10;
        temp = temp / 10;
    }
    arr[size++] = 12, arr[size++] = 13;

    int brk1 = size;

    temp = this->level;
    if (temp == 0)
        arr[size++] = 0;
    while(temp > 0)
    {
        arr[size++] = temp % 10;
        temp /= 10;
    }
    arr[size++] = 12, arr[size++] = 11;

    int brk2 = size;

    temp = this->score;
    if (temp == 0)
        arr[size++] = 0;
    while(temp > 0)
    {
        arr[size++] = temp % 10;
        temp /= 10;
    }
    arr[size++] = 12, arr[size++] = 10;

    for (i = size - 1; i >= 0; i--)
    {
        if(display[arr[i]][0]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + 0.05f;
            vertex_buffer_data[18*c + 1] = disty + 1.1f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 0.05f;
            vertex_buffer_data[18*c + 4] = disty + 1.0f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + 1.05f;
            vertex_buffer_data[18*c + 7] = disty + 1.1f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + 1.05f;
            vertex_buffer_data[18*c + 10] = disty + 1.1f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 1.05f;
            vertex_buffer_data[18*c + 13] = disty + 1.0f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 0.05f;
            vertex_buffer_data[18*c + 16] = disty + 1.0f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][1]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + -0.05f;
            vertex_buffer_data[18*c + 1] = disty + 1.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 0.05f;
            vertex_buffer_data[18*c + 4] = disty + 1.0f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + -0.05f;
            vertex_buffer_data[18*c + 7] = disty + 0.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + -0.05f;
            vertex_buffer_data[18*c + 10] = disty + 0.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 0.05f;
            vertex_buffer_data[18*c + 13] = disty + 1.0f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 0.05f;
            vertex_buffer_data[18*c + 16] = disty + 0.0f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][2]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + -0.05f;
            vertex_buffer_data[18*c + 1] = disty + 0.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 0.05f;
            vertex_buffer_data[18*c + 4] = disty + 0.0f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + -0.05f;
            vertex_buffer_data[18*c + 7] = disty + -1.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + -0.05f;
            vertex_buffer_data[18*c + 10] = disty + -1.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 0.05f;
            vertex_buffer_data[18*c + 13] = disty + 0.0f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 0.05f;
            vertex_buffer_data[18*c + 16] = disty + -1.0f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][3]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + 0.05f;
            vertex_buffer_data[18*c + 1] = disty + -1.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 0.05f;
            vertex_buffer_data[18*c + 4] = disty + -1.1f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + 1.05f;
            vertex_buffer_data[18*c + 7] = disty + -1.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + 1.05f;
            vertex_buffer_data[18*c + 10] = disty + -1.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 1.05f;
            vertex_buffer_data[18*c + 13] = disty + -1.1f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 0.05f;
            vertex_buffer_data[18*c + 16] = disty + -1.1f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][4]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + 1.0f;
            vertex_buffer_data[18*c + 1] = disty + 0.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 1.1f;
            vertex_buffer_data[18*c + 4] = disty + 0.0f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + 1.0f;
            vertex_buffer_data[18*c + 7] = disty + -1.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + 1.0f;
            vertex_buffer_data[18*c + 10] = disty + -1.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 1.1f;
            vertex_buffer_data[18*c + 13] = disty + 0.0f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 1.1f;
            vertex_buffer_data[18*c + 16] = disty + -1.0f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][5]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + 1.0f;
            vertex_buffer_data[18*c + 1] = disty + 1.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 1.1f;
            vertex_buffer_data[18*c + 4] = disty + 1.0f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + 1.0f;
            vertex_buffer_data[18*c + 7] = disty + 0.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + 1.0f;
            vertex_buffer_data[18*c + 10] = disty + 0.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 1.1f;
            vertex_buffer_data[18*c + 13] = disty + 1.0f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 1.1f;
            vertex_buffer_data[18*c + 16] = disty + 0.0f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        if(display[arr[i]][6]==1)
        {
            vertex_buffer_data[18*c + 0] = distx + 0.05f;
            vertex_buffer_data[18*c + 1] = disty + 0.0f;
            vertex_buffer_data[18*c + 2] = 4.0f;

            vertex_buffer_data[18*c + 3] = distx + 0.05f;
            vertex_buffer_data[18*c + 4] = disty + 0.1f;
            vertex_buffer_data[18*c + 5] = 4.0f;

            vertex_buffer_data[18*c + 6] = distx + 1.05f;
            vertex_buffer_data[18*c + 7] = disty + 0.0f;
            vertex_buffer_data[18*c + 8] = 4.0f;

            vertex_buffer_data[18*c + 9] = distx + 1.05f;
            vertex_buffer_data[18*c + 10] = disty + 0.0f;
            vertex_buffer_data[18*c + 11] = 4.0f;

            vertex_buffer_data[18*c + 12] = distx + 1.05f;
            vertex_buffer_data[18*c + 13] = disty + 0.1f;
            vertex_buffer_data[18*c + 14] = 4.0f;

            vertex_buffer_data[18*c + 15] = distx + 0.05f;
            vertex_buffer_data[18*c + 16] = disty + 0.1f;
            vertex_buffer_data[18*c + 17] = 4.0f;
            c++;
        }
        distx += 1.3;
        if (i == brk1 || i == brk2)
        {
            disty += 2.5;
            distx = 0;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, c * 6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Seven::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Seven::tick() {
    
}

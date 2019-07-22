#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coin.h"
#include "line.h"
#include "beam.h"
#include "boomerang.h"
#include "platform.h"
#include "prop.h"
#include "magnet.h"
#include "powerup.h"
#include "powerup2.h"
#include "ring.h"
#include "water.h"
#include "7-segment.h"
#include "wall.h"
#include "dragon.h"
#include "ice.h"

#define pb push_back
typedef long long ll;
const ll L = 1e5 + 5;

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball player;
Wall wall;
vector<Coin> coins;
vector<Platform> ground;
vector<Line> lines;
vector<Beam> beam;
vector<Boomerang> boom;
vector<Prop> props;
vector<Magnet> magnet;
vector<Powerup> boost;
vector<Powerup2> extra_coins;
vector<Ring> ring;
vector<Water> water;
vector<Ice> ice;
Seven display;
Dragon dragon;

bool coins_detect[L];
bool special_coins[L];
bool speed_up = false;
bool semi_circle = false;
int dis_covered = 0;
ll played = 0;

float screen_zoom = 0.25, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
/* Render the scene with openGL */
/* Edit this function according to your assignment */

void move_screen(ll dir) {
    ll i;
    double increase = 0.15;
    if (speed_up)
        increase = 3;
    else if (display.level == 2)
        increase = 0.3;
    if (screen_center_x + dir * increase <= 0)
    {
        for (i = 0; i < coins.size(); i++)
        {
            if (!coins_detect[i])
                coins[i].position.x += dir * increase;
        }
        for(i = 0; i < lines.size(); i++)
            lines[i].position.x += dir * increase;
        screen_center_x += dir * increase;
    }
}

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0, 0, 10);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    int i;
    for (i = 0; i < ground.size(); i++)
        ground[i].draw(VP);

    player.draw(VP);

    display.draw(VP);

    wall.draw(VP);

    for(i=0;i<props.size();i++)
    {
        ll check = abs(props[i].position.y-player.position.y);
        if(check > 1.3 && check < 5)
            props[i].draw(VP);
    }
    for (i = 0; i < coins.size(); i++)
    {
        if(!coins_detect[i])
            coins[i].draw(VP);
    }

    for(i = 0; i < lines.size(); i++)
    {
        if(lines[i].flag)
            lines[i].draw(VP);
    }

    if(beam.size() != 0)
        beam.back().draw(VP);

    if(boom.size() != 0)
        boom.back().draw(VP);

    if(magnet.size() != 0)
        magnet.back().draw(VP);

    if(boost.size() != 0)
        boost.back().draw(VP);

    if(extra_coins.size() != 0)
        extra_coins.back().draw(VP);

    if(ring.size()!=0)
        ring.back().draw(VP);

    
    for (i=0;i<water.size();i++)
    {
        if(water[i].exist)
            water[i].draw(VP);
    }

    for (i=0;i<ice.size();i++)
    {
        if(ice[i].exist)
            ice[i].draw(VP);
    }

    if (dragon.flag == 1)
        dragon.draw(VP);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(screen_zoom >= 0.04)
        screen_zoom += yoffset * 0.01;
    else
        screen_zoom = 0.041;
    float top    = 4 / screen_zoom;
    float bottom = -4 / screen_zoom;
    float left   = -4 / screen_zoom;
    float right  = 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    // int right = glfwGetKey(window, GLFW_KEY_RIGHT);

    glfwSetScrollCallback(window, scroll_callback);
    if (speed_up)
        return;
    if (semi_circle)
    {
        if (right)
        {
            if (player.position.x >= 0)
                move_screen(-1);
            played++;
            player.position.x += 0.15;
            player.position.y = - sqrt(16 - player.position.x * player.position.x);
            if (player.position.x > 3.9)
            {
                player.position.x = -1;
                player.position.y = -12;
                semi_circle = false;
                ring.clear();
            }
        }
        if (left)
        {
            if (player.position.x <= -12)
                move_screen(1);
            player.position.x -= 0.15;
            player.position.y = - sqrt(16 - player.position.x * player.position.x);
            if (player.position.x < -3.9)
            {
                player.position.x = -1;
                player.position.y = -12;
                semi_circle = false;
            }
        }
        return;
    }
    if (up)
    {
        player.speed_y += 1;
        props.pb(Prop(player.position.x, player.position.y - 2, COLOR_ORANGE));
        props.pb(Prop(player.position.x - 0.3, player.position.y - 2, COLOR_ORANGE));
        props.pb(Prop(player.position.x + 0.3   , player.position.y - 2, COLOR_ORANGE));
    }
    if (!up)
        props.clear();
    if (right)
    {
        if (player.position.x >= 0)
            move_screen(-1);
        else
            player.position.x += 0.15;
        played++;
    }
    if (left)
    {
        if (player.position.x <= -12)
            move_screen(1);
        else
            player.position.x -= 0.15;
    }
    if (space)
    {
        water.pb(Water(player.position.x, player.position.y, COLOR_LIGHTBLUE));
        water.back().speed_y = player.speed_y + 5;
        water.back().speed_x = player.speed_x + 5;
    }
}

void check_magnetic_force()
{
    if(magnet.size() != 0)
    {
        ll pos_x = magnet.back().position.x;
        ll temp = abs(player.position.y - 15);
        if (temp < 1)temp = 1;
        if (player.position.x >= pos_x && player.position.x <= pos_x + 5)
        {
            player.speed_y += (250 / (temp * temp));
            if (player.position.y > 15.0)
                player.position.y = 15.0;
        }
    }
}

void check_powerups_collision(bounding_box_t play_box)
{
    if(boost.size() != 0)
    {
        bounding_box_t boost_box;
        boost_box.x = boost.back().position.x;
        boost_box.y = boost.back().position.y;
        boost_box.width = 2.0;
        boost_box.height = 2.0;
        if(detect_collision(boost_box, play_box))
        {
            speed_up = true;
            boost.clear();
        }
    }
    if(extra_coins.size() != 0)
    {
        bounding_box_t extra_coins_box;
        extra_coins_box.x = extra_coins.back().position.x;
        extra_coins_box.y = extra_coins.back().position.y;
        extra_coins_box.width = 2.0;
        extra_coins_box.height = 2.0;
        if(detect_collision(extra_coins_box, play_box))
        {
            display.score += 10;
            extra_coins.clear();
        }
    }
}

void check_semicircle()
{
    if(ring.size() == 0)
        return;
    double check_dist_x = player.position.x * player.position.x; 
    double check_dist_y = player.position.y * player.position.y;
    double check_dist = check_dist_y + check_dist_x;
    if (check_dist < 17 && check_dist > 15 && player.position.y <= 0)
        semi_circle = true;
}

void check_collision_water()
{
    ll i,j;
    for(i=0;i<water.size();i++)
    {
        if(water[i].exist)
        {
            for(j=0;j<lines.size();j++)
            {
                double co = 4.65 * cos((lines[j].rotation * M_PI) / 180);
                double si = 4.65 * sin((lines[j].rotation * M_PI) / 180);
                
                double p1_x = lines[j].position.x + co;
                double p1_y = lines[j].position.y + si;
                
                double p2_x = lines[j].position.x - co;
                double p2_y = lines[j].position.y - si;

                double len1_x = (p1_x - water[i].position.x) * (p1_x - water[i].position.x);
                double len2_x = (p2_x - water[i].position.x) * (p2_x - water[i].position.x);

                double len1_y = (p1_y - water[i].position.y) * (p1_y - water[i].position.y);
                double len2_y = (p2_y - water[i].position.y) * (p2_y - water[i].position.y);

                double check = sqrt(len1_x + len1_y) + sqrt(len2_x + len2_y) - 9.3;

                if(abs(check) < 0.1)
                    lines[j].flag = false;
            }
        }
    }
}

void check_collision_barry()
{
    ll j;
    for(j=0;j<lines.size();j++)
    {
        double co = 4.65 * cos((lines[j].rotation * M_PI) / 180);
        double si = 4.65 * sin((lines[j].rotation * M_PI) / 180);
        
        double p1_x = lines[j].position.x + co;
        double p1_y = lines[j].position.y + si;
        
        double p2_x = lines[j].position.x - co;
        double p2_y = lines[j].position.y - si;

        double len1_x = (p1_x - player.position.x) * (p1_x - player.position.x);
        double len2_x = (p2_x - player.position.x) * (p2_x - player.position.x);

        double len1_y = (p1_y - player.position.y) * (p1_y - player.position.y);
        double len2_y = (p2_y - player.position.y) * (p2_y - player.position.y);

        double check = sqrt(len1_x + len1_y) + sqrt(len2_x + len2_y) - 9.3;
        
        if(lines[j].flag && abs(check) < 0.1)
        {
            cout << "Hit by a Line" << endl;
            player.position.x = -12;
            player.position.y = -10;
            player.speed_y = player.speed_x = 0;
            display.lives -= 1;
        }   
    }
}

void check_collision_water_beam()
{
    ll i,j;
    for(i=0;i<water.size();i++)
    {
        if(water[i].exist && beam.size() != 0)
        {
            bounding_box_t water_box;
            water_box.x = water[i].position.x;
            water_box.y = water[i].position.y;
            water_box.width = 1;
            water_box.height = 1;
            bounding_box_t p1;
            bounding_box_t p2;
            p1.y = beam.back().rand_y;
            p1.x = -15.0f + (beam.back().size + 1) / 2;
            p1.width = beam.back().size + 1;
            p1.height = 2;
            p2.y = beam.back().rand_y;
            p2.x = 15.0f - (beam.back().size + 1) / 2;
            p2.width = beam.back().size + 1;
            p2.height = 2;
            if(detect_collision(water_box, p1) || detect_collision(water_box, p2))
            {
                beam.back().flag = false;
                beam.back().color = COLOR_LIGHTBLUE;
            }
        }
    }
}

void check_collision_barry_beam(bounding_box_t play_box)
{
    if(beam.size() == 0)
        return;
    else if (beam.back().flag == false)
        return;
    bounding_box_t p1;
    bounding_box_t p2;
    p1.y = beam.back().position.y;
    p1.x = -15.0f + (beam.back().size + 1) / 2;
    p1.width = beam.back().size + 1;
    p1.height = 2;
    p2.y = beam.back().position.y;
    p2.x = 15.0f - (beam.back().size + 1) / 2;
    p2.width = beam.back().size + 1;
    p2.height = 2;
    if(detect_collision(play_box, p1) || detect_collision(play_box, p2))
    {
        beam.clear();
        cout << "Hit by a Beam" << endl;
        player.position.x = -12;
        player.position.y = -10;
        player.speed_y = player.speed_x = 0;
        display.lives -= 1;
    }
}

void check_collision_boomerang(bounding_box_t play_box)
{
    if(boom.size() == 0)
        return;
    bounding_box_t b_box;
    b_box.x = boom.back().position.x;
    b_box.y = boom.back().position.y;
    b_box.width = 4;
    b_box.height = 4;
    if(detect_collision(play_box, b_box))
    {
        cout << "Hit by a Boomerang" << endl;
        player.position.x = -12;
        player.position.y = -10;
        player.speed_y = player.speed_x = 0;
        display.lives -= 1;
    }
}

void check_collision_ice(bounding_box_t play_box)
{
    ll i;
    for (i = 0; i < ice.size(); i++)
    {
        if (ice[i].exist)
        {
	        bounding_box_t i_box;
	        i_box.x = ice[i].position.x;
	        i_box.y = ice[i].position.y;
	        i_box.width = 1;
	        i_box.height = 1;
	        if(detect_collision(play_box, i_box))
	        {
	            cout << "Hit by ice" << endl;
	            player.position.x = -12;
	            player.position.y = -10;
	            player.speed_y = player.speed_x = 0;
	            display.lives -= 1;
	            ice[i].exist = false;
	        }
        }
    }
}

void tick_elements() {
    int i;
    if (speed_up && dis_covered <= 100)
    {
        move_screen(-1);
        dis_covered++;
        return;
    }
    speed_up = false, dis_covered = 0;

    if (!semi_circle)
        player.tick();

    if (dragon.flag == 1)
        dragon.tick();

    bounding_box_t play_box;
    play_box.x = player.position.x;
    play_box.y = player.position.y;
    play_box.width = 2.0;
    play_box.height = 2.0;
    for (i = 0; i < coins.size(); i++)
    {
        bounding_box_t coin_box;
        coin_box.x = coins[i].position.x;
        coin_box.y = coins[i].position.y;
        coin_box.width = 1.3;
        coin_box.height = 1.3;
        if (detect_collision(coin_box, play_box))
        {
            int temp = coins[i].position.x;
            if(!coins_detect[i])
            {
                if (special_coins[i])
                    display.score += 2;
                else
                    display.score += 1;
            }
            coins_detect[i] = true;
        }
    }

    check_powerups_collision(play_box);

    if (beam.size()!=0 && beam.back().size > 18)
        beam.clear();

    if (played % 300 == 0)
        magnet.pb(Magnet((rand() % 10) - 11, 15, COLOR_DARKRED));

    if ((played + 200 ) % 350 == 0)
        beam.pb(Beam(0, 0, (rand() % 4) - 4, COLOR_DARKRED));

    if ((played + 1) % 400 == 0)
        boom.pb(Boomerang(13, 13, COLOR_GOLDENROD));

    if ((played + 600) % 700 == 0)
        boost.pb(Powerup(-15, 9, COLOR_LIGHTRED));

    if ((played + 250) % 700 == 0)
        extra_coins.pb(Powerup2(-15, 9, COLOR_GOLDENROD));

    if (played % 250 == 0 && ring.size() == 0)
        ring.pb(Ring(0, 0, COLOR_LIGHTGREY));

    if ((played + 100) % 250 == 0)
    {
        semi_circle = false;
        player.speed_y = 0;
        ring.clear();
    }

    if(played % 450 == 0)
        magnet.clear();

    if (played == 1700)
        dragon.flag = 1;

    if(dragon.flag == 1)
    {
        if (ice.size() == 0 || abs(dragon.position.x - ice.back().position.x) > 9.0)
            ice.pb(Ice(dragon.position.x, dragon.position.y, COLOR_ICEBLUE));
        ice.back().speed_y = 2.0;
        ice.back().speed_x = -12.0;
    }

    if(display.score >= 35)
    {
        if (display.level == 1)
        {
            cout << "----------" << endl;
            cout << "Level 2!" << endl;
            cout << "----------" << endl;
        }
        display.level = 2;
    }

    if(beam.size() != 0)
        beam.back().tick();

    if(boom.size() != 0)
        boom.back().tick();

    if(boost.size() != 0)
    {
        if(boost.back().position.x > 1.0)
            boost.clear();
        else
            boost.back().tick();
    }

    if(extra_coins.size() != 0)
    {
        if(extra_coins.back().position.x > 1.0)
            extra_coins.clear();
        else
            extra_coins.back().tick();
    }

    for(i=0;i<props.size();i++)
        props[i].tick();

    for(i=0;i<water.size();i++)
    {
        if(abs(water[i].position.x) > 17 || abs(water[i].position.y) > 17)
            water[i].exist = false;
        if(water[i].exist)
            water[i].tick();
    }

    for(i=0;i<ice.size();i++)
    {
        if(abs(ice[i].position.x) > 17 || abs(ice[i].position.y) > 17)
            ice[i].exist = false;
        if(ice[i].exist)
            ice[i].tick();
    }

    check_magnetic_force();

    check_semicircle();
    
    if(!semi_circle)
    {
        check_collision_water();

        check_collision_barry();

        check_collision_water_beam();
        
        check_collision_barry_beam(play_box);

        check_collision_boomerang(play_box);

        check_collision_ice(play_box);
    }

    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Ball(-12, -10, COLOR_RED);
    display = Seven(-15, 9, COLOR_BLACK);
    wall = Wall(0, 0);
    dragon = Dragon(13, 4, COLOR_DARKBLUE);
    int i, j;
    for (i = -30; i < 30; i+=4)
        ground.pb(Platform(i, -14.77, COLOR_RED));
    for (i = 2; i < 2000; i+=24)
    {
        int rand_y = (rand() % 24) - 12;
        color_t color= COLOR_YELLOW;
        int flag = 1;
        if (i!=2 && ((i - 2) / 24) % 4 == 0 )
            color = COLOR_BLUE, flag = 0;
        for(j = i; j < i + 10; j+=2)
        {
            coins.pb(Coin(j, rand_y, color));
            if(flag == 0)
                special_coins[coins.size() - 1] = true;
        }
    }
    for(i = 18; i < 2000; i+=24)
    {
        int rand_y = (rand() % 16) - 8;
        lines.pb(Line(i, rand_y, 4, COLOR_ORANGE));
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 1.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);
    cout << "---------------------------------------------" << endl;
    cout << "Health, Level, Score displayed on the screen!" << endl;
    cout << "---------------------------------------------" << endl;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (display.lives == 0)
        {
            cout << "YOU LOST!!" << endl;
            break;
        }

        if (played == 2400)
        {   
            cout << "YOU WON!!" << endl;
            cout << "YOUR SCORE: " << -(int)screen_center_x + display.score + display.lives * 5 << endl;
            break;
        }

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

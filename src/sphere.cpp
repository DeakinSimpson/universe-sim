#include<sphere.hpp>
#include<vector>
#include<math.h>

// for testing
#include<iostream>

// TODO: change later as these are static and not customisable
static int lat_line_count = 10;
static int lon_line_count = 4;

// contructors
// --------------------------------------------------------------------------

Sphere::Sphere(float radius, Coord coord)
{
    this->radius = radius;
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
    this->shader = nullptr;

    setVerticies();
    setIndicies();
}

Sphere::Sphere(float radius, float x, float y, float z)
{
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->z = z;
    this->shader = nullptr;

    setVerticies();
    setIndicies();
}

// setters
// --------------------------------------------------------------------------

// set pos with Coord struct
void Sphere::setPos(Coord coord)
{
    this->x = coord.x;
    this->y = coord.y;
    this->z = coord.z;
}

// set pos with x, y, z input
void Sphere::setPos(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// set the radius of the sphere
void Sphere::setRadius(float radius)
{
    this->radius = radius;
}

void Sphere::setShader(const char* vertex_shader, const char* fragment_shader)
{
    this->shader = new Shader(vertex_shader, fragment_shader);
}

// getters
// --------------------------------------------------------------------------
Coord Sphere::getPos()
{
    return {this->x, this->y, this->z};
}

float Sphere::getRadius()
{
    return this->radius;
}

std::vector<float> Sphere::getVerticies()
{
    return this->verticies;
}

std::vector<unsigned int> Sphere::getIndicies()
{
    return this->indicies;
}

// functions
// --------------------------------------------------------------------------

// gets an array of verticies for the sphere
void Sphere::setVerticies()
{
    // create the output verticies vector
    std::vector<float> verticies;

    // loop through each verticle (latitude) angle
    for (int lat_increment = 0; lat_increment < lat_line_count; ++lat_increment)
    {
        float lat_angle  = (-90.0f + (180.0f / lat_line_count) * lat_increment) * (3.14159265358979323f / 180.0f); // get the current angle for lat (divide the total split by current increment)
        float lat_radius = this->radius * cos(lat_angle); // get the circle radius
        float lon_height = radius * sin(lat_angle); // get the circle height

        // loop through each horizontal (longitude) edge
        for (int lon_increment = 0; lon_increment < lon_line_count; ++lon_increment)
        {
            // get the current angle for lon (divide the total split by current increment)
            float lon_angle = ((360.0f / lon_line_count) * lon_increment) * (3.14159265358979323f / 180.0f);

            // get the vertex xyz
            float v_x = lat_radius * cos(lon_angle);
            float v_y = lat_radius * sin(lon_angle);
            float v_z = lon_height;

            // add verticies to verticie array
            verticies.push_back(v_x);
            verticies.push_back(v_y);
            verticies.push_back(v_z);
        }
    }

    this->verticies = verticies;
}

void Sphere::setIndicies()
{
    // create the output vector
    std::vector<unsigned int> indicies;

        // loop through each verticle (latitude) angle (-1 because it indexs the line above)
    for (int lat_increment = 0; lat_increment < lat_line_count - 1; ++lat_increment)
    {
        for (int lon_increment = 0; lon_increment < lon_line_count; ++lon_increment)
        {
            // get current lat pos
            int top_ring_pos = (lat_increment * lon_line_count);
            int bottom_ring_pos = ((lat_increment + 1) * lon_line_count);

            int left_ring_pos = (lon_increment % lon_line_count);
            int right_ring_pos = ((lon_increment  + 1) % lon_line_count);

            // get the verticies of the quad
            int top_left        = top_ring_pos    + left_ring_pos;
            int top_right       = top_ring_pos    + right_ring_pos;
            int bottom_left     = bottom_ring_pos + left_ring_pos;
            int bottom_right    = bottom_ring_pos + right_ring_pos;

            // add the indicies to the indicies array (must share same diagonal)
            // --------------------------------------
            // first triangle
            indicies.push_back(top_left);
            indicies.push_back(top_right);
            indicies.push_back(bottom_left);
            // second triangle
            indicies.push_back(top_right);
            indicies.push_back(bottom_right);
            indicies.push_back(bottom_left);
        }
    }

    this->indicies = indicies;
}


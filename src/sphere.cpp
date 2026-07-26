#include<sphere.hpp>
#include<vector>
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<renderer.hpp>

// for testing
#include<iostream>

// TODO: change later as these are static and not customisable
static int lat_line_count = 100;
static int lon_line_count = 100;

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
    setUV();
    setNormals();
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
    setUV();
    setNormals();
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

void Sphere::addPos(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}


// getters
// --------------------------------------------------------------------------
Coord Sphere::getPos() const
{
    return {this->x, this->y, this->z};
}

float Sphere::getRadius() const
{
    return this->radius;
}

std::vector<float> Sphere::getVerticies() const
{
    return this->verticies;
}

std::vector<unsigned int> Sphere::getIndicies() const
{
    return this->indicies;
}

Shader* Sphere::getShader() const
{
    return this->shader;
}

std::vector<float> Sphere::getUV() const
{
    return this->uv;
}

std::vector<float> Sphere::getNormals() const
{
    return this->normals;
}

// TODO! add variable model to not perform translation every frame
// gets the initial models matrix for the position of the sphere
glm::mat4 Sphere::getModelMatrix()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(this->x, this->y, this->z));
}

std::vector<float> Sphere::getInterleavedVerticies() const
{
    std::vector<float> interleavedVerticies;

    // loop through all verticies (verticies and uv and create a final output)
    for (size_t i = 0; i < this->verticies.size() / 3; i++)
    {
        // push verticies
        interleavedVerticies.push_back(this->verticies[(i * 3)    ]); // push x
        interleavedVerticies.push_back(this->verticies[(i * 3) + 1]); // push y
        interleavedVerticies.push_back(this->verticies[(i * 3) + 2]); // push z

        // // push uv
        // interleavedVerticies.push_back(this->uv[(i * 2)    ]); // push u
        // interleavedVerticies.push_back(this->uv[(i * 2) + 1]); // push v

        // push normals (nx, ny, nz)
        interleavedVerticies.push_back(this->normals[(i * 3)    ]);
        interleavedVerticies.push_back(this->normals[(i * 3) + 1]);
        interleavedVerticies.push_back(this->normals[(i * 3) + 2]);
    }

    return interleavedVerticies;
}


// public functions
// --------------------------------------------------------------------------
void Sphere::draw(glm::vec3 lightPos)
{
    // TODO! add variable model to not perform translation every frame
    drawObject(getInterleavedVerticies(), this->indicies, this->shader, getModelMatrix(), lightPos);
}

// private functions
// --------------------------------------------------------------------------

// gets an array of verticies for the sphere
void Sphere::setVerticies()
{
    // create the output verticies vector
    std::vector<float> verticies;

    // loop through each verticle (latitude) angle
    for (int lat_increment = 0; lat_increment <= lat_line_count; ++lat_increment)
    {
        float lat_angle  = (-90.0f + (180.0f / lat_line_count) * lat_increment) * (3.14159265358979323f / 180.0f); // get the current angle for lat (divide the total split by current increment)
        float lat_radius = this->radius * cos(lat_angle); // get the circle radius
        float lon = radius * sin(lat_angle); // get the circle height

        // loop through each horizontal (longitude) edge
        for (int lon_increment = 0; lon_increment < lon_line_count; ++lon_increment)
        {
            // get the current angle for lon (divide the total split by current increment)
            float lon_angle = ((360.0f / lon_line_count) * lon_increment) * (3.14159265358979323f / 180.0f);

            // get the vertex xyz
            float v_x = lat_radius * cos(lon_angle);
            float v_z = lat_radius * sin(lon_angle);
            float v_y = lon;

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

        // loop through each verticle (latitude) angle
    for (int lat_increment = 0; lat_increment < lat_line_count; ++lat_increment)
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

void Sphere::setUV()
{
    std::vector<float> uv;

    // loop through all verticies
    for (int lat_increment = 0; lat_increment <= lat_line_count; ++lat_increment)
    {
        for (int lon_increment = 0; lon_increment < lon_line_count; ++lon_increment)
        {
            // get both u and v values
            float u = (float)lon_increment / lon_line_count;
            float v = (float)lat_increment / lat_line_count;

            // push them to the uv vector
            uv.push_back(u);
            uv.push_back(v);
        }
    }

    this->uv = uv;
}

void Sphere::setNormals()
{
    std::vector<float> normals;

    float length_inverse = 1.0f / this->radius;

    // loop through all verticies
    for (size_t i = 0; i < verticies.size() / 3; i++)
    {
        // push the normals for all 
        normals.push_back(verticies[i * 3]     * length_inverse);
        normals.push_back(verticies[i * 3 + 1] * length_inverse);
        normals.push_back(verticies[i * 3 + 2] * length_inverse);
    }

    this->normals = normals;
}
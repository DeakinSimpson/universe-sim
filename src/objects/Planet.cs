using System.Numerics;
using Silk.NET.Maths;
using Silk.NET.Windowing;

public class Planet
{
    // public variables
    public float x, y, z, radius;
    public int resolution;

    // private variables
    private List<float> vertices = new List<float>();
    private List<uint> indicies = new List<uint>();
    private List<float> uv = new List<float>();
    private List<float> normals = new List<float>();
    private Shader shader;

    public Planet(float x, float y, float z, float radius, int resolution, Shader shader)
    {
        // set initial variables
        this.x = x;
        this.y = y;
        this.z = z;
        this.radius = radius;
        this.resolution = resolution;
        this.shader = shader;

        // run initialisation functions
        setVertices();
        setIndicies();
        setUv();
        setNormals();
    }

    // setters
    // -------------------------------------------------------------------------
    private void setVertices()
    {
        // create the output vertices vector
        List<float> vertices = new List<float>();

        for (int lat_i = 0; lat_i <= resolution; ++lat_i)
        {
            float lat_angle  = (-90.0f + (180.0f / resolution) * lat_i) * (3.14159265358979323f / 180.0f); // get the current angle for lat (divide the total split by current increment)
            float lat_radius = this.radius * (float) Math.Cos(lat_angle); // get the circle radius
            float lon = radius * (float) Math.Sin(lat_angle); // get the circle height  

            // loop through each horizontal (longitude) edge
            for (int lon_i = 0; lon_i < resolution; ++lon_i)
            {
                // get the current angle for lon (divide the total split by current increment)
                float lon_angle = ((360.0f / resolution) * lon_i) * (3.14159265358979323f / 180.0f);

                // get the vertex xyz
                float v_x = lat_radius * (float) Math.Cos(lon_angle);
                float v_z = lat_radius * (float) Math.Sin(lon_angle);
                float v_y = lon;

                // add vertices to verticie array
                vertices.Add(v_x);
                vertices.Add(v_y);
                vertices.Add(v_z);
            }
        }

        this.vertices = vertices;
    }

    private void setIndicies()
    {
        // create the output vector
        List<uint> indicies = new List<uint>();

            // loop through each verticle (latitude) angle
        for (int lat_i = 0; lat_i < resolution; ++lat_i)
        {
            for (int lon_i = 0; lon_i < resolution; ++lon_i)
            {
                // get current lat pos
                int top_ring_pos = lat_i * resolution;
                int bottom_ring_pos = (lat_i + 1) * resolution;

                int left_ring_pos = lon_i % resolution;
                int right_ring_pos = (lon_i  + 1) % resolution;

                // get the vertices of the quad
                int top_left        = top_ring_pos    + left_ring_pos;
                int top_right       = top_ring_pos    + right_ring_pos;
                int bottom_left     = bottom_ring_pos + left_ring_pos;
                int bottom_right    = bottom_ring_pos + right_ring_pos;

                // add the indicies to the indicies array (must share same diagonal)
                // --------------------------------------
                // first triangle
                indicies.Add((uint) top_left);
                indicies.Add((uint) top_right);
                indicies.Add((uint) bottom_left);
                // second triangle
                indicies.Add((uint) top_right);
                indicies.Add((uint) bottom_right);
                indicies.Add((uint) bottom_left);
            }
        }

        this.indicies = indicies;
    }

    private void setUv()
    {
        List<float> uv = new List<float>();

        // loop through all vertices
        for (int lat_i = 0; lat_i <= resolution; ++lat_i)
        {
            for (int lon_i = 0; lon_i < resolution; ++lon_i)
            {
                // get both u and v values
                float u = (float)lon_i / resolution;
                float v = (float)lat_i / resolution;

                // push them to the uv vector
                uv.Add(u);
                uv.Add(v);
            }
        }

        this.uv = uv;        
    }

    private void setNormals()
    {
        List<float> normals = new List<float>();

        float length_inverse = 1.0f / this.radius;

        // loop through all vertices
        for (int i = 0; i < vertices.Count() / 3; i++)
        {
            // push the normals for all 
            normals.Add(vertices[i * 3]     * length_inverse);
            normals.Add(vertices[i * 3 + 1] * length_inverse);
            normals.Add(vertices[i * 3 + 2] * length_inverse);
        }

        this.normals = normals;        
    }

    public List<float> getBufferData()
    {
        List<float> bufferData = new List<float>();

        // loop through all vertices (vertices and uv and create a final output)
        for (int i = 0; i < vertices.Count() / 3; i++)
        {
            // push vertices
            bufferData.Add(vertices[(i * 3)    ]); // push x
            bufferData.Add(vertices[(i * 3) + 1]); // push y
            bufferData.Add(vertices[(i * 3) + 2]); // push z

            // // push uv
            // interleavedVertices.push_back(this->uv[(i * 2)    ]); // push u
            // interleavedVertices.push_back(this->uv[(i * 2) + 1]); // push v

            // push normals (nx, ny, nz)
            bufferData.Add(normals[(i * 3)    ]);
            bufferData.Add(normals[(i * 3) + 1]);
            bufferData.Add(normals[(i * 3) + 2]);
        }

        return bufferData;
    }

    // getters
    // -------------------------------------------------------------------------

    public List<float> getVertices()
    {
        return this.vertices;
    }

    public List<uint> getIndicies()
    {
        return this.indicies;
    }

    public List<float> getUv()
    {
        return this.uv;
    }

    public List<float> getNormals()
    {
        return this.normals;
    }

    public Matrix4x4 getModel()
    {
        return Matrix4x4.CreateTranslation(x, y, z);
    }

    // -- Functions --
    // -------------------------------------------------------------------------

    // TODO: refactor
    public void Render(Renderer renderer, Camera camera, IWindow window, Vector3 lightPosition)
    {
        renderer.renderObject(getBufferData(), indicies, shader, getModel(), camera, window, lightPosition);
    }
}

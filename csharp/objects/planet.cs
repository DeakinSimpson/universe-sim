using System.Numerics;

public class Planet
{
    // public variables
    public float x, y, z, radius;
    public int resolution;

    // private variables
    private List<float> verticies = new List<float>();
    private List<uint> indicies = new List<uint>();
    private List<float> uv = new List<float>();
    private List<float> normals = new List<float>();

    public Planet(float x, float y, float z, float radius, int resolution)
    {
        // set initial variables
        this.x = x;
        this.y = y;
        this.z = z;
        this.radius = radius;
        this.resolution = resolution;

        // run initialisation functions
        setVerticies();
        setIndicies();
        setUv();
        setIndicies();
    }

    private void setVerticies()
    {
        // create the output verticies vector
        List<float> verticies = new List<float>();

        for (int lat_i = 0; lat_i < resolution; ++lat_i)
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

                // add verticies to verticie array
                verticies.Add(v_x);
                verticies.Add(v_y);
                verticies.Add(v_z);
            }
        }

        this.verticies = verticies;
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

                // get the verticies of the quad
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

        // loop through all verticies
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

        // loop through all verticies
        for (int i = 0; i < verticies.Count() / 3; i++)
        {
            // push the normals for all 
            normals.Add(verticies[i * 3]     * length_inverse);
            normals.Add(verticies[i * 3 + 1] * length_inverse);
            normals.Add(verticies[i * 3 + 2] * length_inverse);
        }

        this.normals = normals;        
    }

    public List<float> getVerticies()
    {
        return this.verticies;
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
}

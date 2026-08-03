using System.Numerics;
using Silk.NET.Maths;
using Silk.NET.Windowing;

public class Planet
{
    // public variables
    public float x, y, z, radius;
    public int resolution;
    public Mesh mesh;

    // private variables
    private Shader shader;

    public Planet(float x, float y, float z, float radius, int resolution, Shader shader, Mesh mesh)
    {
        // set initial variables
        this.x = x;
        this.y = y;
        this.z = z;
        this.radius = radius;
        this.resolution = resolution;
        this.shader = shader;
        this.mesh = mesh;
    }

    // getters
    // -------------------------------------------------------------------------

    public Matrix4x4 getModel()
    {
        return Matrix4x4.CreateTranslation(x, y, z);
    }

    // -- Functions --
    // -------------------------------------------------------------------------

    // TODO: refactor
    public void Render(Renderer renderer, Camera camera, IWindow window, Vector3 lightPosition)
    {
        renderer.renderObject(mesh, shader, getModel(), camera, window, lightPosition);
    }
}

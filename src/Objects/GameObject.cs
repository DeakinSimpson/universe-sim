using System.Numerics;
using Silk.NET.Windowing;

public class GameObject
{
    public float x, y, z;
    public Mesh mesh;
    public Shader shader;

    public GameObject(float x, float y, float z, Mesh mesh = null, Shader shader = null)
    {
        this.x          = x;
        this.y          = y;
        this.z          = z;
        this.mesh       = mesh;
        this.shader     = shader;
    }

    // render the game object if it contains a mesh and a shader
    public void Render(Renderer renderer, Camera camera, IWindow window, Vector3 lightPosition)
    {
        if (mesh != null && shader != null)
        {
            renderer.renderObject(mesh, shader, getModelMatrix(), camera, window, lightPosition);
        }
    }

    // get the models 4x4 position matrix
    private Matrix4x4 getModelMatrix()
    {
        return Matrix4x4.CreateTranslation(x, y, z);
    }
}
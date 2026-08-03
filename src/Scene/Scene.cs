using Silk.NET.Windowing;
using System.Numerics;
using System.Drawing;

/*
Scene implements IUpdateables and IRenderables
*/

public class Scene : IUpdatable, IRenderable
{
    /*
    Scene does not own the readonly's

    It does however store them as it is necessary for the scene
    */
    private readonly Renderer renderer;
    private readonly Camera camera;
    private readonly IWindow window;

    /*
    these are dynamic and not needed
    */
    private Mesh sphere_mesh;
    private Vector3 lightPosition = new Vector3(3.0f, 3.0f, 3.0f);
    private Shader shader;
    private GameObject sphere1;
    private GameObject sphere2;

    // this creates the scene and adds all the objects
    public Scene(Renderer renderer, Camera camera, IWindow window)
    {   
        // assign the given variables (not owned)
        this.renderer = renderer;
        this.camera = camera;
        this.window = window;

        // create the shader
        string vertexCode = Shader.fileToString("shaders/planet.vs");
        string fragmentCode = Shader.fileToString("shaders/planet.fs");
        shader = new Shader(vertexCode, fragmentCode, renderer);

        IModelLoader objLoader = new ObjLoader();
        sphere_mesh = objLoader.Load("resources/models/sphere.obj");

        sphere1 = new GameObject(0, 0, 0, sphere_mesh, shader);
        sphere2 = new GameObject(2, 0, 0, sphere_mesh, shader);
    }

    // this updates before each frame
    public void Update(double deltaTime)
    {
        // future: physics/position updates go here
    }

    public void Render(double deltaTime)
    {
        renderer.setBackgroundColour(Color.Black);
        sphere1.Render(renderer, camera, window, lightPosition);
        sphere2.Render(renderer, camera, window, lightPosition);
    }
}
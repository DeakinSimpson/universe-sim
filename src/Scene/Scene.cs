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
    private Planet planet1;
    private Planet planet2;
    private Vector3 lightPosition = new Vector3(3.0f, 3.0f, 3.0f);
    private SolarSystem solarSystem = new SolarSystem();
    private Shader shader;

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

        planet1 = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20, shader, sphere_mesh);
        planet2 = new Planet(5.0f, 0.0f, 0.0f, 2.0f, 10, shader, sphere_mesh);

        solarSystem.addPlanet(planet1);
        solarSystem.addPlanet(planet2);
    }

    // this updates before each frame
    public void Update(double deltaTime)
    {
        // future: physics/position updates go here
    }

    public void Render(double deltaTime)
    {
        renderer.setBackgroundColour(Color.Black);
        solarSystem.Render(renderer, camera, window, lightPosition);
    }
}
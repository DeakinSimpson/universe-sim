using Silk.NET.Windowing;
using System.Numerics;

public class Scene
{
    private Planet planet1;
    private Planet planet2;
    private Vector3 lightPosition = new Vector3(3.0f, 3.0f, 3.0f);

    SolarSystem solarSystem = new SolarSystem();

    private Shader shader;

    string vertexCode = Shader.fileToString("shaders/planet.vs");
    string fragmentCode = Shader.fileToString("shaders/planet.fs");

    public void Load(Renderer renderer)
    {
        shader = new Shader(vertexCode, fragmentCode, renderer);

        planet1 = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20, shader);
        planet2 = new Planet(5.0f, 0.0f, 0.0f, 2.0f, 10, shader);

        solarSystem.addPlanet(planet1);
        solarSystem.addPlanet(planet2);

    }

    public void Update(float deltaTime)
    {
        // future: physics/position updates go here
    }

    public void Render(Renderer renderer, Camera camera, IWindow window)
    {
        solarSystem.Render(renderer, camera, window, lightPosition);
    }
}
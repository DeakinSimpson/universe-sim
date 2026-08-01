using Silk.NET.Windowing;
using System.Numerics;
using System.Runtime.CompilerServices;

public class Scene
{
    private Planet planet1;
    private Planet planet2;
    private Shader shader;

    string vertexCode = Shader.fileToString("shaders/planet.vs");
    string fragmentCode = Shader.fileToString("shaders/planet.fs");

    public void Load(Renderer renderer)
    {
        planet1 = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20);
        planet2 = new Planet(5.0f, 0.0f, 0.0f, 2.0f, 10);
        shader = new Shader(vertexCode, fragmentCode, renderer);
    }

    public void Update(float deltaTime)
    {
        // future: physics/position updates go here
    }

    public void Render(Renderer renderer, Camera camera, IWindow window)
    {
        renderer.renderObject(planet1.getBufferData(), planet1.getIndicies(), shader, planet1.getModel(), camera, window, new Vector3(3.0f, 3.0f, 3.0f));
        renderer.renderObject(planet2.getBufferData(), planet2.getIndicies(), shader, planet2.getModel(), camera, window, new Vector3(3.0f, 3.0f, 3.0f));
    }
}
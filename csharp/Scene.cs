using Silk.NET.Windowing;

public class Scene
{
    private Planet planet;
    private Shader shader;

    //! testing, to delete
    const string vertexCode = @"
    #version 330 core
    layout (location = 0) in vec3 aPosition;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPosition, 1.0);
    }";

    const string fragmentCode = @"
    #version 330 core
    out vec4 out_color;

    void main()
    {
        out_color = vec4(1.0, 0.5, 0.2, 1.0);
    }";
    //! testing ended

    public void Load(Renderer renderer)
    {
        planet = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20);
        shader = new Shader(vertexCode, fragmentCode, renderer);
    }

    public void Update(float deltaTime)
    {
        // future: physics/position updates go here
    }

    public void Render(Renderer renderer, Camera camera, IWindow window)
    {
        renderPlanet(renderer, camera, window);
    }

    private void renderPlanet(Renderer renderer, Camera camera, IWindow window)
    {
        renderer.renderObject(planet.getVertices(), planet.getIndicies(), shader, planet.getModel(), camera, window);
    }
}
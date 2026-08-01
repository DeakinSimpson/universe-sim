using Silk.NET.Windowing;
using System.Numerics;

public class Scene
{
    private Planet planet;
    private Shader shader;

    //! testing, to delete
    const string vertexCode = @"
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    // send the position of the fragment
    out vec3 FragPos;

    // send normal out for fragment shader
    out vec3 Normal;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0f);
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
    }";

    const string fragmentCode = @"
    #version 330 core
    out vec4 FragColor;

    uniform vec3 objectColor;
    uniform vec3 lightColor;
    uniform vec3 lightPos;

    // take in the fragpos
    in vec3 FragPos;

    // take in normal value from vertex shader
    in vec3 Normal;

    void main()
    {
        // ambient strength
        float ambientStrength = 0.25f;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // final output
        vec3 result = (ambient + diffuse) * objectColor;
        FragColor = vec4(result, 1.0);
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
        renderer.renderObject(planet.getBufferData(), planet.getIndicies(), shader, planet.getModel(), camera, window, new Vector3(3.0f, 3.0f, 3.0f));
    }
}
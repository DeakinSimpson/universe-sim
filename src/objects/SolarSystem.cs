using System.Numerics;
using Silk.NET.Windowing;

public class SolarSystem
{
    List<Planet> planets = new List<Planet>();

    public void addPlanet(Planet planet)
    {
        planets.Add(planet);
    }

    public void Render(Renderer renderer, Camera camera, IWindow window, Vector3 lightPosition)
    {
        foreach (Planet planet in planets)
        {
            planet.Render(renderer, camera, window, lightPosition);
        }
    }
}
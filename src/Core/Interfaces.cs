/* -- This stores all interfaces -- */

// all objects that get updated can be placed under the IUpdateables interface, this allows for lists to be parsed
public interface IUpdatable
{
    void Update(double deltaTime);
}

// all objects that get renderered can be placed under the IUpdateables interface, this allows for lists to be parsed
public interface IRenderable
{
    void Render(double deltaTime);
}

// this will be used by all model parsers
public interface IModelLoader
{
    Mesh Load(string filepath);
}
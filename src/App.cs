using Silk.NET.Maths;
using Silk.NET.Windowing;
using Silk.NET.Input;

/* 
Owns all the variables that are responsible for running the app
*/

public class App
{
    public void Run()
    {
        // create the window options
        var options = WindowOptions.Default with
        {
            Size = new Vector2D<int>(800, 600),
            Title = "BUFFER Ngin"
        };

        // create a new window
        IWindow window = Window.Create(options);

        // create the variables for the app
        Camera camera = new Camera();
        Controller controller = new Controller(camera);
        Renderer renderer = null;

        // add the window.Load function same as Load() { ... }
        window.Load += () =>
        {   
            renderer = new Renderer(window);
            Scene scene = new Scene(renderer, camera, window);

            // create the input and initialise controller
            var input = window.CreateInput();
            controller.onLoad(input);

            for (int i = 0; i < input.Keyboards.Count; i++)
            {
                input.Keyboards[i].KeyDown += (keyboard, key, keyCode) =>
                {
                    if (key == Key.Escape) window.Close();
                    if (key == Key.E) renderer.ToggleWireframe();
                };
            }

            // create the Engine with the renderables and the updateables
            Engine engine = new Engine(
                window,
                new List<IUpdatable> {controller, scene},
                new List<IRenderable> {scene}
            );
        };

        // same as if (renderer != null) FramebufferResize(newSize) { renderer.getGL().Viewport(newSize); }
        window.FramebufferResize += (newSize) =>
        {
            renderer?.getGL().Viewport(newSize);
        };

        // run the window which start scene
        window.Run();
    }
}
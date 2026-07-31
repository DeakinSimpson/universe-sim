using Silk.NET.Input;
using Silk.NET.Maths;
using Silk.NET.OpenGL;
using Silk.NET.Windowing;
using System.Drawing;

public class WindowObj
{
    // reference to the window
    private static IWindow _window;
    private static Renderer renderer;
    private static Planet planet;

    // set the default window options
    WindowOptions options = WindowOptions.Default with
    {   
        // create a window with size 800x600
        Size = new Vector2D<int>(800, 600),

        // set the top title
        Title = "Universe Simulator"
    };

    // initialise the WindowObj
    public WindowObj()
    {
        // create the window
        _window = Window.Create(options);

        // add functions to the window so it knows what to call
        _window.Load += OnLoad;
        _window.Update += OnUpdate;
        _window.Render += OnRender;

        // run the window
        _window.Run();
    }

    // runs code on window launch 
    private static unsafe void OnLoad()
    {
        // now that the window/context actually exists, safe to create input
        IInputContext input = _window.CreateInput();

        // subscribe every connected keyboard to the KeyDown handler
        for (int i = 0; i < input.Keyboards.Count; i++)
        {
            input.Keyboards[i].KeyDown += KeyDown;
        }

        // load the opengl renderer
        renderer = new Renderer(_window);

        // make planet
        planet = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20);

    }

    // runs code before rendering, great for things that need to change each frame
    private static void OnUpdate(double deltaTime)
    {
        // Console.WriteLine("Update!");
    }

    // renders the frame
    private static unsafe void OnRender(double deltaTime)
    {
        renderer.onRender();

        // render planet
        renderer.renderObject(planet.getVertices(), planet.getIndicies());
    }

    // checks if key is pressed
    private static void KeyDown(IKeyboard keyboard, Key key, int keyCode)
    {
        if (key == Key.Escape)
            _window.Close();
    }

}

public class Renderer
{
    private static GL gl;
    private static uint vao;
    private static uint vbo;
    private static uint ebo;

    public Renderer(IWindow window)
    {
        // initialise the OpenGL instance
        gl = window.CreateOpenGL();
        Console.WriteLine("OpenGL opened successfully");

        setBackgroundColour(Color.CornflowerBlue);

        // -- bind buffer arrays --
        // bind vertex array object
        vao = gl.GenVertexArray();
        gl.BindVertexArray(vao);

        // initalise vertex buffer array (used for vertices)
        vbo = gl.GenBuffer();
        gl.BindBuffer(BufferTargetARB.ArrayBuffer, vbo);

        ebo = gl.GenBuffer();
        gl.BindBuffer(BufferTargetARB.ElementArrayBuffer, ebo);

        // describe the vertex layout once — same as configuring this in
        // initRenderer() rather than repeating it every draw call in C++
        unsafe
        {
            gl.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 3 * sizeof(float), (void*)0);
        }
        gl.EnableVertexAttribArray(0);

        gl.BindVertexArray(0);
    }

    public void onRender()
    {
        setBackgroundColour(Color.CornflowerBlue);
    }

    private void setBackgroundColour(Color color)
    {
        // set the clear colour
        gl.ClearColor(color);

        // render the clear colour
        gl.Clear(ClearBufferMask.ColorBufferBit);
    }

    public unsafe void renderObject(List<float> vertices, List<uint> indices)
    {
        // convert lists to arrays
        float[] vertexArray = vertices.ToArray();
        uint[] indexArray = indices.ToArray();

        gl.BindVertexArray(vao);

        // upload vertex data
        gl.BindBuffer(BufferTargetARB.ArrayBuffer, vbo);
        fixed (float* buf = vertexArray)
            gl.BufferData(BufferTargetARB.ArrayBuffer, (nuint)(vertexArray.Length * sizeof(float)), buf, BufferUsageARB.StaticDraw);

        // upload index data
        gl.BindBuffer(BufferTargetARB.ElementArrayBuffer, ebo);
        fixed (uint* buf = indexArray)
            gl.BufferData(BufferTargetARB.ElementArrayBuffer, (nuint)(indexArray.Length * sizeof(uint)), buf, BufferUsageARB.StaticDraw);

        // the actual draw call
        gl.DrawElements(PrimitiveType.Triangles, (uint)indexArray.Length, DrawElementsType.UnsignedInt, null);

        gl.BindVertexArray(0);
    }
}
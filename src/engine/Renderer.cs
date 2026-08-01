using Silk.NET.OpenGL;
using Silk.NET.Windowing;
using System.Drawing;
using System.Numerics;

public class RendererOld
{
    // -- private variables --
    private static GL gl;
    private static uint vao;
    private static uint vbo;
    private static uint ebo;
    private bool wireframe = false;

    // initialise renderer
    public RendererOld(IWindow window)
    {
        // initialise the OpenGL instance
        gl = window.CreateOpenGL();
        Console.WriteLine("OpenGL opened successfully");

        /*
        depth testing allows for the engine to render the verticies furthest away first
        */
        gl.Enable(EnableCap.DepthTest);

        setBackgroundColour(Color.Black);

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
            gl.EnableVertexAttribArray(0);
            gl.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), (void*) 0);

            gl.EnableVertexAttribArray(1);
            gl.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        }

        gl.BindVertexArray(0);
    }

    public void setBackgroundColour(Color color)
    {
        // set the clear colour
        gl.ClearColor(color);

        // render the clear colour
        gl.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
    }
    //! TEMP constant values
    Vector3 lightColor = new Vector3(1.0f, 0.85f, 0.61f);
    Vector3 initialColor = new Vector3(1.0f, 1.0f, 1.0f);

    // -- renders any object --
    public unsafe void renderObject(List<float> vertices, List<uint> indices, Shader shader, Matrix4x4 model, Camera camera, IWindow window, Vector3 lightPosition)
    {

        // activate shader
        shader.Use();

        // get the window size
        var size = window.FramebufferSize;

        // get the projection matrix
        var projection = Matrix4x4.CreatePerspectiveFieldOfView(MathHelper.DegreesToRadians(camera.CameraZoom), (float)size.X / size.Y, 0.1f, 100.0f);

        // get the viewport matrix
        var view = Matrix4x4.CreateLookAt(camera.CameraPosition, camera.CameraPosition + camera.CameraFront, camera.CameraUp);

        shader.SetUniform("model", model);
        shader.SetUniform("view", view);
        shader.SetUniform("projection", projection);

        // set the shader colour "objectColor" to white
        shader.SetUniform("objectColor", initialColor);

        // set lightColor
        shader.SetUniform("lightColor", lightColor);

        // set up a light
        shader.SetUniform("lightPos", lightPosition);

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

        gl.EnableVertexAttribArray(0);
        gl.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), (void*) 0);

        gl.EnableVertexAttribArray(1);
        gl.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        // draw to screen
        gl.BindVertexArray(vao);
        gl.DrawElements(PrimitiveType.Triangles, (uint) indices.Count(), DrawElementsType.UnsignedInt, (void*) 0);

        // cleanup (clear buffers)
        gl.BindVertexArray(0);
        gl.BindBuffer(BufferTargetARB.ArrayBuffer, 0);
        gl.BindBuffer(BufferTargetARB.ElementArrayBuffer, 0);
    }

    // get the gl instance
    public GL getGL()
    {
        return gl;
    }

    public void ToggleWireframe()
    {
        wireframe = !wireframe;
        gl.PolygonMode(GLEnum.FrontAndBack, wireframe ? GLEnum.Line : GLEnum.Fill);
    }
}

// -- maths functions --
public static class MathHelper
{
    public static float DegreesToRadians(float degrees)
    {
        return MathF.PI / 180f * degrees;
    }
}
using Silk.NET.Input;
using System.Numerics;

public class Controller
{
    private readonly Camera camera; // Controller does not own the camera but requires a camera to be made
    private IKeyboard primaryKeyboard;
    float lookSensitivity = 0.1f;

    // initialising Controller justs sets its camera
    public Controller(Camera camera)
    {
        this.camera = camera;
    }

    // on load add all the movements to the input
    public void onLoad(IInputContext input)
    {
        for (int i = 0; i < input.Mice.Count; i++)
        {
            input.Mice[i].Cursor.CursorMode = CursorMode.Raw;
            input.Mice[i].MouseMove += OnMouseMove;
            input.Mice[i].Scroll += OnMouseWheel;
        }
    }

    public void OnUpdate(float deltaTime)
    {
        var moveSpeed = 2.5f * deltaTime;

        if (primaryKeyboard.IsKeyPressed(Key.W)) camera.MoveForward(moveSpeed);
        if (primaryKeyboard.IsKeyPressed(Key.S)) camera.MoveForward(-moveSpeed);
        if (primaryKeyboard.IsKeyPressed(Key.A)) camera.Strafe(-moveSpeed);
        if (primaryKeyboard.IsKeyPressed(Key.D)) camera.Strafe(moveSpeed);
    }

    private Vector2 lastMousePosition;

    private void OnMouseMove(IMouse mouse, Vector2 position)
    {
        if (lastMousePosition == default)
        {
            lastMousePosition = position;
            return;
        }

        var xOffset = (position.X - lastMousePosition.X) * lookSensitivity;
        var yOffset = (position.Y - lastMousePosition.Y) * lookSensitivity;
        lastMousePosition = position;

        camera.Rotate(xOffset, yOffset);
    }

    private void OnMouseWheel(IMouse mouse, ScrollWheel scrollWheel)
    {
        camera.Zoom(-scrollWheel.Y);
    }
}
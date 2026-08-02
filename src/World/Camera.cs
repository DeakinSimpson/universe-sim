using System.Numerics;

/*
Camera does not have its own functions to move

Instead the Controller function can call the camera move functions

the camera by itself is unmoving
*/

public class Camera
{
    public Vector3 CameraPosition = new Vector3(0.0f, 0.0f, 3.0f);
    public Vector3 CameraFront = new Vector3(0.0f, 0.0f, -1.0f);
    public Vector3 CameraUp = Vector3.UnitY;
    public Vector3 CameraDirection = Vector3.Zero;
    public float CameraYaw = -90f;
    public float CameraPitch = 0f;
    public float CameraZoom = 45f;

    public void MoveForward(float amount)
    {
        CameraPosition += amount * CameraFront;
    }

    // move camera side to side
    public void Strafe(float amount)
    {
        CameraPosition += Vector3.Normalize(Vector3.Cross(CameraFront, CameraUp)) * amount;
    }

    public void Rotate(float yawDelta, float pitchDelta)
    {
        CameraYaw += yawDelta;
        CameraPitch = Math.Clamp(CameraPitch - pitchDelta, -89.0f, 89.0f);

        CameraDirection.X = MathF.Cos(MathHelper.DegreesToRadians(CameraYaw)) * MathF.Cos(MathHelper.DegreesToRadians(CameraPitch));
        CameraDirection.Y = MathF.Sin(MathHelper.DegreesToRadians(CameraPitch));
        CameraDirection.Z = MathF.Sin(MathHelper.DegreesToRadians(CameraYaw)) * MathF.Cos(MathHelper.DegreesToRadians(CameraPitch));
        CameraFront = Vector3.Normalize(CameraDirection);
    }

    public void Zoom(float amount)
    {
        CameraZoom = Math.Clamp(CameraZoom + amount, 1.0f, 45f);
    }
}
// using Silk.NET.Input;
// using System.Numerics;

// public class Camera
// {
//     //Setup the camera's location, directions, and movement speed
//     public Vector3 CameraPosition = new Vector3(0.0f, 0.0f, 3.0f);
//     public Vector3 CameraFront = new Vector3(0.0f, 0.0f, -1.0f);
//     public Vector3 CameraUp = Vector3.UnitY;
//     public Vector3 CameraDirection = Vector3.Zero;
//     public float CameraYaw = -90f;
//     public float CameraPitch = 0f;
//     public float CameraZoom = 45f;

//     //Used to track change in mouse movement to allow for moving of the Camera
//     private Vector2 LastMousePosition;

//     public void onLoad(IInputContext input)
//     {
//         for (int i = 0; i < input.Mice.Count; i++)
//         {
//             input.Mice[i].Cursor.CursorMode = CursorMode.Raw;
//             input.Mice[i].MouseMove += OnMouseMove;
//             input.Mice[i].Scroll += OnMouseWheel;
//         }
//     }

//     public void onUpdate(float deltaTime, IKeyboard primaryKeyboard)
//     {
//         var moveSpeed = 2.5f * (float) deltaTime;

//         if (primaryKeyboard.IsKeyPressed(Key.W))
//         {
//             //Move forwards
//             CameraPosition += moveSpeed * CameraFront;
//         }
//         if (primaryKeyboard.IsKeyPressed(Key.S))
//         {
//             //Move backwards
//             CameraPosition -= moveSpeed * CameraFront;
//         }
//         if (primaryKeyboard.IsKeyPressed(Key.A))
//         {
//             //Move left
//             CameraPosition -= Vector3.Normalize(Vector3.Cross(CameraFront, CameraUp)) * moveSpeed;
//         }
//         if (primaryKeyboard.IsKeyPressed(Key.D))
//         {
//             //Move right
//             CameraPosition += Vector3.Normalize(Vector3.Cross(CameraFront, CameraUp)) * moveSpeed;
//         }
//     }

//     private unsafe void OnMouseWheel(IMouse mouse, ScrollWheel scrollWheel)
//     {
//         //We don't want to be able to zoom in too close or too far away so clamp to these values
//         CameraZoom = Math.Clamp(CameraZoom - scrollWheel.Y, 1.0f, 45f);
//     }

//     public unsafe void OnMouseMove(IMouse mouse, Vector2 position)
//     {
//         var lookSensitivity = 0.1f;
//         if (LastMousePosition == default) { LastMousePosition = position; }
//         else
//         {
//             var xOffset = (position.X - LastMousePosition.X) * lookSensitivity;
//             var yOffset = (position.Y - LastMousePosition.Y) * lookSensitivity;
//             LastMousePosition = position;

//             CameraYaw += xOffset;
//             CameraPitch -= yOffset;

//             //We don't want to be able to look behind us by going over our head or under our feet so make sure it stays within these bounds
//             CameraPitch = Math.Clamp(CameraPitch, -89.0f, 89.0f);

//             CameraDirection.X = MathF.Cos(MathHelper.DegreesToRadians(CameraYaw)) * MathF.Cos(MathHelper.DegreesToRadians(CameraPitch));
//             CameraDirection.Y = MathF.Sin(MathHelper.DegreesToRadians(CameraPitch));
//             CameraDirection.Z = MathF.Sin(MathHelper.DegreesToRadians(CameraYaw)) * MathF.Cos(MathHelper.DegreesToRadians(CameraPitch));
//             CameraFront = Vector3.Normalize(CameraDirection);
//         }
//     }
// }
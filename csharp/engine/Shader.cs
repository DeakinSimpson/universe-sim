using Silk.NET.OpenGL;
using System.Numerics;

public class Shader
{
    public uint program;
    private GL gl;
    
    public unsafe Shader(string vertexCode, string fragmentCode, Renderer renderer)
    {
        gl = renderer.getGL();

        // -- compile shaders --
        uint vertexShader, fragmentShader;

        // compile vertex
        // set shader
        vertexShader = gl.CreateShader(ShaderType.VertexShader);
        gl.ShaderSource(vertexShader, vertexCode);
        
        // compile shader
        gl.CompileShader(vertexShader);

        // check for errors in program shader
        gl.GetShader(vertexShader, ShaderParameterName.CompileStatus, out int vStatus);
        if (vStatus != (int) GLEnum.True)
        {
            throw new Exception("Vertex shader failed to compile: " + gl.GetShaderInfoLog(vertexShader));
        }

        // compile fragment
        // set shader
        fragmentShader = gl.CreateShader(ShaderType.FragmentShader);
        gl.ShaderSource(fragmentShader, fragmentCode);
        
        // compile shader
        gl.CompileShader(fragmentShader);

        // check for errors in fragment shader
        gl.GetShader(fragmentShader, ShaderParameterName.CompileStatus, out int fStatus);
        if (fStatus != (int) GLEnum.True)
            throw new Exception("Fragment shader failed to compile: " + gl.GetShaderInfoLog(fragmentShader));        

        // -- create shader program --
        
        // create new program
        program = gl.CreateProgram();

        // attach the vertex and fragment shader to the program
        gl.AttachShader(program, vertexShader);
        gl.AttachShader(program, fragmentShader);

        // link the program to openGL
        gl.LinkProgram(program);

        // check for errors in program
        gl.GetProgram(program, ProgramPropertyARB.LinkStatus, out int lStatus);
        if (lStatus != (int) GLEnum.True)
            throw new Exception("Program failed to link: " + gl.GetProgramInfoLog(program));

        // detach the shaders
        // TODO: check as this might need to be done in the onLoad method
        gl.DetachShader(program, vertexShader);
        gl.DetachShader(program, fragmentShader);
        gl.DeleteShader(vertexShader);
        gl.DeleteShader(fragmentShader);
    }

    public void Use()
    {
        gl.UseProgram(program);
    }

    // -- set uniforms for shader --
    public void SetUniform(string name, int value)
    {
        int location = gl.GetUniformLocation(program, name);
        if (location == -1)
        {
            throw new Exception($"{name} uniform not found on shader.");
        }
        gl.Uniform1(location, value);
    }

    public unsafe void SetUniform(string name, Matrix4x4 value)
    {
        // A new overload has been created for setting a uniform so we can use the transform in our shader.
        int location = gl.GetUniformLocation(program, name);
        if (location == -1)
        {
            throw new Exception($"{name} uniform not found on shader.");
        }
        gl.UniformMatrix4(location, 1, false, (float*) &value);
    }

    public void SetUniform(string name, float value)
    {
        int location = gl.GetUniformLocation(program, name);
        if (location == -1)
        {
            throw new Exception($"{name} uniform not found on shader.");
        }
        gl.Uniform1(location, value);
    }
}
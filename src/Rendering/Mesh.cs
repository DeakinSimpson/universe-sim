/*
This calss will be used to hold all mesh data

this is so that objects can have object specific data
but keep the mesh data (verticies indicies etc) stored
in its own class

This will also hold any Mesh related functions
*/

public class Mesh
{
    private List<float> vertices = new List<float>();
    private List<uint> indicies = new List<uint>();
    private List<float> uv = new List<float>();
    private List<float> normals = new List<float>();
}
/*
This calss will be used to hold all mesh data

this is so that objects can have object specific data
but keep the mesh data (verticies indicies etc) stored
in its own class

This will also hold any Mesh related functions
*/

using System.Reflection.Metadata;
using System.Runtime.ExceptionServices;

public class Mesh
{
    public List<float> vertices = new List<float>();   // interleaved: x,y,z, nx,ny,nz
    public List<uint> indicies = new List<uint>();

    public Mesh() { }

    public Mesh(List<float> vertices, List<uint> indicies)
    {
        this.vertices = vertices;
        this.indicies = indicies;
    }
}
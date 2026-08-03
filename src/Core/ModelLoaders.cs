using System.Numerics;

public class ObjLoader : IModelLoader
{
    // these hold the raw values exactly as read from the file, before combining
    private List<Vector3> rawPositions;
    private List<Vector3> rawNormals;
    private List<Vector2> rawUVs;

    // maps a face triplet "1/1/1" to its index in the final combined vertex buffer
    private Dictionary<string, uint> vertexCache;

    public Mesh Load(string filepath)
    {
        rawPositions = new List<Vector3>();
        rawNormals = new List<Vector3>();
        rawUVs = new List<Vector2>();
        vertexCache = new Dictionary<string, uint>();

        // OpenGL-ready data - one combined vertex per unique v/vt/vn triplet
        var vertices = new List<float>();
        var indicies = new List<uint>();

        /*
        OBJ File
        v = verticies (x, y, z, [w]) w optional and 0 by default
        vt = texture coordinates (u, [v, w]), v, w are optional and set to 0 by default
        vn = normals (x, y, z), there is a possibility these arent unit vecors, might need to handle later
        vp = Parameter space verticies (u, [v, w]) | these are for curves and will not be implemented
        f = Polygon indicies elements
        l = this specifiec the order in which to build the verticie elements | these will not be implemented
        */
        try
        {
            foreach (string line in File.ReadLines(filepath))
            {
                // split on spaces to get the line type (v/vn/vt/f) and its values
                string[] parts = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                if (parts.Length == 0) continue; // skip if its an empty line

                switch (parts[0])
                {
                    case "v":
                        rawPositions.Add(ParseVector3(parts));
                        break;
                    case "vn":
                        rawNormals.Add(ParseVector3(parts));
                        break;
                    case "vt":
                        rawUVs.Add(ParseVector2(parts));
                        break;
                    case "f":
                        ParseFace(parts, vertices, indicies);
                        break;
                }
            }
        }
        catch
        {
            Console.WriteLine("Failed to open OBJ file.");
        }

        return new Mesh(vertices, indicies);
    }


    private void ParseFace(string[] parts, List<float> vertices, List<uint> indicies)
    {
        var faceVertexIndices = new List<uint>();

        for (int i = 1; i < parts.Length; i++)
        {
            // gets the key "v, vt, etc..."
            string key = parts[i];

            // if we've already built a combined vertex for this exact triplet, reuse its index
            if (vertexCache.TryGetValue(key, out uint existingIndex))
            {
                faceVertexIndices.Add(existingIndex);
                continue;
            }


            // split the face by / gives us {1, 1, 1}
            string[] faceIndices = key.Split('/');

            // OBJ indices start at 1 not 0, so subtract 1 to match our 0-based lists
            int vIndex = int.Parse(faceIndices[0]) - 1;
            int nIndex = faceIndices.Length > 2 && faceIndices[2] != "" ? int.Parse(faceIndices[2]) - 1 : -1;

            Vector3 position = rawPositions[vIndex];
            Vector3 normal;

            // check if the index is not negative
            if (nIndex >= 0)
            {
                normal = rawNormals[nIndex];
            }
            else
            {
                normal = Vector3.Zero;
            }

            // append the new combined vertex (interleaved: x,y,z, nx,ny,nz)
            vertices.Add(position.X);
            vertices.Add(position.Y);
            vertices.Add(position.Z);
            vertices.Add(normal.X);
            vertices.Add(normal.Y);
            vertices.Add(normal.Z);

            // record this triplet's new index so later faces reusing it don't duplicate the vertex
            uint newIndex = (uint)(vertices.Count / 6 - 1);
            vertexCache[key] = newIndex;
            faceVertexIndices.Add(newIndex);
        }

        // fan-triangulate: works for any convex face (triangle, quad, etc.)
        for (int i = 1; i < faceVertexIndices.Count - 1; i++)
        {
            indicies.Add(faceVertexIndices[0]);
            indicies.Add(faceVertexIndices[i]);
            indicies.Add(faceVertexIndices[i + 1]);
        }
    }

    private Vector3 ParseVector3(string[] parts) =>
        new Vector3(float.Parse(parts[1]), float.Parse(parts[2]), float.Parse(parts[3]));

    private Vector2 ParseVector2(string[] parts) =>
        new Vector2(float.Parse(parts[1]), float.Parse(parts[2]));
}
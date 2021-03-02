#include "l-SystemDraw/l-SystemDrawBuffer.h"

#ifdef pxr_FOUND
    #include "l-SystemDraw/l-SystemOutputUSD.h"
#endif

////////////////////////////////////////
// Operators
////////////////////////////////////////

bool LSystem::DrawBuffer::operator==(const DrawBuffer& _other) const
{
    // Test if the vertices matches
    if (vertices != _other.getVertices()) { return false; }
    // Test if the indices matches
    if (indices != _other.getIndices()) { return false; }

    return true;
}

bool LSystem::DrawBuffer::operator!=(const DrawBuffer& _other) const
{
    // Test if the vertices matches
    if (vertices != _other.getVertices()) { return true; }
    // Test if the indices matches
    if (indices != _other.getIndices()) { return true; }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const LSystem::DrawBuffer& _drawBuffer)
{
    // Print the Vertexes
    stream << "Vertices : ";
    for (Imath::V3f _vertex : _drawBuffer.getVertices()) { stream << _vertex << ", "; }
    stream << "\n";
    // Print the color
    stream << "Indices : ";
    for (int _indice : _drawBuffer.getIndices()) { stream << _indice << ", "; }
    stream << "\n";

    return stream;
}


////////////////////////////////////////
// Vertices
////////////////////////////////////////

int LSystem::DrawBuffer::appendVertex(Imath::V3f _vertex)
{
    vertices.emplace_back(_vertex);

    // Allways return true for now
    return vertices.size() - 1;
}

bool LSystem::DrawBuffer::appendVertices(std::vector<Imath::V3f> _vertices)
{
    // Save current vertices buffer
    std::vector<Imath::V3f> _verticesRollBack = vertices;

    // Reserve memory
    vertices.reserve(vertices.size() + _vertices.size());

    // Add the vertices one by one to check if they are correct
    for(Imath::V3f _vertex : _vertices)
    {
        // If one of the vertex can't be added
        if(appendVertex(_vertex) == -1)
        {
            // Return to the original state
            vertices = _verticesRollBack;
            return false;
        }
    }

    return true;
}

bool LSystem::DrawBuffer::setVertices(std::vector<Imath::V3f> _vertices)
{
    // Clear the vertex buffer
    vertices.clear();

    // Append the vertices to the cleard buffer
    return appendVertices(_vertices);
}


////////////////////////////////////////
// Indexes
////////////////////////////////////////

int LSystem::DrawBuffer::appendIndice(int _indice)
{
    // If the index is out of range, don't add it
    if(_indice > vertices.size() - 1) { return -1; }

    indices.emplace_back(_indice);
    return indices.size() - 1;
}

bool LSystem::DrawBuffer::appendIndices(std::vector<int> _indices)
{
    // Save current indexes buffer
    std::vector<int> _indicesRollBack = indices;

    // Reserve memory
    indices.reserve(indices.size() + _indices.size());

    // Add the indexes one by one to check if they are correct
    for(int _index : _indices)
    {
        // If one of the index can't be added
        if(appendIndice(_index) == -1)
        {
            // Return to the original state
            indices = _indicesRollBack;
            return false;
        }
    }

    return true;
}

bool LSystem::DrawBuffer::setIndices(std::vector<int> _indices)
{
    // Clear the index buffer
    indices.clear();

    // Append the indexes to the cleard buffer
    return appendIndices(_indices);
}


////////////////////////////////////////
// Export
////////////////////////////////////////

#ifdef pxr_FOUND
    LSystem::OutputUSD LSystem::DrawBuffer::exportUSD(std::string _root)
    {
        LSystem::OutputUSD _exportUSD(_root);

        // Convert std::vector vertices to pxr::VtArray vertices
        pxr::VtArray<pxr::GfVec3f> _vertices;
        _vertices.reserve(vertices.size());
        for (Imath::V3f _vertex : vertices) { _vertices.emplace_back(pxr::GfVec3f(_vertex.x, _vertex.y, _vertex.z)); }
        // Create the faces vertex count
        pxr::VtArray<int> _faceVertexCount(indices.size() / 2, 2);
        // Convert std::vector indices to pxr::VtArray indices
        pxr::VtArray<int> _faceIndices(indices.begin(), indices.end());

        std::cout << std::endl;

        _exportUSD.setMesh(_vertices, _faceVertexCount, _faceIndices);
        return _exportUSD;
    }


    LSystem::OutputUSD LSystem::DrawBuffer::exportUSD(std::string _root, std::string _location)
    {
        LSystem::OutputUSD _exportUSD = exportUSD(_root);
        _exportUSD.writeToDisk(_location);

        return _exportUSD;
    }
#endif

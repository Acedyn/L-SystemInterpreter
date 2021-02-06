#include "l-SystemDraw/l-SystemDrawBuffer.h"

#include "l-SystemDraw/l-SystemOutputUSD.h"

////////////////////////////////////////
// Vertices
////////////////////////////////////////

bool LSystem::DrawBuffer::appendVertex(Imath::V3f _vertex)
{
    vertices.emplace_back(_vertex);

    // Allways return true for now
    return true;
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
        if(!appendVertex(_vertex))
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

bool LSystem::DrawBuffer::appendIndice(int _indice)
{
    // If the index is out of range, don't add it
    if(_indice > vertices.size() - 1) { return false; }

    indices.emplace_back(_indice);
    return true;
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
        if(!appendIndice(_index))
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

    _exportUSD.setMesh(_vertices, _faceVertexCount, _faceIndices);
    return _exportUSD;
}


LSystem::OutputUSD LSystem::DrawBuffer::exportUSD(std::string _root, std::string _location)
{
    LSystem::OutputUSD _exportUSD = exportUSD(_root);
    _exportUSD.writeToDisk(_location);

    return _exportUSD;
}
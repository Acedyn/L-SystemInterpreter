#include "l-SystemDraw/l-SystemDrawBuffer.h"

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

bool LSystem::DrawBuffer::appendIndex(int _index)
{
    // If the index is out of range, don't add it
    if(_index > vertices.size() - 1) { return false; }

    indexes.emplace_back(_index);
    return true;
}

bool LSystem::DrawBuffer::appendIndexes(std::vector<int> _indexes)
{
    // Save current indexes buffer
    std::vector<int> _indexesRollBack = indexes;

    // Reserve memory
    indexes.reserve(indexes.size() + _indexes.size());

    // Add the indexes one by one to check if they are correct
    for(int _index : _indexes)
    {
        // If one of the index can't be added
        if(!appendIndex(_index))
        {
            // Return to the original state
            indexes = _indexesRollBack;
            return false;
        }
    }

    return true;
}

bool LSystem::DrawBuffer::setIndexes(std::vector<int> _indexes)
{
    // Clear the index buffer
    indexes.clear();

    // Append the indexes to the cleard buffer
    return appendIndexes(_indexes);
}

#pragma once

#include <Imath/ImathVec.h>
#include <vector>

namespace LSystem 
{
    class DrawBuffer
    {
    public:
        // Constructors / Destructors
        DrawBuffer() { }
        ~DrawBuffer() { }

        // Vertices
        std::vector<Imath::V3f> getVertices() const { return vertices; }
        bool appendVertex(Imath::V3f _vertex);
        bool appendVertices(std::vector<Imath::V3f> _vertices);
        bool setVertices(std::vector<Imath::V3f> _vertices);

        // Indexes
        std::vector<int> getIndexes() const { return indexes; }
        bool appendIndex(int _index);
        bool appendIndexes(std::vector<int> _indexes);
        bool setIndexes(std::vector<int> _indexes);


    private:
        std::vector<Imath::V3f> vertices;
        std::vector<int> indexes;
    };
}

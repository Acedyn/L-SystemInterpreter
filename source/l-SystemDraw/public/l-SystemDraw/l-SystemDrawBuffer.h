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
        std::vector<int> getIndices() const { return indices; }
        bool appendIndice(int _indice);
        bool appendIndices(std::vector<int> _indices);
        bool setIndices(std::vector<int> _indices);

        // Export
        class OutputUSD exportUSD(std::string _root);
        class OutputUSD exportUSD(std::string _root, std::string _location);

    private:
        std::vector<Imath::V3f> vertices;
        std::vector<int> indices;
    };
}

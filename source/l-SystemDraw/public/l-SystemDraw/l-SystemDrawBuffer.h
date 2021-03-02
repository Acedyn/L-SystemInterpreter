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

        // Operators
        bool operator==(const DrawBuffer& _other) const;
        bool operator!=(const DrawBuffer& _other) const;

        // Vertices
        std::vector<Imath::V3f> getVertices() const { return vertices; }
        int appendVertex(Imath::V3f _vertex);
        bool appendVertices(std::vector<Imath::V3f> _vertices);
        bool setVertices(std::vector<Imath::V3f> _vertices);

        // Indexes
        std::vector<int> getIndices() const { return indices; }
        int appendIndice(int _indice);
        bool appendIndices(std::vector<int> _indices);
        bool setIndices(std::vector<int> _indices);

        // Export
        #ifdef pxr_FOUND
            class OutputUSD exportUSD(std::string _root);
            class OutputUSD exportUSD(std::string _root, std::string _location);
        #endif

    private:
        std::vector<Imath::V3f> vertices;
        std::vector<int> indices;
    };
}


std::ostream& operator<<(std::ostream& stream, const LSystem::DrawBuffer& _drawBuffer);

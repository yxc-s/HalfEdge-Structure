#pragma once


namespace halfedge{
//#define HALFEDGE_USE_DOUBLE
#ifdef HALFEDGE_USE_DOUBLE
    using real_t = double;
#else
    using real_t = float;
#endif
    template<typename T> class Vertex3;

    template<typename T = real_t>
    struct Point3 {
        Point3()                    : x(0), y(0), z(0) {}
        Point3(const Point3& other) : x(other.x), y(other.y), z(other.z) {}
        ~Point3() = default;
        
        T x, y, z;
    };

    template<typename T = real_t>
    class Vertex3 {
    public:
        Vertex3()                                     : m_halfEdge(nullptr), m_vertexIdx(-1) {}
        Vertex3(const T& x, const T& y, const T& z)   : m_point(x, y, z), m_halfEdge(nullptr) {}
        Vertex3(const Point3& point)                  : m_point(point), m_halfEdge(nullptr) {}

        Point3<T>      m_point;
        HalfEdge*      m_halfEdge;
        int            m_vertexIdx;
    };

}




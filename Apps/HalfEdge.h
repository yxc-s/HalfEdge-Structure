#pragma once


namespace he{
//#define HALFEDGE_USE_DOUBLE
#ifdef HALFEDGE_USE_DOUBLE
    using real_t = double;
#else
    using real_t = float;
#endif
    template<typename T = real_t> class HalfEdge;

    template<typename T = real_t>
    struct Point3 {
        Point3()                    : x(0), y(0), z(0) {}
        Point3(const Point3& other) : x(other.x), y(other.y), z(other.z) {}
        ~Point3() = default;
        
        T x, y, z;
    };




    template<typename T = real_t>
    class Vertex3 {
		using PointType     =  Point3<T>;
		using HalfEdgeType  =  HalfEdge<T>;
    public:
        Vertex3()                                     : m_halfEdge(nullptr), m_vertexIdx(-1) {}
        Vertex3(const T& x, const T& y, const T& z)   : m_point(x, y, z), m_halfEdge(nullptr) {}
        Vertex3(const PointType& point)               : m_point(point), m_halfEdge(nullptr) {}

		PointType          m_point;
		HalfEdgeType*      m_halfEdge;
        int                m_vertexIdx;
    };




	class Edge {
		using HalfEdgeType = HalfEdge<>;
	public:
		Edge() = default;
		~Edge() = default;

		int m_edgeId;
		HalfEdgeType* m_halfEdge[2] = {};
	};



	class Face {
		using HalfEdgeType = HalfEdge<>;
	public:
		Face() = default;
		~Face() = default;

		int m_faceID;
		HalfEdgeType* m_halfEdge;
	};




	template<typename T = real_t>
	class HalfEdge {
		using VertexType = Vertex3<real_t>;

	public:
		HalfEdge();
		~HalfEdge();

	private:
		VertexType* m_vertex;
		VertexType* m_sourceVertex;
		VertexType* m_targetVertex;
	};

}




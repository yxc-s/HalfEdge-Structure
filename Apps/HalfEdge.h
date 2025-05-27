#pragma once

#include <vector>
namespace he {

#ifdef HALFEDGE_USE_DOUBLE
    using Real = double;
#else
    using Real = float;
#endif

template<typename T>
class Halfedge;

template<typename T>
class Vertex {
public:
    using Point           = std::array<T, 3>;
    using Halfedge_handle = Halfedge<T>*;

    Vertex() : halfedge_(nullptr), id_(-1) {}
    Vertex(const T& x, const T& y, const T& z)
        : point_({x, y, z}), halfedge_(nullptr), id_(-1) {}

    const Point& point() const { return point_; }
    Point& point() { return point_; }

    Halfedge_handle halfedge() const { return halfedge_; }
    void set_halfedge(Halfedge_handle h) { halfedge_ = h; }

    int id() const { return id_; }
    void set_id(int id) { id_ = id; }

private:
    Point point_;
    Halfedge_handle halfedge_;
    int id_;
};

template<typename T>
class Edge {
public:
    using Halfedge_handle = Halfedge<T>*;

    Edge() : id_(-1) {
        halfedge_[0] = nullptr;
        halfedge_[1] = nullptr;
    }

    Halfedge_handle halfedge(int i) const { return halfedge_[i]; }
    void set_halfedge(int i, Halfedge_handle h) { halfedge_[i] = h; }

    int id() const { return id_; }
    void set_id(int id) { id_ = id; }

private:
    Halfedge_handle halfedge_[2];
    int id_;
};

template<typename T>
class Face {
public:
    using Halfedge_handle = Halfedge<T>*;

    Face() : halfedge_(nullptr), id_(-1) {}

    Halfedge_handle halfedge() const { return halfedge_; }
    void set_halfedge(Halfedge_handle h) { halfedge_ = h; }

    int id() const { return id_; }
    void set_id(int id) { id_ = id; }

private:
    Halfedge_handle halfedge_;
    int id_;
};

template<typename T>
class Halfedge {
public:
    using Vertex_handle   = Vertex<T>*;
    using Edge_handle     = Edge<T>*;
    using Face_handle     = Face<T>*;
    using Halfedge_handle = Halfedge<T>*;

    Halfedge()
        : vertex_(nullptr), source_(nullptr), target_(nullptr),
          edge_(nullptr), face_(nullptr),
          prev_(nullptr), next_(nullptr), twin_(nullptr) {}

    Vertex_handle vertex() const { return vertex_; }
    void set_vertex(Vertex_handle v) { vertex_ = v; }

    Vertex_handle source() const { return source_; }
    void set_source(Vertex_handle v) { source_ = v; }

    Vertex_handle target() const { return target_; }
    void set_target(Vertex_handle v) { target_ = v; }

    Halfedge_handle prev() const { return prev_; }
    void set_prev(Halfedge_handle h) { prev_ = h; }

    Halfedge_handle next() const { return next_; }
    void set_next(Halfedge_handle h) { next_ = h; }

    Halfedge_handle twin() const { return twin_; }
    void set_twin(Halfedge_handle h) { twin_ = h; }

    Face_handle face() const { return face_; }
    void set_face(Face_handle f) { face_ = f; }

    Edge_handle edge() const { return edge_; }
    void set_edge(Edge_handle e) { edge_ = e; }

private:
    Vertex_handle vertex_;       // current vertex (commonly the target)
    Vertex_handle source_, target_;
    Edge_handle edge_;
    Face_handle face_;
    Halfedge_handle prev_, next_, twin_;
};

template<typename T>
class Mesh {
public:
    using Vertex        = Vertex<T>;
    using Edge          = Edge<T>;
    using Face          = Face<T>;
    using Halfedge      = Halfedge<T>;

    using Vertex_handle     = Vertex*;
    using Edge_handle       = Edge*;
    using Face_handle       = Face*;
    using Halfedge_handle   = Halfedge*;

    using Vertex_iterator   = typename std::vector<Vertex_handle>::iterator;
    using Edge_iterator     = typename std::vector<Edge_handle>::iterator;
    using Face_iterator     = typename std::vector<Face_handle>::iterator;
    using Halfedge_iterator = typename std::vector<Halfedge_handle>::iterator;

    Mesh() = default;
    ~Mesh() { clear(); }

    void clear() {
        for (auto v : vertices_) delete v;
        for (auto e : edges_) delete e;
        for (auto f : faces_) delete f;
        for (auto h : halfedges_) delete h;
        vertices_.clear(); edges_.clear(); faces_.clear(); halfedges_.clear();
    }

    Vertex_handle add_vertex(const T& x, const T& y, const T& z) {
        Vertex_handle v = new Vertex(x, y, z);
        v->set_id(static_cast<int>(vertices_.size()));
        vertices_.push_back(v);
        return v;
    }

    Halfedge_handle add_halfedge() {
        Halfedge_handle h = new Halfedge();
        halfedges_.push_back(h);
        return h;
    }

    Edge_handle add_edge(Halfedge_handle h0, Halfedge_handle h1) {
        Edge_handle e = new Edge();
        e->set_halfedge(0, h0);
        e->set_halfedge(1, h1);
        e->set_id(static_cast<int>(edges_.size()));
        h0->set_edge(e);
        h1->set_edge(e);
        h0->set_twin(h1);
        h1->set_twin(h0);
        edges_.push_back(e);
        return e;
    }

    Face_handle add_face(Halfedge_handle h) {
        Face_handle f = new Face();
        f->set_halfedge(h);
        f->set_id(static_cast<int>(faces_.size()));
        h->set_face(f);
        faces_.push_back(f);
        return f;
    }

    Vertex_iterator vertices_begin() { return vertices_.begin(); }
    Vertex_iterator vertices_end()   { return vertices_.end(); }

    Edge_iterator edges_begin() { return edges_.begin(); }
    Edge_iterator edges_end()   { return edges_.end(); }

    Face_iterator faces_begin() { return faces_.begin(); }
    Face_iterator faces_end()   { return faces_.end(); }

    Halfedge_iterator halfedges_begin() { return halfedges_.begin(); }
    Halfedge_iterator halfedges_end()   { return halfedges_.end(); }

private:
    std::vector<Vertex_handle>   vertices_;
    std::vector<Edge_handle>     edges_;
    std::vector<Face_handle>     faces_;
    std::vector<Halfedge_handle> halfedges_;
};

} // namespace he

#include <iostream>
#include "HalfEdge.h"

int main(){
	using namespace he;
	Mesh mesh;
	auto v0 = mesh.add_vertex(0, 0, 0);
	auto v1 = mesh.add_vertex(1, 0, 0);
	auto v2 = mesh.add_vertex(0, 1, 0);
	auto v3 = mesh.add_vertex(1, 1, 0);

	//TODO：应该以face为基准，不再去手动操作添加边这些操作，直接给定面的顶点索引，然后添加face。
	auto h0 = mesh.add_halfedge();
	auto h1 = mesh.add_halfedge();
	auto h2 = mesh.add_halfedge();
	h0->set_source(v0); h0->set_target(v1);
	h1->set_source(v1); h1->set_target(v2);
	h2->set_source(v2); h2->set_target(v0);
	h0->set_next(h1); h1->set_next(h2); h2->set_next(h0);
	h0->set_prev(h2); h1->set_prev(h0); h2->set_prev(h1);
	auto f0 = mesh.add_face(h0);
	h1->set_face(f0); h2->set_face(f0);

	auto e0 = mesh.add_edge(h0, mesh.add_halfedge()); // twin of h0
	e0->halfedge(1)->set_source(v1);
	e0->halfedge(1)->set_target(v0);



	auto h3 = mesh.add_halfedge();
	auto h4 = mesh.add_halfedge();
	auto h5 = mesh.add_halfedge();
	h3->set_source(v2); h3->set_target(v1);
	h4->set_source(v1); h4->set_target(v3);
	h5->set_source(v3); h5->set_target(v2);
	h3->set_next(h4); h4->set_next(h5); h5->set_next(h3);
	h3->set_prev(h5); h4->set_prev(h3); h5->set_prev(h4);

	auto f1 = mesh.add_face(h3);
	h4->set_face(f1); h5->set_face(f1);
	auto e1 = mesh.add_edge(h3, h1);
	auto e2 = mesh.add_edge(h4, mesh.add_halfedge());
	auto e3 = mesh.add_edge(h5, mesh.add_halfedge());

	v0->set_halfedge(h0);
	v1->set_halfedge(h1);
	v2->set_halfedge(h2);
	v3->set_halfedge(h4);

	std::cout << "Mesh has " << std::distance(mesh.vertices_begin(), mesh.vertices_end()) << " vertices\n";
	std::cout << "Mesh has " << std::distance(mesh.faces_begin(), mesh.faces_end()) << " faces\n";
	std::cout << "Mesh has " << std::distance(mesh.edges_begin(), mesh.edges_end()) << " edges\n";
	return 0;
}
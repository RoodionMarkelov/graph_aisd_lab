// graph_aisd_lab.cpp: определяет точку входа для приложения.
//

#include "graph_aisd_lab.h"

using namespace std;

int main()
{
	Graph<int, double> graph1;
	graph1.add_vertex(1);
	graph1.add_vertex(2);
	graph1.add_vertex(3);
	graph1.add_vertex(4);
	graph1.add_edge(1, 3, 7.5);
	graph1.add_edge(1, 1, 1.0);
	graph1.add_edge(1, 2, 2.7);
	graph1.add_edge(2, 3, 1.45);
	graph1.add_edge(3, 4, 17.25);
	graph1.add_edge(4, 2, 3.89);

	cout << graph1;

	cout << "Test has_vertex" << endl;
	cout << graph1.has_vertex(1) << graph1.has_vertex(4) << graph1.has_vertex(5) << endl;

	cout << "Test remove_vertex" << endl;
	cout << graph1.remove_vertex(2) << ' ' << graph1.remove_vertex(2) << ' ' << graph1.remove_vertex(5) << endl;
	cout << graph1;

	cout << "Test vertices()" << endl;
	vector<int> vec1 = graph1.vertices();
	for (auto i : vec1) {
		cout << i << ' ';
	}
	cout << endl;
	
	cout << "Test has_edge(from, to)" << endl;
	cout << graph1.has_edge(1, 1) << ' ' << graph1.has_edge(1, 2) << ' ' << graph1.has_edge(1, 3) << endl;

	cout << "Test has_edge(from, edge)" << endl;
	cout << graph1.has_edge(1, Graph<int, double>::Edge(3, 7.5)) << ' ' << graph1.has_edge(1, Graph<int, double>::Edge(2, 7.5)) << ' ' << graph1.has_edge(1, Graph<int, double>::Edge(1, 3.75)) << endl;

	cout << "Test edges()" << endl;
	vector<Graph<int, double>::Edge> edges = graph1.edges(1);
	for (auto i : edges) {
		cout << i;
	}
	cout << endl;

	cout << "Test remove(from, to)" << endl;
	cout << graph1.remove_edge(1, 1) << ' ' << graph1.remove_edge(1, 2) << ' ' << graph1.remove_edge(1, 3) << endl;
	cout << graph1;

	cout << "Test remove(from, e)" << endl;
	cout << graph1.remove_edge(1, Graph<int, double>::Edge(2, 3.75)) << ' ' << graph1.remove_edge(2, Graph<int, double>::Edge(2, 1.45)) << ' ' << graph1.remove_edge(4, Graph<int, double>::Edge(2, 3.89)) << endl;
	cout << graph1; 

	return 0;
}

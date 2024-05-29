// graph_aisd_lab.cpp: определяет точку входа для приложения.
//

#include "graph_aisd_lab.h"

using namespace std;

int main()
{
	Graph<string, double> graph_s;
	graph_s.add_vertex("a");
	graph_s.add_vertex("b");
	graph_s.add_vertex("c");
	graph_s.add_vertex("d");
	graph_s.add_vertex("e");
	graph_s.add_edge("a", "c", 7.5);
	graph_s.add_edge("c", "d", 1.0);
	graph_s.add_edge("e", "b", 2.7);
	graph_s.add_edge("c", "e", 1.45);
	graph_s.add_edge("b", "a", 17.25);
	graph_s.add_edge("d", "b", 3.89);
	cout << graph_s << endl;

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

	cout << "Test degree" << endl;
	cout << graph1.degree(1) << graph1.degree(2) << graph1.degree(3) << graph1.degree(4) << endl;

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
	cout << graph1 << endl;

	cout << "Test walk(start vertex)" << endl;
	Graph<int, double> graph2;
	graph2.add_vertex(1);
	graph2.add_vertex(2);
	graph2.add_vertex(3);
	graph2.add_vertex(4);
	graph2.add_edge(1, 3, 7.5);
	graph2.add_edge(1, 1, 1.0);
	graph2.add_edge(1, 2, 2.7);
	graph2.add_edge(2, 3, 1.45);
	graph2.add_edge(3, 4, 17.25);
	graph2.add_edge(4, 2, 3.89);

	vector<Graph<int, double>::Edge> walked = graph2.walk(1);
	for (auto i : walked) {
		cout << i << ' ';
	}
	cout << endl << endl;

	cout << "Test shortest_path" << endl;
	vector<Graph<int, double>::Edge> shortest1 = graph2.shortest_path(1, 4);
	if (shortest1.size() != 0) {
		for (auto i : shortest1) {
			cout << i << ' ';
		}
	}
	cout << endl << endl;

	vector<Graph<int, double>::Edge> shortest2 = graph2.shortest_path(2, 4);
	if (shortest2.size() != 0) {
		for (auto i : shortest2) {
			cout << i << ' ';
		}
	}
	cout << endl << endl;

	vector<Graph<int, double>::Edge> shortest3 = graph2.shortest_path(4, 2);
	if (shortest3.size() != 0) {
		for (auto i : shortest3) {
			cout << i << ' ';
		}
	}
	cout << endl << endl;

	Graph<int, double> graph3;
	graph3.add_vertex(1);
	graph3.add_vertex(2);
	graph3.add_vertex(3);
	graph3.add_vertex(4);
	graph3.add_edge(1, 3, -7.5);
	graph3.add_edge(1, 1, -1.0);
	graph3.add_edge(1, 2, -2.7);
	graph3.add_edge(2, 3, -1.45);
	graph3.add_edge(3, 4, -17.25);
	graph3.add_edge(4, 2, -3.89);

	vector<Graph<int, double>::Edge> shortest4 = graph3.shortest_path(1, 4);
	if (shortest4.size() != 0) {
		for (auto i : shortest4) {
			cout << i << ' ';
		}
	}
	cout << endl << endl;

	cout << "Test task(start vertex)" << endl;
	int vert = graph2.find_max_average_distance();
	cout << vert << endl;

	return 0;
}

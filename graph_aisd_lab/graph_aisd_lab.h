#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <map>

using namespace std;

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex _to_id;
		Distance _distance;
		Edge(Vertex to_id, Distance distance) : _to_id(to_id), _distance(distance) {};
		bool operator==(const Edge& other) const {
			return (_to_id == other._to_id && _distance == other._distance);
		}
		friend std::ostream& operator<<(std::ostream& stream, const Edge& other) {
			stream << '(' << other._to_id << ' ' << other._distance << ") ";
			return stream;
		}
	};

private:
	map<Vertex, list<Edge>> _graph;

public:

	Graph() = default;
	~Graph() = default;

	//проверка-добавление-удаление вершин
	bool has_vertex(const Vertex& v) const {
		if (_graph.size() == 0) return false;
		else return _graph.contains(v);
	}

	void add_vertex(const Vertex& v) {
		if (has_vertex(v)) {
			cout << "Vertex already in graph." << endl;
			return;
		}
		else {
			_graph.insert({ v, list<Edge>() });
		}
	}

	bool remove_vertex(const Vertex& v) {
		if (!has_vertex(v)) return false;
		for (auto i = _graph.begin(); i != _graph.end(); ++i) {
			if (has_edge(i->first, v)) {
				remove_edge(i->first, v);
			}
		}
		return _graph.erase(v);
	}

	std::vector<Vertex> vertices() const {
		vector<Vertex> vert;
		if (_graph.size() == 0) return vert;
		else {
			for (auto i : _graph) {
				vert.push_back(i.first);
			}
			return vert;
		}
	}

	//проверка-добавление-удаление ребер
	void add_edge(const Vertex& from, const Vertex& to,
		const Distance& d) {
		if (has_vertex(from) && has_vertex(to)) {
			_graph[from].push_back(Edge(to, d));
		}
		else {
			cout << "One of vertexes not exist." << endl;
			return;
		}
	}


	bool remove_edge(const Vertex& from, const Vertex& to) {
		if (has_edge(from, to)) {
			for (auto i = _graph.at(from).begin(); i != _graph.at(from).end(); ++i) {
				if ((*i)._to_id == to) {
					_graph.at(from).erase(i);
					return true;
				}
			}
		}
		else return false;
	}

	bool remove_edge(const Vertex& from, const Edge& e) {//c учетом расстояния
		if (has_edge(from, e)) {
			for (auto i = _graph.at(from).begin(); i != _graph.at(from).end(); ++i) {
				if ((*i) == e) {
					_graph.at(from).erase(i);
					return true;
				}
			}
		}
		else return false;
	}

	bool has_edge(const Vertex& from, const Vertex& to) const {
		if (has_vertex(from) && has_vertex(to)) {
			for (auto i = _graph.at(from).begin(); i != _graph.at(from).end(); ++i) {
				if ((*i)._to_id == to) {
					return true;
				}
			}
			return false;
		}
		else return false;
	}

	bool has_edge(const Vertex& from, const Edge& e) const { //c учетом расстояния в Edge
		if (has_vertex(from) && has_vertex(e._to_id)) {
			for (auto i = _graph.at(from).begin(); i != _graph.at(from).end(); ++i) {
				if ((*i) == e) {
					return true;
				}
			}
			return false;
		}
		else return false;
	}

	//получение всех ребер, выходящих из вершины
	std::vector<Edge> edges(const Vertex& vertex) {
		vector<Edge> edges;
		if (!has_vertex(vertex)) return edges;
		for (auto i = _graph.at(vertex).begin(); i != _graph.at(vertex).end(); ++i) {
			edges.push_back((*i));
		}
		return edges;
	}

	size_t order() const { //порядок
		return _graph.size();
	}
	size_t degree(const Vertex& v) const { //степень вершины
		if (!has_vertex(v)) throw runtime_error("Vertex is not exist.");
		else {
			return _graph[v].size();
		}
	}

	friend std::ostream& operator<<(std::ostream& stream, const Graph& graph) {
		for (auto &[vertex, edges] : graph._graph) {
			stream << "Vertex(" << vertex << "): ";
			for (auto j : edges) {
				cout << j;
			}
			stream << endl;
		}
		return stream;
	}

	//поиск кратчайшего пути
	std::vector<Edge> shortest_path(const Vertex& from,
		const Vertex& to) const;
	//обход
	std::vector<Vertex>  walk(const Vertex& start_vertex) const;
};


#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <unordered_map>
#include <queue>
#include <limits>


using namespace std;

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex _to_id;
		Distance _distance;
		Edge(const Vertex& to_id,const Distance& distance) : _to_id(to_id), _distance(distance) {};
		bool operator==(const Edge& other) const {
			return (_to_id == other._to_id && _distance == other._distance);
		}
		friend std::ostream& operator<<(std::ostream& stream, const Edge& other) {
			stream << '(' << other._to_id << ": " << other._distance << ") ";
			return stream;
		}
	};

	struct Walk {
		string _color;
		Vertex _prev;
		Distance _distance;
		Walk() {
			_color = "white";
			_distance = -1;
		}
	};

	struct Shortest_ways {
		Distance _dist;
		Vertex _prev;
		Shortest_ways() {
			_dist = numeric_limits<Distance>::max();
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
	unordered_map<Vertex, Shortest_ways> Bellman_Ford_algorithm(const Vertex& from, const Vertex& to) {
		unordered_map<Vertex, Shortest_ways> shortest_ways;
		vector<Vertex> vert = vertices();
		for (auto i : vert) {
			shortest_ways[i] = Shortest_ways();
		}

		shortest_ways[from]._dist = 0;
		vector<Edge> _edges = edges(from);
		for (auto edge : _edges) {
			if ((shortest_ways[from]._dist != numeric_limits<Distance>::max()) && shortest_ways[edge._to_id]._dist > shortest_ways[from]._dist + edge._distance) {
				shortest_ways[edge._to_id]._dist = shortest_ways[from]._dist + edge._distance;
				shortest_ways[edge._to_id]._prev = from;
			}
		}

		for (int i = 0; i < vert.size(); ++i) {
			vector<Edge> _edges = edges(i);
			for (auto edge : _edges) {
				if ((shortest_ways[i]._dist != numeric_limits<Distance>::max()) && shortest_ways[edge._to_id]._dist > shortest_ways[i]._dist + edge._distance) {
					shortest_ways[edge._to_id]._dist = shortest_ways[i]._dist + edge._distance;
					shortest_ways[edge._to_id]._prev = i;
				}
			}
		}

		for (auto& [vertex, edges] : _graph) {
			for (auto j : edges) {
				if ((shortest_ways[vertex]._dist != numeric_limits<Distance>::max()) && shortest_ways[j._to_id]._dist > shortest_ways[vertex]._dist + j._distance) {
					shortest_ways.clear();
					return shortest_ways;
				}
			}
		}
		return shortest_ways;
	}

	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) {
		if (!has_vertex(from) || !has_vertex(from)) throw runtime_error("Vertex is not found.");

		vector<Edge> result_shortest_ways;

		unordered_map<Vertex, Shortest_ways> result = Bellman_Ford_algorithm(from, to);

		if (result.empty()) {
			cout << "Shortest_way is not exsist" << endl;
			return result_shortest_ways;
		}

		vector<Vertex> vert = vertices();
		for (auto v : vert) {
			if (result[v]._dist != numeric_limits<Distance>::max()) {
				result_shortest_ways.push_back(Edge(v, result[v]._dist));
			}
		}
		return result_shortest_ways;
	}

	//обход
	std::vector<Edge>  walk(const Vertex& start_vertex) const {
		if (!has_vertex(start_vertex)) throw runtime_error("Vertex is not found.");
		vector<Edge> result_of_walking;

		unordered_map<Vertex, Walk> walked;
		vector<Vertex> vert = vertices();
		for (auto i : vert) {
			walked[i] = Walk();
		}

		queue<Vertex> v_queue;
		v_queue.push(start_vertex);
		walked[start_vertex]._color = "grey";
		walked[start_vertex]._distance = 0;
		result_of_walking.push_back(Edge(start_vertex, 0));
		while (!v_queue.empty()) {
			Vertex u = v_queue.front();
			v_queue.pop();
			for (auto edge : _graph.at(u)) {
				Vertex vert = edge._to_id;
				if (walked[vert]._color == "white") {
					walked[vert]._color = "grey";
					walked[vert]._prev = u;
					walked[vert]._distance = walked[u]._distance + 1;
					result_of_walking.push_back(Edge(vert, walked[vert]._distance));
					v_queue.push(vert);
				}
			}
			walked[u]._color == "black";
		}
		return result_of_walking;
	}
};


#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Vertex {
public:
    Vertex(string name) {_name=move(name); }
    virtual ~Vertex() = default;
    const string& name() const { return _name; }
protected:
    string _name;
};

class Graph {
public:
    template<typename T>
    using VertexMap     = unordered_map<Vertex*, T>;
    using AdjacencyList = VertexMap<vector<Vertex*>>;
    void Edge(Vertex* u, Vertex* v) { _vertices[u];  _vertices[v].push_back(u); }
    vector<Vertex*> topoSort();
    VertexMap<int> outdegrees() const;  int outdegree(Vertex*) const;
    const AdjacencyList& adjacencyList() const;
protected:
    AdjacencyList _vertices;
};

enum Colour { White, Grey, Black };

void topoSortVertex(Vertex* vertex,
                    Colour& colour,
                    const Graph::AdjacencyList& adjacencyList,
                    Graph::VertexMap<Colour>& visited,
                    vector<Vertex*>& sorted) {
    colour = Grey;
    for (Vertex* neighbour : adjacencyList.at(vertex)) {
        Colour& neighbour_colour = visited[neighbour];
        if (neighbour_colour == White) {
            topoSortVertex(neighbour, neighbour_colour, adjacencyList, visited, sorted); }
        else
        if (neighbour_colour == Grey)  {
            throw runtime_error("error: cycle in graph"); }  }
    colour = Black;   sorted.push_back(vertex);
}

vector<Vertex*> Graph::topoSort() {
    VertexMap<int> outdegs = outdegrees();
    vector<Vertex*> sorted;
    sorted.reserve(outdegs.size());
    VertexMap<Colour> visited;
    visited.reserve(outdegs.size());
    for (auto& pair : outdegs)  {
        if (pair.second == 0) {
            Vertex* vertex = pair.first;
            Colour& colour = visited[vertex];
            if (colour == White)  {
                topoSortVertex(vertex, colour, _vertices, visited, sorted); }  }  }
    return sorted;
}

Graph::VertexMap<int> Graph::outdegrees() const {
    VertexMap<int> outdegrees;
    for (auto& pair : _vertices) {
        outdegrees[pair.first];  // initialise outdegree for this vertex
        for (Vertex* neighbour : pair.second)  {  ++outdegrees[neighbour]; }  }
    return outdegrees;
}

int Graph::outdegree(Vertex* v) const {  return outdegrees().at(v); }
const Graph::AdjacencyList& Graph::adjacencyList() const { return _vertices; }

int main() {
    Graph g;

    Vertex n_2("2"); Vertex n_3("3");
    Vertex n_4("4");  Vertex n_5("5");
    Vertex s_s("s"); Vertex s_x("x"); Vertex s_y("y");
    Vertex plus1("+_1"); Vertex plus2("+_2");
    Vertex minus1("-_1"); Vertex minus2("-_2");
    Vertex mult("*"); Vertex div("/"); Vertex pow("^");
    Vertex f_log("log"); Vertex f_atan2("atan2"); Vertex f_sin("sin");

    g.Edge(&s_x, &pow); g.Edge(&n_2, &pow);
    g.Edge(&s_y, &mult); g.Edge(&n_5, &mult);
    g.Edge(&s_s, &div); g.Edge(&n_3, &div);
    g.Edge(&pow,  &minus1);
    g.Edge(&minus1, &plus1); g.Edge(&mult, &plus1);
    g.Edge(&plus1,  &f_sin);
    g.Edge(&div, &plus2); g.Edge(&f_sin, &plus2);
    g.Edge(&n_4, &f_atan2); g.Edge(&s_y, &f_atan2);
    g.Edge(&plus1,  &f_log);
    g.Edge(&f_log, &minus2); g.Edge(&f_atan2, &minus2);

    cout << "adjacency list:\n";
    for (auto& pair : g.adjacencyList()) {
        cout << pair.first->name() << ": ";
        for (const Vertex* neighbour : pair.second)
            cout << neighbour->name() << ", ";
        cout << "\n";
    }

    cout << "outdegrees:\n";
    for (auto& pair : g.outdegrees())
        cout << pair.first->name() << ": " << pair.second << "; ";

    cout << "\ntopoSort:\n";
    for (Vertex* v : g.topoSort())   cout << v->name() << ", ";
    cout << '\n';

    // add cycle
    g.Edge(&minus2, &minus1);
    cout << minus1.name() << ": ";
    const Graph::AdjacencyList& adj_list=g.adjacencyList();
    for (Vertex* neighbour : adj_list.at(&minus1))
            cout << neighbour->name() << ", ";
     cout << "\n";
    try {  g.topoSort(); }
    catch (const exception& e) { cerr << e.what() << endl; }
}

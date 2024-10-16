#include "../include/graph/graph.h"

std::ostream &operator<<(std::ostream &os, const Tile &t)
{
    return (os << "y: " << t.y << " - x: " << t.x );
}

std::istream &operator>>(std::istream &is, Tile &t)
{
    LOG("Inserisci y:");
    is >> t.y;
    LOG("Inserisci x:");
    is >> t.x;
    return is;
}

bool operator==(const Tile &a, const Tile &b)
{
    if (a.x == b.x && a.y == b.y)
        return true;
    return false;
}

bool operator<(const Tile &a, const Tile &b)
{
    if (a.y == b.y)
    {
        return a.x < b.x;
    }
    else
{
        return a.y < b.y;
    }
}

bool operator>(const Tile &a, const Tile &b)
{
    if (a.y == b.y)
    {
        return a.x > b.x;
    }
    else
{
        return a.y > b.y;
    }
}
//--------------------
Vertex::Vertex(Tile t, HalfEdge *adjacency_list)
{
    this->tile = t;
    this->adjacency_list = adjacency_list;
}
Vertex::Vertex(Tile t)
{
    this->tile = t;
}
//--------------------
graph::graph()
{
    graph_.reserve(1000);
}
graph::~graph() {
    for (int32_t i = 0; i < graph_.size(); i++) {
        delete graph_.at(i).adjacency_list;
    }
}

// The GetNode function searches for a node (vertex) in the graph based on a given tile.
// It iterates over the graph and returns the index of the node if found, or -1 if not found.
int32_t graph::GetNode(const Tile &t)
{
    for (int32_t i = 0; i < graph_.size(); i++)
    {
        if (graph_.at(i).tile == t)
            return i;
    }
    return -1;
}

// The IsVertexIn function is a helper function used by other functions to check if a vertex exists in the graph.
// It also updates the index parameter if the vertex is found.
bool IsVertexIn(Tile t, int32_t &index, const std::vector<Vertex> &graph_)
{
    for (int32_t i = 0; i < graph_.size(); i++)
    {
        if (graph_.at(i).tile == t)
        {
            index = i;
            return true;
        }
    }
    return false;
}

// The AuxAreAdjacent function checks if two nodes (vertices) are adjacent in the graph by examining their adjacency lists.
bool AuxAreAdjacent(int32_t index_from, int32_t index_to, const std::vector<Vertex> &graph_)
{
    HalfEdge *aux = graph_.at(index_from).adjacency_list;
    while (aux != nullptr)
    {
        if (aux->vertex_index == index_to)
            return true;
        aux = aux->next_edge;
    }
    return false;
}

// The AddHalfEdge function adds a half-edge between two nodes in the graph.
// It creates a new HalfEdge object and adds it to the adjacency list of the source node.
void AddHalfEdge(int32_t index_from, int32_t index_to, std::vector<Vertex> &graph_)
{
    HalfEdge *e = new HalfEdge;
    e->vertex_index = index_to;
    e->next_edge = graph_.at(index_from).adjacency_list;
    graph_.at(index_from).adjacency_list = e;
}

// The RemoveHalfEdge function removes a half-edge between two nodes in the graph.
// It searches for the specified edge and removes it from the adjacency list of the source node.
void RemoveHalfEdge(int32_t index_from, int32_t index_to, std::vector<Vertex> &graph_)
{
    for (HalfEdge *edges = graph_.at(index_from).adjacency_list; edges != nullptr; edges = edges->next_edge)
    {
        if (edges->vertex_index == index_to)
        {
            edges = edges->next_edge;
            graph_.at(index_from).adjacency_list = edges;
            return;
        }
        // PProbabile cause di errore (prossima istruzione)
        if (edges->next_edge->vertex_index == index_to)
        {
            edges->next_edge = edges->next_edge->next_edge;
            return;
        }
    }
}

/*******************************************************************************************************/
// Graph
/*******************************************************************************************************/

bool graph::AddVertex(Tile t)
{
    if (GetNode(t) >= 0)
        return false;
    Vertex n = Vertex(t, nullptr);
    graph_.push_back(n);

    // AddEdge prev top and back tile 
    Tile x_t_pre = {t.y, t.x - 1};
    Tile y_t_pre = {t.y - 1, t.x};
    AddEdge(x_t_pre, t);
    AddEdge(y_t_pre, t);
    return true;
}

bool graph::AddEdge(Tile from, Tile to)
{
    if (from == to)
        return false;
    int32_t index_from;
    int32_t index_to;
    if (!IsVertexIn(from, index_from, graph_) || !IsVertexIn(to, index_to, graph_))
        return false;
    if (AuxAreAdjacent(index_from, index_to, graph_))
        return false;
    AddHalfEdge(index_from, index_to, graph_);
    AddHalfEdge(index_to, index_from, graph_);
    return true;
}

int graph::NumVertices()
{
    return graph_.size();
}

int graph::NumEdges()
{
    int tot = 0;
    for (int32_t i = 0; i < graph_.size(); i++)
    {
        NodeDegree(graph_.at(i).tile, tot);
    }
    return (tot / 2);
}

bool graph::NodeDegree(Tile t, int &degree)
{
    if (GetNode(t) < 0)
        return false;
    Vertex vertex = graph_.at(GetNode(t));
    for (HalfEdge *edges = vertex.adjacency_list; edges != nullptr; edges = edges->next_edge)
    {
        ++degree;
    }
    return true;
}

bool graph::AreAdjacent(Tile v1, Tile v2)
{
    int32_t index_from = -1;
    int32_t index_to = -1;
    if (!IsVertexIn(v1, index_from, graph_) || !IsVertexIn(v2, index_to, graph_))
        return false;
    return AuxAreAdjacent(index_from, index_to, graph_);
}

std::vector<Tile> graph::GetAdjacencyList(Tile v1)
{
    std::vector<Tile> tile_vect;
    if (GetNode(v1) != -1)
    {
        Vertex aux = graph_.at(GetNode(v1));
        HalfEdge *edges = aux.adjacency_list;
        while (edges != nullptr)
        {
            tile_vect.push_back(graph_.at(edges->vertex_index).tile);
            edges = edges->next_edge;
        }
    }
    return tile_vect;
}

void graph::PrintGraph()
{
    std::cout << "Graph:\n";
    for (int32_t i = 0; i < graph_.size(); i++)
    {
        std::cout << "(" << graph_.at(i).tile << ") |->| ";
        HalfEdge *adjnode = graph_.at(i).adjacency_list;
        while (adjnode != nullptr)
        {
            std::cout << "(" << graph_.at(adjnode->vertex_index).tile << ")";
            if (adjnode->next_edge == nullptr)
                break;
            std::cout << " || ";
            adjnode = adjnode->next_edge;
        }
        std::cout << std::endl;
    }
}

//--------------------

struct TileDistance
{
    Tile tile;
    double distance;
};

// Heuristic function for A* algorithm
int32_t Heuristic(const Tile &current, const Tile &goal)
{
    return sqrt(pow((current.x - goal.x), 2) + pow((current.y - goal.y), 2));
}

struct TileHasher
{
    std::size_t operator()(const Tile &tile) const
    {
        std::size_t h1 = std::hash<int32_t>{}(tile.y);
        std::size_t h2 = std::hash<int32_t>{}(tile.x);
        return h1 ^ (h2 << 1);
    }
};

struct CompareDist
{
    bool operator()(const TileDistance &a, const TileDistance &b)
    {
        return a.distance > b.distance;
    }
};

struct DistanceCalculator
{
    double operator()(const Tile &node1, const Tile &node2) const
    {
        return Heuristic(node1, node2);
    }
};

double potential(const Tile &node, const Tile &end)
{
    return sqrt(pow(node.x - end.x, 2) + pow(node.y - end.y, 2));
}

void graph::FindPathAStar(const Tile &start, const Tile &goal, std::vector<Tile> &path)
{
    path.clear();
    std::unordered_map<Tile, double, TileHasher> dist;
    std::priority_queue<TileDistance, std::vector<TileDistance>, CompareDist> open_nodes;
    std::unordered_set<Tile, TileHasher> closed_nodes;
    std::unordered_map<Tile, Tile, TileHasher> predecessor;

    DistanceCalculator distance;

    open_nodes.push({start, 0.0});
    dist[start] = 0.0;

    while (!open_nodes.empty())
    {
        TileDistance cur_node = open_nodes.top();
        open_nodes.pop();

        if (cur_node.tile == goal)
        {
            Tile current = cur_node.tile;
            while (!(current == start))
            {
                path.push_back(current);
                current = predecessor[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return;
        }

        closed_nodes.insert(cur_node.tile);

        for (const auto &neighbor : GetAdjacencyList(cur_node.tile))
        {
            if (closed_nodes.count(neighbor) == 0)
            {
                double new_dist = dist[cur_node.tile] + 1 + distance(neighbor, goal); /* costo tile adiacente +1 */
                if (!dist.count(neighbor) || new_dist < dist[neighbor])
                {
                    dist[neighbor] = new_dist;
                    predecessor[neighbor] = cur_node.tile;
                    open_nodes.push({neighbor, new_dist});
                }
            }
        }
    }
}

//--------------------
void graph::PrintMaze(std::vector<Tile> &path)
{
    if (graph_.size() == 0)
    {
        return;
    }
    std::vector<Tile> ordered_nodes;
    ordered_nodes.reserve(1000);
    for (int32_t i = 0; i < graph_.size(); i++)
    {
        int32_t temp_index = 0;
        for (int32_t j = 0; j < ordered_nodes.size(); j++)
        {
            if (graph_.at(i).tile < ordered_nodes.at(j))
            {
                break;
            }
            temp_index++;
        }
        ordered_nodes.insert(ordered_nodes.begin() + temp_index, graph_.at(i).tile);
    }

    int32_t max_x = ordered_nodes.at(0).x;
    int32_t min_x = ordered_nodes.at(0).x;
    int32_t max_y = ordered_nodes.at(0).y;
    int32_t min_y = ordered_nodes.at(0).y;

    for (int i = 0; i < ordered_nodes.size(); i++)
    {
        if (max_x < ordered_nodes.at(i).x )
            max_x = ordered_nodes.at(i).x;
        if (min_x > ordered_nodes.at(i).x )
            min_x = ordered_nodes.at(i).x;
        if (max_y < ordered_nodes.at(i).y )
            max_y = ordered_nodes.at(i).y;
        if (min_y > ordered_nodes.at(i).y )
            min_y = ordered_nodes.at(i).y;
    }


    for (int8_t y = min_y; y <= max_y; y++)
    {
        for (int8_t i = 0; i < 3; i++)
        {
            for (int8_t x = min_x; x <= max_x; x++)
            {
                if (i == 0)
                {
                    if (GetNode({y, x}) == -1)
                    {
                        if (GetNode({y - 1, x}) != -1)
                        {
                            std::cout << "+---";
                        }
                        else
                    {
                            if (GetNode({y, x - 1}) != -1)
                            {
                                std::cout << "+   ";
                            }
                            else
                        {
                                std::cout << "    ";
                            }
                        }
                    }
                    else
                {
                        if (AreAdjacent({y, x}, {y - 1, x}))
                        {
                            if (AreAdjacent({y, x}, {y, x - 1}) && AreAdjacent({y, x - 1}, {y - 1, x - 1}) && AreAdjacent({y - 1, x - 1}, {y - 1, x}))
                            {
                                std::cout << " ";
                                std::cout << "   ";
                            }
                            else
                        {
                                std::cout << "+";
                                std::cout << "   ";
                            }
                        }
                        else
                    {
                            std::cout << "+";
                            std::cout << "---";
                        }
                    }
                }
                else if (i == 1)
                {
                    if (GetNode({y, x}) == -1)
                    {
                        if (GetNode({y, x - 1}) != -1)
                        {
                            std::cout << "| # ";
                        }
                        else
                    {
                            std::cout << "  # ";
                        }
                    }
                    else
                {
                        if (AreAdjacent({y, x}, {y, x - 1}))
                        {
                            bool in_path = false;
                            for (int8_t p = 0; p < path.size(); p++)
                            {
                                if (Tile{y, x} == path.at(p))
                                {
                                    in_path = true;
                                    break;
                                }
                            }
                            if (in_path)
                            {
                                if (Tile{y, x} == path.at(0))
                                {
                                    std::cout << "  S ";
                                }
                                else if (Tile{y, x} == path.at(path.size()-1))
                                {
                                    std::cout << "  E ";
                                }
                                else
                            {
                                    std::cout << "  O ";
                                }
                            }
                            else
                        {
                                std::cout << "    ";
                            }

                        }
                        else
                    {
                            bool in_path = false;
                            for (int8_t p = 0; p < path.size(); p++)
                            {
                                if (Tile{y, x} == path.at(p))
                                {
                                    in_path = true;
                                    break;
                                }
                            }
                            if (in_path)
                            {
                                if (Tile{y, x} == path.at(0))
                                {
                                    std::cout << "| S ";
                                }
                                else if (Tile{y, x} == path.at(path.size()-1))
                                {
                                    std::cout << "| E ";
                                }
                                else
                            {
                                    std::cout << "| O ";
                                }
                            }
                            else
                        {
                                std::cout << "|   ";
                            }}
                    }
                }
            }
            if (i == 0)
            {
                if (GetNode({y, max_x}) != -1 || GetNode({y - 1, max_x}) != -1)
                    std::cout << "+\n";
                else
                    std::cout << "\n";
            }
            else if (i == 1)
            {
                if (GetNode({y, max_x}) != -1)
                    std::cout << "|\n";
                else
                    std::cout << "\n";
            }
        }
    }
    for (int8_t x = min_x; x <= max_x; x++)
    {
        if (GetNode({max_y, x}) == -1)
        {
            if (GetNode({max_y, x - 1}) == -1)
            {
                std::cout << "    ";
            }
            else
        {
                std::cout << "+   ";
            }
        }
        else
    {
            std::cout << "+---";
        }
    }
    if (GetNode({max_y, max_x}) != -1)
        std::cout << "+\n";
    else
        std::cout << "\n";
}

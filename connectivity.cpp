#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

class Graph {
public:
    std::vector<std::vector<int>> adjacencyList;

    Graph(int numVertices) {
        adjacencyList.resize(numVertices + 1);  
    }

    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
};

std::vector<int> DFS(Graph& graph, int vertex,  std::vector<bool>& isVisited) {
    std::vector<int> component;
    
    std::stack<int> visitStack;
    visitStack.push(vertex);
    
    while(!visitStack.empty()) {
        int currentVertex = visitStack.top();
        visitStack.pop();

        if (!isVisited[currentVertex]) {
            isVisited[currentVertex] = true;
            component.push_back(currentVertex);
        }
        
        if (!graph.adjacencyList[currentVertex].empty()) 
            for (int nextVertex : graph.adjacencyList[currentVertex])
                if (!isVisited[nextVertex])
                    visitStack.push(nextVertex);
    }

    return component;
}

std::vector<std::vector<int>> findConnectivityComponents(Graph& graph) {
    std::vector<std::vector<int>> connectivityComponents;
    std::vector<bool> isVisited(graph.adjacencyList.size(), false);

    auto maxVertexByEdges = std::max_element(graph.adjacencyList.begin() + 1, 
                                            graph.adjacencyList.end(),
                                            [](const auto& a, const auto& b) {
                                                return a.size() < b.size();
                                            });
    int startVertex = std::distance(graph.adjacencyList.begin(), maxVertexByEdges);

    connectivityComponents.push_back(DFS(graph, startVertex, isVisited));

    for (int i = 1; i < graph.adjacencyList.size(); ++i) 
        if (!isVisited[i]) 
            connectivityComponents.push_back(DFS(graph, i, isVisited));

    return connectivityComponents;
}

template <typename T>
void print(std::vector<T> vec) {
    for (T element : vec)
        std::cout << element << ' ';
    std::cout << '\n';
}

int main() {
    int numVertices, numEdges;
    int u, v;
    std::cin >> numVertices >> numEdges;

    Graph graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    std::vector<std::vector<int>> connectivityComponents = findConnectivityComponents(graph);

    std::cout << "Number of connectivity components: " << connectivityComponents.size() << '\n';
    std::cout << "Connectivity components:\n";
    for (const auto& component : connectivityComponents) {
        std::cout << "Component: ";
        print(component);
    }

    return 0;
}

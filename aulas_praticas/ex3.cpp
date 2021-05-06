#include "graphviewer.h"
#include <fstream>

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex3() {
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(300, 300));
    gv.createWindow(600, 600);

    fstream nodes_file;
    nodes_file.open("../TP7_graphviewer/resources/map1/nodes.txt");
    int N;
    nodes_file >> N;
    vector<Node> nodes;
    for(int i = 0; i < N; ++i){
        int id, x, y;
        nodes_file >> id >> x >> y;
        Node &n = gv.addNode(id, sf::Vector2f(x,y));
        nodes.push_back(n);
    }
    nodes_file.close();

    fstream edge_file;
    edge_file.open("../TP7_graphviewer/resources/map1/edges.txt");
    edge_file >> N;
    for(int i = 0; i < N; ++i){
        int id, s, d;
        edge_file >> id >> s >> d;
        gv.addEdge(id, nodes[s], nodes[d]);
    }
    edge_file.close();
    gv.join();
}


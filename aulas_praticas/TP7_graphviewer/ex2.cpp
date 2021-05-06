#include <fstream>
#include <iostream>
#include <unistd.h>
#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex2() {
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(300, 300));
    gv.createWindow(600, 600);

    fstream node_file;
    node_file.open("../TP7_graphviewer/resources/ex2_nodes.txt");
    char buffer[1024];
    vector<Node> nodes;
    while(node_file.getline(buffer, 1024)){
        int id,x,y;
        sscanf(buffer, "id:%d, x: %d, y:%d\n", &id, &x, &y);
        nodes.push_back(gv.addNode(id, sf::Vector2f(x,y)));
    }
    node_file.close();

    fstream edge_file;
    edge_file.open("../TP7_graphviewer/resources/ex2_edges.txt");
    vector<Edge> edges;
    while(edge_file.getline(buffer, 1024)){
        int id, s, d;
        sscanf(buffer, "id:%d, idSourceVertex:%d, idDestinationVertex:%d", &id, &s, &d);
        edges.push_back(gv.addEdge(id, nodes[s], nodes[d], GraphViewer::Edge::EdgeType::UNDIRECTED));
    }


    int nsecs = 10;
    sf::Vector2f pos12 = sf::Vector2f(250, 550);
    sf::Vector2f pos13 = sf::Vector2f(350, 550);
    while(nsecs-- > 0){
        gv.lock();
        sf::Vector2f tmppos = nodes[12].getPosition();
        nodes[12].setPosition(pos12);
        pos12 = tmppos;

        tmppos = nodes[13].getPosition();
        nodes[13].setPosition(pos13);
        pos13 = tmppos;
        cout << pos13.x << "," << pos13.y << '\n';
        gv.unlock();
        sleep(1);
    }
    gv.join();
}


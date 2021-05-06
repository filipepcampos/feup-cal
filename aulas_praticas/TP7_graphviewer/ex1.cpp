#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void setupGV(GraphViewer &gv){
    gv.setCenter(sf::Vector2f(300, 300));
    gv.createWindow(600, 600);
}

Node &addNode(GraphViewer &gv, double x, double y, GraphViewer::Color color){

}

void ex1() {
    GraphViewer gv;
    setupGV(gv);
    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300));
    node0.setColor(GraphViewer::BLUE);

    Node &node1 = gv.addNode(1, sf::Vector2f(400, 300));
    node1.setColor(GraphViewer::BLACK);

    Edge &edge1 = gv.addEdge(0,node0,node1,GraphViewer::Edge::EdgeType::DIRECTED);

    gv.removeNode(1);
    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));
    node2.setColor(GraphViewer::RED);
    gv.setBackground("../TP7_graphviewer/resources/background.png");
   gv.join();
}

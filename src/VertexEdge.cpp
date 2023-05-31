#include "VertexEdge.h"

using namespace std;

/************************* Vertex  **************************/

Vertex::Vertex(int id, double longitude, double latitude)
        : id(id), latitude(latitude), longitude(longitude) {}

Vertex::Vertex(int id) : id(id) {
    this->latitude = 0;
    this->longitude = 0;
}

int Vertex::getId() const {
    return this->id;
}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getId() == id) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

double Vertex::getPrimDist() const {
    return this->primDist;
}

void Vertex::setPrimDist(double dist) {
    this->primDist = dist;
}
bool Vertex::getVisited() const {
    return this->visited;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->primDist < vertex.primDist;
}

double Vertex::getLatitude() const {
    return latitude;
}

void Vertex::setLatitude(double latitude) {
    Vertex::latitude = latitude;
}

double Vertex::getLongitude() const {
    return longitude;
}

void Vertex::setLongitude(double longitude) {
    Vertex::longitude = longitude;
}

Edge *Vertex::findEdge(int dest) {
    for (Edge *e: this->adj) {
        if (e->getDest()->getId() == dest)
            return e;
    }

    return nullptr;
}

/********************** Edge  ****************************/


Edge::Edge(Vertex *orig, Vertex *dest, double distance): orig(orig), dest(dest), distance(distance) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getDistance() const {
    return this->distance;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}


void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}


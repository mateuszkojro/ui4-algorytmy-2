#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <cassert>
#include <chrono>
#include <map>

class Node;

class Edge;

class Edge {
public:
    Edge(int name1, int name2, int cost) :
            name1_(name1),
            name2_(name2),
            cost_(cost),
            one_(nullptr),
            two_(nullptr) {};

    bool operator<(const Edge &other) const {
        return this->cost_ < other.cost_;
    }


    int cost_;
    int name1_;
    int name2_;

    Node *one_;
    Node *two_;
};

class Node {
public:
    explicit Node(int name) :
            name_(name) {}

    int name_;
    std::vector<Edge *> edges_;
};

using Tree = Node *;
using Forest = std::vector<Tree>;


Node *find_mst(std::vector<Edge *> edges, std::vector<Node *> forest);

Node *find_node(Node *tree, Node *from, int target);

bool try_connect(Forest &forest, Edge *edge);

void connect(Node *node1, Node *node2, Edge *edge);

void print_tree(Node *node, std::map<int, std::string> &node_id);//



int main() {

    std::map<int, std::string> node_id;

    // todo how many
    int no_nodes;
    std::cin >> no_nodes;

    std::vector<Node *> nodes;
    std::vector<Edge *> edges;

    nodes.reserve(no_nodes);
    int temp;
    std::string name;
    for (int i = 0; i < no_nodes; i++) {
        std::cin >> temp;
        std::cin >> name;
        nodes.push_back(new Node(temp));
        node_id.insert({temp, name});
    }
    int no_edges;
    std::cin >> no_edges;

    int from, to, cost;
    for (int i = 0; i < no_edges; i++) {
        std::cin >> from >> to >> cost;
        edges.push_back(new Edge(from, to, cost));
    }


    auto result = find_mst(edges, nodes);

    print_tree(result, node_id);

    return 0;
}


void connect(Node *node1, Node *node2, Edge *edge) {
    assert(edge->name1_ == node1->name_ || edge->name2_ == node1->name_);
    assert(edge->name1_ == node2->name_ || edge->name2_ == node2->name_);

    edge->one_ = node1;
    edge->two_ = node2;

    node1->edges_.push_back(edge);
    node2->edges_.push_back(edge);
}

Node *find_node(Node *tree, Node *from, int target) {
    Node *result = nullptr;

    if (tree->name_ == target)
        return tree;

    for (Edge *child : tree->edges_) {

        if (child->name1_ == tree->name_) {

            if (child->two_ == from)
                continue;

            if (child->two_->name_ == target)
                return child->two_;

            else {
                result = find_node(child->two_, tree, target);
                if (result)
                    return result;
            }
        } else {
            if (child->one_ == from)
                continue;

            if (child->one_->name_ == target)
                return child->one_;
            else {
                result = find_node(child->one_, tree, target);
                if (result)
                    return result;
            }
        }
    }
    return result;
}

bool try_connect(Forest &forest, Edge *edge) {
    Node *node1 = nullptr;
    int tree_idx1 = -1;

    Node *node2 = nullptr;
    int tree_idx2 = -1;

    for (Node *tree : forest) {
        tree_idx1++;
        node1 = find_node(tree, forest[tree_idx1], edge->name1_);

        if (node1)
            break;
    }

    for (Node *tree : forest) {
        tree_idx2++;
        node2 = find_node(tree, forest[tree_idx2], edge->name2_);

        if (node2)
            break;
    }

    if (tree_idx2 == tree_idx1)
        return false;

    if (!node1)
        return false;

    if (!node2)
        return false;

    connect(node1, node2, edge);
    forest.erase(forest.begin() + tree_idx2);
    return true;
}

void sort(std::vector<Edge *> &edges) {
    for (int i = 0; i < edges.size(); i++) {

        for (int j = 0; j < edges.size(); j++) {

            if (*edges[i] < *edges[j]) {

                Edge *temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;

            }
        }
    }
}

Node *find_mst(std::vector<Edge *> edges, std::vector<Node *> forest) {


    sort(edges);

    Node *mst = nullptr;

    while (!edges.empty()) {
        try_connect(forest, edges.front());

        edges.erase(edges.begin());

        if (forest.size() == 1) break;

    }
    return forest[0];
}


void print_tree(Node *node,std::map<int, std::string> &node_id) {

    for (Edge *child : node->edges_) {

        std::cout << node_id[node->name_] << node_id[child->name1_] <<child->cost_ <<std::endl;

        print_tree(child->two_, node_id);

    }
}
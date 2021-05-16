#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

class Node;

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

std::vector<Node *> find_mst(std::vector<Edge *> edges, std::vector<Node *> forest, int beg, int end, int count);

void print_tree(Node *node, Node *from, Edge *edge) {
    std::cout << "Name:\t" << node->name_ << "\tEdge:\t" << edge->cost_
              << std::endl; //"\tEdge from:\t" << edge->name1_ << "\tEdge to\t"<< edge->name2_  << std::endl;
    for (Edge *child : node->edges_) {
        if (child->name1_ == node->name_) {
            if (child->two_ == from)
                continue;
            print_tree(child->two_, node, child);
        } else {
            if (child->one_ == from)
                continue;
            print_tree(child->one_, node, child);
        }
    }
}

int main() {
    using namespace std;

    // todo how many
    int no_nodes, no_edges;
    cin >> no_nodes >> no_edges;

    vector<Node *> nodes;
    vector<Edge *> edges;

    nodes.reserve(no_nodes);
    for (int i = 0; i < no_nodes; i++) {
        nodes.push_back(new Node(i));
    }

    int itr = no_edges;
    while (itr--) {
        int from, to, cost;
        cin >> from >> to >> cost;
        edges.push_back(new Edge(from, to, cost));
    }

    int beginning, end, no_passengers;
    cin >> beginning >> end;
    cin >> no_passengers;
    auto result = find_mst(edges, nodes, beginning, end, no_passengers);
    for (Node *tree : result) {
        std::cout << "New tree" << std::endl;
        print_tree(tree, tree, tree->edges_[0]);
    }

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

//bool is_mst(Node *tree, Node *from, Node *start, Node *end) {
//
//    if (!find_node(tree, from, start->name_))
//        return false;
//    if (!find_node(tree, from, start->name_))
//        return false;
//    return true;
//}

//Node *check_forest(std::vector<Node *> forest, Node *start, Node *end) {
//    for (Node *tree : forest) {
//        if (is_mst(tree, tree, start, end))
//            return tree;
//    }
//    return nullptr;
//}

bool try_connect(std::vector<Node *> &forest, Edge *edge) {
    Node *node1 = nullptr;
    int tree_idx1 = -1;

    Node *node2 = nullptr;
    int tree_idx2 = -1;

    for (Node *tree : forest) {
        tree_idx1++;
        node1 = find_node(tree, tree, edge->name1_);
        if (node1)
            break;
    }

    for (Node *tree : forest) {
        tree_idx2++;
        node2 = find_node(tree, tree, edge->name2_);
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
        for (int j = 0; j < edges.size() ; j++) {
            if (*edges[i] < *edges[j]) {
                Edge *temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

std::vector<Node *> find_mst(std::vector<Edge *> edges, std::vector<Node *> forest, int beg, int end, int count) {
//    std::sort(edges.begin(), edges.end(), [](const Edge *& one, const Edge *& two) {
//        return *one < *two;
//    });
    sort(edges);

    for(auto edge : edges){
        std::cout << edge->cost_ << std::endl;
    }
    //    for (Edge *edge : edges) {
////        if (check_forest(forest, nodes.size())) {
////          return true;
////        }
//        try_connect(forest, edge);
//    }

    while (!edges.empty()) {
        try_connect(forest, edges.back());
        edges.erase(edges.end() - 1);
    }

    return forest;
}

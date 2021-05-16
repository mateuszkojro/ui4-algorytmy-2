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

    bool operator<(const Edge &other) {
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
    Node(int name) :
            name_(name) {}

    int name_;
    std::vector<Edge *> edges_;
};

std::vector<Node *> find_mst(std::vector<Edge *> edges, std::vector<Node *> nodes, int beg, int end, int count);

void print_tree(Node *node, Node *from) {
    std::cout << node->name_ << std::endl;
    for (Edge *child : node->edges_) {
        if (child->name1_ == node->name_) {
            if (child->two_ == from)
                continue;
            print_tree(child->two_, node);
        } else {
            if (child->one_ == from)
                continue;
            print_tree(child->one_, node);
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
        print_tree(tree, tree);
    }

    return 0;
}

void fill_empty(std::vector<std::pair<int, bool>> &data, int no) {
    for (int i = 0; i < no; i++) {
        data.emplace_back(no, false);
    }
}

//bool is_mst(Node *node, std::vector<std::pair<int, bool>> state) {
//    for(Node* child : node.)
//}

//bool check_forest(std::vector<Node *> forest, int no_nodes) {
//
//    for (Node *tree : forest) {
//        std::vector<std::pair<int, bool>> state;
//        fill_empty(state, no_nodes);
//        if (is_mst(tree))
//            return true;
//    }
//    return false;
//}

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


void try_connect(std::vector<Node *> &forest, Edge *edge) {
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
        return;

    if (!node1)
        return;

    if (!node2)
        return;
    connect(node1, node2, edge);
    forest.erase(forest.begin() + tree_idx2);
}

std::vector<Node *> find_mst(std::vector<Edge *> edges, std::vector<Node *> nodes, int beg, int end, int count) {
    std::sort(edges.begin(), edges.end());
    std::vector<Node *> forest;
    forest = nodes;
//    for (Edge *edge : edges) {
////        if (check_forest(forest, nodes.size())) {
////          return true;
////        }
//        try_connect(forest, edge);
//    }

    while (!edges.empty()) {
        try_connect(forest, edges.back());
        edges.erase(edges.end()-1);
    }

    return forest;
}

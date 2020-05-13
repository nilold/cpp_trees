#include <iostream>
#include "node.h"
#include <queue>
#include <unordered_set>

#include "visitor.h"

typedef std::shared_ptr<nilo::Node<int>> node_ptr;

node_ptr make_tree();

void bfs(const node_ptr &node1);

int main() {

    node_ptr node1 = make_tree();

    bfs(node1);


    return 0;
}

void bfs(const node_ptr &node1) {
    std::queue<node_ptr> nextToVisit;
    std::unordered_set<node_ptr> willVisit;
    node_ptr current = node1;
    nextToVisit.push(current);

    std::cout << "Visited: ";

    nilo::BFSVisitor<int> visitor;
    visitor.visit(current, nullptr);

    while (!nextToVisit.empty()) {
        current = nextToVisit.front();

        nextToVisit.pop();
        std::cout << current->value() << " ";

        for (const auto &child : current->children()) {
            visitor.visit(child, current);
            if (willVisit.find(child) == willVisit.end()) {
                nextToVisit.push(child);
                willVisit.emplace(child);
            }
        }
    }

    std::cout << std::endl;
    std::cout << visitor <<std::endl;
}

node_ptr make_tree() {
    node_ptr n1 = std::make_shared<nilo::Node<int>>(1);
    node_ptr n2 = std::make_shared<nilo::Node<int>>(2);
    node_ptr n3 = std::make_shared<nilo::Node<int>>(3);
    node_ptr n4 = std::make_shared<nilo::Node<int>>(4);
    node_ptr n5 = std::make_shared<nilo::Node<int>>(5);
    node_ptr n6 = std::make_shared<nilo::Node<int>>(6);
    node_ptr n7 = std::make_shared<nilo::Node<int>>(7);
    node_ptr n8 = std::make_shared<nilo::Node<int>>(8);
    node_ptr n9 = std::make_shared<nilo::Node<int>>(9);
    node_ptr n10 = std::make_shared<nilo::Node<int>>(10);
    node_ptr n11 = std::make_shared<nilo::Node<int>>(11);

    n1->add_child(n3);
    n1->add_child(n2);
    n1->add_child(n4);

    n2->add_child(n3);
    n2->add_child(n6);

    n3->add_child(n6);

    n4->add_child(n5);

    n6->add_child(n7);
    n6->add_child(n8);

    n7->add_child(n10);

    n8->add_child(n9);
    n8->add_child(n6);

    n9->add_child(n10);
    n10->add_child(n11);

    return n1;
}

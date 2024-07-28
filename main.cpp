#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include "gui.hpp"
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    Node<double> root_node(1.1);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    
    // Pre-order traversal
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << (*node).get_value() << endl;
    }

    // Post-order traversal
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << (*node).get_value() << endl;
    }

    // In-order traversal
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << (*node).get_value() << endl;
    }

    // BFS traversal
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << (*node).get_value() << endl;
    }

    // DFS traversal
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << (*node).get_value() << endl;
    }
    GUI gui;
    cout << tree;
    gui.printTree(tree);
    Tree<double, 3> three_ary_tree;
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // Print the structure of the three_ary_tree
    cout << "Three-ary Tree Structure:" << endl;
    cout << three_ary_tree;
    gui.printTree(three_ary_tree);
    return 0;
}

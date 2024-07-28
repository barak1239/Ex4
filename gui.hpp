#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "tree.hpp"

class GUI {
public:
    void printTree(const Tree<double>& tree);
    void printTree(const Tree<double, 3>& tree); // Overloaded method for three-ary tree
};

#endif // GUI_HPP

#include "gui.hpp"
#include <cmath>
#include <iostream> // For std::cerr
#include <iomanip>  // For std::setprecision
#include <sstream>  // For std::stringstream

void GUI::printTree(const Tree<double>& tree) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

    auto nodes = tree.getNodesBFS();

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        std::cerr << "Failed to load font '/usr/share/fonts/truetype/msttcorefonts/arial.ttf'" << std::endl;
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        float y_offset = 50;
        float x_center = window.getSize().x / 2.0f;  // Center horizontally
        float level_height = 170;  // Slightly increased level height

        std::map<std::shared_ptr<Node<double>>, sf::Vector2f> positions;
        std::queue<std::shared_ptr<Node<double>>> q;
        q.push(tree.getRoot());
        positions[tree.getRoot()] = sf::Vector2f(x_center, y_offset);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            auto pos = positions[node];

            // Draw lines to children
            float child_x_spacing = 250.0f / (node->children.size() + 1);  // Slightly increased spacing for better separation
            for (size_t i = 0; i < node->children.size(); ++i) {
                auto child = node->children[i];
                float x_offset = (i - (node->children.size() - 1) / 2.0f) * child_x_spacing;
                positions[child] = sf::Vector2f(pos.x + x_offset, pos.y + level_height);
                sf::Vertex line[] = {
                    sf::Vertex(pos),
                    sf::Vertex(positions[child])
                };
                window.draw(line, 2, sf::Lines);
                q.push(child);
            }

            // Draw node
            sf::CircleShape shape(25);  // Slightly larger circles
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::White);
            shape.setPosition(pos.x - shape.getRadius(), pos.y - shape.getRadius());
            window.draw(shape);

            // Draw text
            sf::Text text;
            text.setFont(font);
            
            // Format the number to one decimal place
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << node->get_value();
            text.setString(ss.str());
            
            text.setCharacterSize(16);  // Slightly larger text
            text.setFillColor(sf::Color::White);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(pos.x, pos.y);
            window.draw(text);
        }

        window.display();
    }
}

void GUI::printTree(const Tree<double, 3>& tree) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Three-Ary Tree Visualization");

    auto nodes = tree.getNodesBFS();

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/msttcorefonts/arial.ttf")) {
        std::cerr << "Failed to load font '/usr/share/fonts/truetype/msttcorefonts/arial.ttf'" << std::endl;
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        float y_offset = 50;
        float x_center = window.getSize().x / 2.0f;  // Center horizontally
        float level_height = 170;  // Slightly increased level height

        std::map<std::shared_ptr<Node<double>>, sf::Vector2f> positions;
        std::queue<std::shared_ptr<Node<double>>> q;
        q.push(tree.getRoot());
        positions[tree.getRoot()] = sf::Vector2f(x_center, y_offset);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();

            auto pos = positions[node];

            // Draw lines to children
            float child_x_spacing = 250.0f / (node->children.size() + 1);  // Slightly increased spacing for better separation
            for (size_t i = 0; i < node->children.size(); ++i) {
                auto child = node->children[i];
                float x_offset = (i - (node->children.size() - 1) / 2.0f) * child_x_spacing;
                positions[child] = sf::Vector2f(pos.x + x_offset, pos.y + level_height);
                sf::Vertex line[] = {
                    sf::Vertex(pos),
                    sf::Vertex(positions[child])
                };
                window.draw(line, 2, sf::Lines);
                q.push(child);
            }

            // Draw node
            sf::CircleShape shape(25);  // Slightly larger circles
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::White);
            shape.setPosition(pos.x - shape.getRadius(), pos.y - shape.getRadius());
            window.draw(shape);

            // Draw text
            sf::Text text;
            text.setFont(font);
            
            // Format the number to one decimal place
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << node->get_value();
            text.setString(ss.str());
            
            text.setCharacterSize(16);  // Slightly larger text
            text.setFillColor(sf::Color::White);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(pos.x, pos.y);
            window.draw(text);
        }

        window.display();
    }
}

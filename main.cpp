// Copyright 2025 Danny Nguyen
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./Sokoban <level_file>\n";
        return 1;
    }

    std::string filename = "sokoban/" + std::string(argv[1]);

    try {
        SB::Sokoban game(filename);
        sf::RenderWindow window(sf::VideoMode(game.pixelWidth(), game.pixelHeight()), "Sokoban");

        // Timer and Move Counter Initialization
        sf::Font font;
        if (!font.loadFromFile("sokoban/Movistar Text Regular.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
            return 1;
        }

        sf::Text moveCounterText("Moves: 0", font, 24);
        moveCounterText.setFillColor(sf::Color::White);
        moveCounterText.setPosition(10, game.pixelHeight() - 40);

        sf::Text timerText("Time: 0s", font, 24);
        timerText.setFillColor(sf::Color::White);
        timerText.setPosition(game.pixelWidth() - 150, game.pixelHeight() - 40);

        // Timer and move count
        int moveCounter = 0;
        auto startTime = std::chrono::high_resolution_clock::now();

        bool gameRunning = true;
        // Main game loop
        while (window.isOpen() && gameRunning) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                // Handle key press events
                if (event.type == sf::Event::KeyPressed) {
                    // Handle specific key presses
                    if (event.key.code == sf::Keyboard::Up) {
                        moveCounter++;
                    } else if (event.key.code == sf::Keyboard::Right) {
                        moveCounter++;
                    } else if (event.key.code == sf::Keyboard::Down) {
                        moveCounter++;
                    } else if (event.key.code == sf::Keyboard::Left) {
                        moveCounter++;
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        gameRunning = false;
                    }
                }
            }

            // Update timer
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = currentTime - startTime;
            int elapsedSeconds = static_cast<int>(elapsed.count());

            // Update the display strings
            moveCounterText.setString("Moves: " + std::to_string(moveCounter));
            timerText.setString("Time: " + std::to_string(elapsedSeconds) + "s");

            // Clear the window
            window.clear();
            window.draw(game);  // Draw the game state

            // Draw the move counter and timer text
            window.draw(moveCounterText);
            window.draw(timerText);

            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


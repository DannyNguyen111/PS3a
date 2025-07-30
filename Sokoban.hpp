// Copyright 2025 Danny Nguyen
#pragma once


#include <iostream>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {
// Enum for movement directions
enum class Direction {
Up, Down, Left, Right
};

enum class Tile {
Empty   = 0,
Wall    = 1 << 0,
Crate   = 1 << 1,
Storage = 1 << 2,
Player  = 1 << 3,
Ground  = 1 << 4
};

class Sokoban : public sf::Drawable {
 public:
static const int TILE_SIZE = 64;

Sokoban();
explicit Sokoban(const std::string& filename);

unsigned int pixelHeight() const;
unsigned int pixelWidth() const;

unsigned int height() const;
unsigned int width() const;
sf::Vector2u playerLoc() const;

bool isWon() const;

void movePlayer(Direction dir);
void reset();

 protected:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
unsigned int S_width = 0;
unsigned int S_height = 0;
std::vector<std::vector<Tile>> S_grid;
sf::Vector2u S_playerLocation;
std::unordered_map<Tile, sf::Texture> S_textures;

void loadTextures();

bool isTileSet(Tile value, Tile flag) const;

friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
friend std::istream& operator>>(std::istream& in, Sokoban& s);
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);
}  // namespace SB


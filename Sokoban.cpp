// Copyright 2025 Danny Nguyen
#include "Sokoban.hpp"
#include <fstream>

namespace SB {

Sokoban::Sokoban() {}

Sokoban::Sokoban(const std::string& filename) {
std::ifstream inFile(filename);
if (!inFile) {
    throw std::runtime_error("Failed to open file: " + filename);
}

inFile >> S_height >> S_width;
inFile.ignore();
S_grid.resize(S_height, std::vector<Tile>(S_width, Tile::Empty));

for (unsigned int i = 0; i < S_height; i++) {
    std::string line;
    std::getline(inFile, line);
    for (unsigned int j = 0; j < S_width; j++) {
        char c = line[j];
        switch (c) {
            case '#': S_grid[i][j] = Tile::Wall; break;
            case '.': S_grid[i][j] = Tile::Ground; break;
            case 'a': S_grid[i][j] = Tile::Storage; break;
            case 'A': S_grid[i][j] = static_cast<Tile>(static_cast<int>(Tile::Crate)
            | static_cast<int>(Tile::Storage)); break;
            case '@': S_grid[i][j] = Tile::Player; S_playerLocation = { j, i }; break;
            default: S_grid[i][j] = Tile::Empty; break;
        }
    }
}

loadTextures();
}

unsigned int Sokoban::pixelHeight() const { return S_height * TILE_SIZE; }
unsigned int Sokoban::pixelWidth() const { return S_width * TILE_SIZE; }
unsigned int Sokoban::height() const { return S_height; }
unsigned int Sokoban::width() const { return S_width; }
sf::Vector2u Sokoban::playerLoc() const { return S_playerLocation; }

void Sokoban::loadTextures() {
S_textures[Tile::Wall].loadFromFile("sokoban/block_06.png");
S_textures[Tile::Ground].loadFromFile("sokoban/ground_01.png");
S_textures[Tile::Storage].loadFromFile("sokoban/ground_04.png");
S_textures[Tile::Crate].loadFromFile("sokoban/crate_03.png");
S_textures[Tile::Player].loadFromFile("sokoban/player_05.png");
}


bool Sokoban::isTileSet(Tile value, Tile flag) const {
return static_cast<int>(value) & static_cast<int>(flag);
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
sf::Sprite sprite;
for (unsigned int row = 0; row < S_height; ++row) {
    for (unsigned int col = 0; col < S_width; ++col) {
        Tile tile = S_grid[row][col];

        if (isTileSet(tile, Tile::Ground)) {
            sprite.setTexture(S_textures.at(Tile::Ground));
        } else if (isTileSet(tile, Tile::Storage)) {
            sprite.setTexture(S_textures.at(Tile::Storage));
        }
        sprite.setPosition(col * TILE_SIZE, row * TILE_SIZE);
        target.draw(sprite, states);

        if (isTileSet(tile, Tile::Wall)) {
            sprite.setTexture(S_textures.at(Tile::Ground));
            target.draw(sprite, states);
            sprite.setTexture(S_textures.at(Tile::Wall));
            target.draw(sprite, states);
        }
        if (isTileSet(tile, Tile::Crate)) {
            sprite.setTexture(S_textures.at(Tile::Ground));
            target.draw(sprite, states);
            sprite.setTexture(S_textures.at(Tile::Crate));
            target.draw(sprite, states);
        }
        if (isTileSet(tile, Tile::Player)) {
            sprite.setTexture(S_textures.at(Tile::Ground));
            target.draw(sprite, states);
            sprite.setTexture(S_textures.at(Tile::Player));
            target.draw(sprite, states);
        }
    }
}
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
out << s.S_height << " " << s.S_width << "\n";
for (unsigned int i = 0; i < s.S_height; i++) {
    for (unsigned int j = 0; j < s.S_width; j++) {
        Tile tile = s.S_grid[i][j];
        if (s.isTileSet(tile, Tile::Wall)) out << '#';
        else if (s.isTileSet(tile, Tile::Crate) &&
        s.isTileSet(tile, Tile::Storage)) out << 'A';
        else if (s.isTileSet(tile, Tile::Crate)) out << 'C';
        else if (s.isTileSet(tile, Tile::Storage)) out << 'a';
        else if (s.isTileSet(tile, Tile::Player)) out << '@';
        else if (s.isTileSet(tile, Tile::Ground)) out << '.';
        else
        out << ' ';
    }
    out << '\n';
}
return out;
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
in >> s.S_height >> s.S_width;
s.S_grid.resize(s.S_height, std::vector<Tile>(s.S_width, Tile::Empty));
in.ignore();

for (unsigned int i = 0; i < s.S_height; ++i) {
    for (unsigned int j = 0; j < s.S_width; ++j) {
        char c;
        in.get(c);
        switch (c) {
            case '#': s.S_grid[i][j] = Tile::Wall; break;
            case '.': s.S_grid[i][j] = Tile::Ground; break;
            case 'a': s.S_grid[i][j] = Tile::Storage; break;
            case 'A': s.S_grid[i][j] = static_cast<Tile>(
                static_cast<int>(Tile::Crate) | static_cast<int>(Tile::Storage)); break;
            case '@': s.S_grid[i][j] = Tile::Player; s.S_playerLocation = { j, i }; break;
            default: s.S_grid[i][j] = Tile::Empty; break;
        }
    }
    in.ignore();
}
return in;
}
void SB::Sokoban::movePlayer(SB::Direction) {}
bool SB::Sokoban::isWon() const { return false; }
void SB::Sokoban::reset() {}
}  // namespace SB


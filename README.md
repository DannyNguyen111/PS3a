# PS3a
Sokoban

This project implements the classic Sokoban game in C++ using SFML for graphics and input. The game board is represented using a bitflag-based Tile enum system, efficiently encoding walls, boxes, storage locations, and the player’s position within each grid cell. Levels are loaded from text files, and rendering dynamically uses sprite images loaded from the sokoban subdirectory, matching tile types and player position according to the level file. The program supports resetting the level and processes real-time keyboard input scaffolding to enable future player movement implementation. Unit tests are set up to validate game state loading and basic tile handling, laying a solid foundation for further game logic development.


<img width="771" height="549" alt="screenshot" src="https://github.com/user-attachments/assets/1cb4e93a-4ff4-4d83-ad5b-a8e14a15a2fb" />

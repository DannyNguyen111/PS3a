# PS3a
Sokoban

This project implements the classic Sokoban game in C++ using SFML for graphics and input. The game board uses a bitflag-based Tile enum system to represent walls, boxes, storage locations, and the player’s position in each grid cell. Levels are loaded from text files, and rendering dynamically uses sprite images from the sokoban subdirectory, matching tile types and player orientation per the level data. The program tracks the number of player moves and elapsed time, providing basic gameplay metrics displayed during play. The framework supports level resetting and real-time keyboard input scaffolding to build upon. Unit tests verify correct level loading and tile representation, establishing a foundation for expanding gameplay mechanics.


<img width="771" height="549" alt="screenshot" src="https://github.com/user-attachments/assets/1cb4e93a-4ff4-4d83-ad5b-a8e14a15a2fb" />

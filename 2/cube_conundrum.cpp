#include <algorithm>
#include <iostream>
#include <inttypes.h>
#include <vector>
#include <fstream>

using namespace std;

enum class Color {
  RED,
  GREEN,
  BLUE
};

struct CubeSet {
  size_t count;
  Color color;
};

typedef vector<CubeSet> Revealed;

struct Game {
  vector<Revealed> revealed;
  uint8_t id;
};

Game parseGame(const string game);
Revealed parseRevealed(const string revealed);
CubeSet parseCube(const string cube);


int main (int argc, char *argv[]) {
  ifstream file("./input.txt");

  string buf;
  while (std::getline(file, buf)) {
    if (buf.length() == 0) continue;
    Game game = parseGame(buf);
    std::cout << "Game: " << std::to_string(game.id) << std::endl;
  }
  return 0;
}


Game parseGame(const string game) {
  auto begin = std::find(game.begin(), game.end(), ':');
  auto end = game.end();

  Game new_game;

  new_game.id = (uint8_t)std::stoi(game.substr(game.find(' '), game.find(':'))); // Here the beging value could be used

  while (begin < end) {
    auto idx = std::find(begin, end, ';');

    string revealed(begin, idx);
    new_game.revealed.emplace_back(parseRevealed(revealed));
    begin = ++idx;
  }

  return new_game;
}

Revealed parseRevealed(const string revealed) {
  auto begin = revealed.begin();
  auto end = revealed.end();

  Revealed revs;

  while (begin < end) {
    auto idx = std::find(begin, end, ',');

    string cube_set(begin, idx);
    revs.emplace_back(parseCube(cube_set));
    begin = ++idx;
  }
  return revs;
}

CubeSet parseCube(const string cube) {
  if (cube.length() == 0) return CubeSet { .count = 0, .color = Color::RED };

  uint8_t num = (uint8_t)std::stoi(cube.substr(1, cube.find(' ', 2)));
  string color_str = cube.substr(cube.find(' ', 2), cube.length());

  Color color;

  switch (color_str[1]) {
    case 'r': color = Color::RED; break;
    case 'g': color = Color::GREEN; break;
    case 'b': color = Color::BLUE; break;
    default: std::cout << "What da heeeeelll!" << std::endl; // TODO: Remove debug messages
  }

  return CubeSet { .count = num, .color = color};
}


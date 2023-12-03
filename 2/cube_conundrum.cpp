#include <algorithm>
#include <iostream>
#include <inttypes.h>
#include <vector>
#include <fstream>
#include <array>


#define GAME_2

using namespace std;

enum class Color {
  RED = 0,
  GREEN = 1,
  BLUE = 2
};

struct CubeSet {
  size_t count;
  Color color;
};

typedef vector<CubeSet> Revealed;

struct Game {
  uint8_t id;
  array<size_t, 3> color_pairs;
};

Game parseGame(const string game);
Revealed parseRevealed(const string revealed);
CubeSet parseCube(const string cube);


int main (int argc, char *argv[]) {
  ifstream file("./input.txt");

  string buf;

  #ifdef GAME_1
  size_t sum = 0;
  while (std::getline(file, buf)) {
    if (buf.length() == 0) continue;
    Game game = parseGame(buf);
    if (game.color_pairs[(int)Color::GREEN] <= 13 && game.color_pairs[(int)Color::RED] <= 12 && game.color_pairs[(int)Color::BLUE] <= 14) {
      sum += game.id;
    }
  }
  cout << sum << endl;
  #endif

  #ifdef GAME_2
  size_t sum = 0;
  while (std::getline(file, buf)) {
    if (buf.length() == 0) continue;
    Game game = parseGame(buf);

    sum += game.color_pairs[(int)Color::GREEN] * game.color_pairs[(int)Color::RED] * game.color_pairs[(int)Color::BLUE];
  }
  cout << sum << endl;
  #endif
  return 0;
}


Game parseGame(const string game) {
  auto begin = std::find(game.begin(), game.end(), ':');
  auto end = game.end();

  Game new_game;

  new_game.id = (uint8_t)std::stoi(game.substr(game.find(' '), game.find(':'))); // Here the beging value could be used

  array<size_t, 3> color_sum = {};
  while (begin < end) {
    auto idx = std::find(begin, end, ';');

    string revealed(begin, idx);
    Revealed parsed = parseRevealed(revealed);
    for (CubeSet set : parsed) {
      color_sum[(size_t)set.color] = std::max(color_sum[(size_t)set.color], set.count);
    }
    begin = ++idx;
  }
  new_game.color_pairs = color_sum;

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


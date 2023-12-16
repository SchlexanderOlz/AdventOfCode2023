#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <execution>


using namespace std;

struct Node {
  string name;
  Node *left;
  Node *right;
  Node(string name) : name(name), left(nullptr), right(nullptr) {}
};

int main (int argc, char *argv[]) {
  ifstream file("./input.txt");

  string buf;
  std::getline(file, buf);
  string directions = buf;

  vector<Node> nodes;
  nodes.reserve(1000);


  vector<Node*> entry_points;

  while (std::getline(file, buf)) {
    if (buf.size() == 0) continue;

    int eq_pos = buf.find('=');
    string name = buf.substr(0, 3);

    int op_pos = buf.find('(');
    int cl_pos = buf.find(')');

    string lables = buf.substr(op_pos + 1, 8); // Dont hardcode this

    int delimiter = lables.find(',');
    const string left = lables.substr(0, 3);
    const string right = lables.substr(delimiter + 2, 3);
    
    Node *new_node = nullptr;

    for (Node& node : nodes) {
        if (node.name == name) {
            new_node = &node;
            break;
        }
    }

    if (new_node == nullptr) {
        nodes.emplace_back(Node(name));
        new_node = &nodes.back();
    }

    if (name[2] == 'A') entry_points.push_back(new_node);

    if (new_node->left != nullptr && new_node->right != nullptr) continue;

    for (Node& node : nodes) {
      if (node.name == left) new_node->left = &node;
    }

    if (new_node->left == nullptr) {
      nodes.emplace_back(Node(left));
      new_node->left = &nodes.back();
    }

    for (Node& node : nodes) {
      if (node.name == right) new_node->right = &node;
    }

    if (new_node->right == nullptr) {
      nodes.emplace_back(Node(right));
      new_node->right = &nodes.back();
    }
  }

  vector<size_t> increment;

  const size_t length = directions.size();
  std::for_each(entry_points.begin(), entry_points.end(), [length, &directions, &increment](Node* entry_point){
    Node* last_node = entry_point;

    size_t pos = 0;
    while (last_node->name[2] != 'Z') {
      const char direction = directions[pos % length];
      if (direction == 'L') {
        last_node = last_node->left;
      }

      if (direction == 'R') {
        last_node = last_node->right;
      }
      ++pos;
    }
    increment.push_back(pos);
  });

  size_t sum = 0;
  for (size_t pos : increment) {
    std::cout << "It took: " << pos << " iterations" << std::endl;
    if (sum == 0) {
      sum = pos;
    } else {
      sum = lcm(sum, pos);
    }
  }

  std::cout << "It took: " << sum << " iterations" << std::endl;

  return 0;
}



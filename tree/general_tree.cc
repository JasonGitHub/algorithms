#include <iostream>
#include <vector>

using namespace std;

struct BNode {
  int val;
  BNode* left_child;
  BNode* right_sibling;
};

struct GNode {
  int val;
  vector<GNode*> children;
};

string Serialize(GNode* tree) {
}

GNode* Deserialize(string tree) {
}

BNode* ToBinaryTree(GNode* tree) {
}

int main() {
  string tree;
  cin >> tree;
  cout << serialize(deserialize(tree)) << endl;
  return 0;
}

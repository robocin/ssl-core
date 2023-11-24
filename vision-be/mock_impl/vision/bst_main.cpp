#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

// Estrutura para representar um nó da árvore AVL
struct Node {
  int key;     // Valor do nó
  Node* left;  // Ponteiro para o filho da esquerda
  Node* right; // Ponteiro para o filho da direita
  int height;  // Altura do nó na árvore

  // Construtor para criar um novo nó com a chave dada
  Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Classe que representa a árvore AVL
class AVLTree {
 private:
  Node* root; // Raiz da árvore

  // Função auxiliar para obter a altura de um nó
  int height(Node* node) {
    if (!node)
      return 0;
    return node->height;
  }

  // Função auxiliar para calcular o fator de balanceamento de um nó
  int balanceFactor(Node* node) {
    if (!node)
      return 0;
    return height(node->right) - height(node->left);
  }

  // Função auxiliar para atualizar a altura de um nó
  void updateHeight(Node* node) {
    // if (node) {
    node->height = 1 + max(height(node->left), height(node->right));
    // }
  }

  // Função auxiliar para realizar a rotação para a direita
  Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  // Função auxiliar para realizar a rotação para a esquerda
  Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  // Função auxiliar para equilibrar um nó após uma inserção ou remoção
  Node* balance(int key, Node* node) {
    if (!node)
      return nullptr;

    updateHeight(node);

    int balanceFactor = this->balanceFactor(node);

    if (balanceFactor > 1) {
      if (key < node->right->key)
        node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    if (balanceFactor < -1) {
      if (key >= node->left->key)
        node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    return node;
  }

  // Função auxiliar para inserir um elemento na árvore
  Node* insert(Node* root, int key) {
    if (!root)
      return new Node(key);

    if (key < root->key)
      root->left = insert(root->left, key);
    else if (key > root->key)
      root->right = insert(root->right, key);
    else
      return root; // Duplicates are not allowed

    return balance(key, root);
  }

  // Função auxiliar para encontrar o menor elemento de uma subárvore
  Node* findMin(Node* node) { // OK
    while (node->left)
      node = node->left;
    return node;
  }

  // Função auxiliar para remover um elemento da árvore
  Node* remove(Node* root, int key) {
    if (!root) {
      cout << "Valor " << key << " inexistente\n";
      return root;
    }

    if (key < root->key)
      root->left = remove(root->left, key);
    else if (key > root->key)
      root->right = remove(root->right, key);
    else {
      if (!root->left || !root->right) {
        Node* temp = root->left ? root->left : root->right;
        if (!temp) {
          temp = root;
          root = nullptr;
        } else
          *root = *temp;
        delete temp;
      } else {
        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = remove(root->right, temp->key);
      }
    }

    if (!root)
      return root;

    return balance(key, root);
  }

  // Função auxiliar para buscar o nível de um elemento na árvore
  int searchLevel(Node* root, int key, int level = 0) { // OK
    if (!root)
      return -1;

    if (key < root->key)
      return searchLevel(root->left, key, level + 1);
    else if (key > root->key)
      return searchLevel(root->right, key, level + 1);
    else
      return level;
  }

  // Função auxiliar para percorrer a árvore em ordem e imprimir os elementos
  void inorderTraversal(Node* root) { // OK
    if (root) {
      inorderTraversal(root->left);
      cout << root->key << ",";
      inorderTraversal(root->right);
    }
  }

  // Função auxiliar para percorrer a árvore em pré-ordem e imprimir os elementos
  void preorderTraversal(Node* root) { // OK
    if (root) {
      cout << root->key << ",";
      preorderTraversal(root->left);
      preorderTraversal(root->right);
    }
  }

  // Função auxiliar para percorrer a árvore em pós-ordem e imprimir os elementos
  void postorderTraversal(Node* root) { // OK
    if (root) {
      postorderTraversal(root->left);
      postorderTraversal(root->right);
      cout << root->key << ",";
    }
  }

 public:
  AVLTree() : root(nullptr) {}

  // Função para executar os comandos fornecidos pela entrada
  void executeCommand(const string& command) {
    string op;
    int arg;
    istringstream iss(command);
    iss >> op;
    // cout << op << "\n";
    if (op == "ADICIONA") {
      iss >> arg;
      root = insert(root, arg);
    } else if (op == "REMOVE") {
      iss >> arg;
      root = remove(root, arg);
    } else if (op == "NIVEL") {
      iss >> arg;
      int level = searchLevel(root, arg);
      // cout << "level: " << level << "n";
      if (level == -1)
        cout << "Valor " << arg << " inexistente\n";
      else
        cout << "Nivel de " << arg << ": " << level << "\n";
    } else if (op == "PRINT") {
      iss >> op;
      if (op == "EMORDEM") {
        cout << "[";
        inorderTraversal(root);
        cout << "]\n";
      } else if (op == "PREORDEM") {
        cout << "[";
        preorderTraversal(root);
        cout << "]\n";
      } else if (op == "POSORDEM") {
        cout << "[";
        postorderTraversal(root);
        cout << "]\n";
      }
    }
  }
};

// Função principal
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  AVLTree avl;

  string command;
  while (getline(cin, command)) {
    if (command == "FIM")
      break;
    avl.executeCommand(command);
  }

  return 0;
}

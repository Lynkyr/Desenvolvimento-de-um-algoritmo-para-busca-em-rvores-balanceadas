#include <iostream>
#include <algorithm> // Para a função max()

using namespace std;

// 1. Estrutura do Nó da Árvore
struct Node {
    int key;
    Node *left;
    Node *right;
    int height; // Altura necessária para verificar o balanceamento
};

// --- Funções Utilitárias ---

// Função para obter a altura de um nó (trata NULL como 0)
int getHeight(Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Novo nó é adicionado na folha
    return(node);
}

// Obter o fator de balanceamento do nó
int getBalance(Node *n) {
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// --- Rotações para Balanceamento ---

// Rotação à Direita (Simples)
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Retorna nova raiz
    return x;
}

// Rotação à Esquerda (Simples)
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Retorna nova raiz
    return y;
}

// --- Inserção com Balanceamento Automático ---

Node* insert(Node* node, int key) {
    // 1. Inserção normal de BST
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas
        return node;

    // 2. Atualiza a altura deste nó ancestral
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Obtém o fator de balanceamento para verificar se ficou desbalanceado
    int balance = getBalance(node);

    // Se o nó ficar desbalanceado, temos 4 casos:

    // Caso 1: Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso 2: Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso 3: Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retorna o ponteiro do nó (sem alterações)
    return node;
}

// --- O ALGORITMO DE BUSCA (O Foco do seu pedido) ---

// Complexidade: O(log n)
Node* search(Node* root, int key) {
    // Caso base: raiz é nula ou a chave está na raiz
    if (root == NULL || root->key == key)
        return root;

    // Se a chave for maior que a raiz, busca na direita
    if (root->key < key)
        return search(root->right, key);

    // Se a chave for menor que a raiz, busca na esquerda
    return search(root->left, key);
}

// Função auxiliar para imprimir a árvore (Pre-Order)
void preOrder(Node *root) {
    if (root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// --- Função Principal ---
int main() {
    Node *root = NULL;

    // Inserindo dados para criar a árvore
    // Note que mesmo inserindo em ordem (10, 20, 30...), a AVL vai balancear.
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* A árvore construída será:
            30
           /  \
         20   40
        /  \    \
      10   25   50
    */

    cout << "Travessia Pre-Order da árvore balanceada AVL:\n";
    preOrder(root);
    cout << endl;

    // Testando a Busca
    int valorBusca = 25;
    cout << "\nProcurando pelo valor " << valorBusca << "..." << endl;
    
    Node* resultado = search(root, valorBusca);

    if (resultado != NULL)
        cout << "Sucesso! Valor " << resultado->key << " encontrado na árvore." << endl;
    else
        cout << "Valor não encontrado." << endl;

    return 0;
}

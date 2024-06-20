#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>

class Obat {
public:
    int id;
    std::string nama;
    double harga;
    int stok;

    Obat(int id, std::string nama, double harga, int stok);
};

class BSTNode {
public:
    Obat data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Obat data);
};

class BST {
private:
    BSTNode* root;
    BSTNode* insert(BSTNode* node, Obat data);
    BSTNode* search(BSTNode* node, const std::string& nama);
    void inOrderTraversal(BSTNode* node);
    void inOrderTraversal(BSTNode* node, std::vector<Obat>& obatList);

public:
    BST();
    void insert(Obat data);
    Obat* search(const std::string& nama);
    std::vector<Obat> toArray();
    void inOrderTraversal();
};

#endif

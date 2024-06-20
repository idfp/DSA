#include "data.h"
#include <iostream>

Obat::Obat(int id, std::string nama, double harga, int stok) 
    : id(id), nama(nama), harga(harga), stok(stok) {}

BSTNode::BSTNode(Obat data) : data(data), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr) {}

BSTNode* BST::insert(BSTNode* node, Obat data) {
    if (node == nullptr) {
        return new BSTNode(data);
    }

    if (data.nama < node->data.nama) {
        node->left = insert(node->left, data);
    } else if (data.nama > node->data.nama) {
        node->right = insert(node->right, data);
    }
    
    return node;
}

void BST::insert(Obat data) {
    root = insert(root, data);
}

BSTNode* BST::search(BSTNode* node, const std::string& nama) {
    if (node == nullptr || node->data.nama == nama) {
        return node;
    }

    if (nama < node->data.nama) {
        return search(node->left, nama);
    } else {
        return search(node->right, nama);
    }
}

Obat* BST::search(const std::string& nama) {
    BSTNode* result = search(root, nama);
    if (result != nullptr) {
        return &(result->data);
    }
    return nullptr;
}

void BST::inOrderTraversal(BSTNode* node) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left);
    std::cout << "ID: " << node->data.id << ", Nama: " << node->data.nama 
              << ", Harga: " << node->data.harga << ", Stok: " << node->data.stok << std::endl;
    inOrderTraversal(node->right);
}

void BST::inOrderTraversal() {
    inOrderTraversal(root);
}

void BST::inOrderTraversal(BSTNode* node, std::vector<Obat>& obatList) {
    if (node == nullptr) {
        return;
    }

    inOrderTraversal(node->left, obatList);
    obatList.push_back(node->data);
    inOrderTraversal(node->right, obatList);
}

std::vector<Obat> BST::toArray() {
    std::vector<Obat> obatList;
    inOrderTraversal(root, obatList);
    return obatList;
}

#include "data.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <queue>

Obat::Obat(int id, std::string nama, double harga, int stok)
    : id(id), nama(nama), harga(harga), stok(stok) {}

Obat::Obat()
    : id(0), nama(""), harga(0), stok(0) {}

BSTNode::BSTNode(Obat data) : data(data), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr) {}

BSTNode *BST::insert(BSTNode *node, Obat data)
{
    if (node == nullptr)
    {
        return new BSTNode(data);
    }

    if (data.nama < node->data.nama)
    {
        node->left = insert(node->left, data);
    }
    else if (data.nama > node->data.nama)
    {
        node->right = insert(node->right, data);
    }

    return node;
}

void BST::insert(Obat data)
{
    root = insert(root, data);
}

BSTNode *BST::search(BSTNode *node, const std::string &nama)
{
    if (node == nullptr || node->data.nama == nama)
    {
        return node;
    }

    if (nama < node->data.nama)
    {
        return search(node->left, nama);
    }
    else
    {
        return search(node->right, nama);
    }
}

Obat *BST::search(const std::string &nama)
{
    BSTNode *result = search(root, nama);
    if (result != nullptr)
    {
        return &(result->data);
    }
    return nullptr;
}

void BST::inOrderTraversal(BSTNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    inOrderTraversal(node->left);
    std::cout << "ID: " << node->data.id << ", Nama: " << node->data.nama
              << ", Harga: " << node->data.harga << ", Stok: " << node->data.stok << std::endl;
    inOrderTraversal(node->right);
}

void BST::inOrderTraversal()
{
    inOrderTraversal(root);
}

void BST::inOrderTraversal(BSTNode *node, std::vector<Obat> &obatList)
{
    if (node == nullptr)
    {
        return;
    }

    inOrderTraversal(node->left, obatList);
    obatList.push_back(node->data);
    inOrderTraversal(node->right, obatList);
}

std::vector<Obat> BST::toArray()
{
    std::vector<Obat> obatList;
    inOrderTraversal(root, obatList);
    return obatList;
}

void OrderQueue::placeOrder(const Order &order)
{
    std::lock_guard<std::mutex> lock(mtx);
    orders.push(order);
    std::cout << "Pesanan Diterima Untuk " << order.namaPembeli << ", Mohon Tunggu " << std::endl;
}

void OrderQueue::processOrders()
{
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::lock_guard<std::mutex> lock(mtx);
    Order completedOrder = orders.front();
    orders.pop();
    std::cout << "Pesanan oleh " << completedOrder.namaPembeli << " telah selesai" << std::endl;
    std::cout << "Pesanan yang dibeli: ";
    double total = 0;
    for (const auto &obat : completedOrder.obat)
    {
        std::cout << obat.nama << " ";
        total = total + obat.harga;
    }
    std::cout << "\n Total: Rp." << total;
    std::cout << std::endl;
}

std::vector<Order> OrderQueue::getOrders()
{
    std::vector<Order> result;
    std::queue<Order> temporder = orders;
    for (size_t i = 0; i < orders.size(); ++i)
    {
        result.push_back(temporder.front());
        temporder.pop();
    }
    return result;
}

Order::Order(std::vector<Obat> obat, std::string namaPembeli) : obat(obat), namaPembeli(namaPembeli) {}

Pharmacy::Pharmacy(std::string name, std::string address) : name(name), address(address) {}
Pharmacy::Pharmacy() : name(""), address("") {}

Edge::Edge(int to, double distance, Direction direction) : to(to), distance(distance), direction(direction) {}
Edge::Edge() : to(0), distance(0), direction(EAST) {}

PharmacyGraph::PharmacyGraph(int numPharmacies)
{
    pharmacies.resize(numPharmacies);
    adjacencyList.resize(numPharmacies);
}

std::string PharmacyGraph::directionToString(Direction direction)
{
    switch (direction)
    {
    case NORTH:
        return "NORTH";
    case NORTHEAST:
        return "NORTHEAST";
    case EAST:
        return "EAST";
    case SOUTHEAST:
        return "SOUTHEAST";
    case SOUTH:
        return "SOUTH";
    case SOUTHWEST:
        return "SOUTHWEST";
    case WEST:
        return "WEST";
    case NORTHWEST:
        return "NORTHWEST";
    default:
        return "UNKNOWN";
    }
}

std::pair<int, int> PharmacyGraph::getDirectionOffset(Direction direction, double distance)
{
    switch (direction)
    {
    case NORTH:
        return {-1 * distance, 0 * distance};
    case NORTHEAST:
        return {-1 * distance, 1 * distance};
    case EAST:
        return {0 * distance, 1 * distance};
    case SOUTHEAST:
        return {1 * distance, 1 * distance};
    case SOUTH:
        return {1 * distance, 0 * distance};
    case SOUTHWEST:
        return {1 * distance, -1 * distance};
    case WEST:
        return {0 * distance, -1 * distance};
    case NORTHWEST:
        return {-1 * distance, -1 * distance};
    default:
        return {0, 0};
    }
}

void PharmacyGraph::printGrid(const std::vector<std::vector<char>> &grid)
{
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            std::cout << cell;
        }
        std::cout << "\n";
    }
}

void PharmacyGraph::addPharmacy(int index, const std::string &name, const std::string &address)
{
    pharmacies[index] = Pharmacy(name, address);
}

void PharmacyGraph::addEdge(int from, int to, double distance, Direction direction)
{
    adjacencyList[from].emplace_back(to, distance, direction);
}

Pharmacy PharmacyGraph::getPharmacy(int index)
{
    return pharmacies[index];
}

std::vector<Edge> PharmacyGraph::getNeighbors(int index)
{
    return adjacencyList[index];
}

void PharmacyGraph::printGraph()
{
    for (size_t i = 0; i < pharmacies.size(); ++i)
    {
        for (const auto &edge : adjacencyList[i])
        {
            std::vector<std::string> addressSource = splitString(pharmacies[i].address, '\n');
            std::vector<std::string> addressDest = splitString(pharmacies[edge.to].address, '\n');
            std::cout << pharmacies[i].name << std::setw(57 - pharmacies[i].name.length()) << edge.distance << "km" << "           "
                      << pharmacies[edge.to].name << "\n";
            std::cout << addressSource[0] << std::setw(60 - addressSource[0].length()) << "---->" << "          "
                      << addressDest[0] << "\n";
            std::cout << std::left << std::setw(70) << addressSource[1] << addressDest[1] << "\n";
            std::cout << std::right;
            std::cout << std::endl;
        }
    }
}
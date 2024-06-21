#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>

enum Direction {
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST
};

class Obat
{
public:
    int id;
    std::string nama;
    double harga;
    int stok;

    Obat(int id, std::string nama, double harga, int stok);
    Obat();
};

class BSTNode
{
public:
    Obat data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(Obat data);
};

class BST
{
private:
    BSTNode *root;
    BSTNode *insert(BSTNode *node, Obat data);
    BSTNode *search(BSTNode *node, const std::string &nama);
    void inOrderTraversal(BSTNode *node);
    void inOrderTraversal(BSTNode *node, std::vector<Obat> &obatList);

public:
    BST();
    void insert(Obat data);
    Obat *search(const std::string &nama);
    std::vector<Obat> toArray();
    void inOrderTraversal();
};

class Order
{
public:
    std::vector<Obat> obat;
    std::string namaPembeli;
    Order(std::vector<Obat> obat, std::string namaPembeli);
};

class OrderQueue
{
private:
    std::queue<Order> orders;
    std::mutex mtx;

public:
    void placeOrder(const Order &order);
    void processOrders();
    std::vector<Order> getOrders();
};

class Pharmacy
{
public:
    std::string name;
    std::string address;
    Pharmacy(std::string name, std::string address);
    Pharmacy();
};

class Edge
{
public:
    int to;
    double distance;
    Direction direction;
    Edge(int to, double distance, Direction direction);
    Edge();
};

class PharmacyGraph
{
private:
    std::vector<Pharmacy> pharmacies;
    std::vector<std::vector<Edge>> adjacencyList;
    std::string directionToString(Direction direction);
    std::pair<int, int> getDirectionOffset(Direction direction, double distance);
    void printGrid(const std::vector<std::vector<char>>& grid);

public:
    PharmacyGraph(int numPharmacies);
    void addPharmacy(int index, const std::string& name, const std::string& address);
    void addEdge(int from, int to, double distance, Direction direction);
    Pharmacy getPharmacy(int index);
    std::vector<Edge> getNeighbors(int index);
    void printGraph();
};


#endif

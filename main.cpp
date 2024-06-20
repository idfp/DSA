#include <iostream>
#include "utils.h"
#include "data.h"
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::string> medicineNames = {
    "Paracetamol", "Aspirin", "Ibuprofen", "Amoxicillin", "Ciprofloxacin",
    "Doxycycline", "Azithromycin", "Metformin", "Atorvastatin", "Lisinopril",
    "Omeprazole", "Simvastatin", "Losartan", "Gabapentin", "Hydrochlorothiazide",
    "Levothyroxine", "Metoprolol", "Amlodipine", "Albuterol", "Furosemide",
    "Pantoprazole", "Prednisone", "Sulfamethoxazole", "Tamsulosin", "Citalopram",
    "Clopidogrel", "Meloxicam", "Propranolol", "Fluconazole", "Rosuvastatin",
    "Diclofenac", "Celecoxib", "Venlafaxine", "Warfarin", "Duloxetine",
    "Oxycodone", "Lorazepam", "Tramadol", "Esomeprazole", "Sertraline"
};

std::vector<Obat> generateDummyData() {
    std::vector<Obat> dummyData;
    for (int i = 0; i < medicineNames.size(); ++i) {
        std::string name = medicineNames[i];
        double price = (rand() % 10000) + 1000;   // Random price between 1000 and 11000
        int stock = (rand() % 200) + 1;           // Random stock between 1 and 200
        dummyData.push_back(Obat(i + 1, name, price, stock));
    }
    return dummyData;
}

int main(){
    srand(time(0));
    printHeader();
    BST tree;
    std::vector<Obat> dummyData = generateDummyData();
    for (const auto& obat : dummyData) {
        tree.insert(obat);
    }

    std::cout << "In-order traversal of the BST:" << std::endl;
    tree.inOrderTraversal();

    return 0;
}
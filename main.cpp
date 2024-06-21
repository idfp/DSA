#include <iostream>
#include "utils.h"
#include "data.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <thread>

std::vector<std::string> namaObat = {
    "Paracetamol", "Aspirin", "Ibuprofen", "Amoxicillin", "Ciprofloxacin",
    "Doxycycline", "Azithromycin", "Metformin", "Atorvastatin", "Lisinopril",
    "Omeprazole", "Simvastatin", "Losartan", "Gabapentin", "Hydrochlorothiazide",
    "Levothyroxine", "Metoprolol", "Amlodipine", "Albuterol", "Furosemide",
    "Pantoprazole", "Prednisone", "Sulfamethoxazole", "Tamsulosin", "Citalopram",
    "Clopidogrel", "Meloxicam", "Propranolol", "Fluconazole", "Rosuvastatin",
    "Diclofenac", "Celecoxib", "Venlafaxine", "Warfarin", "Duloxetine",
    "Oxycodone", "Lorazepam", "Tramadol", "Esomeprazole", "Sertraline"};

std::vector<Obat> generateDummyData()
{
    std::vector<Obat> dummyData;
    for (int i = 0; i < namaObat.size(); ++i)
    {
        std::string nama = namaObat[i];
        double harga = (rand() % 10000) + 1000;
        int stok = (rand() % 200) + 1;
        dummyData.push_back(Obat(i + 1, nama, harga, stok));
    }
    return dummyData;
}

int main()
{
    srand(time(0));
    printHeader();
    BST tree;
    OrderQueue antreanPesanan;
    const int numPharmacies = 3;

    PharmacyGraph graph(numPharmacies);
    graph.addPharmacy(0, "Permadicare Pondok Labu", "Jl. RS. Fatmawati Raya No.15, RT.2/RW.1,\nPd. Labu, Kota Jakarta Selatan Jakarta 12430");
    graph.addPharmacy(1, "Permadicare Limo", "Jl. Limo Raya No.7, RT.2/RW.5,\nLimo, Kota Depok, Jawa Barat 16514");
    graph.addPharmacy(2, "Permadicare Cipedak", "Jl. Aselih, RT.12/RW.1,\nCipedak, Kec. Jagakarsa, Jakarta 12630");

    graph.addEdge(0, 1, 5, SOUTHWEST);
    graph.addEdge(0, 2, 4, SOUTH); 
    graph.addEdge(1, 2, 3, EAST);

    std::vector<Obat> dummyData = generateDummyData();
    for (const auto &obat : dummyData)
    {
        tree.insert(obat);
    }
    while (true)
    {
        std::string tempinput;
        printMenu();
        std::getline(std::cin, tempinput);
        int input = std::atoi(tempinput.c_str());
        switch (input)
        {
        case 1:
        {
            std::vector<Obat> listobat = tree.toArray();
            std::string sortbyN;

            std::cout << "Sortir Obat berdasar (id, nama, harga, stok):";
            std::getline(std::cin, sortbyN);
            std::string sortby = toLowercase(sortbyN);

            if (sortby == "id")
            {
                countingSortObat(listobat, "id");
            }
            else if (sortby == "stok")
            {
                countingSortObat(listobat, "stok");
            }
            else if (sortby == "harga")
            {
                countingSortObat(listobat, "harga");
            }

            printObatTable(listobat);
            break;
        }
        case 2:
        {
            std::string keyword;
            std::cout << "Masukkan kata kunci pencarian: ";
            std::getline(std::cin, keyword);
            keyword[0] = std::toupper(keyword[0]);
            Obat *obat = tree.search(keyword);
            if (obat != nullptr)
            {
                std::cout << "\nObat " << keyword << " Ditemukan : \n"
                          << " \033[1;36mID: \033[0m" << obat->id
                          << "\n \033[1;36mHarga: \033[0mRp." << obat->harga
                          << "\n \033[1;36mStok: \033[0m" << obat->stok << std::endl;
            }
            else
            {
                std::cout << "\n Obat "
                          << keyword << " tidak ditemukan." << std::endl;
            }
            break;
        }
        case 3:
        {
            std::string namaPembeli;
            std::string idObat;

            std::cout << "Masukkan nama anda: ";
            std::getline(std::cin, namaPembeli);

            std::cout << "Masukkan ID obat yang dibeli (pisahkan dengan koma apabila lebih dari 1): ";
            std::getline(std::cin, idObat);
            std::vector<Obat> listobatobj;
            std::vector<std::string> listobat = splitString(idObat, ',');
            for (const auto &idobat : listobat)
            {
                int id = std::atoi(idobat.c_str());
                std::string nama = namaObat[id - 1];
                Obat *obat = tree.search(nama);
                if (obat != nullptr)
                {
                    listobatobj.push_back(*obat);
                }
            }
            Order order = Order(listobatobj, namaPembeli);
            antreanPesanan.placeOrder(order);
            std::thread asyncThread(&OrderQueue::processOrders, &antreanPesanan);
            asyncThread.detach();

            break;
        }
        case 4:
        {
            std::vector<Order> listpesanan = antreanPesanan.getOrders();
            std::cout << "Pesanan obat: \n";
            for (const auto &pesanan : listpesanan)
            {
                std::cout << "Oleh " << pesanan.namaPembeli << ", membeli: ";
                double total = 0;
                for (const auto &obat : pesanan.obat)
                {
                    std::cout << obat.nama << " ";
                    total = total + obat.harga;
                }
                std::cout << ", Total: Rp." << total << "\n";
            }
            break;
        }
        case 5:
        {
            graph.printGraph();
            break;
        }
        case 6:
            exit(0);
        default:
        {
            std::cout << "Masukkan input yang sesuai!" << std::endl;
        }
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
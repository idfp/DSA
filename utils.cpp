#include <iostream>
#include <vector>
#include "utils.h"
#include "data.h"
#include <iomanip>
#include <cctype>
#include <sstream>
#include <string>

void printHeader()
{
    std::cout << "\033[1;34m __   ___  __              __     __        __   ___ " << std::endl;
    std::cout << "|__) |__  |__)  |\\/|  /\\  |  \\ | /  `  /\\  |__) |__  " << std::endl;
    std::cout << "|    |___ |  \\  |  | /--\\ |__/ | \\__, /--\\ |  \\ |___ \n" << std::endl;
    std::cout << "v0.1 Kelompok 7 S1 Sistem Informasi UPN Veteran Jakarta\033[0m" << std::endl;
}

void printMenu()
{
    std::cout << "Pilih aksi yang akan dilakukan:" << std::endl;
    std::cout << "1. Tampilkan Obat" << std::endl;
    std::cout << "2. Cari Obat" << std::endl;
    std::cout << "3. Buat Pesanan Obat" << std::endl;
    std::cout << "4. Lihat Antrean" << std::endl;
    std::cout << "5. Tampilkan Lokasi Apotek Cabang" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "> ";
}

void printObatTable(const std::vector<Obat>& obatArray) {
    std::cout << std::left << std::setw(17) << "\033[1;35mID" 
              << std::setw(20) << "Nama" 
              << std::setw(10) << "Harga" 
              << std::setw(5) << "Stok" << std::endl;
    std::cout << "----------------------------------------------\033[0m" << std::endl;

    for (const auto& obat : obatArray) {
        std::cout << std::left << std::setw(10) << obat.id
                  << std::setw(20) << obat.nama
                  << std::setw(10) << obat.harga
                  << std::setw(5) << obat.stok << std::endl;
    }
}

void countingSortObat(std::vector<Obat>& arr, const std::string& sortBy) {
    if (sortBy == "id") {
        
        int maxId = 0;
        for (const auto& obat : arr) {
            if (obat.id > maxId) {
                maxId = obat.id;
            }
        }

        std::vector<int> count(maxId + 1, 0);
        std::vector<Obat> output(arr.size());

        for (const auto& obat : arr) {
            count[obat.id]++;
        }

        for (int i = 1; i <= maxId; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i].id] - 1] = arr[i];
            count[arr[i].id]--;
        }

        arr = output;
    } else if (sortBy == "nama") {
        
        int n = arr.size();
        std::vector<Obat> output(n);
        int maxLen = 0;

        for (const auto& obat : arr) {
            if (obat.nama.length() > maxLen) {
                maxLen = obat.nama.length();
            }
        }

        for (int exp = maxLen - 1; exp >= 0; --exp) {
            std::vector<int> count(256, 0);

            for (const auto& obat : arr) {
                int index = (exp < obat.nama.length()) ? obat.nama[exp] : 0;
                count[index]++;
            }

            for (int i = 1; i < 256; ++i) {
                count[i] += count[i - 1];
            }

            for (int i = n - 1; i >= 0; --i) {
                int index = (exp < arr[i].nama.length()) ? arr[i].nama[exp] : 0;
                output[count[index] - 1] = arr[i];
                count[index]--;
            }

            arr = output;
        }
    } else if (sortBy == "harga") {
        int n = arr.size();
        const int range = 11001; 
        std::vector<std::vector<Obat>> buckets(range);

        for (const auto& obat : arr) {
            int bucketIndex = static_cast<int>(obat.harga);
            buckets[bucketIndex].push_back(obat);
        }

        arr.clear();
        for (auto& bucket : buckets) {
            for (auto& obat : bucket) {
                arr.push_back(obat);
            }
        }
    } else if (sortBy == "stok") {
        int maxStok = 0;
        for (const auto& obat : arr) {
            if (obat.stok > maxStok) {
                maxStok = obat.stok;
            }
        }

        std::vector<int> count(maxStok + 1, 0);
        std::vector<Obat> output(arr.size());

        for (const auto& obat : arr) {
            count[obat.stok]++;
        }

        for (int i = 1; i <= maxStok; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i].stok] - 1] = arr[i];
            count[arr[i].stok]--;
        }

        arr = output;
    } else {
        std::cerr << "Invalid sortBy parameter" << std::endl;
    }
}

std::string toLowercase(const std::string& input) {
    std::string result = input;

    for (char& c : result) {
        c = std::tolower(c);
    }

    return result;
}

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


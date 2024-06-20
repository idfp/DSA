#include <iostream>
#include "utils.h"

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
    std::cout << "4. Lihat Keranjang" << std::endl;
}
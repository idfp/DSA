#ifndef UTILS_H
#define UTILS_H
#include "data.h"
#include <vector>

void printHeader();
void printMenu();
void printObatTable(const std::vector<Obat>& obatArray);
void countingSortObat(std::vector<Obat>& arr, const std::string& sortBy);
std::string toLowercase(const std::string& input);
std::vector<std::string> splitString(const std::string& input, char delimiter);

#endif

#pragma once
#include <string>
#include <vector>

class RouteCipher {
private:
    int key; // количество столбцов

public:
    RouteCipher() = delete;
    RouteCipher(int k);
    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};

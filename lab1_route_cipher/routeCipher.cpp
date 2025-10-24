#include "routeCipher.h"
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

RouteCipher::RouteCipher(int k) {
    if (k <= 0) {
        throw invalid_argument("Ключ должен быть положительным числом");
    }
    key = k;
}

string RouteCipher::encrypt(const string& text) {
    if (text.empty()) {
        throw invalid_argument("Текст не может быть пустым");
    }

    int rows = (text.length() + key - 1) / key;
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу слева направо, сверху вниз
    for (int i = 0; i < text.length(); i++) {
        int row = i / key;
        int col = i % key;
        table[row][col] = text[i];
    }

    // Читаем сверху вниз, справа налево (ТОЛЬКО ЗАНЯТЫЕ ЯЧЕЙКИ)
    string result;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            // Добавляем только если ячейка не пустая (не пробел)
            if (table[row][col] != ' ') {
                result += table[row][col];
            }
        }
    }
    return result;
}

string RouteCipher::decrypt(const string& text) {
    if (text.empty()) {
        throw invalid_argument("Текст не может быть пустым");
    }

    int rows = (text.length() + key - 1) / key;
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    // Заполняем таблицу сверху вниз, справа налево
    int index = 0;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (index < text.length()) {
                table[row][col] = text[index++];
            }
        }
    }

    // Читаем слева направо, сверху вниз (ТОЛЬКО ЗАНЯТЫЕ ЯЧЕЙКИ)
    string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            // Добавляем только если ячейка не пустая (не пробел)
            if (table[row][col] != ' ') {
                result += table[row][col];
            }
        }
    }
    
    return result;
}

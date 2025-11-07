#include "routeCipher.h"
#include <vector>
#include <string>
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

    // Читаем по спирали: сверху вниз, справа налево
    string result;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            // Проверяем, что позиция была заполнена при записи
            if (row * key + col < text.length()) {
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

    // Заполняем таблицу по спирали: сверху вниз, справа налево
    int index = 0;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            // Заполняем только те ячейки, которые были заполнены при шифровании
            if (row * key + col < text.length()) {
                if (index < text.length()) {
                    table[row][col] = text[index++];
                }
            }
        }
    }

    // Читаем слева направо, сверху вниз
    string result;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            if (row * key + col < text.length()) {
                result += table[row][col];
            }
        }
    }

    return result;
}

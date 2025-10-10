#include <iostream>
#include <vector>
#include <string>

using namespace std;

string encrypt(const string& text, int key) {
    int rows = (text.length() + key - 1) / key;
    vector<vector<char>> table(rows, vector<char>(key, ' '));
    
    cout << "Encrypt: text='" << text << "', key=" << key << ", rows=" << rows << endl;
    
    // Запись
    int index = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            if (index < text.length()) {
                table[row][col] = text[index++];
                cout << "Write '" << table[row][col] << "' to [" << row << "][" << col << "]" << endl;
            }
        }
    }
    
    // Чтение
    string result;
    for (int col = key - 1; col >= 0; col--) {
        for (int row = 0; row < rows; row++) {
            if (table[row][col] != ' ') {
                result += table[row][col];
                cout << "Read '" << table[row][col] << "' from [" << row << "][" << col << "]" << endl;
            }
        }
    }
    
    cout << "Result: '" << result << "'" << endl;
    return result;
}

int main() {
    cout << "=== DEBUG ===" << endl;
    encrypt("ABC", 2);
    return 0;
}

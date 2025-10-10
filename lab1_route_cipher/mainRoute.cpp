#include <iostream>
#include "routeCipher.h"

using namespace std;

void testCipher(const string& text, int key_value) {
    try {
        RouteCipher cipher(key_value);

        string encrypted = cipher.encrypt(text);
        string decrypted = cipher.decrypt(encrypted);

        cout << "=== ТЕСТ ===" << endl;
        cout << "Ключ (столбцов): " << key_value << endl;
        cout << "Исходный текст: " << text << endl;
        cout << "Зашифрованный: " << encrypted << endl;
        cout << "Расшифрованный: " << decrypted << endl;

        if (text == decrypted) {
            cout << "✓ ТЕСТ ПРОЙДЕН УСПЕШНО!" << endl;
        } else {
            cout << "✗ ОШИБКА В РАБОТЕ ШИФРАТОРА!" << endl;
        }
        cout << "---" << endl;

    } catch (const exception& e) {
        cout << "ОШИБКА: " << e.what() << endl;
        cout << "---" << endl;
    }
}

int main() {
    cout << "=== ШИФР ТАБЛИЧНОЙ МАРШРУТНОЙ ПЕРЕСТАНОВКИ ===" << endl;
    cout << "Тестирование алгоритма" << endl;
    cout << endl;
    
    testCipher("HELLOWORLD", 3);
    testCipher("PROGRAMMING", 4);
    testCipher("CRYPTOGRAPHY", 5);
    testCipher("COMPUTER", 2);
    testCipher("TEST", 3);
    testCipher("A", 1);
    testCipher("ALGORITHM", 3);
    testCipher("SECURITY", 4);
    
    // Тесты с ошибками
    testCipher("TEST", 0);
    testCipher("", 3);
    
    return 0;
}

#include <iostream>
#include <locale>
#include <codecvt>
#include "modAlphaCipher.h"

// Функция проверки валидности текста (русские буквы и пробелы)
bool isValid(const std::wstring& s) {
    for(auto c : s) {
        if (!iswalpha(c) && c != L' ')  // если не буква и не пробел
            return false;
    }
    return true;
}

int main() {
    // Настройка локали для русского языка
    std::locale::global(std::locale(""));
    std::wstring key;
    std::wstring text;
    int operation;
    
    std::wcout << L"=== ШИФРАТОР ГРОНСФЕЛЬДА ===" << std::endl;
    std::wcout << L"Теперь поддерживаются пробелы между словами!" << std::endl;
    
    // Запрос ключа
    std::wcout << L"Введите ключ (только русские буквы): ";
    std::wcin >> key;
    if (!isValid(key) || key.find(L' ') != std::wstring::npos) {
        std::wcout << L"Ошибка: ключ должен содержать только буквы без пробелов!" << std::endl;
        return 1;
    }

    // Создаем шифратор с введенным ключом
    modAlphaCipher cipher(key);
    std::wcout << L"Ключ установлен успешно!" << std::endl;
    
    // Главный цикл программы
    do {
        std::wcout << L"\nВыберите операцию:" << std::endl;
        std::wcout << L"0 - Выход" << std::endl;
        std::wcout << L"1 - Зашифровать" << std::endl;
        std::wcout << L"2 - Расшифровать" << std::endl;
        std::wcout << L"Ваш выбор: ";
        std::wcin >> operation;
        
        // Очищаем буфер после чтения числа
        std::wcin.ignore();
        
        if (operation == 0) {
            std::wcout << L"Выход из программы..." << std::endl;
            break;
        }
        else if (operation == 1 || operation == 2) {
            std::wcout << L"Введите текст: ";
            std::getline(std::wcin, text); // Читаем всю строку с пробелами
            
            if (!isValid(text)) {
                std::wcout << L"Ошибка: текст должен содержать только русские буквы и пробелы!" << std::endl;
                continue;
            }
            
            if (operation == 1) {
                // Шифрование
                std::wstring encrypted = cipher.encrypt(text);
                std::wcout << L"Зашифрованный текст: " << encrypted << std::endl;
            }
            else {
                // Расшифрование
                std::wstring decrypted = cipher.decrypt(text);
                std::wcout << L"Расшифрованный текст: " << decrypted << std::endl;
            }
        }
        else {
            std::wcout << L"Ошибка: неверная операция!" << std::endl;
        }

    } while (operation != 0);
    return 0;
}

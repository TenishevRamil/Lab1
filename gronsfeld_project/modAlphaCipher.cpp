#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <vector>

std::locale loc("ru_RU.UTF-8");

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    for (size_t i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(skey);
}

void modAlphaCipher::find_space_positions(const std::wstring& text)
{
    space_positions.clear();
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == L' ') {
            space_positions.push_back(i);
        }
    }
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    // Сохраняем позиции пробелов
    find_space_positions(open_text);
    
    // Убираем пробелы для шифрования
    std::wstring text_without_spaces;
    for (wchar_t c : open_text) {
        if (c != L' ') {
            text_without_spaces += c;
        }
    }
    
    std::vector<int> work = convert(text_without_spaces);
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    
    return convert(work); // Возвращаем без пробелов
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    // Дешифруем текст без пробелов
    std::vector<int> work = convert(cipher_text);
    
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    
    std::wstring decrypted_without_spaces = convert(work);
    
    // Восстанавливаем пробелы на сохраненные позиции
    std::wstring result;
    size_t text_index = 0;
    size_t space_index = 0;
    
    for (size_t i = 0; i < decrypted_without_spaces.length() + space_positions.size(); i++) {
        if (space_index < space_positions.size() && i == space_positions[space_index]) {
            result += L' ';
            space_index++;
        } else {
            if (text_index < decrypted_without_spaces.length()) {
                result += decrypted_without_spaces[text_index];
                text_index++;
            }
        }
    }
    
    return result;
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (wchar_t c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        } else {
            result.push_back(0); // Заменяем неизвестные символы на А
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (int i : v) {
        if (i >= 0 && i < (int)numAlpha.size()) {
            result += numAlpha[i];
        } else {
            result += L'?';
        }
    }
    return result;
}

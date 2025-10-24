#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    // Добавляем пробел в алфавит как последний символ
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    
    // Убираем пробелы из ключа при создании
    std::wstring clean_key;
    for (auto c : skey) {
        if (c != L' ') {
            clean_key += c;
        }
    }
    
    if (clean_key.empty()) {
        throw std::invalid_argument("Ключ не может быть пустым");
    }
    
    key = convert(clean_key);
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    for (unsigned i = 0; i < work.size(); i++) {
        // Пропускаем пробелы при шифровании (они остаются пробелами)
        if (work[i] != numAlpha.size() - 1) {
            work[i] = (work[i] + key[i % key.size()]) % (numAlpha.size() - 1);
        }
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(cipher_text);
    for (unsigned i = 0; i < work.size(); i++) {
        // Пропускаем пробелы при дешифровании
        if (work[i] != numAlpha.size() - 1) {
            work[i] = (work[i] + (numAlpha.size() - 1) - key[i % key.size()]) % (numAlpha.size() - 1);
        }
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for (auto c : s) {
        if (alphaNum.find(c) != alphaNum.end()) {
            result.push_back(alphaNum[c]);
        } else {
            // Если символ не найден в алфавите, заменяем на пробел
            result.push_back(alphaNum[L' ']);
        }
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        if (i < numAlpha.size()) {
            result.push_back(numAlpha[i]);
        } else {
            result.push_back(L'?'); // На случай ошибки
        }
    }
    return result;
}

#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale> 

class modAlphaCipher
{
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; 
    std::map<wchar_t, int> alphaNum; 
    std::vector<int> key;
    std::vector<size_t> space_positions; // ← ДОБАВЛЯЕМ

    std::vector<int> convert(const std::wstring& s);
    std::wstring convert(const std::vector<int>& v);
    void find_space_positions(const std::wstring& text); // ← ДОБАВЛЯЕМ

public:
    modAlphaCipher() = delete;
    modAlphaCipher(const std::wstring& skey);
    
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};

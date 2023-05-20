#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string removeComments(const std::string& sourceCode) {
    std::string code = sourceCode;
    

    code = std::regex_replace(code, std::regex("//.*"), "");
    
   
    code = std::regex_replace(code, std::regex("/\\*.*?\\*/"), "");
    
    return code;
}

std::string removeStringLiterals(const std::string& sourceCode) {
    std::string code = sourceCode;
    
    // Замена строковых литералов на пустую строку
    code = std::regex_replace(code, std::regex("\".*?\""), "");
    code = std::regex_replace(code, std::regex("\'.*?\'"), "");
    
    return code;
}

std::string removeStandardComments(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }
    
    std::string sourceCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    // Удаление комментариев
    std::string code = removeComments(sourceCode);
    
    // Удаление строковых литералов
    code = removeStringLiterals(code);
    
    return code;
}

int main() {
    std::string filePath = "file.cpp";
    
   
    std::string code = removeStandardComments(filePath);
    

    std::cout << code << std::endl;
    
    return 0;
}
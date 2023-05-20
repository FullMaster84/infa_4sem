#include <iostream>
#include <fstream>
#include <string>

std::string readLineByNumber(const std::string& filePath, int lineNumber) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return "";
    }
    
    std::string line;
    int currentLineNumber = 1;
    
    while (std::getline(file, line)) {
        if (currentLineNumber == lineNumber) {
            file.close();
            return line;
        }
        currentLineNumber++;
    }
    
    file.close();
    
    return ""; // Если указанный номер строки некорректен
}

int main() {
    std::string filePath = "file.txt";
    int lineNumber;
    
    std::cout << "Введите номер строки: ";
    std::cin >> lineNumber;
    
    std::string line = readLineByNumber(filePath, lineNumber);
    if (line.empty()) {
        std::cout << "Некорректный номер строки или файл пустой." << std::endl;
    } else {
        std::cout << "Строка " << lineNumber << ": " << line << std::endl;
    }
    
    return 0;
}

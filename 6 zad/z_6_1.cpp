#include <iostream>
#include <iomanip>
#include <locale>

int main() {
    // Установка европейской  локали для ввода суммы в EUR
    std::locale inputLocale("de_DE.UTF-8");
    std::cin.imbue(inputLocale);

    // Установка русской  локали для вывода суммы в RUB
    std::locale outputLocale("");

    
    double euroAmount;
    std::cout << "Введите сумму в EUR: ";
    std::cin >> std::get_money(euroAmount);

    // Конвертация в RUB
    double rubAmount = euroAmount * 70;

    
    std::cout.imbue(outputLocale);
    std::cout << "Сумма в RUB: " << std::put_money(rubAmount, true) << std::endl;

    return 0;
}
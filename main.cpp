#include <iostream>
#include <windows.h>
#include "h.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout<<"~~~~~~~Игра «Быки и коровы»~~~~~~~"<<std::endl;
    interface_game();
    int choice=0;
    while (choice < 4) {
        std::cout<<"Ваш выбор: ";
        std::cin>>choice;

        //проверка, что в переменную choice введены только числа
        if (std::cin.fail()) {
            std::cout<<"Ошибка! Введите число.\n"<<std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        switch (choice) {
            case (1): {
                game_with_computer();
                std::cout<<std::endl;
                interface_game();
                break;
            }

            case (2): {
                two_players_game();
                std::cout<<std::endl;
                interface_game();
                break;
            }

            case (3): {
                rules_game();
                interface_game();
                break;
            }

            default: {
                break;
            }
        }
    }
}
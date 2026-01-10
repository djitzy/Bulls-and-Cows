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
        std::cout<<"Ваш выбор (0-4): ";
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
                std::cout<<"Возврат в главное меню..."<<std::endl;
                Sleep(1500); 
                std::cout<<std::endl;
                interface_game();
                break;
            }

            case (2): {
                two_players_game();
                std::cout<<"Возврат в главное меню..."<<std::endl;
                Sleep(1500);
                std::cout<<std::endl;
                interface_game();
                break;
            }

            case (3): {
                rules_game();
                std::cout<<"Возврат в главное меню..."<<std::endl;
                Sleep(1500);
                interface_game();
                break;
            }
            
            case(4): {
                std::cout<<"Завершение работы..."<<std::endl;
                Sleep(1000);
                std::cout<<"Работа завершена. Ждем вас снова в нашей игре)"<<std::endl;
                break;
            }

            default: {
                break;
            }
        }
    }
}

#include <algorithm>
#include <iostream>
#include <windows.h>
#include <vector>
#include <ctime>
#include <random>
#include <cctype>
#include <fstream>
#include "h.h"

//Интерфейс меню
void interface_game() {

    std::cout<<std::string(26,'-')<<std::endl;
    std::cout<<"|"<<std::string(2,' ')<<"1) Игра с компьтером "<<std::string(2,' ')<<"|"<<std::endl;
    std::cout<<std::string(26,'-')<<std::endl;

    std::cout<<std::string(30,'-')<<std::endl;
    std::cout<<"|"<<std::string(2,' ')<<"2) Игра для двух игроков "<<std::string(2,' ')<<"|"<<std::endl;
    std::cout<<std::string(30,'-')<<std::endl;

    std::cout<<std::string(20,'-')<<std::endl;
    std::cout<<"|"<<std::string(2,' ')<<"3) Правила игры "<<std::string(2,' ')<<"|"<<std::endl;
    std::cout<<std::string(20,'-')<<std::endl;

    std::cout<<std::string(19,'-')<<std::endl;
    std::cout<<"|"<<std::string(2,' ')<<"4) Выход 【⏻】"<<std::string(2,' ')<<"|"<<std::string(2,' ')<<std::endl;
    std::cout<<std::string(19,'-')<<std::endl;
}

//Правила игры
void rules_game() {
    std::cout<<"~~~~~Правила игры~~~~~\n"<<std::endl;
    std::cout<<"Быки и коровы - логическая игра, в ходе которой игрок должен отгадать \nзадуманное 4-значное число.\n"<<std::endl;
    std::cout<<"Попытка - это 4-значное число с неповторяющимися цифрами, \nсообщаемое пользователю.\n"<<std::endl;
    std::cout<<"Есть два режима для игры: \n";
    std::cout<<std::string(5,' ')<<"1) Игра с компьтером\n"<<std::endl;
    std::cout<<std::string(5,' ')<<"2) Игра двух пользовтелей\n"<<std::endl;
    std::cout<<"Компьютер сообщает в ответ сколько цифр угадано без совпадения с их \nпозициями в тайном числе (то есть количество коров) и сколько \nугадано вплоть до позиции в тайном числе (то есть количество быков).\n"<<std::endl;
    std::cout<<"Пример: "<<std::endl;
    std::cout<<"Задумано тайное число «3219».\n"<<std::endl;
    std::cout<<"Попытка: «2310».\n"<<std::endl;
    std::cout<<"Результат: две «коровы» (две цифры: «2» и «3» — угаданы на неверных \nпозициях) и один «бык» (одна цифра «1» угадана вплоть до позиции).\n"<<std::endl;
    std::cout<<"Вот и все правила. Хорошей игры)\n"<<std::endl;
}

//Генерация случайного 4-значного числа
std::vector<int> generate_secret_number(int length) {

    std::vector<int> digits {0,1,2,3,4,5,6,7,8,9};
    std::vector<int> secret_number;

    std::srand(std::time(0));
    //генератор случайных чисел, без повторяющихся чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(digits.begin(), digits.end(), gen);

    for (int i = 0; i < length; i++) {
        secret_number.push_back(digits[i]);
    }
    return secret_number;
}

//Проверка корректности числа (без повтора)
bool input_validation(const std::vector<int>& guess, int length) {

    //проверка на повторы в числе
    for (int i = 0; i < length; i++) {
        for (int j = i+1; j < length; j++ ) {
            if (guess[i] == guess[j]) {
                return false;
            }
        }
    }

    return true;
}

//Подсчет быков и коров
void counting_bulls_and_cows(const std::vector<int>& secret_number, const std::vector<int>& guess, int& bulls, int& cows) {
    bulls = 0;
    cows = 0;

    for (size_t i = 0; i < secret_number.size(); i++) {
        if (guess[i] == secret_number[i]) {
            bulls++;
        }
        else {
            for (size_t j = 0; j < secret_number.size(); j++) {
                if (guess[i] == secret_number[j]) {
                    cows++;
                }
            }
        }
    }
}

//Ввод числа (для игрока 1)
bool hidden_input_number(std::vector<int>& secret, int length) {
    secret.clear();
    std::cout<<"Введите секретное 4-значное число: ";
    std::string input;
    std::cin>>input;


    if (input.length() != length) {
        std::cout<<"⚠️ Нужно ввести 4-значное число!\n"<<std::endl;
        return false;
    }

    secret.clear();
    bool error = false;
    //проверка, что все символы числа
    for (char c : input) {//проверка, что все символы числа
        if (!isdigit(c)) {
            error = true;
            break;
        }
        secret.push_back(c - '0');//преобразуем символ в число и добавляем его в вектор
    }

    if (error) {
        std::cout<<"⚠️ Вводите только цифры (0-9)!\n"<<std::endl;
        return false;
    }

    if (!input_validation(secret, length)) {
        std::cout<<"⚠️ Цифры не должны повторяться!\n"<<std::endl;
        return false;
    }
    return true;
}

//Логирование в файл
void log_to_file(const std::string& message) {
    std::ofstream file("log.txt", std::ios::app);
    if (!file.is_open()) {
        std::cout<<"Ошибка! Файл не открывается!"<<std::endl;
    }
    else {
        file << message << std::endl;
    }

}
//игра с компьютером
void game_with_computer() {
    const int length = 4;
    std::vector<int> secret_number = generate_secret_number(length);
    std::vector<int> guess;

    std::cout<<"~~~~~~~Игра «Быки и коровы»~~~~~~~"<<std::endl;
    std::cout<<"~~~~~Режим игры с компьютером~~~~~"<<std::endl;
    std::cout<<"Загадано 4-значное число без повторений\n"<<std::endl;

    int bulls = 0, cows = 0;
    int attempt_counter = 0;

    //Записываем игру в файл log.txt
    log_to_file("\nИгра с компьютером\n");
    std::string secretStr = "";
    for(int d : secret_number) secretStr += std::to_string(d);
    log_to_file("Секретное число: " + secretStr + '\n');

    while (bulls != length) {
        std::cout<<"Введите число:";

        std::string input;
        std::cin >> input;
        attempt_counter++;

        if (input.length() != length) {
            std::cout<<"⚠️ Нужно ввести 4-значное число!\n"<<std::endl;
            continue;
        }

        guess.clear();
        bool error = false;
        //проверка, что все символы числа
        for (char c : input) {
            if (!isdigit(c)) {
                error = true;
                break;
            }
            guess.push_back(c - '0');//преобразуем символ в число и добавляем его в вектор
        }

        if (error) {
            std::cout<<"⚠️ Вводите только цифры (0-9)!\n"<<std::endl;
            continue;
        }

        if (!input_validation(guess, length)) {
            std::cout<<"⚠️ Цифры не должны повторяться!\n"<<std::endl;
            continue;
        }

        counting_bulls_and_cows(secret_number, guess, bulls, cows);
        std::cout<<"Быки: "<< bulls <<" | Коровы: "<< cows <<std::endl<<std::endl;
        log_to_file(std::to_string(attempt_counter) + ") Игрок: " + input + " | Быки=" + std::to_string(bulls) + " Коровы=" + std::to_string(cows));
    }

    std::cout<<"Поздравляем! Вы угадали число!"<<std::endl;
    std::cout<<"Количество попыток: "<<attempt_counter<<std::endl;
    log_to_file("Попытки: " + std::to_string(attempt_counter));
}

//игра двух игроков
void two_players_game() {
    const int length = 4;
    std::vector<int> secret;
    std::vector<int> guess;
    std::string input;

    std::cout<<"~~~~~~~Игра «Быки и коровы»~~~~~~~"<<std::endl;
    td::cout<<"~~~~Режим игры для двух игроков~~~~"<<std::endl;
    std::cout<<"Очередь Игрока 1"<<std::endl;
    while (!hidden_input_number(secret, length)) {
        std::cout<<"Попробуйте еще раз"<<std::endl;
    }

    std::cout<<std::string(50,'\n');

    std::cout<<"Число загадано. Игрок 2, угадывайте!"<<std::endl;

    int bulls = 0, cows = 0;
    int attempt_counter = 0;

    //Записываем игру в файл log.txt
    log_to_file("\nИгра двух игроков\n");
    std::string secretStr = "";
    for(int d : secret) secretStr += std::to_string(d);
    log_to_file("Секретное число: " + secretStr + '\n');

    while (bulls != length) {
        std::cout<<"Введите число: ";
        std::cin>>input;
        attempt_counter++;

        if (input.length() != length) {
            std::cout<<"⚠️ Нужно ввести 4-значное число!\n"<<std::endl;
            continue;
        }

        guess.clear();
        bool error = false;
        //проверка, что все символы числа
        for (char c : input) {
            if (!isdigit(c)) {
                error = true;
                break;
            }
            guess.push_back(c - '0'); //преобразуем символ в число и добавляем его в вектор
        }

        if (error) {
            std::cout<<"⚠️ Вводите только цифры (0-9)!\n"<<std::endl;
            continue;
        }

        if (!input_validation(guess, length)) {
            std::cout<<"⚠️ Цифры не должны повторяться!\n"<<std::endl;
            continue;
        }

        counting_bulls_and_cows(secret, guess, bulls, cows);
        std::cout<<"Быки: "<< bulls <<" | Коровы: "<< cows <<std::endl<<std::endl;
        log_to_file(std::to_string(attempt_counter) + ") Игрок 2: " + input + " | Быки=" + std::to_string(bulls) + " Коровы=" + std::to_string(cows));
    }
    std::cout<<"Поздравляем! Вы угадали число!"<<std::endl;
    std::cout<<"Количество попыток: "<<attempt_counter<<std::endl;
    log_to_file("Попытки: " + std::to_string(attempt_counter));
}



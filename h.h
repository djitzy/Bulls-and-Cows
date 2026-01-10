#include <vector>

#ifndef BULLS_AND_COWS_H_H
#define BULLS_AND_COWS_H_H

//интерфейс
void interface_game();

//правила игры
void rules_game();

//генератор
std::vector<int> generate_secret_number(int length);
//проверка на повторы
bool input_validation(const std::vector<int>& guess, int length);
//подсчет коров и быков
void counting_bulls_and_cows(const std::vector<int>& secret_number, const std::vector<int>& guess, int& bulls, int& cows);
//ввод для первого игрока
bool hidden_input_number(std::vector<int>& secret, int length);
//Логирование в файл
void log_to_file(const std::string& message);

//игра с компьютером
void game_with_computer();

//игра двух игроков
void two_players_game();
#endif //BULLS_AND_COWS_H_H
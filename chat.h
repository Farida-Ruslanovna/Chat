#pragma once

#include "hash_table.h"

// Класс чата с использованием хеш-таблицы для хранения данных
class Chat {
public:
    // Конструктор
    Chat();

    // Регистрация — добавление логина и пароля
    void reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length);

    // Попытка входа
    bool login(const char _login[LOGINLENGTH], const char _pass[], int pass_length);

private:
    HashTable table; // Хранение логинов и хешей паролей
};
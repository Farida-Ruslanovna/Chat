#pragma once

#include "sha1.h"
#include <cstring>

#define TABLE_SIZE 101  // Размер хеш-таблицы (простое число для хорошего распределения)
#define LOGINLENGTH 50  // или любое нужное вам значение
// Структура записи в таблице
struct Entry {
  
    char login[LOGINLENGTH];            // Логин пользователя
    uint* pass_sha1_hash;               // Хеш пароля (хранится динамически)
    bool is_occupied;                   // Флаг занятости ячейки

    // Конструктор по умолчанию
    Entry() : pass_sha1_hash(nullptr), is_occupied(false) {
        login[0] = '\0';
    }

    // Деструктор для очистки памяти
    ~Entry() {
        if (pass_sha1_hash) delete[] pass_sha1_hash;
    }
};

// Класс хеш-таблицы с методом умножения и квадратичным пробированием
class HashTable {
public:
    HashTable();
    ~HashTable();

    // Вставить логин и хеш пароля в таблицу
    bool insert(const char* login, const uint* hash);

    // Найти запись по логину
    const Entry* find(const char* login) const;

private:
    // Массив записей
    Entry table[TABLE_SIZE];

    // Хеш-функция по методу умножения
    unsigned int hashFunction(const char* login) const;
};
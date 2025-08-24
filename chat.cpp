// Chat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "chat.h"
#include <cstring>

// Конструктор по умолчанию
Chat::Chat() {
    // ничего особенного
}

// Регистрация пользователя
void Chat::reg(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    // Вычисляем sha1 хеш пароля
    uint* hash = sha1(const_cast<char*>(_pass), pass_length);
    // Вставляем логин и хеш в таблицу
    table.insert(_login, hash);
    delete[] hash; // освобождаем временную память
}

// Попытка входа
bool Chat::login(const char _login[LOGINLENGTH], const char _pass[], int pass_length) {
    // Ищем запись по логину
    const Entry* entry = table.find(_login);
    if (!entry) {
        // Пользователь не найден
        return false;
    }

    // Вычисляем хеш присланного пароля
    uint* digest = sha1(const_cast<char*>(_pass), pass_length);
    // Сравниваем с сохраненным хешем
    bool result = !memcmp(entry->pass_sha1_hash, digest, SHA1HASHLENGTHBYTES);
    delete[] digest; // освобождаем память
    return result; // возвращаем результат
}
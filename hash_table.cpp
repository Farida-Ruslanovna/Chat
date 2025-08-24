#include "hash_table.h"


// Константа для метода умножения, дробная часть которой используется для хеширования
const float A = 0.6180339887f; // (sqrt(5)-1)/2 — широко используемое число

// Конструктор инициализирует таблицу, все ячейки пустые
HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i)
        table[i].is_occupied = false;
}

// Деструктор — освобождает память, выделенную для хешей
HashTable::~HashTable() {
    // автоматический вызов деструкторов Entry
}

// Хеш-функция по методу умножения
unsigned int HashTable::hashFunction(const char* login) const {
    unsigned int hash_value = 0;

    // Простая хеш-функция для строки
    for (size_t i = 0; i < strlen(login); ++i) {
        hash_value = hash_value * 31 + login[i];
    }

    // Получение дробной части произведения
    double frac = (hash_value * A) - (int)(hash_value * A);

    // Масштабирование до размера таблицы
    return (unsigned int)(TABLE_SIZE * frac);
}

// Вставка новой записи
bool HashTable::insert(const char* login, const uint* hash) {
    unsigned int index = hashFunction(login); // начальный индекс
    unsigned int original_index = index;
    int probe = 0;

    // Квадратичное пробирование для разрешения коллизий
    while (table[index].is_occupied) {
        if (strcmp(table[index].login, login) == 0) {
            // Обновляем существующую запись (если логин уже есть)
            if (table[index].pass_sha1_hash) delete[] table[index].pass_sha1_hash;
            table[index].pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(table[index].pass_sha1_hash, hash, SHA1HASHLENGTHBYTES);
            return true;
        }
        probe++;
        // Квадратичное пробирование: смещение по формуле (original_index + probe^2) mod size
        index = (original_index + probe * probe) % TABLE_SIZE;

        // Если таблица заполнена
        if (probe >= TABLE_SIZE) {
            return false; // вставка невозможна
        }
    }
    // Вставляем новую запись
    strcpy(table[index].login, login);
    table[index].pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
    memcpy(table[index].pass_sha1_hash, hash, SHA1HASHLENGTHBYTES);
    table[index].is_occupied = true;
    return true;
}

// Поиск по логину
const Entry* HashTable::find(const char* login) const {
    unsigned int index = hashFunction(login); // начальный индекс
    unsigned int original_index = index;
    int probe = 0;

    // Поиск по квадратичному пробированию
    while (table[index].is_occupied) {
        if (strcmp(table[index].login, login) == 0) {
            return &table[index]; // найден
        }
        probe++;
        index = (original_index + probe * probe) % TABLE_SIZE;

        if (probe >= TABLE_SIZE) break; // прошли всю таблицу
    }
    return nullptr; // не найден
}
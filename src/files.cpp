#include "Header.h"


BIGNUM* text_to_number(const std::string& text) {
    BIGNUM* num = BN_new();

    // Проходимо по кожному символу в тексті
    for (char c : text) {
        // Отримуємо ASCII-код символу і додаємо його до числа
        BN_mul_word(num, 256);  // Зсуваємо число на 8 біт вліво
        BN_add_word(num, static_cast<unsigned char>(c));  // Додаємо ASCII-код символу
    }

    return num;
}

BIGNUM* read_and_convert_file(const std::string& filename) {
    // Відкриваємо файл для читання
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    // Отримуємо розмір файлу
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Перевіряємо, чи розмір файлу не перевищує 50 МБ
    if (fileSize > 50 * 1024 * 1024) {
        std::cerr << "File size exceeds the limit of 50 MB." << std::endl;
        return nullptr;
    }

    // Створюємо буфер для збереження вмісту файлу
    std::string buffer;
    buffer.resize(fileSize);

    // Читаємо вміст файлу
    file.read(&buffer[0], fileSize);

    // Закриваємо файл
    file.close();

    // Перетворюємо текст на числове представлення
    BIGNUM* m = text_to_number(buffer);

    return m;
}

bool number_to_text(const BIGNUM* num, const std::string& filename) {
    // Отримуємо розмір числового представлення
    int size = BN_num_bytes(num);

    // Створюємо буфер для збереження числа
    std::vector<unsigned char> buffer(size);

    // Копіюємо числове представлення до буфера
    BN_bn2bin(num, buffer.data());

    // Перетворюємо буфер на текст
    std::string text;
    for (unsigned char byte : buffer) {
        text += static_cast<char>(byte);
    }

    // Записуємо текст у файл
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    file << text;
    file.close();

    // Виводимо текст у консоль
    std::cout << "Decrypted text in string view: " << text << std::endl;

    return true;
}

bool write_bignums_to_file(const BIGNUM* num1, const BIGNUM* num2, const std::string& filename) {
    // Відкриваємо файл для запису
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    // Отримуємо розмір числових представлень
    int size1 = BN_num_bytes(num1);
    int size2 = BN_num_bytes(num2);

    // Створюємо буфери для збереження чисел
    std::vector<unsigned char> buffer1(size1);
    std::vector<unsigned char> buffer2(size2);

    // Копіюємо числові представлення до буферів
    BN_bn2bin(num1, buffer1.data());
    BN_bn2bin(num2, buffer2.data());

    // Записуємо буфери у файл
    file.write(reinterpret_cast<char*>(buffer1.data()), size1);
    file.write(reinterpret_cast<char*>(buffer2.data()), size2);

    // Закриваємо файл
    file.close();

    return true;
}


bool write_bignum_to_file(const BIGNUM* num, const std::string& filename) {
    // Відкриваємо файл для запису
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    // Отримуємо розмір числового представлення
    int size = BN_num_bytes(num);

    // Створюємо буфер для збереження числа
    std::vector<unsigned char> buffer(size);

    // Копіюємо числове представлення до буфера
    BN_bn2bin(num, buffer.data());

    // Записуємо буфер у файл
    file.write(reinterpret_cast<char*>(buffer.data()), size);

    // Закриваємо файл
    file.close();

    return true;
}

BIGNUM* read_text_to_bignum(const std::string& filename) {
    // Відкриваємо файл для читання
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return nullptr;
    }

    // Отримуємо розмір файлу
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Перевіряємо, чи розмір файлу не перевищує 50 МБ
    if (fileSize > 50 * 1024 * 1024) {
        std::cerr << "File size exceeds the limit of 50 MB." << std::endl;
        return nullptr;
    }

    // Створюємо буфер для збереження вмісту файлу
    std::string buffer;
    buffer.resize(fileSize);

    // Читаємо вміст файлу
    file.read(&buffer[0], fileSize);

    // Закриваємо файл
    file.close();

    // Перетворюємо текст на числове представлення
    BIGNUM* num = text_to_number(buffer);

    return num;
}







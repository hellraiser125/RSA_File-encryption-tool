#include "Header.h"

int main() {

    //генеруємо прості числа та обчислюємо фукцію ейлера
    BIGNUM* p = generatePrime(1024);
    BIGNUM* q = generatePrime(1024);
    BIGNUM* fi = BN_new();
    fi = euler(p, q);
 
    //виводим числа на екран
    char* p_1 = BN_bn2dec(p);
    char* q_1 = BN_bn2dec(q);
    std::cout << "Prime num p: " << p_1 << std::endl << std::endl;
    std::cout << "Prime num q: " << q_1 << std::endl << std::endl;

    // обчислюємо n
    BIGNUM* n = generateModulus(q, p);
    char* n_1 = BN_bn2dec(n);
    std::cout << "Module n (first key part): " << n_1 << std::endl << std::endl;


    //виводимо значення ейлера
    char* phiStr = BN_bn2dec(fi);
    std::cout << "Eiler (n): " << phiStr << std::endl << std::endl;

    //обчислюємо експоненту е
    BIGNUM* e = choose_public_exponent(fi);

    // Виводимо результат
    std::cout << "Public exponent e (second key part): " << BN_bn2dec(e) << std::endl << std::endl;

    //записуємо публічний ключ в файл
    std::cout << "Writing pub key to file..." << std::endl << std::endl;
    std::string pubF = "D:/pub.txt";
    write_bignums_to_file(n,e, pubF);
    

    //генеруємо private key
    BIGNUM* prv_key = generatePrivateKey(e, fi);
    char* prvt = BN_bn2dec(prv_key);
    std::cout << "private key: " << prvt << std::endl << std::endl;

    std::cout << "Writing private key to file..." << std::endl << std::endl;
    //записуємо його в файл
    std::string prvF = "D:/priv.txt";
    write_bignum_to_file(prv_key, prvF);

    std::string filename = "D:/text.txt";
    BIGNUM* m = BN_new();
    if (read_and_convert_file(filename) == nullptr)
        return 0;
    else
        m = read_and_convert_file(filename);
    //читаємо текст з файла
    std::string line;
    std::cout << "Reading text from file\nText in file: ";
    std::ifstream myfile("D:/text.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::cout << line << '\n';
        }
        myfile.close();
    }

    else std::cout << "Unable to open file";


    //read from file and generate data for encrypt
   
    BIGNUM* enc_text = BN_new();

    //перед початком шифрування читаємо ключ




    if (m != nullptr) {
        // Виводимо числове представлення m
        std::cout << "Num view m: " << BN_bn2dec(m) << std::endl;

        //encrypt text
        enc_text = encrypt_message(m, e, n);

        // Виводимо зашифрований текст
        std::cout << "Encrypted text (C): " << BN_bn2dec(enc_text) << std::endl;

        std::cout << "Writing encrypted text to file" << std::endl << std::endl;
        write_bignum_to_file(enc_text, "D:/enc.txt");

    }

    //decrypt text
    BIGNUM* dec_text = decrypt_message(read_text_to_bignum("D:/enc.txt"), read_text_to_bignum("D:/priv.txt"), n);

    // Виводимо відновлене повідомлення
    std::cout << "Decrypted text in numeric view (m): " << BN_bn2dec(dec_text) << std::endl;

    std::cout << "Writing decrypted text to file"<<std::endl<<std::endl;
    number_to_text(dec_text,"D:/dec.txt");
    


    // Звільняємо пам'ять
    BN_free(q);
    BN_free(p);
    BN_free(n);
    BN_free(e);
    BN_free(fi);
    BN_free(enc_text);
    BN_free(m);
    BN_free(prv_key);
    BN_free(dec_text);
    OPENSSL_free(prvt);
    OPENSSL_free(phiStr);
    OPENSSL_free(n_1);
    OPENSSL_free(p_1);
    OPENSSL_free(q_1);

    return 0;
}
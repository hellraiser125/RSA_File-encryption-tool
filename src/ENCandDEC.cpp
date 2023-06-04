#include "Header.h"

//encrypt
BIGNUM* encrypt_message(const BIGNUM* m, const BIGNUM* e, const BIGNUM* n) {
    BIGNUM* C = BN_new();

    // Виконуємо шифрування: C = m^e mod n
    BN_mod_exp(C, m, e, n, BN_CTX_new());

    return C;
}

//decrypt
BIGNUM* decrypt_message(BIGNUM* enc_text, BIGNUM* prv_key, BIGNUM* n) {
    BIGNUM* dec_text = BN_new();

    // Розшифровуємо повідомлення
    BN_mod_exp(dec_text, enc_text, prv_key, n, BN_CTX_new());

    return dec_text;
}



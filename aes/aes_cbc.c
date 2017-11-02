#include "aes/aes.h"

//s_rand is seed of random
//change AES type in the encrypt(char *ptext, char *key) and decrypt(char *ctext, char *key) function

int s_rand=0;

void resetiv_outbound(char *iv) {
    memset(iv,0,16);
  }

void randominit() {
    s_rand = readADC(3);
}

int random_() {
    srand(readADC((s_rand%5)));
    int x = rand();
    s_rand = x;
    return x;
}

void populate_iv_outbound(char *iv) {
    resetiv_outbound();
    int i;
    for (i;i<16;i++) {
        iv[i] = random_();
    }
}

int encrypt(char *ptext, char *key){
    aes256_ctx_t ctx;
    aes256_init(key,&ctx);
    aes256_enc(ptext,&ctx);
    return 1;
}

int decrypt(char *ctext, char *key){
    aes256_ctx_t ctx;
    aes256_init(key,&ctx);
    aes256_dec(ctext,&ctx);
    return 1;
}

int encrypt_cbc(char *ptext, char *iv, int msgblocks) {
    int i=0;
    int j=0;
    char plainText[16];
    memset(plainText,0,16);
    //populate_iv_outbound();
    for (i=0;i<msgblocks;i++) {
        // SET PLAINTEXT STARTS //
        j=0;
         for(j=0;j<16;j++) {
             plainText[j] = ptext[(i*16)+j];
         }
        // SET PLAINTEXT ENDS //
        j=0;
        if (i==0) {
            for (j=0;j<16;j++) {
                plainText[j] = plainText[j] ^ iv[j];
            }
        } else {
            for (j=0;j<16;j++) {
                plainText[j] = plainText[j] ^ ptext[((i-1)*16)+j];
            }
        }
        
        encrypt(plainText);
        // WRITE PLAINTEXT TO PTEXT STARTS //
        j = 0;
        for (j=0;j<16;j++) {
            ptext[(i*16)+j] = plainText[j];
        }
        // WRITE PLAINTEXT TO PTEXT ENDS //
    }

    return 1;
}

int decrypt_cbc(char *ctext,char *ptext, char *iv,int msgblocks) {
    int i=0;
    int j=0;
    char cipherText[16];
    memset(ptext,0,200);
    memset(cipherText,0,16);
    for (i=0;i<msgblocks;i++) {
        // SET CIPHERTEXT STARTS //
        j=0;
         for(j=0;j<16;j++) {
             cipherText[j] = ctext[(i*16)+j];
         }
        // SET CIPHERTEXT ENDS //

        decrypt(cipherText);

        j=0;
        if (i==0) {
            for (j=0;j<16;j++) {
                cipherText[j] = cipherText[j] ^ iv[j];
            }
        } else {
            for (j=0;j<16;j++) {
                cipherText[j] = cipherText[j] ^ ctext[((i-1)*16)+j];
            }
        }
        
        
        // WRITE CIPHERTEXT TO CTEXT STARTS //
        j = 0;
        for (j=0;j<16;j++) {
            ptext[(i*16)+j] = cipherText[j];
        }
        // WRITE CIPHERTEXT TO CTEXT ENDS //
    }
}
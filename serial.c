#include <string.h>
#include "openssl/md5.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 50 // Максимальная длина обрабатываемой строки

int N, K; // Длина алфавита, длина искомой строки
int thf[BUFF_SIZE]; // Индексный массив
char *alphabet; // Алфавит поиска
char *wanted; // Искомая строка
unsigned char md5_input[MD5_DIGEST_LENGTH]; // Хеш искомой функции
static int count_perm = 0;

// Вывод хеша
void print(unsigned char *str) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02x", str[i]);
}

// Сравниваем хеши. Нашли или нет
int compare_hash(const unsigned char *a) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        if (a[i] != md5_input[i]) return -1;
    return 0;
}

void repeat_permutations(int k) {
    if (k == K) {
        char current_line[BUFF_SIZE];
        unsigned char cur_key[MD5_DIGEST_LENGTH];

        int i;
        for (i = 0; i < K; i++) {
            current_line[i] = alphabet[thf[i]];
        }
        current_line[i] = '\0';

        MD5((const unsigned char *) current_line,
            strlen(current_line),
            (cur_key)
        );

        count_perm++;
        /*
         printf("%s|%d\n", current_line, count_perm);
         printf("[%d] \t(%s)\t", (int)strlen(current_line), current_line);
         print(cur_key);printf(" ");print(md5_input);
        */
        if (compare_hash(cur_key) == 0) {
            print(cur_key);
            printf(" ");
            print(md5_input);
            printf(" <= Password is %s\n", current_line);
            exit(0);
        }

        //printf("\n");
    } else {
        for (int j = N - 1; j >= 0; j--) {
            // Генерируем последовательность
            thf[k] = j;
            // Уходим в рекурсию для 1 элемента
            repeat_permutations(k + 1);
        }
    }
}

int main(int argc, char **args) {
    if (argc != 4) {
        printf("Format: \"Alphabet\" \"Wanted\" \"Lenght\"\n");
        return EXIT_FAILURE;
    }

    alphabet = args[1];
    wanted = args[2];

    N = (int) strlen(alphabet); // Длина алфавита
    K = atoi(args[3]); // Искомая строка

    printf("Alphabet: %s\nWanted: %s\n\n", alphabet, wanted);

    MD5((const unsigned char *) wanted,
        strlen(wanted),
        (md5_input)
    ); // Считаем 1 раз хеш для искомой строки

    // Вызываем функцию перебора
    // уменьшая длину искомой строки до 1
    int h = K;
    K = 1;
    do {
        repeat_permutations(0);
    } while (K++ < h);

    printf("\n\n%d", count_perm);
    return 0;
}
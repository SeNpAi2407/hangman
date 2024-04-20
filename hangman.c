#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}
int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int findFlag = 0;
    for (int i = 0; i < strlen(secret); i++) {
        findFlag = 0;
        for (int j = 0; j < strlen(letters_guessed); j++) {
            if (secret[i] == letters_guessed[j]) {
                findFlag = 1;
                break;
            }
        }
        if (findFlag == 0) {
            return 0;
        }   
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    for (int i = 0; i < strlen(secret); i++) {
        int letter_guessed = 0;
        for (int j = 0; j < strlen(letters_guessed); j++) {
            if (secret[i] == letters_guessed[j]) {
                letter_guessed = 1;
                break;
            }
        }
        if (letter_guessed) {
            guessed_word[i] = secret[i];
        } else {
            guessed_word[i] = '_';
        }
    }
    guessed_word[strlen(secret)] = '\0';
}
void get_available_letters(const char letters_guessed[], char available_letters[]) {
    int index = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        available_letters[index++] = c;
    }
    available_letters[index] = '\0'; 
    int len_guessed = strlen(letters_guessed);
    int len_available = strlen(available_letters);
    for (int i = 0; i < len_guessed; i++) {
        for (int j = 0; j < len_available; j++) {
            if (letters_guessed[i] == available_letters[j]) {
                for (int k = j; k < len_available - 1; k++) {
                    available_letters[k] = available_letters[k + 1];
                }
                available_letters[len_available - 1] = '\0';
                len_available--;
                break;
            }
        }
    }
    for (int i = 0; i < len_available - 1; i++) {
        for (int j = i + 1; j < len_available; j++) {
            if (available_letters[i] > available_letters[j]) {
                char temp = available_letters[i];
                available_letters[i] = available_letters[j];
                available_letters[j] = temp;
            }
        }
    }
}

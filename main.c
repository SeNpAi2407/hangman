#include <stdio.h>
#include "hangman.h"
#include <stdlib.h>
#include <time.h>


int main() {
    srand(time(NULL));
    char secret[16];
    get_word(secret);
    printf("%s\n", secret);

    printf("%d\n", is_word_guessed("secret","aeiou"));
    // prints: 0
    printf("%d\n", is_word_guessed("hello","aeihoul"));
    // prints^ 1
    char resalt[30];
    get_guessed_word("container", "arpstxgoieyu", resalt);
    printf("%s\n", resalt);  // Выведет: "_o_tai_er"
    char result[30];
    get_available_letters("arpstxgoieyu", result);
    printf("%s\n", result);
    return 0;
}
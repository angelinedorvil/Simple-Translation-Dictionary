// TODO - Implement your tests in this file using testlib functions
//Angeline Dorvil

#include <stdio.h>
#include <stdlib.h>

#include "testlib.h"
#include "tools.h"


void test_negative_size(){
    struct dictionary * d = NULL;
    d = dictionary_build(-3);
    TEST("Building with negative size should return NULL", d == NULL);
    
    dictionary_free(&d);
    TEST("Freeing NULL pointer should return -1", d == NULL);
}    
 
void test_zero_size(){ 
    struct dictionary * f = NULL;
    f = dictionary_build(0);
    TEST("Building with zero size should return NULL", f == NULL);  
    
    dictionary_free(&f);
    TEST("Freeing NULL pointer should return -1", f == NULL);
}

void test_appropriate_size(){    
    struct dictionary * c = NULL;
    c = dictionary_build(3);
    TEST("Building appropriate size dictionary should return a pointer", c != NULL);  
    dictionary_free(&c);
    TEST("Freeing dictionary pointer should return -1", c == NULL);      
}

void test_memory_size_failure(){
    struct dictionary * a = NULL;
    a = dictionary_build(1000000000);
    TEST("Memory allocation failure returns NULL", a == NULL);
    
    dictionary_free(&a);
    TEST("Freeing NULL pointer should return -1", a == NULL);

}


void test_add_multiple_words() {
    printf("\n");
    printf("Building a new dictionary of size 10 with 5 pairs of words in English and French\n");    
    struct dictionary *b = dictionary_build(10); // Assuming a dictionary of size 10
    
    const char *english_words[] = {"apple", "book", "cat", "dog", "notebook"};
    const char *foreign_words[] = {"pomme", "livre", "chat", "chien", "cahier"};
    
    int num_words = sizeof(english_words) / sizeof(english_words[0]); // Get the number of words
    
    for (int i = 0; i < num_words; i++) {
        int result = dictionary_add(b, english_words[i], foreign_words[i]);
        if (result == 0) {
            printf("Added: %s - %s\n", english_words[i], foreign_words[i]);
        } else {
            printf("Failed to add: %s - %s because of failure code %d\n", english_words[i], foreign_words[i], result);
        }
    }

    dictionary_free(&b);
}

void test_translate_eng_words() {
    printf("\n");
    printf("Looking up translations\n");
    struct dictionary *v = dictionary_build(10); 
    
    const char *english_words[] = {"apple", "book", "cat", "dog", "notebook"};
    const char *foreign_words[] = {"pomme", "livre", "chat", "chien", "cahier"};
    
    int num_words = sizeof(english_words) / sizeof(english_words[0]);    
    for (int i = 0; i < num_words; ++i) {
        dictionary_add(v, english_words[i], foreign_words[i]);
    }

    char* result = dictionary_translate(v, "book", NULL);
    if (result != NULL) {
        printf("Translation of 'book': %s\n", result);
        free(result);
    } else {
        printf("Failed to translate 'book'\n");
    }

    char* result2 = dictionary_translate(v, NULL, NULL);
    if (result2 != NULL) {
        printf("Translation of 'book': %s\n", result2);
        free(result2);
    } else {
        printf("Failed to translate; No word looked up, result is: %s\n", result2);
    }

    char* result3 = dictionary_translate(v, NULL, "cahier");
    if (result3 != NULL) {
        printf("Translation of 'cahier': %s\n", result3);
        free(result3);
    } else {
        printf("Failed to translate %s\n", result3);
    }

    char* result4 = dictionary_translate(v, NULL, "papier");
    if (result4 != NULL) {
        printf("Translation of 'papier': %s\n", result4);
        free(result4);
    } else {
        printf("Failed to translate; word looked up is 'papier' result is %s\n", result4);
    }
    dictionary_free(&v);
}

    

void runAllTests(){
    test_negative_size();
    test_zero_size();  
    test_appropriate_size();  
    test_memory_size_failure();
    test_add_multiple_words();
    test_translate_eng_words();
}

// TODO - Implement the functions in this file
//Angeline Dorvil
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"


struct dictionary *dictionary_build(int size) {
    if (size <= 0) {
        return NULL;
    }
    
    struct dictionary *new_dictionary = malloc(sizeof(struct dictionary));
    if (new_dictionary == NULL) {
        return NULL;
    }
    
    new_dictionary->data = malloc(size * sizeof(struct wordPair *));
    if (new_dictionary->data == NULL) {
        free(new_dictionary);
        return NULL;
    }
    
    for (int i = 0; i < size; ++i) {
        new_dictionary->data[i] = NULL; // Initialize each element to NULL
    }
    
    new_dictionary->size = size;
    new_dictionary->nbwords = 0;
    
    return new_dictionary;
}


int dictionary_add(struct dictionary* d,
                    const char * const english,
                    const char * const foreign) {
    
    if (d == NULL || english == NULL || foreign == NULL) {
        return -1; // Handle bad parameters
    }    
    
    if (strlen(english) == 0 || strlen(foreign) == 0) {
    	return -1;
    }

    // Find the index to insert the new word pair
    int index = d->nbwords; // Using the number of words as the index
    
    // Check if the dictionary is already full
    if (index >= d->size) {
        return -5; // Dictionary is full
    }

    // Allocate memory for the new word pair
    struct wordPair *newWordPair = malloc(sizeof(struct wordPair));
    if (newWordPair == NULL) {
        return -2; // Unable to allocate new wordPair
    }

    // Copy English and foreign words into the new word pair
    newWordPair->englishWord = strdup(english);
    newWordPair->foreignWord = strdup(foreign);

    // Add the new word pair to the dictionary
    d->data[index] = newWordPair;
    d->nbwords++; // Increment the count of words in the dictionary
    
    return 0;
}


int dictionary_free( struct dictionary ** p){
	if (p == NULL || *p == NULL) {
		return -1;
	}
	
	free(*p);
	*p = NULL;
	
	return 0;
}

char* dictionary_translate(struct dictionary* d,
                                  const char* const english,
                                  const char* const foreign) {
    // Check for invalid parameters
    if (d == NULL || (english == NULL && foreign == NULL) || (english != NULL && foreign != NULL)) {
        return NULL; // Return NULL for invalid parameter combinations
    }

    int i;
    char* translation = NULL;

    // Look up translation based on the provided word(s)
    if (english != NULL) {
        // Find translation of English word in the foreign language and return it
        for (i = 0; i < d->nbwords; ++i) {
            if (strcmp(d->data[i]->englishWord, english) == 0) {
                translation = strdup(d->data[i]->foreignWord);
                break;
            }
        }
    } else {
        // Find translation of foreign word in English and return it
        for (i = 0; i < d->nbwords; ++i) {
            if (strcmp(d->data[i]->foreignWord, foreign) == 0) {
                translation = strdup(d->data[i]->englishWord);            
                break;
            }
        }
    } 

    return translation;
}



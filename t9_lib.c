
/* Tegbir Lalli
   February 21st, 2024
   CSE 374
   HW6 : T9 Implementation
   This code implements a T9 predictive word text library.
   It uses a dictionary of words to populate its word entries
   and then when a user presses a combination of numbers and # 
   as input, the corresponding word to that combination is displayed.
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t9_lib.h"
#include "t9_priv.h"

#define MAX_INPUT_LEN 50
#define LINK 9

/* The following function creates a T9 node that can be used to 
   build the trie.
   Input Parameters: 
  word: word that needs to be added to the trie dictionary that has
        a max length of 50 characters.
  max: the amount of actual letters in the input word string
  Returns a T9* that points to the node with all fields of the
  T9* fields initialized*/
T9* makeNode(const char word[50], int max);

/* The following function processes the words in an external dictionary
   and builds the trie structure necessary for the predictive testing.
   Ins: 
  word: word that needs to be added to the trie dictionary
  dict: a pointer to the dictionary that the word needs to be added to
  last_ind: the index of the last valid letter
   Returns the either the same dictionary as the input or an updated
  dictionary with a new path and/or word added depending on the 
  validity of the input*/
T9* process_word(const char* word, T9* dict, int last_ind);

T9* makeNode(const char wordExt[50], int max) {
  // creates memory for node with size of itself which makes sure enough mem
  T9* node = (T9*) malloc(sizeof(T9));
  if (!node) {
    return NULL;
  }
  // initialize all fields, word is either all null or contains word
  // and the rest of it is null, this clears pre existing mem;
  // These buckets are children nodes for each of the 8 possible
  // characters
  for (int i = 0; i < LINK; i++) {
    node->buckets[i] = NULL;
  }
  int end = 0;
  for (int i = 0; i < max; i++) {
    node->word[i] = wordExt[i];
    end = end + 1;
  }
  for (int i = end; i < MAX_INPUT_LEN; i++) {
    node->word[i] = '\0';
  }
  return node;
}

// Makes instance of empty dictionary
T9* InitializeEmptyT9() {
  T9* dict = makeNode('\0', 0);
  return dict;
}

// Makes instance of dictionary with words in file if valid file
T9* InitializeFromFileT9(const char* filename) {
  T9* dict = makeNode('\0', 0);
  char lines[MAX_INPUT_LEN];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Invalid Input File. \n");
    return NULL;
  }
  while (fgets(lines, MAX_INPUT_LEN, file)) {
    AddWordToT9(dict, lines);
  }
  fclose(file);
  return dict;
}

// Adds the param word into the parameter dictionary with use of T9 nodes
// if the input dictionary and word is valid
void AddWordToT9(T9* dict, const char* word) {
  if (!dict || word == NULL) {
    return;
  }
  int length = strlen(word);
  if (length > MAX_INPUT_LEN || length < 1 || word == NULL) {
    return;
  }

  int last_ind = 0;
  // logic to handle newline character at end of word
  if (word[strlen(word)-1] == '\n') {
    last_ind = strlen(word) -1;
  } else {
    last_ind = strlen(word);
  }
  int val;
  // checks for word validity by comparing with a using a's ascii value
  for (int i = 0; i < last_ind; i++) {
    val = word[i] - 'a';
    if (val < 0 || val > 25) {
      return;
    }
  }
  // if valid word, proceed to adding to dict
  dict = process_word(word, dict, last_ind);
}

T9* process_word(const char* word, T9* dict, int last_ind) {
  // following is the mapping of letters to corresponding indexes of
  // the dict buckets
  char char_to_index[26] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                            4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7};
  T9* dict_temp = dict;
  int index_of_char;
  // processes word up until last valid index
  for (int j = 0; j < last_ind; j++) {
    index_of_char = char_to_index[word[j] - 'a'];
    // if bucket is empty and not at last index, add path to dictionary
    if (dict_temp->buckets[index_of_char] == NULL && last_ind != j+1) {
      dict_temp->buckets[index_of_char] = makeNode('\0', 0);
      dict_temp = dict_temp->buckets[index_of_char];
    } else if (last_ind == j+1) {
      // this path controls order of operations if the current
      // index corresponds to the last letter
      if (dict_temp->buckets[index_of_char] == NULL) {
        // first word in bucket
        dict_temp->buckets[index_of_char] = makeNode(word, last_ind);
        dict_temp = dict_temp->buckets[index_of_char];
      } else if (dict_temp->buckets[index_of_char]->word[0]!= '\0') {
        // checks duplicate
        if (!strncmp(dict_temp->buckets[index_of_char]->word, word, 50)) {
          return dict;
        }
        dict_temp = dict_temp->buckets[index_of_char];
        if (dict_temp->buckets[8] == NULL) {
          // starts adding to "linked list"
          dict_temp->buckets[8]= makeNode(word, last_ind);
        } else {
          // checks dupes one more time
          if (!strncmp(dict_temp->buckets[8]->word, word, 50)) {
            return dict;
          }
          dict_temp = dict_temp->buckets[8];
          // builds linked list
          while (dict_temp->buckets[8] != NULL) {
            if (!strncmp(dict_temp->buckets[8]->word, word, 50)) {
              return dict;
            }
            dict_temp = dict_temp->buckets[8];
          }
            dict_temp->buckets[8] = makeNode(word, last_ind);
        }
      } else {
        // if already a node with memory, just add word
        dict_temp = dict_temp->buckets[index_of_char];
        for (int i = 0; i < last_ind; i++) {
          dict_temp->word[i] = word[i];
        }
        }
      } else {
        // iterate through path
        dict_temp = dict_temp->buckets[index_of_char];
      }
  }
  return dict;
}

// Predicts whether the dictionary in param contains the path corresponding
// to the nums pattern, returns the actual string if found or null if not
char* PredictT9(T9* dict, const char* nums) {
  if (dict == NULL) {
    return NULL;
  }
  int total_null_buck = 0;
  // case that only a head exists of the dictionary
  for (int i = 0; i < LINK; i++) {
    if (dict->buckets[i] == NULL) {
      total_null_buck= total_null_buck + 1;
    }
  }
  if (total_null_buck == 9) {
    return NULL;
  }
  if (nums[0] == '\0' || nums[0] == '#') {
    return NULL;
  }
  for (int i = strlen(nums) - 2; i >= 0; i--) {
    if (nums[i] == '#' && nums[i+1] !='#') {
      return NULL;
    } else if (nums[i] != '#' && (nums[i] -'2' < 0 || nums[i] -'2' > 7)) {
      return NULL;
    }
  }
  // only makes temp after figuring out needed
  T9* dict_temp = dict;
  bool switched_into_linked = false;
  int index_of_char;
  for (int i = 0; i < strlen(nums); i++) {
    index_of_char = nums[i] - '2';
    // go into bucket[8] branch if bucket already has word
    if (nums[i] == '#') {
      if (!switched_into_linked && dict_temp->buckets[8] != NULL) {
        dict_temp = dict_temp->buckets[8];
        switched_into_linked = true;
      } else if (switched_into_linked && dict_temp->buckets[8] != NULL) {
        dict_temp = dict_temp->buckets[8];
      } else {
        return NULL;
      }
    } else if (dict_temp->buckets[index_of_char] == NULL) {
      // no word found
      return NULL;
    } else {
      dict_temp = dict_temp->buckets[index_of_char];
    }
  }
    // if path exists but word doesnt exist
  if (dict_temp->word[0] == '\0') {
    return NULL;
  }
  // return word
  return dict_temp->word;
}

// frees the nodes memory via recursion
void DestroyT9(T9* dict) {
  if (!dict) {
    return;
  }
  for (int i = 0; i < LINK; i++) {
    DestroyT9(dict->buckets[i]);
  }
  free(dict);
}

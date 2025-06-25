
#include <string.h>

#include "safe_assert.h"
#include "t9_lib.h"

void AssertReturnedStringEquals(char* expected, char* actual);

suite("T9") {
  test("Empty initialization") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);
    DestroyT9(dict);
  }

  test("Empty Predict") {
    T9* dict = InitializeEmptyT9();
    char* word = PredictT9(dict, "2345");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("Testing single end hashtag") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "book");
    AddWordToT9(dict, "cool");

    char* word = PredictT9(dict, "2665#");
    printf("%s", word);
    AssertReturnedStringEquals("cool", word);
    DestroyT9(dict);
  }

  test("check empty add") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "");

    char* word = PredictT9(dict, "");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("middle hashtag") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "cool");
    AddWordToT9(dict, "book");

    char* word = PredictT9(dict, "26#65");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("transfer from words") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "book");
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "cool");
    char* word = PredictT9(dict, "2665#");
    safe_assert(strncmp(word, "book", 5));
    word = PredictT9(dict, "2665#");
    safe_assert(strncmp(word, "cool", 5));
    DestroyT9(dict);
  }

  test("case input too big") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "az");
    char* word = PredictT9(dict, "4131");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("case input too small") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "az");
    char* word = PredictT9(dict, "2");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("dict from file correct") {
    T9* dict = InitializeFromFileT9("./dictionary.txt");
    safe_assert(dict != NULL);
    DestroyT9(dict);
  }

  test("predict from dict") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    char* word = PredictT9(dict, "227");
    AssertReturnedStringEquals("abs", word);
    DestroyT9(dict);
  }

  test("predict empty from dict") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    char* word = PredictT9(dict, "");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("predict one letter from dict") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    char* word = PredictT9(dict, "2");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("fortnite baller") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "zzzzzz");
    char* word = PredictT9(dict, "999999");
    AssertReturnedStringEquals("zzzzzz", word);
    DestroyT9(dict);
  }

  test("all letters") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "a");
    AddWordToT9(dict, "b");
    AddWordToT9(dict, "c");
    AddWordToT9(dict, "d");
    AddWordToT9(dict, "e");
    AddWordToT9(dict, "f");
    AddWordToT9(dict, "g");
    AddWordToT9(dict, "h");
    AddWordToT9(dict, "i");
    AddWordToT9(dict, "j");
    AddWordToT9(dict, "k");
    AddWordToT9(dict, "a");
    AddWordToT9(dict, "b");
    AddWordToT9(dict, "c");
    AddWordToT9(dict, "d");
    AddWordToT9(dict, "e");
    AddWordToT9(dict, "f");
    AddWordToT9(dict, "g");
    AddWordToT9(dict, "h");
    AddWordToT9(dict, "i");
    AddWordToT9(dict, "j");
    AddWordToT9(dict, "k");
    AddWordToT9(dict, "l");
    AddWordToT9(dict, "m");
    AddWordToT9(dict, "n");
    AddWordToT9(dict, "o");
    AddWordToT9(dict, "p");
    AddWordToT9(dict, "q");
    AddWordToT9(dict, "r");
    AddWordToT9(dict, "s");
    AddWordToT9(dict, "t");
    AddWordToT9(dict, "u");
    AddWordToT9(dict, "v");
    AddWordToT9(dict, "w");
    AddWordToT9(dict, "x");
    AddWordToT9(dict, "y");
    AddWordToT9(dict, "z");
    char *word;
    for (int i = 0; i < 26; i++) {
      char* letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
      if (i == 0) {
        word = "2";
      } else if (i == 1) {
        word = "2#";
      } else if (i ==2) {
        word = "2##";
      } else if (i == 3) {
        word = "3";
      } else if (i == 4) {
        word = "3#";
      } else if (i ==5) {
        word = "3##";
      } else if (i == 6) {
        word = "4";
      } else if (i == 7) {
        word = "4#";
      } else if (i ==8) {
        word = "4##";
      } else if (i == 9) {
        word = "5";
      } else if (i == 10) {
        word = "5#";
      } else if (i ==11) {
        word = "5##";
      } else if (i == 12) {
        word = "6";
      } else if (i == 13) {
        word = "6#";
      } else if (i ==14) {
        word = "6##";
      } else if (i == 15) {
        word = "7";
      } else if (i == 16) {
        word = "7#";
      } else if (i ==17) {
        word = "7##";
      } else if (i == 18) {
        word = "7###";
      } else if (i == 19) {
        word = "8";
      } else if (i ==20) {
        word = "8#";
      } else if (i == 21) {
        word = "8##";
      } else if (i == 22) {
        word = "9";
      } else if (i ==23) {
        word = "9#";
      } else if (i == 24) {
        word = "9##";
      } else {
        word = "9###";
      }
      char* predict = PredictT9(dict, word);
      printf("%s = %s \n", letters[i], predict);
      AssertReturnedStringEquals(letters[i], predict);
    }
  }

  test("randdommdm") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    char* word = PredictT9(dict, "2");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("add symbol") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "123");
    char* word = PredictT9(dict, "123");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("repeat") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "cool");
    char* word = PredictT9(dict, "2665#");
    printf("%s\n", word);
    AssertReturnedStringEquals("cool", word);
    DestroyT9(dict);
  }

  test("hastags") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "cool");
    char* word = PredictT9(dict, "266#5#");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("hastags2") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "bonk");
    AddWordToT9(dict, "cool");
    char* word = PredictT9(dict, "2665##");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("add dict") {
    T9* dict = InitializeFromFileT9("./dictionary.txt");
    char* word = PredictT9(dict, "2665123");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("massive word") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    char* word = PredictT9(dict, "222222222222222222222222222222222222222222"
    "222222222222222222222222222222222222222222222222222222222222222");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("massive word #") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "####");
    char* word = PredictT9(dict, "####");
    printf("%s", word);
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("# first") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "#yoooo");
    char* word = PredictT9(dict, "123456");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

    test("dupes") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "book");
    AddWordToT9(dict, "book");
    AddWordToT9(dict, "book");
    char* word = PredictT9(dict, "2556##");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("init file") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    AddWordToT9(dict, "Mirrors");
    char* word = PredictT9(dict, "93272");
    AssertReturnedStringEquals("zebra", word);
    word = PredictT9(dict, "6477677");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("init file dupes") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    AddWordToT9(dict, "mirrors");
    char* word = PredictT9(dict, "6477677");
    AssertReturnedStringEquals("mirrors", word);
    AddWordToT9(dict, "mirror");
    word = PredictT9(dict, "647767");
    AssertReturnedStringEquals("mirror", word);
    DestroyT9(dict);
  }

  test("init file dupes") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    AddWordToT9(dict, "");
    char* word = PredictT9(dict, "");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("init special chars") {
    T9* dict = InitializeFromFileT9("./small_dictionary.txt");
    AddWordToT9(dict, "+++");
    char* word = PredictT9(dict, "***");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("special chars single") {
    T9* dict = InitializeFromFileT9("./dictionary.txt");
    char* word = PredictT9(dict, "99999827");
    AssertReturnedStringEquals("zyzzyvas", word);
    word = PredictT9(dict, "22");
    AssertReturnedStringEquals("aa", word);
    DestroyT9(dict);
  }

  test("init nonfile") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "+");
    char* word = PredictT9(dict, "*");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("init space") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, " ");
    char* word = PredictT9(dict, "0");
    safe_assert(word == NULL);
    DestroyT9(dict);
  }

  test("sheep baaa") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "def");
    AddWordToT9(dict, "fed");
    AddWordToT9(dict, "efd");
    char* word = PredictT9(dict, "333##");
    safe_assert(word != NULL);
  }

  test("dog woof") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "def");
    AddWordToT9(dict, "fed");
    AddWordToT9(dict, "efd");
    char* word = PredictT9(dict, "333##");
    AssertReturnedStringEquals("efd", word);
  }

  test("dog woof") {
    T9* dict = InitializeEmptyT9();
    AddWordToT9(dict, "#abc");
    AddWordToT9(dict, "#");
    AddWordToT9(dict, "##");
    char* word = PredictT9(dict, "#");
    safe_assert(word == NULL);
  }

  // test("cat meow") {
  //   T9* dict = InitializeEmptyT9();
  //   char* ret = PredictT9(dict, "");
  //   AssertReturnedStringEquals(ret, NULL);
  //   DestroyT9(dict);
  // }
}

void AssertReturnedStringEquals(char* expected, char* actual) {
  safe_assert(actual > 0);
  safe_assert(strlen(actual) == strlen(expected));
  safe_assert(strcmp(actual, expected) == 0);
}

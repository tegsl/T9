#ifndef T9_PRIV_H_
#define T9_PRIV_H_
#define MAX_INPUT_LEN 50
#define NUM_BUCKS 9

// T9 stuct that returns "nodes"
typedef struct T9 {
  // 50 length word
  char word[MAX_INPUT_LEN];
  // 9 buckets for digits 2-9 and #
  T9* buckets[NUM_BUCKS];
} T9;

#endif  // T9_PRIV_H_

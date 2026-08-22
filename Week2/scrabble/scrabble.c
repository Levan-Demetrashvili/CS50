#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int LETTER_POINTS[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int calculate_letter_point(string word, int i);

int main(void) {
  int sum1 = 0 , sum2 = 0;
  string word1 = get_string("Player 1: ");
  string word2 = get_string("Player 2: ");
  int length = strlen(word1) > strlen(word2) ? strlen(word1) : strlen(word2);

 
  for (int i = 0; i < length; i++) {
    sum1 += calculate_letter_point(word1,i);
    sum2 += calculate_letter_point(word2,i);
  } 

  if (sum1 > sum2) {
    printf("Player 1 wins!\n");
  } 
  else if (sum1 < sum2) {
    printf("Player 2 wins!\n");
  } 
  else{
    printf("Tie!\n");
  }
}

int calculate_letter_point(string word, int i) {
  int letter_point = 0;
  if (i >= strlen(word)) {
    return 0;
  }
  word[i] = toupper(word[i]);
  if (isalpha(word[i])) {
      int index = word[i] - 65; 
      letter_point +=LETTER_POINTS[index];
    }
  return letter_point;
} 
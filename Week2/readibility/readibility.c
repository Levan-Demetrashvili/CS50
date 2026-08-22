#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int main(void) {
  int letters_count = 0, words_count = 0, sentences_count = 0, grade = 0;
  double L = 0.00, S  = 0.00;
  string text = get_string("Text: ");
  int length = strlen(text); 
  
  // Calculate the letters, words and sentences count in given text
  for (int i = 0; i < length; i++){
    if (isalpha(text[i])) {
      if (i == 0) words_count++;
      letters_count++;
    }
    else if (text[i] == ' ') {
      words_count++;
    }
    else if(text[i] == '.' || text[i] == '?' || text[i] == '!') {
      sentences_count++;
    }
  }
  // Calculate L, S and grade
  L =  ((double) letters_count / words_count) * 100;
  S =  ((double) sentences_count / words_count) * 100;

  grade = round(0.0588 * L - 0.296 * S - 15.8);

  if (grade >= 16) {
    printf("Grade 16+\n");
  }
  else if (grade < 1) {
    printf("Before Grade 1\n");
  }
  else  {
    printf("Grade %i\n",grade);
  }
}
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);

int main(int argc, string argv[]){
  if (argc != 2 || !only_digits(argv[1])) {
    printf("Usage: ./caesar key\n");
    return 1;
  }
  int key = atoi(argv[1]);
  string plaintext = get_string("plaintext:  ");
  int len = strlen(plaintext);

  char ciphertext[len];
  
  // Encrypt the plaintext
  for (int i = 0; i < len; i++ ) {
  
    if (isalpha(plaintext[i])) {
      if (isupper(plaintext[i])){
        ciphertext[i] = 65 + ((plaintext[i] % 65 + (key % 26)) % 26);
      } else {
        ciphertext[i] = 97 + ((plaintext[i] % 97 + (key % 26)) % 26);
      }
    } else {
      ciphertext[i] = plaintext[i];
    }
  }

  // Print the ciphered text
  printf("ciphertext: ");
    for (int i = 0; i < len; i++ ) {
      printf("%c",ciphertext[i]);
    }
  printf("\n");

}


bool only_digits(string s) {
  for (int i = 0, len = strlen(s); i < len; i++ ) {
    if (!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

  
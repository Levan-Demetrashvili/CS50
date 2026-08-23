#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


bool valid_key(string key);


int main(int argc, string argv[]){
  // guard case
  if (argc != 2|| !valid_key(argv[1])) {
    printf("Usage: ./substitution key");
    return 1;
  }
  string plaintext = get_string("plaintext: ");
  int len = strlen(plaintext);
  string key = argv[1];
  char ciphertext[len];

  // Encrypt the plaintext
  for (int i = 0; i < len; i++) {
    if (!isalpha(plaintext[i])) {
      ciphertext[i] = plaintext[i];
    } else {
        ciphertext[i] = isupper(plaintext[i]) ? toupper(key[plaintext[i] % 65]) : tolower(key[plaintext[i] % 97]);
    }
  }
  // Print the ciphered text
  printf("ciphertext: ");
  for (int i = 0; i < len; i++) {
    printf("%c", ciphertext[i]);
  }
  printf("\n");

}

bool valid_key(string key) {
  char letters[26] = {0};
  int len = strlen(key);
  if (len != 26) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    if (!isalpha(key[i])) {
      return false;
    }
    // Check if key contains same letters 
    key[i] = toupper(key[i]);
    if (letters[key[i] - 65]) {
      return false;
    } else {
      letters[key[i] - 65] = key[i];
    }
  }
  return true;
}

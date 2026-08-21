#include <stdio.h>
#include <cs50.h>
#include <math.h>



int main(void){
  int index;
  int digits[16];
  int sum_of_odds = 0;
  int sum_of_products = 0;
  int sum = 0;
  int length = 1;
  long long credit_number = get_long_long("Number: "); 
  long long n = credit_number;

  while ( n / 10  > 0) {
    n /= 10;
    length++;
  }

  if (length != 13 && length != 15 && length != 16 ) {
    printf("INVALID");
    return 0;
  }
  

  for(int i = 0; i < length; i++) {
    digits[i] = (credit_number - credit_number % ((long long) pow(10,length - 1 - i))) / ((long long) pow(10,length - 1- i)) % 10;
  }  

  index = digits[0] * 10 + digits[1];

  for(int i = length; i > 0; i-=2) {
    // multiply every second digit from last
    digits[i - 2] *= 2;
    // add up every other digit
    sum_of_odds += digits[i - 1];
    // add up products
    if (digits[i - 2] / 10 != 0) {
      sum_of_products += digits[i - 2] / 10 + digits[i - 2] % 10;
    } else {
      sum_of_products += digits[i - 2];
    }
  }
  sum = sum_of_odds + sum_of_products;
  
  // Determine if card is valid and what type of card it is
  if (sum % 10 == 0) {
    if (length == 15 && (index == 34 || index == 37)) {
      printf("AMEX\n");
      return 0;
    }
    else if (length == 16 && (index >= 50 && index <= 55)) {
      printf("MASTERCARD\n");
      return 0;
    }
    else if ((length == 13 || length == 16) && index / 10 == 4) {
      printf("VISA\n");
      return 0;
    }
    else {
      printf("INVALID\n");
      return 0;
    }
  } else {
    printf("INVALID\n");
    return 0;
  }
 
}
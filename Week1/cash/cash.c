#include <stdio.h>
#include <cs50.h>

int change;
int coins = 0;

void calculate_coins(int n);

int main(void){
  do {
    change = get_int("Change owed: ");
  }  
  while (change < 0);
  // calculate each coins
  calculate_coins(25);
  calculate_coins(10);
  calculate_coins(5);
  calculate_coins(1);
  printf("%i", coins);

}

void calculate_coins(int n) {
  // calculate the minimum amount of an individual coin quantity using greedy algorithm
  while (change >= n) {
    change = change - n;
    coins++;
  }
}
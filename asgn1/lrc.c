#include <stdio.h>
#include <stdlib.h>
#include "philos.h"

// Returns the position of the player to the left
int left(int pos, int players) {
  return ((pos + players - 1) % players);
}

// Returns the position of the player to the right
int right(int pos, int players) {
  return ((pos + 1) % players);
}

int main() {
  
  // Define die faces
  typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
  faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
  
  // Get random seed from user
  int seed;
  printf("Random seed: ");
  scanf("%d", &seed);
  srand(seed);
  
  // Get number of players from user
  int players;
  printf("How many players? ");
  scanf("%d", &players);
  
  // Create player banks
  int banks[players];
  
  // Give each player $3
  for (int i = 0; i < players; i = i + 1) {
    banks[i] = 3;
  }
  
  // Initially all players are active and pot is empty
  int active = players;
  int pot = 0;

  // Starting from pos 0, cycle through all players until
  // only 1 active player remains
  for (int pos = 0;
       active > 1;
       pos = (pos == players - 1) ? 0 : pos + 1) {
    
    // Display statistics
//    printf("\n");
//    printf("pos: %d\n", pos);
//    printf("pot: %d\n", pot);
//    printf("active players: %d\n", active);
//    printf("banks: ");
//    for (int i = 0; i < players; i++) {
//      printf("%d  ", banks[i]);
//    }
//    printf("\n");
    
    // Determine how many rolls this player will get
    int rolls = (banks[pos] > 3) ? 3 : banks[pos];
        
    // If zero rolls, skip
    if (rolls != 0) { // Otherwise roll 1-3 times
      printf("%s rolls...", philosophers[pos]);
      for (int r = 0; r < rolls; r++) {
        int face = die[rand() % 6]; // Get random outcome
        if (face == PASS) { // If PASS, skip
          printf(" gets a pass");
        } else { // Otherwise, player donates
          // Take a dollar from player's bank
          banks[pos] = banks[pos] - 1;
          // If player now has 0 dollars...
          if (banks[pos] == 0) {
            // there is 1 LESS active player
            active--;
          }
          if (face == LEFT) {
            int leftpos = left(pos, players);
            // If left has 0 dollars...
            if (banks[leftpos] == 0) {
              // there is 1 MORE active player
              active++;
            }
            // Add a dollar to left's bank
            banks[leftpos]++;
            printf(" gives $1 to %s", philosophers[leftpos]);
          } else if (face == RIGHT) {
            int rightpos = right(pos, players);
            // If right has 0 dollars...
            if (banks[rightpos] == 0) {
              // there is 1 MORE active player
              active++;
            }
            // Add a dollar to right's bank
            banks[rightpos]++;
            printf(" gives $1 to %s", philosophers[rightpos]);
          } else if (face == CENTER) {
            pot++; // Add a dollar to the pot
            printf(" puts $1 in the pot");
          }
        }
      }
      printf("\n");
    }
  }
  for (int i = 0; i < players; i++) {
    if (banks[i] != 0) {
      printf("%s wins the $%d pot with $%d left in the bank!\n",
             philosophers[i], pot, banks[i]);
    }
  }
  return 0;
}

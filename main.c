#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
enum { SPOCK, SCISSORS, PAPER, ROCK, LIZARD, SHAPE_COUNT } Player, Agent;
const char *SHAPE_STRINGS[] = {"🖖", "✂️",  "️🗒️", "🪨", "🦎",
                               "🎉", "❌", "👫", "🤖"};

enum { MENU, MENU_SELECTION, GAME_SELECTION, BATTLEMODE, DONE } state = MENU;

int buff;
int you;
int youINT;
int scoreYou = 0;
int scoreAgent = 0;

int main() {

  while (true) {
    switch (state) {
    case MENU:

      printf("Welcome to");
      for (int i = 0; i < 5; i++) {
        printf(" %-4s", SHAPE_STRINGS[i]);
      }
      printf(" !\n(s) Single Player\n(e) Exit\n\nSelect path:\n");
      state = MENU_SELECTION;
      break;

    case MENU_SELECTION:

      do { // getcharjust without unwanted spaces
        buff = getchar();
      } while (buff == '\n' || buff == '\r'); //

      if (buff == 's') {
        state = GAME_SELECTION;
        printf("\nStarting game %s\n\n", SHAPE_STRINGS[5]); // THE GAME !!!

        printf("Select a weapon:\n");
        for (int i = 0; i < 5; i++) {
          printf(" %i", i);
          printf("%-4s ", SHAPE_STRINGS[i]);
        }
        printf(":\t");
        break;
      } else if (buff == 'e') {
        state = DONE;
        break;
      } else {
        puts("don't understand, select 's' or 'e'");
        state = MENU_SELECTION;
        break;
      }

    case GAME_SELECTION:

      do {               // getchar just without unwanted spaces
        you = getchar(); // read one character
      } while (you == '\n' || you == '\r');
      youINT = you - '0';

      if (youINT == 0 || youINT == 1 || youINT == 2 || youINT == 3 ||
          youINT == 4) {
        printf("\n");
        state = BATTLEMODE;
        break;

      } else {
        printf("\n %s Try a number between 0 - 4 to choose a weapon against "
               "your oppenent\n",
               SHAPE_STRINGS[6]);
        printf("\n Select a weapon:\n");
        for (int i = 0; i < 5; i++) {
          printf(" %i", i);
          printf("%-4s ", SHAPE_STRINGS[i]);
        }
        printf(":\t");
        state = GAME_SELECTION;
        break;
      }

    case BATTLEMODE:
      srand(time(NULL));

      size_t Agent = rand() % SHAPE_COUNT; // random between 0..4

      Player = youINT;

      printf("You played: %s  and the agent played: %s  => ",
             SHAPE_STRINGS[Player], SHAPE_STRINGS[Agent]);

      if (Player == Agent) {
        printf("it's a tie\n");

      } else if (((Player + 1) % SHAPE_COUNT == Agent) ||
                 ((Player + 3) % SHAPE_COUNT == Agent)) {
        printf("you won this one\n");
        scoreYou++;

      } else if (((Player + 2) % SHAPE_COUNT == Agent) ||
                 ((Player + 4) % SHAPE_COUNT == Agent)) {
        printf("agent won this one\n");
        scoreAgent++;
      }

      // SCORECOUNTER //
      printf("\n%s : %s \t %d : %d\n", SHAPE_STRINGS[7], SHAPE_STRINGS[8],
             scoreYou, scoreAgent);
      if (scoreYou == 5) {
        printf("\nWuuuuuHuuuu! YOU WON!! %s%s%s\n\n", SHAPE_STRINGS[5],
               SHAPE_STRINGS[5], SHAPE_STRINGS[5]);
        state = DONE;
        break;
        // END??
      } else if (scoreAgent == 5) {
        printf("\n YOU LOST THE GAME LOOSER 4EVER\n");
        state = DONE;
        break;
        // END??
      }

      printf("\nSelect a weapon again, first one to reach 5 points wins:\n");
      for (int i = 0; i < 5; i++) {
        printf(" %i", i);
        printf("%-4s ", SHAPE_STRINGS[i]);
      }
      printf(":\t");

      state = GAME_SELECTION;
      break;

    case DONE:

      puts("THE END ☕");
      return 0;
    }
  }
}

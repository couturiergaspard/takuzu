#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"

int main(void) {
  game g = game_default();
  if (game_is_over(g) == true) {
    printf("Congratulations\n");
    return EXIT_SUCCESS;
  }
  printf("Do you want to play on a saved game ? (y/n)\n");
  char k;
  scanf(" %c", &k);
  if (k == 'y') {
    printf("Name :");
    char name[256] = {0};
    scanf(" %s", name);
    g = game_load(name);
  }
  if (k == 'w' || k == 'b' || k == 'e') {
    int i, j;
    scanf(" %d %d", &i, &j);
    if (k == 'b') {
      if (game_check_move(g, i, j, S_ONE)) {
        game_play_move(g, i, j, S_ONE);
      }
    }
    if (k == 'w') {
      if (game_check_move(g, i, j, S_ZERO)) {
        game_play_move(g, i, j, S_ZERO);
      }
    }
    if (k == 'e') {
      if (game_check_move(g, i, j, S_EMPTY)) {
        game_play_move(g, i, j, S_EMPTY);
      }
    }
  }

  game_print(g);
  while (game_is_over(g) != true) {
    for (int i = 0; i < DEFAULT_SIZE; i++) {
      for (int j = 0; j < DEFAULT_SIZE; j++) {
        if (game_has_error(g, i, j) != 0) {
          printf("There is an error at (%u,%u)!\n", i, j);
        }
      }
    }
    printf("> [h for help]\n");
    char chr;
    scanf(" %c", &chr);
    if (chr == 's') {
      char file[256] = {0};
      printf("Save name: ");
      scanf(" %s", file);
      game_save(g, file);
      return EXIT_SUCCESS;
    }
    if (chr == 'h') {
      printf("-press 'r' to restart\n");
      printf("-press 'q' to quit\n");
      printf("-press 'w <i><j>' to put a zero/white square at (i,j)\n");
      printf("-press 'b <i><j>' to put a one/black square at (i,j)\n");
      printf("-press 'e <i><j>' to empty square at (i,j)\n");
      printf("-press 'z' to cancel the last move\n");
      printf("-press 'y' to restore the last undone move\n");
      printf("-press 's' to save the game\n");
    }
    if (chr == 'r') {
      game_restart(g);
    }
    if (chr == 'q') {
      printf("Shame !\n");
      game_delete(g);
      return EXIT_SUCCESS;
    }
    if (chr == 'z') {
      game_undo(g);
    }
    if (chr == 'y') {
      game_redo(g);
    }
    if (chr == 'w' || chr == 'b' || chr == 'e') {
      int i, j;
      scanf(" %d %d", &i, &j);
      if (chr == 'b') {
        if (game_check_move(g, i, j, S_ONE)) {
          game_play_move(g, i, j, S_ONE);
        }
      }
      if (chr == 'w') {
        if (game_check_move(g, i, j, S_ZERO)) {
          game_play_move(g, i, j, S_ZERO);
        }
      }
      if (chr == 'e') {
        if (game_check_move(g, i, j, S_EMPTY)) {
          game_play_move(g, i, j, S_EMPTY);
        }
      }
    }
    game_print(g);
    if (game_is_over(g)) {
      printf("Congratulation !\n");
      return EXIT_SUCCESS;
    }
  }
  return EXIT_SUCCESS;
}
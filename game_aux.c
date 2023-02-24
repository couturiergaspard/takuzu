#include "game_aux.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_struct.h"

/*GAME PRINT*/
void game_print(cgame g) {  // Function which print in the terminal the current
                            // state of the game
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  printf("   ");
  for (uint k = 0; k < game_nb_rows(g);
       k++) {  // printing in the terminal cols numbers
    printf("%d", k);
  }
  printf("\n");
  printf("   ");
  for (uint k = 0; k < game_nb_rows(g);
       k++) {  // printing in the terminal rows numbers
    printf("-");
  }
  printf("\n");
  for (int i = 0; i < game_nb_rows(g); i++) {  // printing the framework
    printf("%d |", i);
    for (int j = 0; j < game_nb_cols(g);
         j++) {  // printing the move played & the immutable squares
      if (game_get_square(g, i, j) == S_EMPTY)
        printf(" ");
      else if (game_get_square(g, i, j) == S_ZERO)
        printf("w");
      else if (game_get_square(g, i, j) == S_ONE)
        printf("b");
      else if (game_get_square(g, i, j) == S_IMMUTABLE_ONE)
        printf("B");
      else if (game_get_square(g, i, j) == S_IMMUTABLE_ZERO)
        printf("W");
    }
    printf("|\n");
  }
  printf("   ");
  for (uint k = 0; k < game_nb_rows(g); k++) {
    printf("-");
  }
  printf("\n");
}

/*GAME DEFAULT*/

/* ************************************************************************** */

#define SE S_EMPTY
#define S0 S_ZERO
#define S1 S_ONE
#define SI0 S_IMMUTABLE_ZERO
#define SI1 S_IMMUTABLE_ONE

/* ************************************************************************** */

static square grid_default[] = {
    SE, SI1, SI0, SE, SE,  SE,  /* row 0 */
    SE, SE,  SE,  SE, SE,  SE,  /* row 1 */
    SE, SI0, SE,  SE, SI0, SE,  /* row 2 */
    SE, SI0, SI1, SE, SE,  SE,  /* row 3 */
    SE, SE,  SI1, SE, SE,  SI0, /* row 4 */
    SE, SE,  SE,  SE, SE,  SI0, /* row 5 */
};

/* ************************************************************************** */

static square grid_default_sol[] = {
    S0, SI1, SI0, S1, S0,  S1,  /* row 0 */
    S0, S1,  S1,  S0, S1,  S0,  /* row 1 */
    S1, SI0, S0,  S1, SI0, S1,  /* row 2 */
    S1, SI0, SI1, S0, S0,  S1,  /* row 3 */
    S0, S1,  SI1, S0, S1,  SI0, /* row 4 */
    S1, S0,  S0,  S1, S1,  SI0, /* row 5 */
};

/* ************************************************************************** */

game game_default(void) { return game_new(grid_default); }

/* ************************************************************************** */

game game_default_solution(void) { return game_new(grid_default_sol); }

/* ************************************************************************** */
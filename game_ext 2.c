#include "game_ext.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_private.h"
#include "game_struct.h"
#include "queue.h"

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping,
                  bool unique) {              // Create a game
  if (nb_rows % 2 != 0 || nb_cols % 2 != 0) { /* cols & rows must be even*/
    exit(EXIT_FAILURE);
  }

  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping,
                              unique); /* empty initialisation*/

  if (g == NULL) {
    exit(EXIT_FAILURE);
  }

  if (squares == NULL) {
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < game_nb_rows(g); i++) { /* filling the game*/
    for (int j = 0; j < game_nb_cols(g); j++) {
      g->tab[i][j] = squares[i * (game_nb_rows(g)) +
                             j]; /*linear table of squares so we must use i *
                                    nbrows to reach the correct position*/
    }
  }
  return g;
}
/*GAME NEW EMPTY EXT V2 CHECK */
game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping,
                        bool unique) {        // create an empty game
  if (nb_rows % 2 != 0 || nb_cols % 2 != 0) { /* cols & rows must be even*/
    exit(EXIT_FAILURE);
  }
  game G1 =
      (game)malloc(sizeof(struct game_s)); /* memory allocation for the game*/
  if (G1 == NULL) {
    exit(EXIT_FAILURE);
  }
  G1->height = nb_rows;
  G1->width = nb_cols;

  G1->tab = (square**)malloc(
      G1->height * sizeof(square*)); /* memory allocation for the double squares
                                        table in the struct game*/
  if (G1->tab == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < G1->height; i++) {
    G1->tab[i] = (square*)malloc(G1->width * sizeof(square));
    if (G1->tab[i] == NULL) {
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < G1->width;
         j++) { /* Filling the double table with EMPTY squares*/
      G1->tab[i][j] = S_EMPTY;
    }
  }
  G1->wrapping = wrapping;
  G1->unique = unique;
  return G1;
}

/*GAME NB ROWS V2 CHECK */

uint game_nb_rows(cgame g) {  // rows getter
  if (g == NULL) {
    return EXIT_FAILURE;
  }
  return g->height;
}

/*GAME NB COLS V2 CHECK */

uint game_nb_cols(cgame g) {  // cols getter
  if (g == NULL) {
    return EXIT_FAILURE;
  }
  return g->width;
}

bool game_is_wrapping(cgame g) {  // wrapping getter
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  return g->wrapping;
}
bool game_is_unique(cgame g) {  // unique getter
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  return g->unique;
}
void game_undo(game g) {
  assert(g);
  if (_stack_is_empty(g->undo_stack)) return;
  move m = _stack_pop_move(g->undo_stack);
  game_set_square(g, m.i, m.j, m.old);
  _stack_push_move(g->redo_stack, m);
}

/* ************************************************************************** */

void game_redo(game g) {
  assert(g);
  if (_stack_is_empty(g->redo_stack)) return;
  move m = _stack_pop_move(g->redo_stack);
  game_set_square(g, m.i, m.j, m.new);
  _stack_push_move(g->undo_stack, m);
}

/* ************************************************************************** */
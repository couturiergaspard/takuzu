#include "game_tools.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"

/****************************/
int test_game_load() {
  game g = game_new_empty_ext(8, 8, true, false);
  assert(g);
  game_play_move(g, 0, 0, S_ONE);
  game_save(g, "filename");
  game c = game_load("filename");
  bool test1 = (g->wrapping == c->wrapping);
  bool test2 = (g->unique == c->unique);
  if (game_equal(g, c) && test1 && test2) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/****************************/
int test_game_save() {
  game g = game_new_empty_ext(8, 6, true, false);
  assert(g);
  game_play_move(g, 0, 0, S_ONE);
  game_save(g, "filename");
  game c = game_load("filename");
  bool test1 = (g->wrapping == c->wrapping);
  bool test2 = (g->unique == c->unique);
  if (game_equal(g, c) && test1 && test2) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/****************************/
int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "At least one argument expected !\n");
    return EXIT_FAILURE;
  }
  fprintf(stderr,
          "Starting test of : <%s>"
          "\n",
          argv[1]);
  if (strcmp("game_load", argv[1]) == 0)
    return test_game_save();

  else if (strcmp("game_save", argv[1]) == 0)
    return test_game_load();

  else {
    fprintf(stderr, "Error: Test \"%s\" not found!\n", argv[1]);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

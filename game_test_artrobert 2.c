#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

/* ********** TEST DUMMY ********** */
int test_dummy(void) { return EXIT_SUCCESS; }
/* ********** TEST GAME RESTART ********** */
int test_game_restart(void) { 
  game g1 = game_default();
  game g2 = game_default_solution();
  assert(g1);
  assert(g2);

  game_restart(g2);

  if (!game_equal(g1, g2)) {
    fprintf(stderr, "Error : game_restart didn't restarted the game\n");
    game_delete(g1);
    game_delete(g2);
    return EXIT_FAILURE;
  }
  game_delete(g1);
  game_delete(g2);
  return EXIT_SUCCESS;
}
/* ********** TEST GAME IS OVER ********** */
int test_game_is_over(void) { 
  game g = game_default();
  game g1 = game_default_solution();

  assert(g);
  assert(g1);

  bool test1 = game_is_over(g);
  bool test2 = game_is_over(g1);

  game_set_square(g1, 0, 0, S_ONE);
  game_set_square(g1, 0, 1, S_ONE);
  game_set_square(g1, 0, 2, S_ONE);

  bool test3 = game_is_over(g1);

  game_delete(g1);
  game_delete(g);

  if (test3) {
    return EXIT_FAILURE;
  }
  if (test1 == false && test2 == true && test3 == false) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
/* ********** TEST GAME PLAY MOVE ********** */
int test_game_play_move() { 
  square G1[] = {
      S_EMPTY,          S_IMMUTABLE_ONE,  S_IMMUTABLE_ZERO, S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,
      S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ZERO,
      S_IMMUTABLE_ONE,  S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ONE,  S_EMPTY,
      S_EMPTY,          S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ZERO};

  game g1 = game_new(G1);
  assert(g1);
  game_play_move(g1, 0, 0, S_ONE);
  game_play_move(g1, 0, 3, S_ZERO);
  square getG1 = game_get_square(g1, 0, 0);
  square getG2 = game_get_square(g1, 0, 3);
  if (getG1 != S_ONE || getG2 != S_ZERO) {
    fprintf(stderr, "Error : game_play_move didnt play the right move ! \n");
    game_delete(g1);
    return EXIT_FAILURE;
  }
  game_delete(g1);
  return EXIT_SUCCESS;
}
/* ********** TEST GAME CHECK MOVE ********** */
int test_game_check_move(void) {
  square G1[] = {
      S_EMPTY,          S_IMMUTABLE_ONE,  S_IMMUTABLE_ZERO, S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,
      S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ZERO,
      S_IMMUTABLE_ONE,  S_EMPTY,          S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ONE,  S_EMPTY,
      S_EMPTY,          S_IMMUTABLE_ZERO, S_EMPTY,          S_EMPTY,
      S_EMPTY,          S_EMPTY,          S_EMPTY,          S_IMMUTABLE_ZERO};

  game g1 = game_new(G1);
  assert(g1);
  bool test1 = game_check_move(g1, 0, 0, S_ZERO);
  bool test2 = game_check_move(g1, 0, 2, S_ZERO);
  bool test3 = game_check_move(g1, 0, 7, S_ZERO);

  if (test1 == true && test2 == false && test3 == false) {
    game_delete(g1);
    return EXIT_SUCCESS;
  }

  game_delete(g1);
  return EXIT_FAILURE;
}
/* ********** TEST GAME HAS ERROR ********** */
int test_game_has_error(void) {
  game g = game_default();
  assert(g);

  game_set_square(g, 1, 0, S_ONE);
  game_set_square(g, 1, 1, S_ONE);
  game_set_square(g, 1, 2, S_ONE);

  if (game_has_error(g, 1, 0) == 0 || game_has_error(g, 1, 1) == 0 ||
      game_has_error(g, 1, 2) == 0) {
    game_delete(g);
    return EXIT_FAILURE;
  }
  game_delete(g);
  game gs = game_default_solution();
  assert(gs);

  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_has_error(gs, i, j) != 0) {
        game_delete(gs);
        return EXIT_FAILURE;
      }
    }
  }
  game_delete(gs);
  return EXIT_SUCCESS;
}
/* ********** TEST GAME IS IMMUTABLE ********** */
int test_game_is_immutable(void) {
  game g = game_default();
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g, i, j) == S_IMMUTABLE_ZERO ||
          game_get_square(g, i, j) == S_IMMUTABLE_ONE) {
        if (game_is_immutable(g, i, j) == true) {
          game_delete(g);
          return EXIT_SUCCESS;
        }
      }
    }
  }
  game_delete(g);
  printf("Error : Game is Empty !");
  return EXIT_FAILURE;
}
/* ********** TEST GAME IS EMPTY ********** */
int test_game_is_empty(void) {
  game g = game_default();
  assert(g);
  game_set_square(g, 0, 0, S_ONE);
  game_set_square(g, 1, 4, S_ZERO);

  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_is_empty(g, i, j) && game_get_square(g, i, j) != S_EMPTY) {
        game_delete(g);
        return EXIT_FAILURE;
      }
      if (!game_is_empty(g, i, j) && game_get_square(g, i, j) == S_EMPTY) {
        game_delete(g);
        return EXIT_FAILURE;
      }
    }
  }

  game_delete(g);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "At least one argument expected !\n");
    return EXIT_FAILURE;
  }
  fprintf(stderr,
          "Starting test of : <%s>"
          "\n",
          argv[1]);
  if (strcmp("dummy", argv[1]) == 0)
    return test_dummy();

  else if (strcmp("game_restart", argv[1]) == 0)
    return test_game_restart();

  else if (strcmp("game_is_over", argv[1]) == 0)
    return test_game_is_over();

  else if (strcmp("game_play_move", argv[1]) == 0)
    return test_game_play_move();

  else if (strcmp("game_check_move", argv[1]) == 0)
    return test_game_check_move();

  else if (strcmp("game_has_error", argv[1]) == 0)
    return test_game_has_error();

  else if (strcmp("game_is_immutable", argv[1]) == 0)
    return test_game_is_immutable();

  else if (strcmp("game_is_empty", argv[1]) == 0)
    return test_game_is_empty();

  return EXIT_SUCCESS;
}

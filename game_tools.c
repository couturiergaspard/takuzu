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

// Utiliser fprintf fgetc fscanf

/*******************************/
game game_load(char* filename) {
  if (!filename) {
    exit(EXIT_FAILURE);
  }
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }
  int wrap = 0;
  int uniq = 0;
  int height = 0;
  int width = 0;
  int ret =
      fscanf(file, "%d %d %d %d", &height, &width, &wrap, &uniq); /* \n ???*/
  assert(ret == 4);
  assert(height > 0);
  assert(width > 0);
  assert(wrap == 0 || wrap == 1);
  assert(uniq == 0 || uniq == 1);

  game g = game_new_empty_ext((uint)height, (uint)width, wrap, uniq);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      char c;
      fscanf(file, " %c", &c);
      if (c == '\n') {
        fgetc(file);
      }
      switch (c) {
        case 'b':
          g->tab[i][j] = S_ONE;
          break;
        case 'w':
          g->tab[i][j] = S_ZERO;
          break;
        case 'W':
          g->tab[i][j] = S_IMMUTABLE_ZERO;
          break;
        case 'B':
          g->tab[i][j] = S_IMMUTABLE_ONE;
          break;
        case 'e':
          g->tab[i][j] = S_EMPTY;
          break;
        default:
          break;
      }
    }
  }
  fclose(file);
  return g;
}

/*******************************/
void game_save(cgame g, char* filename) {
  if (!g || !filename) {
    exit(EXIT_FAILURE);
  }
  FILE* file = fopen(filename, "w");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }
  fprintf(file, "%d %d %d %d\n", g->height, g->width, g->wrapping, g->unique);
  for (int i = 0; i < g->height; i++) {
    for (int j = 0; j < g->width; j++) {
      switch (g->tab[i][j]) {
        case S_ONE:
          fprintf(file, "b");
          break;
        case S_ZERO:
          fprintf(file, "w");
          break;
        case S_IMMUTABLE_ZERO:
          fprintf(file, "W");
          break;
        case S_IMMUTABLE_ONE:
          fprintf(file, "B");
          break;
        case S_EMPTY:
          fprintf(file, "e");
          break;
        default:
          exit(EXIT_FAILURE);
          break;
      }
    }
    fprintf(file, "\n");
  }
  fclose(file);
}
/*******************************/
bool game_solve(game g) {
  assert(g);
  int pos = 0;
  int len = g->nb_cols * g->nb_rows;
  square word[len];
  for (int i = 0; i < g->nb_rows; i++) {
    for (int j = 0; j < g->nb_cols; j++) {
      word[i * g->nb_cols + j] = g->tab[i][j];
    }
  }
  game_solve_rec(len, pos, word, g);
  return;
}

void game_solve_rec(int len, int pos, square* word, game g) {
  if (word[pos] != S_EMPTY) {
    game_solve_rec(len, pos + 1, word, g);
  }
  if (pos == len) {
    game g1 =
        game_new_ext(g->nb_rows, g->nb_cols, word, g->wrapping, g->unique);
    if (game_is_over(g1)) {
      return;
    }
    return;
  }
  word[pos] = S_ONE;
  game_solve_rec(len, pos + 1, word, g);

  word[pos] = S_ZERO;
  game_solve_rec(len, pos + 1, word, g);
}

/*******************************/
uint game_nb_solutions(cgame g) {
  assert(g);
  int pos = 0;
  int len = g->nb_cols * g->nb_rows;
  square word[len];
  for (int i = 0; i < g->nb_rows; i++) {
    for (int j = 0; j < g->nb_cols; j++) {
      word[i * g->nb_cols + j] = g->tab[i][j];
    }
  }
  unsigned long count = 0;
  game_nb_solutions_rec(len, pos, &count, word, g);
  return count;
}

void game_nb_solutions_rec(int len, int pos, unsigned long* count, square* word,
                           game g) {
  if (word[pos] != S_EMPTY) {
    game_nb_solutions_rec(len, pos + 1, count, word, g);
  }

  if (pos == len) {
    game g1 =
        game_new_ext(g->nb_rows, g->nb_cols, word, g->wrapping, g->unique);
    if (game_is_over(g1)) {
      (*count)++;
    }
    return;
  }
  word[pos] = S_ONE;
  game_nb_solutions_rec(len, pos + 1, count, word, g);

  word[pos] = S_ZERO;
  game_nb_solutions_rec(len, pos + 1, count, word, g);
}

#include "game_tools.h"

#include <assert.h>
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
      if (c == '\n'){
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
bool game_solve(game g){


}

/*******************************/
uint game_nb_solutions(cgame g){

  
}
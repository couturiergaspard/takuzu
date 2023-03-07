#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_tools.h"

int main(int argc, char* argv[]) {
  if (argc != 4 && argc != 3) {
    fprintf(stderr,
            "Not enought parameter! Please write : ./game_solve <-s or -c> "
            "<filename> <filename>\n");
    exit(EXIT_FAILURE);
  }
  char* c = argv[1];  // Option que l'on veut implémenter
  char* v = argv[2];  // Nom du fichier que l'on veut résoudre ou compter le
                      // nombre de solution
  char* b =
      argv[3];  // Nom du fichier dans lequel on veut sauvegarder la solution

  if (c == "-c") {
    uint c = game_nb_solutions(game_load(v));
  } else if (c == "-s") {
    game_solve(game_load(v));
  } else {
    fprintf(stderr, "Not good option, only -s or -c");
    exit(EXIT_FAILURE);
  }
}
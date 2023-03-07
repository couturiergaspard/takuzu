#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "queue.h"

typedef struct game_s {
  uint height;
  uint width;
  uint nb_rows;
  uint nb_cols;
  square** tab;
  bool wrapping;
  bool unique;
  queue* undo_stack; 
  queue* redo_stack;
} game_s;

#endif  // __GAME_STRUCT_H__
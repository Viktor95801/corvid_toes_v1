#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include "board.h"
#include <stdbool.h>

uint16_t occupied(board b);

typedef struct {
    move* moves;
    uint8_t count;
    bool error;
} move_list;

move_list valid_moves(board b);
move gen_move(uint8_t square, bool side, board b);


#endif // MOVE_GEN_H
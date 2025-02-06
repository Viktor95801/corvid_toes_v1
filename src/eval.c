#include "board.h"
#include "move_gen.h"

// external
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

int8_t evaluate(board b, bool side) {
    for (uint8_t i = 0; i < 8; i++) {
        if ((b.x & win_pos[i]) == win_pos[i]) { // X wins
            return side ? 10 : -10;
        }
        if ((b.o & win_pos[i]) == win_pos[i]) { // O wins
            return side ? -10 : 10;
        }
    }
    move_list ml = valid_moves(b); // Check draw condition
    int8_t eval = (ml.count == 0) ? 0 : ((ml.error) ? -127 : 0) ; // draw
    free(ml.moves); // Free the moves inside ml!
    return eval;
}
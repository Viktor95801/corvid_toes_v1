#include "board.h"
#include "move_gen.h"

// external

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t occupied(board b) {
    return b.x | b.o;
}

move gen_move(uint8_t square, bool side, board b) {
    if (~occupied(b) & (1 << square)) {
        move m = {side, square};
        return m;
    }
    printf("Invalid move");
    return (move){0,0,1};
}

move_list valid_moves(board b) {
    uint16_t occ = occupied(b);
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++) {
        if (!(occ & (1 << i))) {
            count++;
        }
    }
    move* moves = (move*)malloc(count * sizeof(move));
    if (moves == NULL) {
        fprintf(stderr, "Memory allocation failed in valid_moves!\n");
        return (move_list){NULL, 0, 1};
    }
    uint8_t k = 0;
    for (uint8_t i = 0; i < 9; i++) {
        if (!(occ & (1 << i))) {
            moves[k++] = gen_move(i, side, b);
        }
    }

    return (move_list){moves, count, 0};
};

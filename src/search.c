#include "board.h"
#include "move_gen.h"
#include "eval.h"

//external
#include <stdint.h>
#include <limits.h> // For INT_MIN and INT_MAX
#include <stdio.h>
#include <stdlib.h>



int8_t negaMax(int8_t depth, board b, move* to_make) {
    if (depth == 0) {
        return evaluate(b, side);
    }

    move_list moves = valid_moves(b);
    if (moves.error) {
        fprintf(stderr, "Memory allocation failed in negaMax!\n");
        exit(1); 
    }

    int8_t best_score = -128;
    move best_move = {0, 0, 1}; 

    for (uint8_t i = 0; i < moves.count; i++) {
        move m = moves.moves[i];


        make_move(&m, &b);  
        int8_t score = -negaMax(depth - 1, b, NULL);

        unmake_move(m, &b);


        if (score > best_score) {
            best_score = score;
            best_move = m;
            if (to_make != NULL) {
                *to_make = m;
            }
        }
    }

    free(moves.moves);
    return best_score;
}

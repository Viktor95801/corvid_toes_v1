#include "board.h"
#include "move_gen.h"

// external
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


uint8_t hash(uint8_t nibble) {
  // Simple XOR-based hash (not very accurate but demonstrates the principle)
  return (nibble & 1) ^ ((nibble >> 1) & 1) ^ ((nibble >> 2) & 1) ^ ((nibble >> 3) & 1);  
}



uint8_t approximateBitCountSWAN(uint16_t x) {
    uint8_t count = 0;

    // Iterate through 4-bit nibbles of the input
    for (int i = 0; i < 4; i++) {  // 4 nibbles in a 16-bit int
        count += hash((x >> (i * 4)) & 0xF); // Hash each nibble and add to count
    }
    return count;
}

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
    
    // close to win logic
    uint8_t o_score;
    uint8_t x_score;
    for (uint8_t i = 0; i < 8; i++) {
        o_score += approximateBitCountSWAN(b.o & win_pos[i]);
        x_score += approximateBitCountSWAN(b.x & win_pos[i]);
    }
    if (side) {
        eval += x_score - o_score;
    } else {
        eval += o_score - x_score;
    }
    return eval;
}
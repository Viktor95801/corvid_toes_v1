#include "board.h"

// external

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

bool side = 0;

uint16_t mask_nine_bit_int(unsigned short val) {
    return val & 0x1FF; // 0x1FF is a mask for the lower 9 bits
}

uint16_t win_pos[8];
void cache_win_pos() {
    win_pos[0] = 0b111000000;
    win_pos[1] = 0b000111000;
    win_pos[2] = 0b000000111;
    win_pos[3] = 0b100100100;
    win_pos[4] = 0b010010010;
    win_pos[5] = 0b001001001;
    win_pos[6] = 0b100010001;
    win_pos[7] = 0b001010100;
}

void make_move(move m, board* b) {
    if (m.side) { // if side is true then X moves. Update X's position
        b->x |= (1 << m.square);
    } else { // side is false then O moves. update O's position.
        b->o |= (1 << m.square);
    }
    side = !side;  // Toggle the side *after* making the move!!!
    return;
}

void unmake_move(move m, board* b) {
    if (m.side) {
        b->x &= ~(1 << m.square);
    } else {
        b->o &= ~(1 << m.square);
    }
    side = !side;
    return;
}

void print_board(const board *b) {
    char symbols[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    // Fill in the symbols based on the board's bitmask representation
    for (int i = 0; i < 9; i++) {
        if ((b->x & (1 << i))) {
            symbols[i] = 'X';
        } else if ((b->o & (1 << i))) {
            symbols[i] = 'O';
        }
    }

    // Print the board
    printf("   1   2   3\n");
    printf("A  %c | %c | %c \n", symbols[A1], symbols[A2], symbols[A3]);
    printf("  ---+---+---\n");
    printf("B  %c | %c | %c \n", symbols[B1], symbols[B2], symbols[B3]);
    printf("  ---+---+---\n");
    printf("C  %c | %c | %c \n", symbols[C1], symbols[C2], symbols[C3]);
}


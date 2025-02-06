#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>

uint16_t mask_nine_bit_int(unsigned short val);

enum squares {
    A1, A2, A3,
    B1, B2, B3,
    C1, C2, C3
};

typedef struct {
    uint16_t o;
    uint16_t x;
} board;
typedef struct {
    bool side;
    uint8_t square;
    bool invalid;
} move;


void make_move(move* m, board* b);
void unmake_move(move m, board* b);
bool side;

void print_board(const board *b);

uint16_t win_pos[8];
void cache_win_pos();


#endif // BOARD_H
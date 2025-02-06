#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"

uint8_t negaMax(uint8_t depth, board b, move* to_make); // to_make is edited in order to give the answer

#endif // SEARCH_H
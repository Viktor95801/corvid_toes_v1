#include "board.h"
#include "move_gen.h"
#include "eval.h"
#include "search.h"
#include "corvid_toes.h"

// external

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool user_side() {
    char input[255];
    while (true) {
        printf("Do you want to go first? (y/n, 'q' to quit): ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            exit(1);
        }
        input[strcspn(input, "\n")] = 0; // Remove trailing newline
        
        if (strlen(input) != 1) {
            printf("Invalid input. Please enter 'y' or 'n'.");
            continue;
        }

        if (strcmp(input, "q") == 0) {
            exit(0);
        }

        if (input[0] == 'y') {
            return true;
        } else if (input[0] == 'n') {
            return false;
        } else {
            printf("Invalid input. Please enter 'y' or 'n'.");
        }
    }
}
move user_input(board b) {
    char input[255];
    move m = {0, 0, 1}; // Initialize to an invalid move

    while (true) {
        printf("Enter your move (e.g., A1, B2, or 'q' to quit): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            exit(1);
        }
        input[strcspn(input, "\n")] = 0; // Remove trailing newline

        if (strcmp(input, "q") == 0) {
            exit(0);
        }

        if (strlen(input) != 2) {
            printf("Invalid input format. Please use A1, B2, etc.\n");
            continue;
        }

        char row = input[0];
        char col = input[1];

        if (row < 'A' || row > 'C' || col < '1' || col > '3') {
            printf("Invalid input. Please enter a valid square (A1-C3).\n");
            continue;
        }

        int square = (row - 'A') * 3 + (col - '1');

        move_list valid_moves_list = valid_moves(b); // Get valid moves
        bool is_valid = false;
        for (int i = 0; i < valid_moves_list.count; i++) {
            if (valid_moves_list.moves[i].square == square) {
                m = valid_moves_list.moves[i];    // Use the generated move!!!
                is_valid = true;
                break;
            }
        }
        free(valid_moves_list.moves); // Free allocated memory!

        if (!is_valid) {
            printf("Invalid move. Square already occupied.\n");
        } else {
            break; // Only break if valid
        }
    }

    return m;
}


int main () {
    bool end = false;
    board b;
    b.o = 0;
    b.x = 0;
    cache_win_pos();
    bool who_play_first = user_side();
    move m;

    if (!who_play_first) {
        m = gen_move(B2, side, b);
        if (m.invalid) {
            fprintf(stderr, "Internal error.\n");
            exit(1);
        }
        make_move(&m, &b);
        print_board(&b);
    }
    while (end == false) {
        // end conditions
        move_list moves = valid_moves(b);
        if (moves.count == 0) {
            printf("Draw!\n");
            end = true;
            break;
        }
        free(moves.moves);
        
        for (uint8_t i = 0; i < 8; i++) {
            if ((b.x & win_pos[i]) == win_pos[i]) {
                printf("X wins!\n");
                end = true;
                break;
            } else if ((b.o & win_pos[i] == win_pos[i])) {
                printf("O wins!\n");
                end = true;
                break;
            }
        }

        // User logic

        print_board(&b);
        m = user_input(b);
        make_move(&m, &b);
/*         m.side = !m.side; */

        // AI logic
        
        negaMax(7, b, &m);
        make_move(&m, &b);
/*         m.side = !m.side; */
        print_board(&b);

    }
    return 0;
}

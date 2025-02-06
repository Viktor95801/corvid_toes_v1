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


int main(){
    cache_win_pos();
    board b = {0, 0};
    print_board(&b);

    bool end = false; 

    while (!end) {
        move_list moves; 
        move current_move;

        if (side) {
            current_move = user_input(b);
            make_move(current_move, &b);
            print_board(&b); 
        } else { // AI's turn
            moves = valid_moves(b);
            //Check for errors or draws *before* making a move
            if (moves.error) {
                fprintf(stderr, "Error generating moves\n");
                return 1;
            } else if (moves.count == 0) {
                printf("Draw!\n");
                end = true; // Game ends in a draw
            } else {
                negaMax(7, b, &current_move);
                make_move(current_move, &b);
                print_board(&b);


                // Check for AI win *immediately* after AI moves.
                for (uint8_t j = 0; j < 8; j++) {
                    if ((b.x & win_pos[j]) == win_pos[j]) {
                        printf("X wins\n");
                        end = true;
                        break;
                    }
                    if ((b.o & win_pos[j]) == win_pos[j]) {
                        printf("O wins\n");
                        end = true;
                        break;
                    }
                }
            }


            if (moves.moves != NULL) {        
                free(moves.moves);
            }
        }


    }

    return 0;
}


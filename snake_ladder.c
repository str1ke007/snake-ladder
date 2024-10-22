#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100
#define MAX_BIG_SNAKES 3
#define MAX_SMALL_SNAKES 2
#define MAX_BIG_LADDERS 2
#define MAX_SMALL_LADDERS 2

// ANSI color codes
#define RESET       "\033[0m"
#define RED         "\033[31m"   // Red for snakes
#define GREEN       "\033[32m"   // Green for ladders
#define BLUE        "\033[34m"   // Blue for P1
#define YELLOW      "\033[33m"   // Yellow for P2 (Computer or Player 2)
#define CLEAR_SCREEN() printf("\033[H\033[J")  // Clear the console screen

// Structure for snakes and ladders
typedef struct {
    int start;
    int end;
} Jump;

Jump snakes[MAX_BIG_SNAKES + MAX_SMALL_SNAKES];
Jump ladders[MAX_BIG_LADDERS + MAX_SMALL_LADDERS];

// Random number generator for dice roll
int roll_dice() {
    return rand() % 6 + 1;
}

// Initialize snakes and ladders with the specified constraints
void init_board() {
    // Big ladders: 1-10 to 50-60
    for (int i = 0; i < MAX_BIG_LADDERS; i++) {
        ladders[i].start = rand() % 10 + 1;
        ladders[i].end = rand() % 11 + 50;  // Between 50-60
    }

    // Small ladders: 80-90 to 90-99
    for (int i = MAX_BIG_LADDERS; i < MAX_BIG_LADDERS + MAX_SMALL_LADDERS; i++) {
        ladders[i].start = rand() % 11 + 80;  // Between 80-90
        ladders[i].end = rand() % 10 + 90;    // Between 90-99
    }

    // Big snakes:
    // - 50-60 to 1-10
    // - 70-80 to 10-20
    // - 90-99 to 20-30
    snakes[0].start = rand() % 11 + 50;  // Between 50-60
    snakes[0].end = rand() % 10 + 1;     // Between 1-10

    snakes[1].start = rand() % 11 + 70;  // Between 70-80
    snakes[1].end = rand() % 11 + 10;    // Between 10-20

    snakes[2].start = rand() % 10 + 90;  // Between 90-99
    snakes[2].end = rand() % 11 + 20;    // Between 20-30

    // Small snakes:
    // - 99-90 to 80-91
    // - 61-70 to 51-60
    snakes[3].start = rand() % 10 + 90;  // Between 90-99
    snakes[3].end = rand() % 11 + 80;    // Between 80-91

    snakes[4].start = rand() % 10 + 61;  // Between 61-70
    snakes[4].end = rand() % 10 + 51;    // Between 51-60
}

// Display the board with colors for players, snakes, and ladders
void display_board(int player1_pos, int player2_pos) {
    for (int row = 9; row >= 0; row--) {
        if (row % 2 == 0) {  // Even row (left to right)
            for (int col = 1; col <= 10; col++) {
                int pos = row * 10 + col;
                int is_snake = 0, is_ladder = 0;

                // Check if current position is a snake head or ladder start
                for (int j = 0; j < MAX_BIG_SNAKES + MAX_SMALL_SNAKES; j++) {
                    if (snakes[j].start == pos) {
                        printf(RED "S " RESET);
                        is_snake = 1;
                        break;
                    }
                }

                for (int j = 0; j < MAX_BIG_LADDERS + MAX_SMALL_LADDERS; j++) {
                    if (ladders[j].start == pos) {
                        printf(GREEN "L " RESET);
                        is_ladder = 1;
                        break;
                    }
                }

                // Display player positions
                if (!is_snake && !is_ladder) {
                    if (pos == player1_pos && pos == player2_pos)
                        printf(BLUE "P1" RESET YELLOW "P2 " RESET);  // Both players on the same spot
                    else if (pos == player1_pos)
                        printf(BLUE "P1 " RESET);  // Player 1
                    else if (pos == player2_pos)
                        printf(YELLOW "P2 " RESET);  // Player 2
                    else
                        printf("%2d ", pos);
                }
            }
        } else {  // Odd row (right to left)
            for (int col = 10; col >= 1; col--) {
                int pos = row * 10 + col;
                int is_snake = 0, is_ladder = 0;

                for (int j = 0; j < MAX_BIG_SNAKES + MAX_SMALL_SNAKES; j++) {
                    if (snakes[j].start == pos) {
                        printf(RED "S " RESET);
                        is_snake = 1;
                        break;
                    }
                }

                for (int j = 0; j < MAX_BIG_LADDERS + MAX_SMALL_LADDERS; j++) {
                    if (ladders[j].start == pos) {
                        printf(GREEN "L " RESET);
                        is_ladder = 1;
                        break;
                    }
                }

                if (!is_snake && !is_ladder) {
                    if (pos == player1_pos && pos == player2_pos)
                        printf(BLUE "P1" RESET YELLOW "P2 " RESET);  // Both players on the same spot
                    else if (pos == player1_pos)
                        printf(BLUE "P1 " RESET);  // Player 1
                    else if (pos == player2_pos)
                        printf(YELLOW "P2 " RESET);  // Player 2
                    else
                        printf("%2d ", pos);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Check for snake or ladder at current position
int check_position(int position) {
    for (int i = 0; i < MAX_BIG_SNAKES + MAX_SMALL_SNAKES; i++) {
        if (snakes[i].start == position) {
            printf(RED "Oops! Snake from %d to %d.\n" RESET, position, snakes[i].end);
            return snakes[i].end;
        }
    }
    for (int i = 0; i < MAX_BIG_LADDERS + MAX_SMALL_LADDERS; i++) {
        if (ladders[i].start == position) {
            printf(GREEN "Yay! Ladder from %d to %d.\n" RESET, position, ladders[i].end);
            return ladders[i].end;
        }
    }
    return position;
}

// Function to wait for dice roll input from player
void wait_for_roll() {
    printf("Press Enter to roll the dice...");
    while (getchar() != '\n');  // Wait for Enter key press
}

// Play turn for a human player
int play_turn(int current_position, int player_num) {
    wait_for_roll();
    int dice_roll = roll_dice();
    printf("Player %d rolled a %d.\n", player_num, dice_roll);
    current_position += dice_roll;

    if (current_position > BOARD_SIZE)
        return current_position - dice_roll;  // Avoid overshooting

    return check_position(current_position);
}

// Play turn for the computer
int play_computer_turn(int current_position) {
    int dice_roll = roll_dice();
    printf("Computer rolled a %d.\n", dice_roll);
    current_position += dice_roll;

    if (current_position > BOARD_SIZE)
        return current_position - dice_roll;  // Avoid overshooting

    return check_position(current_position);
}

// Menu to select game mode
int show_menu() {
    int choice;
    printf("Choose game mode:\n");
    printf("1. Play against another Player\n");
    printf("2. Play against Computer\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // Clear the newline from the input buffer
    return choice;
}

int main() {
    srand(time(0));

    int player1_pos = 1, player2_pos = 1;
    int game_mode = show_menu();

    init_board();  // Initialize snakes and ladders

    while (player1_pos < BOARD_SIZE && player2_pos < BOARD_SIZE) {
        CLEAR_SCREEN();
        display_board(player1_pos, player2_pos);

        // Player 1 turn
        printf(BLUE "Player 1's turn.\n" RESET);
        player1_pos = play_turn(player1_pos, 1);
        if (player1_pos >= BOARD_SIZE) {
            printf(BLUE "Player 1 wins!\n" RESET);
            break;
        }

        // Player 2 or Computer turn
        printf(YELLOW "Player 2's turn.\n" RESET);
        if (game_mode == 1) {  // Player vs Player
            player2_pos = play_turn(player2_pos, 2);
        } else {  // Player vs Computer
            player2_pos = play_computer_turn(player2_pos);
        }
        if (player2_pos >= BOARD_SIZE) {
            printf(YELLOW "Player 2 wins!\n" RESET);
            break;
        }
        sleep(2);
    }

    return 0;
}

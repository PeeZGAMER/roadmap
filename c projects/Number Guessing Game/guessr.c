#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// structure to combat redefenition of variables
struct GameState
{
    int userGuess;
    int currentGuessCount;
    int maxGuesses;
};

void mainGame(); // declare the main game function
void clearInputBuffer(); // function to combat repetitive loops
char playerName[50];

int timer;

int main()
{
    // When the game starts, it should display a welcome message along with the rules of the game.
    printf("Insert your name: ");
    scanf("%[^\n]", playerName);
    clearInputBuffer();

    printf("\nWelcome to Guessr %s! I'm thinking of a number between 1 and 100.\n", playerName);

    srand(time(NULL));
    while (true)
    {
        mainGame();
        printf("Want to play again? (Yes = 1, No = 2)\nType your answer: ");
        int playAgain;
        while (scanf("%d", &playAgain) != 1 || (playAgain < 1 || playAgain > 2))
        {
            printf("\nInvalid input. Please enter 1 to play again or 2 to quit.\nType your answer: ");
            clearInputBuffer();
        }
        if (playAgain != 1)
        {
            printf("\nThank you for playing %s!\n", playerName);
            break; // exit game loop and end the program
        }
    }
    return 0;
}

void mainGame(void)
{ // define the main game function

    /* The computer should randomly select a number between 1 and 100
    User should select the difficulty level (easy, medium, hard) which will determine the number of chances they get to guess the number. */
    int randomNum;
    randomNum = rand() % 100 + 1;
    // printf("%d\n", randomNum); // Line to check what the answer will be (cheat)
    int difficultyChoice;
    printf("\nWhat difficulty will you choose for this round %s? (easy = 1, medium = 2, hard = 3)\nEnter your choice: ", playerName);
    while (scanf("%d", &difficultyChoice) != 1 || (difficultyChoice < 1 || difficultyChoice > 3))
    {
        printf("\nInvalid input. Please enter a number between 1 and 3.\nEnter your choice: ");
        clearInputBuffer();
    }

    struct GameState playerChoice;

    // switch case to determine the difficulty of the game
    switch (difficultyChoice)
    {
    case 1:
        playerChoice.maxGuesses = 10;
        printf("\nYou chose the easy difficulty, so you will get %d guesses\nLet's start the game!\n\n", playerChoice.maxGuesses);
        break;

    case 2:
        playerChoice.maxGuesses = 5;
        printf("\nYou chose the medium difficulty, so you will get %d guesses\nLet's start the game!\n\n", playerChoice.maxGuesses);
        break;

    case 3:
        playerChoice.maxGuesses = 3;
        printf("\nYou chose the hard difficulty, so you will get %d guesses\nLet's start the game!\n\n", playerChoice.maxGuesses);
        break;

    default:
        printf("\nPlease enter a number between 1 and 3\n");
        break;
    }

    playerChoice.currentGuessCount = 0;
    bool numberGuessed = false;
    // main game loop without using redundant function calls
    while (playerChoice.currentGuessCount < playerChoice.maxGuesses)
    {
        printf("Enter your guess: ");
        while (scanf("%d", &playerChoice.userGuess) != 1 || (playerChoice.userGuess < 1 || playerChoice.userGuess > 100))
        {
            printf("\nInvalid input. Please enter a number between 1 and 100\n");
            clearInputBuffer();
        }

        playerChoice.currentGuessCount++;


        // If the user’s guess is correct, the game should display a congratulatory message along with the number of attempts it took to guess the number.
        if (playerChoice.userGuess == randomNum)
        {
            printf("Congrats! You've guessed the right number. It took you %d tries.\n\n", playerChoice.currentGuessCount);
            numberGuessed = true; // if the number is guessed, set the boolean to true
            break;
        }
        // If the user’s guess is incorrect, the game should display a message indicating whether the number is greater or less than the user’s guess.
        else if (playerChoice.userGuess > randomNum)
        {
            printf("\nWomp womp. The number is less than %d\n", playerChoice.userGuess);
        }
        else if (playerChoice.userGuess < randomNum)
        {
            printf("\nWomp womp. The number is greater than %d\n", playerChoice.userGuess);
        }
        printf("You have %d guesses left\n\n", playerChoice.maxGuesses - playerChoice.currentGuessCount);
    }

    // when the currentGuessCount reaches 0, tell the user what the correct number should have been
    if (!numberGuessed)
    {
        printf("GAME OVER! The correct answer was %d\nYou have no more guesses left... ", randomNum);
    }
}

void clearInputBuffer() {
    while(getchar() != '\n');
}
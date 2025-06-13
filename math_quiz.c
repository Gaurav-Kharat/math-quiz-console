
/*  Title: Console based Timed Math Quiz
    Description: This C program runs a multiple choice math quiz in the console.
    Each question has a 45 second time limit with a beep warning at 10 seconds.
    The program evaluates answers in real time and shows a visual summary at the end.
    Author: Gaurav Chandrakant Kharat   */

#include <stdio.h>      // For standard input/output functions
#include <string.h>     // For string operations like  strcmp,strlwr etc.
#include <windows.h>    // For Windows specific functions like system() and Beep()
#include <conio.h>      // For _kbhit() to detect keypress
#include <time.h>       // For handling time functions like time()

// Text formatting for console output using ANSI escape codes
#define BOLD_GREEN "\033[1;32m"
#define BOLD_RED   "\033[1;31m"
#define BOLD_WHITE "\033[1;37m"
#define RESET      "\033[0m"
#define COLOR_TITLE        "\033[1;96m"
#define COLOR_INSTRUCTION  "\033[1;34m"
#define COLOR_QUESTION     "\033[1;36m"
#define COLOR_INPUT_PROMPT "\033[0;37m"
#define COLOR_TIMER  "\033[1;91m"
#define COLOR_CONGRATES "\033[1;92m"

// Emits a single beep sound to alert the user (used as a timer warning)
int beep_once()
{
    Beep(1000,500);
    return 0;
}

int ask_question(const char *question, const char *correct_option) 
{
    time_t start_time = time(NULL);  // Record the starting time
    int beeped = 0;             //Flag used to beep only one time
    char answer[2] ;       //  store the user's input
    int TOTAL_TIME = 45;         // Time limit per question in seconds

    printf(COLOR_QUESTION"\n%s"RESET, question);     // Print the question and options

    // Main loop to display timer and check user input
    while (1) 
    {
        // Calculate the time left for answering the question
        time_t current_time = time(NULL);
        double time_passed = difftime(current_time, start_time);
        double time_left = TOTAL_TIME-time_passed;

        // Display countdown timer (overwriting the same line)
        printf(COLOR_TIMER"\r Time left: %.0f seconds "RESET, time_left);
        fflush(stdout);  // Force output to appear immediately

        // Play beep sound once when 10 seconds left
        if (time_left <= 10 && beeped == 0) 
        {
            beep_once();
            beeped = 1;
        }

        // If time runs out, auto-submit and return 0 (wrong)
        if (time_left <= 0) 
        {
            printf("\n\n Time's up! " BOLD_RED "No answer given.\n" RESET);
            printf(BOLD_RED "✗ Wrong" BOLD_GREEN" correct option is " BOLD_WHITE "%s\n\n" RESET, correct_option);
            return 0;
        }

        // If a key has been pressed, read the input
        if (_kbhit()) {
            printf(COLOR_INPUT_PROMPT"\nYour answer:"RESET);
            scanf("%s", answer);  // Read users answer

            // Convert  input to lowercase for case insensitive comparison
            strlwr(answer);

            // Compare  answer to correct option 
            if (strcmp(answer,correct_option)==0) 
            {
                printf(BOLD_GREEN "\nCorrect ✓\n\n" RESET);
                return 1;
            } 
            else 
            {
                printf(BOLD_RED "\n✗ Wrong" BOLD_GREEN " correct option is " BOLD_WHITE "%s\n\n" RESET, correct_option);
                return 0;
            }
        }

        
    }
}

int main()
{
    int sum=0;
    char start[10];
    system("chcp 65001");   // Set code page to UTF-8 to properly display special characters 
    clearscreen:
    {
        system("cls");    // Clear the console screen
    } 
    printf(COLOR_TITLE"INSTRUCTIONS:-\n"COLOR_INSTRUCTION"\n-This quiz is based on mathematics."COLOR_INSTRUCTION"\n-There are total 5 questions each for one mark."COLOR_INSTRUCTION"\n-There are 45 seconds for one question after 45 seconds question will be submited automatically and it will be cosiderd as wrong."COLOR_INSTRUCTION"\n-A beep sound will be emitted as an alert when 10 seconds are remaining."RESET);  // Display quiz instructions to the user
    printf(COLOR_TITLE"\n\nDo you want to start a quiz ?(yes/no) :"RESET);  // Ask user whether they want to start the quiz
    scanf("%s",start);
    strlwr(start); 
    if(strcmp(start,"yes")==0 )
    {
        
        // Asking all 5 quiz questions one by one
        
        sum+= ask_question
        (
            "1. What is the Simple Interest on ₹1000 at 5%% per annum for 2 years?\n"
            "a) ₹50\n"
            "b) ₹100\n"
            "c) ₹150\n"
            "d) ₹200\n\n",
            "b"
        );

    sum+= ask_question
        (
            "2. If 2x + 3 = 11, what is the value of x?\n"
            "a) 3\n"
            "b) 4\n"
            "c) 5\n"
            "d) 6\n\n",
            "b"
        );

    sum+= ask_question
        (
            "3. What is the area of a circle with radius 7 cm? (Use π = 22/7)\n"
            "a) 144 cm²\n"
            "b) 154 cm²\n"
            "c) 164 cm²\n"
            "d) 176 cm²\n\n",
            "b"
        );

    sum+= ask_question
        (
            "4. What is the square root of 144?\n"
            "a) 10\n"
            "b) 11\n"
            "c) 12\n"
            "d) 13\n\n",
            "c"
        );

    sum+= ask_question
        (
            "5. 20%% of 250 is:\n"
            "a) 50\n"
            "b) 55\n"
            "c) 60\n"
            "d) 65\n\n",
            "a"
        );
    }
    else
    {
        goto clearscreen;
    }

    // Display final score, summary, and performance graph
    printf(COLOR_CONGRATES"\n\nCongratulations You scored %d out of 5"RESET,sum);
    printf(COLOR_TITLE"\n\nSummary:-"COLOR_INSTRUCTION"\nCorrect answers=%d\nWrong answers=%d\nPercentage score=%d%%"RESET,sum,(5-sum),(sum*20));
    printf(COLOR_TITLE"\n\n\nGraphical output explination:-"COLOR_INSTRUCTION"\nGreen"BOLD_GREEN " ■ "COLOR_INSTRUCTION"segment represents correct answers\nRed"BOLD_RED " ■ "COLOR_INSTRUCTION"segment indicates wrong answers\n"); 
    
    // Print green blocks for correct answers
    for(int i=0;i<sum;i++)
    {
        printf(BOLD_GREEN "■");
    }
    
    // Print red blocks for incorrect answers
    for(int j=0;j<(5-sum);j++)
    {
        printf(BOLD_RED "■");
    }
}
-/***************************************************************************
 * scramble.c
 *
 * Edward M. Poot
 * Hacker 3
 *
 * Implements Scramble with CS50.
 *
 * Usage: scramble [#]
 *
 * where # is an optional grid number.
 ***************************************************************************/
 
#include <cs50.h>
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// duration of a game in seconds
#define DURATION 30

// grid's dimensions
#define DIMENSION 4

// maximum number of words in any dictionary
#define WORDS 172806

// maximum number of letters in any word
#define LETTERS 29

// default dictionary
// http://www.becomeawordgameexpert.com/wordlists.htm
#define DICTIONARY "words"

// for logging
FILE* log;

// grid
char grid[DIMENSION][DIMENSION];

// flags with which we can mark grid's letters while searching for words
bool marks[DIMENSION][DIMENSION];

// used to print inspiration in the draw() function
// i do it this way because else the screen gets cleared before the inspiration is printed
// if inspirationRequested is true, inspiration will be printed after the grid is drawn
bool inspirationRequested;

// defines a word as having an array of letters plus a flag
// indicating whether word has been found on grid
typedef struct
{
    bool found;
    char letters[LETTERS + 1];
}
word;

// defines a dictionary as having a size and an array of words
struct
{
    int size;
    word words[WORDS];
}
dictionary;

// prototypes
void clear(void);
bool crawl(string letters, int x, int y);
void draw(void);
bool find(string s);
void initialize(void);
bool load(string s);
bool lookup(string s);
void inspiration(void);
int scoreForLetters(string s);

// This is Scramble.
int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc > 2)
    {
        printf("Usage: %s [#]\n", basename(argv[0]));
        return 1;
    }

    // seed pseudorandom number generator
    if (argc == 2)
    {
        int seed = atoi(argv[1]);
        if (seed <= 0)
        {
            printf("Invalid grid.\n");
            return 1;
        }
        srand(seed);
    }
    else
        srand(time(NULL));

    // determine path to dictionary
    string directory = dirname(argv[0]);
    char path[strlen(directory) + 1 + strlen(DICTIONARY) + 1];
    sprintf(path, "%s/%s", directory, DICTIONARY);

    // load dictionary
    if (!load(path))
    {
        printf("Could not open dictionary.\n");
        return 1;
    }

    // initialize the grid
    initialize();

    // initialize user's score
    int score = 0;

    // calculate time of game's end
    int end = time(NULL) + DURATION;

    // open log
    log = fopen("log.txt", "w");
    if (log == NULL)
        return 1;
    
    // accept words until timer expires
    while (true)
    {          
        // clear the screen
        clear();

        // draw the current state of the grid
        draw();

        // log board
        for (int row = 0; row < DIMENSION; row++)
        {
            for (int col = 0; col < DIMENSION; col++)
                fprintf(log, "%c", grid[row][col]);
            fprintf(log, "\n");
        }

        // get current time
        int now = time(NULL);

        // report score
        printf("Score: %d\n", score);
        fprintf(log, "%d\n", score);

        // check for game's end
        if (now >= end)
        {
            printf("\033[31m"); // red
            printf("Time:  %d\n\n", 0);
            printf("\033[39m"); // default
            break;
        }

        // report time remaining
        printf("Time:  %d\n\n", end - now);
        
        // prompt for word
        printf("> ");
        
        // string inputted by user
        string s = GetString();
        
        // uppercase the string right after input
        // since everywhere we check later compares with a capitalized string
        // however toupper() only works with single characters, we just loop through all characters
        for (int i = 0, length = strlen(s); i < length; i++)
        {
            s[i] = toupper(s[i]);
        }

        // quit playing if user hits ctrl-d
        if (s == NULL)
            break;
        
        // true if the user has inputted INSPIRATION 
        if (strcmp(s, "INSPIRATION") == 0) {
            inspirationRequested = true;
        }

        // log word
        fprintf(log, "%s\n", s);
              
        // or to look for word on grid and in dictionary
        if (find(s) && lookup(s))
        {     
            // scoreForLetters() calculates amount of points we get for the string,
            // then we add it to the existing score
            score += scoreForLetters(s);     
        }
    }

    // close log
    fclose(log);

    return 0;
}

/**
 * Clears screen.
 */
void clear()
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Crawls grid recursively for letters starting at grid[x][y].
 * Returns true iff all letters are found.
 */
bool crawl(string letters, int x, int y)
{
    // if out of letters, then we must've found them all!
    if (strlen(letters) == 0)
        return true;

    // don't fall off the grid!
    if (x < 0 || x >= DIMENSION)
        return false;
    if (y < 0 || y >= DIMENSION)
        return false;

    // been here before!
    if (marks[x][y])
        return false;

    // check grid[x][y] for current letter
    if (grid[x][y] != letters[0])
        return false;

    // mark location
    marks[x][y] = true;

    // look left and right for next letter
    for (int i = -1; i <= 1; i++)
    {
        // look down and up for next letter
        for (int j = -1; j <= 1; j++)
        {
            // check grid[x + i][y + j] for next letter
            if (crawl(&letters[1], x + i, y + j))
                return true;
        }
    }

    // unmark location
    marks[x][y] = false;

    // fail
    return false;
}

/** 
 * Prints the grid in its current state.
 */
void draw(void)
{   
    printf("\n"); // add a new line so grid becomes more clear to user
    
    // loop through the amount of rows defined
    for (int row = 0; row < DIMENSION; row++)
    {   
        // loop through the amount of columns defined
        for (int col = 0; col < DIMENSION; col++)
            printf("%c ", grid[row][col]); // print the character in the right location of the grid
        printf("\n");
    }
    
    // if the user has requested inspiration, we print it here
    // if we print it in main, the inspiration will be cleared before the user can see it
    // this feels a bit hacky, but is the easiest way without using pointers
    if (inspirationRequested)
    {   
        printf("\n");
        
        // print the inspiration
        inspiration();
        
        // set to false so no inspiration is printed until user types the keyword again
        inspirationRequested = false;
        
        printf("\n");
    }
    
    printf("\n"); // again add a new line for sake of clearness
}

/**
 * Returns true iff word, s, is found in grid.
 */
bool find(string s)
{
    // word must be at least 2 characters in length
    if (strlen(s) < 2)
        return false;

    // search grid for word
    for (int row = 0; row < DIMENSION; row++)
    {
        for (int col = 0; col < DIMENSION; col++)
        {
            // reset marks
            for (int i = 0; i < DIMENSION; i++)
                for (int j = 0; j < DIMENSION; j++)
                    marks[i][j] = false;

            // search for word starting at grid[i][j]
            if (crawl(s, row, col))
                return true;
        }
    }
    return false;
}

/**
 * Initializes grid with letters.
 */
void initialize(void)
{
    // http://en.wikipedia.org/wiki/Letter_frequency
    float frequencies[] = {
     8.167,  // a
     1.492,  // b
     2.782,  // c
     4.253,  // d
     12.702, // e
     2.228,  // f
     2.015,  // g
     6.094,  // h
     6.966,  // i
     0.153,  // j
     0.747,  // k
     4.025,  // l
     2.406,  // m
     6.749,  // n
     7.507,  // o
     1.929,  // p
     0.095,  // q
     5.987,  // r
     6.327,  // s
     9.056,  // t
     2.758,  // u
     1.037,  // v
     2.365,  // w
     0.150,  // x
     1.974,  // y
     0.074   // z
    };
    int n = sizeof(frequencies) / sizeof(float);

    // iterate over grid
    for (int row = 0; row < DIMENSION; row++)
    {
        for (int col = 0; col < DIMENSION; col++)
        {   
            // generate pseudorandom double in [0, 1]
            double d = rand() / (double) RAND_MAX;

            // map d onto range of frequencies
            for (int k = 0; k < n; k++)
            {
                d -= frequencies[k] / 100;
                if (d < 0.0 || k == n - 1)
                {
                    grid[row][col] = 'A' + k;
                    break;
                }
            }
        }
    }
}

/**
 * Loads words from dictionary with given filename, s, into a global array.
 */
bool load(string s)
{
    // open dictionary
    FILE* file = fopen(s, "r");
    if (file == NULL)
        return false;

    // initialize dictionary's size
    dictionary.size = 0;

    // load words from dictionary
    char buffer[LETTERS + 2];
    while (fgets(buffer, LETTERS + 2, file))
    {
        // overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';

        // capitalize word
        for (int i = 0, n = strlen(buffer); i < n; i++)
            buffer[i] = toupper(buffer[i]);

        // ignore INSPIRATION
        if (strcmp(buffer, "INSPIRATION") == 0) 
            continue;

        // copy word into dictionary
        dictionary.words[dictionary.size].found = false;
        strncpy(dictionary.words[dictionary.size].letters, buffer, LETTERS + 1);
        dictionary.size++;
    }

    // success!
    return true;
}

/**
 * Looks up word, s, in dictionary.  Iff found (for the first time), flags word
 * as found (so that user can't score with it again) and returns true.
 */
bool lookup(string s)
{
    // I am going to use a binary search, since the words are already sorted (alphabetically)
    // and binary search here is probably the best option
    
    // initially we set lowIndex to 0 to first try the first half
    int lowIndex = 0;
    
    // the highIndex is equal to the max number of words in dict, minus 1
    // since we're using it later as an array index which starts at 0
    int highIndex = WORDS - 1;
    
    // keep looping until condition isn't met anymore
    while (lowIndex <= highIndex)
    {   
        // calculate new middle
        int middle = (lowIndex + highIndex) / 2;
        
        // the string is actually at the middle
        if (strcmp(s, dictionary.words[middle].letters) == 0)
        {
            // if the word in question is already found, return false
            if (dictionary.words[middle].found)
            {
                return false;
            }
            // if it hasn't been found yet, so flag it return true;
            else
            {   
                dictionary.words[middle].found = true;
                return true;
            }
        }
        
        // s is greater than the word at that position
        if (strcmp(s, dictionary.words[middle].letters) > 0)
        {
            lowIndex = middle + 1;
        }
        // s is less than the word at that position
        else if(strcmp(s, dictionary.words[middle].letters) < 0)
        {
            highIndex = middle - 1;
        }
        // this practically isn't possible, since either middle must be at word, lower or higher than that
        else {
            return false;
        }
    }          
    
    return false;
}

/**
 * Finds random words in dictionary of length 5, 4 and 3.
 * Checks if these words haven't been found yet and that they are in the current grid.
 */
void inspiration(void)
{
    // bool used as while condition. If true, we continue looping. If false, we stop the loop
    bool searching = true;
            
    // bools used to indicate when a word of specific length has been found, so we don't search for that length anymore
    bool WordWithFiveLettersFound = false;
    bool WordWithFourLettersFound = false;
    bool WordWithThreeLettersFound = false;
    
    // count the amount of loops, so we can break out of the while 
    // when we've looped more times then there are words in the dict.
    int amountOfLoops = 0;
            
    printf("Here is your inspiration... ");
    
    while(searching == true)
    {
        // pick a random word
        // any word with an index between [0, WORDS] can be selected
        int randomIndex = rand() % WORDS; 
                
        // the random word we picked
        word randomWord = dictionary.words[randomIndex];

        // make sure random word is of right length, is not yet found, and if it is in the current grid
        if (!WordWithFiveLettersFound &&strlen(randomWord.letters) == 5 && !randomWord.found && find(randomWord.letters)) 
        {   
            printf("%s ", randomWord.letters);
            WordWithFiveLettersFound = true; // we have found the five letter word, so no longer search for it
        } 
        else if (!WordWithFourLettersFound && strlen(randomWord.letters) == 4 && !randomWord.found && find(randomWord.letters)) 
        {   
            printf("%s ",randomWord.letters);
            WordWithFourLettersFound = true; // same as above, but this time we have found the four letter word
        }
        else if (!WordWithThreeLettersFound && strlen(randomWord.letters) == 3 && !randomWord.found && find(randomWord.letters)) 
        {   
            printf("%s ", randomWord.letters);
            WordWithThreeLettersFound = true; // same as above, this final time we have found the three letter word
        }
        // we have found three words of different size, exit the while loop
        else if (WordWithFiveLettersFound && WordWithFourLettersFound && WordWithThreeLettersFound) 
        {   
            searching = false;
        }
        // if we have looped more times then there are words in the dictionary, exit the loop since obviously we can't find a specific word of a given length
        else if (amountOfLoops >= WORDS && (!WordWithFiveLettersFound || !WordWithFourLettersFound || !WordWithThreeLettersFound)) {
            searching = false;
        }
    }  
}

/**
 * Calculates score for each individual letter
 * then calculates sum of all letters together and returns it
 */
int scoreForLetters(string s)
{
    // define scores for each letter from A to Z
    int scoresForLetter[26] = {
     1,  // A
     4,  // B
     4,  // C
     2,  // D
     1,  // E
     4,  // F
     3,  // G
     3,  // H
     1,  // I
     10, // J
     5,  // K
     2,  // L
     4,  // M
     2,  // N
     1,  // O
     4,  // P
     10, // Q
     1,  // R
     1,  // S
     1,  // T
     2,  // U
     5,  // V
     4,  // W
     8,  // X
     3,  // Y
     10  // Z           
    };

    // temporary store the score for this word
    int scorePlaceholder = 0;
    
    // loop through all characters of the string to calculate points for each letter
    for (int i = 0, length = strlen(s); i < length; i++)
    {   
        int letterReference = 'A'; // startingpoint of alphabet
        
        // the value of the char at index i minus the startingpoint of alphabet is equal to the position in the alphabet (e.g. Z is 26)
        scorePlaceholder += scoresForLetter[(s[i] - letterReference)]; // for each letter calculate value and add it to the previous score
    }
        
    //return the score
    return scorePlaceholder;
}

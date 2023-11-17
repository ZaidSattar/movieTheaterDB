#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MOVIES 100 // 100 max movies
#define MAX_NAME_LEN 100 // movie name can only be 100 characters
#define MAX_GENRE_LEN 25 // genre length can only be 25 characters

typedef struct {
    int code; // code variable that holds an integer
    char name[MAX_NAME_LEN]; // name variable that has the property MAX_NAME_LEN so it does not exceed 100 characters, holds character variable
    char genre[MAX_GENRE_LEN]; // genre variable that has the property MAX_GENRE_LEN so it does not exceed 25 characters, holds character variable
    float rating; // rating variable that hgolds a floating integer
} Movie;

int findMovieIndex(Movie movies[], int movieCount, int movieCode); // these are the prototypes for each of the functions that used later, starting with findMovieIndex
void insertMovie(Movie movies[], int *movieCount); // this will be responsible for inserting movie, or doing "i"
void updateMovie(Movie movies[], int movieCount); // this will be responsbile for updating movie, or doing "u"
void printMovie(const Movie *movie); // this will be responsbile for printing movie, this will be used within the other functions
void printAllMovies(const Movie movies[], int movieCount); // this will be responsible for printing all movies, or doing "p"
void searchMovie(const Movie movies[], int movieCount); // this will be responsbile for searching movie, or doing "s"
int getInt(const char *prompt);
float getFloat(const char *prompt, float min, float max); // this will be responsbile for storing the rating


int main() { // main function
    Movie movies[MAX_MOVIES];
    int movieCount = 0; // currently no movies stores in the list, we need to know how many are stored to append them later on
    char operationCode; // operationCode is what we will use to store the user input of whioch operation they want to do

    printf("$ ./movieTheaterDB\n********************\n* 2211 Movie Cinema *\n********************\n"); // basic formatting, adding a title section to the code

    while (1) { // while loop allows for the code to continue running after each function instead of terminating
        printf("\nEnter operation code: "); // asks the user for their operating code input
        scanf(" %c", &operationCode); // stores the user input in char operationCode

        switch (tolower(operationCode)) { // reads the user input in lowercase, incase they enter an uppercase letter it will still be read the same
            case 'i':  // in the case that operation code is "i"
                insertMovie(movies, &movieCount); // it will run the insertmovie function
                break;
            case 'u': // in the case that operation code is "u"
                updateMovie(movies, movieCount); // it will run the updateMovie function
                break;
            case 'p': // in the case that operation code is "p"
                printAllMovies(movies, movieCount); //it will run the PrintAllMovies function
                break;
            case 'q': //in the case that operation code is "q"
                printf("Quitting program.\n"); // it will terminate the program
                return 0; // this will end the while loop from earlier
            case 's': // in the case that operation code is "s"
                searchMovie(movies, movieCount); // it will run the searchMovie function
                break;
            default:
                printf("Invalid operation code.\n"); // if the input does not match any of the operations listed above, it gives the user an error.
        }
    }


}
void searchMovie(const Movie movies[], int movieCount) { // this function will be in charge of searching for the movie, when the operation code is s
    int code = getInt("Enter movie code to search: "); // asks the user for a movie code
    int index = findMovieIndex(movies, movieCount, code); // matches the user code with the same movie code in the list and gets the index of it
    if (index != -1) {  // if it is able to retrieve a valid index
        printf("%-10s %-30s %-15s %-10s\n", "Movie Code", "Movie Name", "Movie Genre", "Movie Rating"); // it prints the table's titles with appropriate spacing and formatting
        printMovie(&movies[index]); // calls for the print movie function given the index retrieved earlier, this allows for the exact movie information to be printed
    } else {
        printf("Movie code not found.\n"); // if the index is invalid (Does not exist) it will give the user an error
    }
}

void insertMovie(Movie movies[], int *movieCount) { // this function will be in chrage of inserting a movie, when the operation code is i
    if (*movieCount >= MAX_MOVIES) { // checks if there are 100 movies in the table
        printf("EXCEEDED LIMIT\n"); // if there is, it does not allow for more to be printed
        return;
    }

    int code = getInt("Enter movie code: "); // asks the user to enter the movie code they would like to insert
    if (code < 0 || findMovieIndex(movies, *movieCount, code) != -1) { // checks if the code already exists
        printf("Movie already exists.\n"); //gives the user an error if it does
        return;
    }

    printf("Enter movie name: "); // asks the user to enter the movie name
    char name[MAX_NAME_LEN];
    scanf(" %[^\n]", name); // reads until newline

    printf("Enter movie genre: "); // asks the user to enter the movie genre to insert
    char genre[MAX_GENRE_LEN];
    scanf(" %[^\n]", genre);

    float rating = getFloat("Enter movie rating: ", 0.0, 10.0); // asks the user to enter a movie rating to insert that must be within 0.0 and 10.0

    Movie newMovie = {code};
    strncpy(newMovie.name, name, MAX_NAME_LEN - 1);
    newMovie.name[MAX_NAME_LEN - 1] = '\0'; //  null-termination
    strncpy(newMovie.genre, genre, MAX_GENRE_LEN - 1);
    newMovie.genre[MAX_GENRE_LEN - 1] = '\0'; //  null-termination
    newMovie.rating = rating;

    movies[*movieCount] = newMovie;
    (*movieCount)++; // increases the count that is responsible for checking how many movies in the table
}

void updateMovie(Movie movies[], int movieCount) { // function will be responsbile for updating movie, or when operation code is U
    int code = getInt("Enter movie code to update: "); // asks the user for a movie code to update
    int index = findMovieIndex(movies, movieCount, code); // finds the index of the movie code to update
    if (index == -1) { // if the index does not exist
        printf("Movie code not found.\n"); // gives the user an errpr
        return;
    }

    printf("Enter movie name: "); // if the index is found, asks the user for a new movie name
    char name[MAX_NAME_LEN];
    scanf(" %[^\n]", name);

    printf("Enter movie genre: "); // asks the user for a new movie genre
    char genre[MAX_GENRE_LEN];
    scanf(" %[^\n]", genre);

    float rating = getFloat("Enter movie rating: ", 0.0, 10.0); // asks the user for a new movie rating

    strncpy(movies[index].name, name, MAX_NAME_LEN - 1);
    movies[index].name[MAX_NAME_LEN - 1] = '\0'; // Ensure null-termination
    strncpy(movies[index].genre, genre, MAX_GENRE_LEN - 1);
    movies[index].genre[MAX_GENRE_LEN - 1] = '\0';
    movies[index].rating = rating;
}

int findMovieIndex(Movie movies[], int movieCount, int movieCode) { // function that will be responsible for finding the movie index
    for (int i = 0; i < movieCount; i++) { // for loop that iterates through the list
        if (movies[i].code == movieCode) { // checks if there is a match
            return i; //stores the index in i
        }
    }
    return -1;
}

void printMovie(const Movie *movie) { // function responsible for printing movie
    printf(" %-10d %-30s %-20s %-10.1f\n", movie->code, movie->name, movie->genre, movie->rating); // prints the movie and all of its elements
}

void printAllMovies(const Movie movies[], int movieCount) { // print all movies prints the entire table, this is used for commands such as P
    printf("%-10s %-30s %-20s %-10s\n", "Movie Code", "Movie Name", "Movie Genre", "Movie Rating"); // print the titles of the table
    for (int i = 0; i < movieCount; i++) { // for loop that goes for as many times as there are movies
        printMovie(&movies[i]); // calls the printMovie function
    }
}

int getInt(const char *prompt) { // getInt function
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    return value; // returns value
}

float getFloat(const char *prompt, float min, float max) { //responsible for getting the floating integer
    float value;
    do {
        printf("%s", prompt);
        scanf("%f", &value);
    } while (value < min || value > max);
    return value;
}

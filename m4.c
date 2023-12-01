#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
int processGames(const char *filename);
int parseLine(const char *line, char *opponentName, int *teamScore, int *opponentScore);

// Main function
int main() {
    int i;
    char *teamFiles[] = {"Toronto Maple Leafs.txt", "New York Yankees.txt", "Manchester United.txt", "Chennai Super Kings.txt"};
    int numFiles = sizeof(teamFiles) / sizeof(teamFiles[0]);

    return 0;
}

// processGames function


// parseLine function
int parseLine(const char *line, char *opponentName, int *teamScore, int *opponentScore) {
    char *token = strtok((char *)line, ",");
    if (token == NULL) return -1;
    strcpy(opponentName, token);

    token = strtok(NULL, "-");
    if (token == NULL) return -1;
    *teamScore = atoi(token);

    token = strtok(NULL, "");
    if (token == NULL) return -1;
    *opponentScore = atoi(token);

    return 0;
}

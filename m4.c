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

    for (i = 0; i < numFiles; i++) {
        if (processGames(teamFiles[i]) != 0) {
            fprintf(stderr, "Error processing file: %s\n", teamFiles[i]);
        }
    }

    return 0;
}

// processGames function
int processGames(const char *filename) {
    FILE *file;
    char line[100], opponentName[50];
    int teamScore, opponentScore;
    int wins = 0, losses = 0, ties = 0;
    int status = 0;

    file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character

        if (strlen(line) == 0) continue;  // Skip empty lines

        if (parseLine(line, opponentName, &teamScore, &opponentScore) == 0) {
            if (teamScore > opponentScore) {
                wins++;
                printf("\t%s beat %s %d-%d\n", filename, opponentName, teamScore, opponentScore);
            } else if (teamScore < opponentScore) {
                losses++;
                printf("\t%s lost to %s %d-%d\n", filename, opponentName, opponentScore, teamScore);
            } else {
                ties++;
                printf("\t%s and %s tied at %d\n", filename, opponentName, teamScore);
            }
        } else {
            fprintf(stderr, "Error parsing line: %s\n", line);
            status = 1;
        }
    }

    if (wins + losses + ties > 0) {
        float winningPercentage = (2.0 * wins + ties) / (2.0 * (wins + losses + ties));
        printf("Season result for %s: %.3f (%d-%d-%d)\n\n", filename, winningPercentage, wins, losses, ties);
    }

    fclose(file);
    return status;
}

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

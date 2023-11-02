#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **_getline(char *line) {
	char **words = NULL;
	char *token = strtok(line, " ");
	int count = 0;

	while (token != NULL) {
		words = realloc(words, (count + 1) * sizeof(char*));
		if (words == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		words[count] = malloc(strlen(token) + 1);
		if (words[count] == NULL) {
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		strcpy(words[count], token);
		token = strtok(NULL, " ");
		count++;
	}

	words = realloc(words, (count + 1) * sizeof(char*));
	if (words == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	words[count] = NULL; 

	return words;
}

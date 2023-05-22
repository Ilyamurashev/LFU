#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates a random number in the specified range [min, max]
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    // Settings
    int cache_lower_limit = 1;
    int cache_upper_limit = 100;
    int num_min = 10;
    int num_max = 1000;
    int page_range_min = 10;
    int page_range_max = 100;

    srand(time(NULL)); // Initializing a random number generator

    int m = generateRandomNumber(cache_lower_limit, cache_upper_limit);
    int n = generateRandomNumber(num_min, num_max);

    FILE* file = fopen("test1.txt", "w");
    if (file == NULL) {
        printf("Failed to create test file\n");
        return 1;
    }

    fprintf(file, "%d %d ", m, n);

    for (int i = 0; i < n; i++) {
        int page = generateRandomNumber(page_range_min, page_range_max);
        fprintf(file, "%d ", page);
    }

    fclose(file);

    return 0;
}

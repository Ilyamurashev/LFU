#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a cache cell
typedef struct {
    int pageNumber;
    int frequency;
    int lastUsed;
} CacheCell;

// Generates a random number in the specified range [min, max]
int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Function for initializing cache cells
void initCacheCells(CacheCell* cache, int m) {
    for (int i = 0; i < m; i++) {
        cache[i].pageNumber = -1; // -1 means an empty cell
        cache[i].frequency = 0;
        cache[i].lastUsed = -1;
    }
}

// Function for finding the least frequently used cell
int findLeastFrequentCell(CacheCell* cache, int m) {
    int minFrequency = cache[0].frequency;
    int leastFrequentIndex = 0;

    for (int i = 1; i < m; i++) {
        if (cache[i].frequency < minFrequency) {
            minFrequency = cache[i].frequency;
            leastFrequentIndex = i;
        } else if (cache[i].frequency == minFrequency) {
            // In case of equal frequencies, select the cell,
            // which was used before
            if (cache[i].lastUsed < cache[leastFrequentIndex].lastUsed) {
                leastFrequentIndex = i;
            }
        }
    }

    return leastFrequentIndex;
}

// Function to update the frequency and last use of the cell
void updateCacheCell(CacheCell* cache, int index) {
    cache[index].frequency++;
    cache[index].lastUsed = index;
}

// Function for counting the number of cache hits
int countCacheHits(int* requests, int n, int m) {
    int cacheHits = 0;
    CacheCell* cache = malloc(m * sizeof(CacheCell));
    initCacheCells(cache, m);

    for (int i = 0; i < n; i++) {
        int pageNumber = requests[i];

        // Checking if the page is in the cache
        int cacheIndex = -1;
        for (int j = 0; j < m; j++) {
            if (cache[j].pageNumber == pageNumber) {
                cacheIndex = j;
                break;
            }
        }

        if (cacheIndex != -1) {
            // The page is in the cache (hit)
            cacheHits++;
            updateCacheCell(cache, cacheIndex);
        } else {
            // The page is not in the cache (miss)
            int leastFrequentIndex = findLeastFrequentCell(cache, m);
            cache[leastFrequentIndex].pageNumber = pageNumber;
            updateCacheCell(cache, leastFrequentIndex);
        }
    }

    free(cache);
    return cacheHits;
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

    // Read the input from the file
    file = fopen("test1.txt", "r+");
    if (file == NULL) {
        printf("Failed to open test file\n");
        return 1;
    }

    fscanf(file, "%d %d", &m, &n);

    int* requests = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &requests[i]);
    }

    fclose(file);

    // Calculate the cache hits
    int cacheHits = countCacheHits(requests, n, m);

    // Write the output to a file
    file = fopen("test1.txt", "a+");
    if (file == NULL) {
        printf("Failed to create output file\n");
        return 1;
    }
    fprintf(file,"\n");
    fprintf(file, "Expected number of cache hits = %d\n", cacheHits);

    fclose(file);

    free(requests);
    return 0;
}

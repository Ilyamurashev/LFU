#include <stdio.h>
#include <stdlib.h>

// Structure to represent a cache cell
typedef struct {
    int pageNumber;
    int frequency;
    int lastUsed;
} CacheCell;

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
    int m, n;
    scanf("%d %d", &m, &n);

    int* requests = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int cacheHits = countCacheHits(requests, n, m);
    printf("%d\n", cacheHits);

    free(requests);
    return 0;
}

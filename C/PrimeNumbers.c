#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 1000000000  // Limit for finding primes
#define OUTPUT_FILE "prime_numbers.txt"  // File to save the primes

void print_progress_bar(long long current, long long total) {
    int bar_width = 50;  // Width of the progress bar
    double progress = (double)current / total;

    printf("\r[");
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %.2f%%", progress * 100);
    fflush(stdout);
}

int main() {
    // Allocate memory for the sieve
    printf("Allocating memory...\n");
    bool *is_prime = malloc((LIMIT + 1) * sizeof(bool));
    if (!is_prime) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize the sieve
    for (long long i = 0; i <= LIMIT; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;  // 0 and 1 are not primes

    printf("Starting the sieve...\n");
    clock_t start_time = clock();  // Start the stopwatch

    // Sieve of Eratosthenes
    long long sqrt_limit = (long long)sqrt(LIMIT);
    for (long long p = 2; p <= sqrt_limit; p++) {
        if (is_prime[p]) {
            for (long long multiple = p * p; multiple <= LIMIT; multiple += p) {
                is_prime[multiple] = false;
            }
        }
        print_progress_bar(p, sqrt_limit);  // Update the progress bar
    }

    print_progress_bar(sqrt_limit, sqrt_limit);  // Complete the progress bar
    printf("\n");

    // Collect primes and write them to a file
    printf("Writing primes to file...\n");
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        free(is_prime);
        return 1;
    }

    long long prime_count = 0;
    for (long long i = 2; i <= LIMIT; i++) {
        if (is_prime[i]) {
            prime_count++;
            fprintf(file, "%lld\n", i);  // Write the prime number to the file
        }
    }
    fclose(file);

    clock_t end_time = clock();  // Stop the stopwatch
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print results
    printf("Number of primes found: %lld\n", prime_count);
    printf("Time taken: %.2f seconds\n", elapsed_time);
    printf("All primes have been saved to '%s'\n", OUTPUT_FILE);

    // Free allocated memory
    free(is_prime);
    return 0;
}

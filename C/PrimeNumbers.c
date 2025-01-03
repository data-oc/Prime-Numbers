// C standard revision = C89 (ANSI C)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 1000000000          // Limit for finding primes
#define OUTPUT_FILE "prime_numbers.txt" // File to save the primes

// uses features specific to a C standard
#if __STDC_VERSION__ >= 201112L
#define C_VERSION "C11"
#elif __STDC_VERSION__ >= 199901L
#define C_VERSION "C99"
#else
#define C_VERSION "C89"
#endif

void print_progress_bar(long long current, long long total) {
    const int bar_width = 50; // Width of the progress bar
    double progress = (double)current / total;

    printf("\r[");
    int pos = (int)(bar_width * progress);
    int i; // Declare outside loop
    for (i = 0; i < bar_width; ++i) {
        if (i < pos)
            printf("=");
        else if (i == pos)
            printf(">");
        else
            printf(" ");
    }
    printf("] %.2f%%", progress * 100);
    fflush(stdout);
}

int main(void) {
    // Variable declarations
    long long i; // Loop variable
    long long p; // Loop variable for primes
    long long multiple; // Loop variable for multiples
    
    printf("C Version: %s\n\n", C_VERSION);

    // Allocate memory for the sieve
    printf("Allocating memory...\n\n");
    bool *is_prime = malloc((LIMIT + 1) * sizeof(bool));
    if (is_prime == NULL) {
        fprintf(stderr, "Memory allocation failed.\n\n");
        return EXIT_FAILURE;
    }

    // Initialize the sieve
    for (i = 0; i <= LIMIT; i++) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not primes

    printf("Starting the sieve...\n");
    clock_t start_time = clock(); // Start the stopwatch

    // Sieve of Eratosthenes
    long long sqrt_limit = (long long)sqrt((double)LIMIT);
    for (p = 2; p <= sqrt_limit; p++) {
        if (is_prime[p]) {
            for (multiple = p * p; multiple <= LIMIT; multiple += p) {
                is_prime[multiple] = false;
            }
        }
        if (p % 1000 == 0) { // Print progress every 1000 iterations to reduce overhead
            print_progress_bar(p, sqrt_limit);
        }
    }

    print_progress_bar(sqrt_limit, sqrt_limit); // Complete the progress bar
    printf("\n");

    // Collect primes and write them to a file
    printf("\nSaving primes to file...\n");
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file == NULL) {
        fprintf(stderr, "\nFailed to open file for writing.\n");
        free(is_prime);
        return EXIT_FAILURE;
    }

    long long prime_count = 0;
    for (i = 2; i <= LIMIT; i++) {
        if (is_prime[i]) {
            prime_count++;
            fprintf(file, "%lld\n", i); // Write the prime number to the file
        }
    }
    fclose(file);
    printf("All primes have been saved to '%s'\n", OUTPUT_FILE);

    clock_t end_time = clock(); // Stop the stopwatch
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print results
    printf("\nNumber of primes found: %lld\n", prime_count);
    printf("Time taken: %.2f seconds\n", elapsed_time);
    
    getch();

    // Free allocated memory
    free(is_prime);
    return EXIT_SUCCESS;
}

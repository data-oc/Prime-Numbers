package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"time"

	"github.com/schollz/progressbar/v3"
)

func sieveOfEratosthenes(limit int) ([]int, *progressbar.ProgressBar) {
	// Create a slice to mark prime numbers
	isPrime := make([]bool, limit+1)
	for i := 2; i <= limit; i++ {
		isPrime[i] = true
	}

	// Prepare progress bar
	sqrtLimit := int(math.Sqrt(float64(limit)))
	bar := progressbar.Default(int64(sqrtLimit), "Processing primes")

	for p := 2; p <= sqrtLimit; p++ {
		if isPrime[p] {
			for multiple := p * p; multiple <= limit; multiple += p {
				isPrime[multiple] = false
			}
		}
		bar.Add(1) // Update progress bar
	}

	// Collect primes into a slice
	primes := []int{}
	for i := 2; i <= limit; i++ {
		if isPrime[i] {
			primes = append(primes, i)
		}
	}

	return primes, bar
}

func savePrimesToFile(primes []int, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for _, prime := range primes {
		_, err := writer.WriteString(fmt.Sprintf("%d\n", prime))
		if err != nil {
			return err
		}
	}
	return writer.Flush()
}

func main() {
	const LIMIT = 1000000000
	const OUTPUT_FILE = "prime_numbers.txt"

	fmt.Printf("Finding all prime numbers up to %d...\n\n", LIMIT)

	// Start the stopwatch
	start := time.Now()

	// Calculate primes
	primes, bar := sieveOfEratosthenes(LIMIT)
	bar.Finish() // Finish the progress bar

	// Save primes to file
	fmt.Println("\nSaving primes to file...")
	err := savePrimesToFile(primes, OUTPUT_FILE)
	if err != nil {
		fmt.Printf("Failed to save primes: %v\n", err)
	} else {
		fmt.Printf("All primes have been saved to '%s'\n", OUTPUT_FILE)
	}

	// Stop the stopwatch
	elapsed := time.Since(start)

	// Print results
	fmt.Printf("\nNumber of primes found: %d\n", len(primes))
	fmt.Printf("Time taken: %.2f seconds\n", elapsed.Seconds())
}

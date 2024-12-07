import * as fs from 'fs';
import { SingleBar, Presets } from 'cli-progress';
import { performance } from 'perf_hooks';

// Function to find prime numbers using Sieve of Eratosthenes
const sieveOfEratosthenes = (limit: number): number[] => {
    const isPrime = new Uint8Array(limit + 1).fill(1); // Array to mark prime numbers
    isPrime[0] = 0; // 0 is not prime
    isPrime[1] = 0; // 1 is not prime

    for (let i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (let j = i * i; j <= limit; j += i) {
                isPrime[j] = 0; // Mark multiples of i as non-prime
            }
        }
    }

    const primes: number[] = [];
    for (let i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push(i);
        }
    }
    return primes;
};

// Main function to manage process and display progress
const main = async (): Promise<void> => {
    const limit = 1_000_000_000; // Define the limit 1 billion
    const chunkSize = 100_000; // Process data in chunks to show progress

    const progressBar = new SingleBar({}, Presets.shades_classic);

    // Start the stopwatch
    const startTime = performance.now();

    progressBar.start(limit, 0);

    const fileStream = fs.createWriteStream('prime_numbers.txt');
    let primeCount = 0;

    for (let start = 2; start <= limit; start += chunkSize) {
        const end = Math.min(start + chunkSize - 1, limit);
        const primes = sieveOfEratosthenes(end);

        // Filter primes within the chunk range
        const chunkPrimes = primes.filter(prime => prime >= start && prime <= end);
        
        // Write primes to file
        fileStream.write(chunkPrimes.join('\n') + '\n');

        primeCount += chunkPrimes.length;
        progressBar.update(start);
    }

    fileStream.end(); // Close the file stream
    progressBar.stop();

    // Stop the stopwatch
    const endTime = performance.now();
    const elapsedTime = ((endTime - startTime) / 1000).toFixed(2); // Convert to seconds

    console.log(`\nAll primes have been saved to 'prime_numbers.txt'`);
    console.log(`\nNumber of primes found: ${primeCount}`);
    console.log(`Time taken: ${elapsedTime} seconds`);
};

// Run the program
main().catch(err => console.error(err));
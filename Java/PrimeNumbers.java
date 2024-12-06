// JDK 23.0.1

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class PrimeNumbers {
    public static void main(String[] args) {
        final int LIMIT = 1_000_000_000;
        final String OUTPUT_FILE = "prime_numbers.txt";

        System.out.println("Finding all prime numbers up to " + LIMIT + "...");

        // Start the stopwatch
        long startTime = System.currentTimeMillis();

        // Calculate primes
        List<Integer> primes = sieveOfEratosthenes(LIMIT);

        // Stop the stopwatch
        long endTime = System.currentTimeMillis();
        double elapsedTime = (endTime - startTime) / 1000.0;

        // Display results
        System.out.println("\nNumber of primes found: " + primes.size());
        System.out.printf("Time taken: %.2f seconds%n", elapsedTime);

        // Save primes to file
        System.out.println("\nSaving primes to file...");
        savePrimesToFile(primes, OUTPUT_FILE);
        System.out.println("All primes have been saved to '" + OUTPUT_FILE + "'");
    }

    private static List<Integer> sieveOfEratosthenes(int limit) {
        boolean[] isPrime = new boolean[limit + 1];
        for (int i = 2; i <= limit; i++) {
            isPrime[i] = true;
        }

        int sqrtLimit = (int) Math.sqrt(limit);
        System.out.println("Processing primes...");

        for (int p = 2; p <= sqrtLimit; p++) {
            if (isPrime[p]) {
                for (long multiple = (long) p * p; multiple <= limit; multiple += p) {
                    isPrime[(int) multiple] = false;
                }
            }
            printProgressBar(p, sqrtLimit);
        }
        printProgressBar(1, 1); // Complete progress bar
        System.out.println();

        // Collect primes into a list
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= limit; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
        return primes;
    }

    private static void savePrimesToFile(List<Integer> primes, String filename) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            for (int prime : primes) {
                writer.write(prime + "\n");
            }
        } catch (IOException e) {
            System.err.println("Failed to save primes: " + e.getMessage());
        }
    }

    private static void printProgressBar(int current, int total) {
        int progress = (int) ((double) current / total * 100);
        StringBuilder bar = new StringBuilder("[");
        for (int i = 0; i < 50; i++) {
            if (i < progress / 2) {
                bar.append("=");
            } else if (i == progress / 2) {
                bar.append(">");
            } else {
                bar.append(" ");
            }
        }
        bar.append("] ").append(progress).append("%\r");
        System.out.print(bar);
    }
}

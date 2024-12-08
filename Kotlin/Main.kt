/*
Kotlin 2.0.21
OpenJDK 23.0.1
 */

package com.mycompany.primenumbers
import java.io.BufferedWriter
import java.io.FileWriter
import java.io.IOException
import kotlin.math.sqrt

fun main() {
    val maximumNumber = 1_000_000_000
    val outputFile = "prime_numbers.txt"

    println("Finding all prime numbers up to $maximumNumber...")

    // Start the stopwatch
    val startTime = System.currentTimeMillis()

    // Calculate primes
    val primes = sieveOfEratosthenes(maximumNumber)
    println("Finished sieve computation.")

    // Save primes to file
    println("\nSaving primes to file...")
    savePrimesToFile(primes, outputFile)
    println("All primes have been saved to '$outputFile'")

    // Stop the stopwatch
    val endTime = System.currentTimeMillis()
    val elapsedTime = (endTime - startTime) / 1000.0

    // Display results
    println("\nNumber of primes found: ${primes.size}")
    println("Time taken: %.2f seconds".format(elapsedTime))
}

fun sieveOfEratosthenes(limit: Int): List<Int> {
    val isPrime = BooleanArray(limit + 1) { true }
    val sqrtLimit = sqrt(limit.toDouble()).toInt()
    println("Processing primes...")

    for (p in 2..sqrtLimit) {
        if (isPrime[p]) {
            for (multiple in (p * p..limit step p)) {
                isPrime[multiple] = false
            }
        }
        printProgressBar(p, sqrtLimit)
    }
    printProgressBar(1, 1) // Complete progress bar
    println()

    // Collect primes into a list
    return (2..limit).filter { isPrime[it] }
}

fun savePrimesToFile(primes: List<Int>, filename: String) {
    try {
        BufferedWriter(FileWriter(filename)).use { writer ->
            primes.forEach { prime ->
                writer.write("$prime\n")
            }
        }
    } catch (e: IOException) {
        println("Failed to save primes: ${e.message}")
    }
}

fun printProgressBar(current: Int, total: Int) {
    val progress = (current.toDouble() / total * 100).toInt()
    val bar = StringBuilder("[")
    for (i in 0..<50) {
        when {
            i < progress / 2 -> bar.append("=")
            i == progress / 2 -> bar.append(">")
            else -> bar.append(" ")
        }
    }
    bar.append("] $progress%")
    print("\r$bar")
}
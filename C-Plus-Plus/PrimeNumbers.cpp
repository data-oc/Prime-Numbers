// C++ version 26

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <iomanip>

void printProgressBar(double progress) {
    const int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

std::vector<int> sieveOfEratosthenes(int limit) {
    std::vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    int sqrtLimit = std::sqrt(limit);

    for (int p = 2; p <= sqrtLimit; ++p) {
        if (isPrime[p]) {
            for (long long multiple = (long long)p * p; multiple <= limit; multiple += p) {
                isPrime[multiple] = false;
            }
        }
        // Update progress bar
        printProgressBar((double)p / sqrtLimit);
    }
    printProgressBar(1.0); // Complete progress bar
    std::cout << std::endl;

    // Collect all primes
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

void savePrimesToFile(const std::vector<int>& primes, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int prime : primes) {
            file << prime << "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

int main() {
    const int LIMIT = 1000000000;
    const std::string OUTPUT_FILE = "prime_numbers.txt";

    std::cout << "Finding all prime numbers up to " << LIMIT << "...\n\n";

    auto start = std::chrono::high_resolution_clock::now();

    // Calculate primes
    std::vector<int> primes = sieveOfEratosthenes(LIMIT);
    
    // Save primes to file
    std::cout << "\nSaving primes to file...\n";
    savePrimesToFile(primes, OUTPUT_FILE);
    std::cout << "All primes have been saved to '" << OUTPUT_FILE << "'\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Results
    std::cout << "\nNumber of primes found: " << primes.size() << std::endl;
    std::cout << "Time taken: " << std::fixed << std::setprecision(2) << elapsed.count() << " seconds\n";

    return 0;
}

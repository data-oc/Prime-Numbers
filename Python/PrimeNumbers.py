import time
import math
from tqdm import tqdm  # For progress bar

def sieve_of_eratosthenes(limit):
    """
    Function to find all primes up to 'limit' using the Sieve of Eratosthenes.
    """
    # Create a boolean array "prime[0..limit]" initialized to True
    prime = [True] * (limit + 1)
    prime[0], prime[1] = False, False  # 0 and 1 are not primes

    sqrt_limit = int(math.sqrt(limit)) + 1

    # Initialize progress bar
    with tqdm(total=sqrt_limit, desc="Processing primes", unit="number") as progress:
        for p in range(2, sqrt_limit):
            if prime[p]:
                # Mark multiples of p as not prime
                for multiple in range(p * p, limit + 1, p):
                    prime[multiple] = False
            progress.update(1)  # Update progress bar

    # Collect all primes
    primes = [p for p in range(2, limit + 1) if prime[p]]
    return primes

def save_primes_to_file(prime_numbers, filename="prime_numbers.txt"):
    """
    Save all prime numbers to a file.
    """
    with open(filename, "w") as f:
        for prime in prime_numbers:
            f.write(f"{prime}\n")
    print(f"All primes have been saved to '{filename}'")

if __name__ == "__main__":
    # Set the range limit
    LIMIT = 1000000000  # 1 billion

    print(f"Finding all prime numbers up to {LIMIT}...\n")
    start_time = time.time()  # Start the stopwatch

    # Calculate all primes
    primes = sieve_of_eratosthenes(LIMIT)

    end_time = time.time()  # Stop the stopwatch
    elapsed_time = end_time - start_time

    # Print results
    print(f"Number of primes found: {len(primes)}")
    print(f"Time taken: {elapsed_time:.2f} seconds")

    # Save primes to a file
    save_primes_to_file(primes)

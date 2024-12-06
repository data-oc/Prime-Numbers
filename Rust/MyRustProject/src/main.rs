use indicatif::{ProgressBar, ProgressStyle};
use std::fs::File;
use std::io::{BufWriter, Write};
use std::time::Instant;

fn sieve_of_eratosthenes(limit: usize) -> Vec<usize> {
    let mut is_prime = vec![true; limit + 1];
    is_prime[0] = false;
    is_prime[1] = false;

    let sqrt_limit = (limit as f64).sqrt() as usize;

    // Create a progress bar
    let bar = ProgressBar::new(sqrt_limit as u64);
    bar.set_style(
        ProgressStyle::default_bar()
            .template("[{elapsed_precise}] {bar:40.cyan/blue} {pos:>7}/{len:7} {msg}")
            .unwrap()
            .progress_chars("#>-"),
    );

    for p in 2..=sqrt_limit {
        if is_prime[p] {
            let mut multiple = p * p;
            while multiple <= limit {
                is_prime[multiple] = false;
                multiple += p;
            }
        }
        bar.inc(1); // Update progress bar
    }

    bar.finish_with_message("Sieve completed!");

    // Collect all prime numbers
    is_prime
        .iter()
        .enumerate()
        .filter(|&(_, &prime)| prime)
        .map(|(index, _)| index)
        .collect()
}

fn save_primes_to_file(primes: &[usize], filename: &str) -> std::io::Result<()> {
    let file = File::create(filename)?;
    let mut writer = BufWriter::new(file);

    for &prime in primes {
        writeln!(writer, "{}", prime)?;
    }

    Ok(())
}

fn main() {
    const LIMIT: usize = 1_000_000_000;
    const OUTPUT_FILE: &str = "prime_numbers.txt";

    println!("Finding all prime numbers up to {}...", LIMIT);

    let start_time = Instant::now();

    // Find all primes using the sieve
    let primes = sieve_of_eratosthenes(LIMIT);

    // Save primes to file
    println!("\nSaving primes to file...");
    match save_primes_to_file(&primes, OUTPUT_FILE) {
        Ok(_) => println!("All primes have been saved to '{}'", OUTPUT_FILE),
        Err(e) => println!("Failed to save primes: {}", e),
    }

    let elapsed_time = start_time.elapsed();
    println!("\nNumber of primes found: {}", primes.len());
    println!("Time taken: {:.2} seconds", elapsed_time.as_secs_f64());
}

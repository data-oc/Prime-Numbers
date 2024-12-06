// .NET 9.0.100

using System.Diagnostics;
using System.Text;

class PrimeNumbers
{
    static void Main(string[] args)
    {
        const int LIMIT = 1000000000; // Limit for prime numbers
        const string OUTPUT_FILE = "prime_numbers.txt"; // File to save primes

        Console.WriteLine($"Finding all prime numbers up to {LIMIT}...\n");

        Stopwatch stopwatch = Stopwatch.StartNew(); // Start the stopwatch

        // Calculate primes
        bool[] isPrime = new bool[LIMIT + 1];
        for (int i = 2; i <= LIMIT; i++)
        {
            isPrime[i] = true;
        }

        int sqrtLimit = (int)Math.Sqrt(LIMIT);

        // Progress bar setup
        int progress = 0;
        int progressStep = sqrtLimit / 100; // Update progress every 1%

        for (int p = 2; p <= sqrtLimit; p++)
        {
            if (isPrime[p])
            {
                for (long multiple = (long)p * p; multiple <= LIMIT; multiple += p)
                {
                    isPrime[(int)multiple] = false;
                }
            }

            // Update progress bar
            if (p % progressStep == 0)
            {
                progress++;
                PrintProgressBar(progress);
            }
        }

        PrintProgressBar(100); // Complete the progress bar
        Console.WriteLine("\n\nFinished sieve computation. \n\nSaving primes to file...");

        // Collect and save primes
        using (StreamWriter writer = new StreamWriter(OUTPUT_FILE))
        {
            int primeCount = 0;

            for (int i = 2; i <= LIMIT; i++)
            {
                if (isPrime[i])
                {
                    primeCount++;
                    writer.WriteLine(i);
                }
            }

            stopwatch.Stop(); // Stop the stopwatch
            double elapsedSeconds = stopwatch.Elapsed.TotalSeconds;

            Console.WriteLine($"All primes have been saved to '{OUTPUT_FILE}'");

            // Results
            Console.WriteLine($"\nNumber of primes found: {primeCount}");
            Console.WriteLine($"Time taken: {elapsedSeconds:F2} seconds");
        }
    }

    static void PrintProgressBar(int progress)
    {
        const int barWidth = 50;
        StringBuilder bar = new StringBuilder();
        bar.Append("[");
        int position = (progress * barWidth) / 100;

        for (int i = 0; i < barWidth; i++)
        {
            if (i < position)
                bar.Append("=");
            else if (i == position)
                bar.Append(">");
            else
                bar.Append(" ");
        }

        bar.Append($"] {progress}%");
        Console.Write($"\r{bar}");
    }
}

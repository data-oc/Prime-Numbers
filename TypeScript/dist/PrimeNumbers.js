"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || (function () {
    var ownKeys = function(o) {
        ownKeys = Object.getOwnPropertyNames || function (o) {
            var ar = [];
            for (var k in o) if (Object.prototype.hasOwnProperty.call(o, k)) ar[ar.length] = k;
            return ar;
        };
        return ownKeys(o);
    };
    return function (mod) {
        if (mod && mod.__esModule) return mod;
        var result = {};
        if (mod != null) for (var k = ownKeys(mod), i = 0; i < k.length; i++) if (k[i] !== "default") __createBinding(result, mod, k[i]);
        __setModuleDefault(result, mod);
        return result;
    };
})();
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const fs = __importStar(require("fs"));
const cli_progress_1 = require("cli-progress");
const perf_hooks_1 = require("perf_hooks");
// Function to find prime numbers using Sieve of Eratosthenes
const sieveOfEratosthenes = (limit) => {
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
    const primes = [];
    for (let i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push(i);
        }
    }
    return primes;
};
// Main function to manage process and display progress
const main = () => __awaiter(void 0, void 0, void 0, function* () {
    const limit = 1000000000; // Define the limit 1 billion
    const chunkSize = 100000; // Process data in chunks to show progress
    const progressBar = new cli_progress_1.SingleBar({}, cli_progress_1.Presets.shades_classic);
    // Start the stopwatch
    const startTime = perf_hooks_1.performance.now();
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
    const endTime = perf_hooks_1.performance.now();
    const elapsedTime = ((endTime - startTime) / 1000).toFixed(2); // Convert to seconds
    console.log(`\nAll primes have been saved to 'prime_numbers.txt'`);
    console.log(`\nNumber of primes found: ${primeCount}`);
    console.log(`Time taken: ${elapsedTime} seconds`);
});
// Run the program
main().catch(err => console.error(err));

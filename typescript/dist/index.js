"use strict";
class TreeNode {
    left;
    right;
    constructor(left, right) {
        this.left = left;
        this.right = right;
    }
    check() {
        if (this.left === null || this.right === null) {
            return 1;
        }
        return 1 + this.left.check() + this.right.check();
    }
}
console.log("Starting benchmarks...\n");
timeBenchmark("1. Fibonacci(42)", () => fibonacci(42));
timeBenchmark("2. Prime Sieve (10M)", () => primeSieve(10_000_000));
timeBenchmark("3. Mandelbrot (2000x2000)", () => mandelbrot(2000));
timeBenchmark("4. Matrix Multiply (500x500)", () => matrixMultiply(500));
timeBenchmark("5. Binary Trees (depth 18)", () => binaryTrees(18));
console.log("\nDone!");
function timeBenchmark(name, action) {
    const start = performance.now();
    const result = action();
    const elapsed = performance.now() - start;
    console.log(`${name}: ${elapsed}ms (result: ${result})`);
}
function fibonacci(n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
function primeSieve(n) {
    const isPrime = new Array(n + 1).fill(true);
    isPrime[0] = isPrime[1] = false;
    for (let i = 2; i * i <= n; i++) {
        if (!isPrime[i])
            continue;
        for (let j = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }
    let count = 0;
    for (let i = 2; i <= n; i++) {
        if (isPrime[i])
            count++;
    }
    return count;
}
function mandelbrot(n) {
    let count = 0;
    const xmin = -2.0;
    const xmax = 1.0;
    const ymin = -1.5;
    const ymax = 1.5;
    const maxIter = 1000;
    for (let py = 0; py < n; py++) {
        for (let px = 0; px < n; px++) {
            const x0 = xmin + ((xmax - xmin) * px) / n;
            const y0 = ymin + ((ymax - ymin) * py) / n;
            let x = 0.0, y = 0.0;
            let iter = 0;
            while (x * x + y * y <= 4.0 && iter < maxIter) {
                const xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter++;
            }
            count += iter;
        }
    }
    return count;
}
function matrixMultiply(n) {
    const a = Array.from({ length: n }, () => new Array(n));
    const b = Array.from({ length: n }, () => new Array(n));
    const c = Array.from({ length: n }, () => new Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    }
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            let sum = 0;
            for (let k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
    return c[Math.floor(n / 2)][Math.floor(n / 2)];
}
function binaryTrees(n) {
    return createTree(n).check();
}
function createTree(n) {
    return n === 0
        ? new TreeNode(null, null)
        : new TreeNode(createTree(n - 1), createTree(n - 1));
}

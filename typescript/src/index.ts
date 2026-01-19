console.log("Starting benchmarks...\n");

timeBenchmark("1. Fibonacci(42)", () => fibonacci(42));
timeBenchmark("2. Prime Sieve (10M)", () => primeSieve(10_000_000));
timeBenchmark("3. Mandelbrot (2000x2000)", () => mandelbrot(2000));
timeBenchmark("4. Matrix Multiply (500x500)", () => matrixMultiply(500));
timeBenchmark("5. Binary Trees (depth 18)", () => binaryTrees(18));

console.log("\nDone!");

function timeBenchmark(name: String, action: () => Object) {
    const start: number = performance.now();
    const result: Object = action();
    const elapsed: number = performance.now() - start;
    console.log(`${name}: ${elapsed}ms (result: ${result})`);
}

function fibonacci(n: number): number {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

function primeSieve(n: number): number {
    const isPrime: boolean[] = new Array(n + 1).fill(true);
    isPrime[0] = isPrime[1] = false;

    for (let i: number = 2; i * i <= n; i++) {
        if (!isPrime[i]) continue;
        for (let j: number = i * i; j <= n; j += i) {
            isPrime[j] = false;
        }
    }

    let count: number = 0;
    for (let i: number = 2; i <= n; i++) {
        if (isPrime[i]) count++;
    }
    return count;
}

function mandelbrot(n: number): number {
    let count: number = 0;
    const xmin: number = -2.0;
    const xmax: number = 1.0;
    const ymin: number = -1.5;
    const ymax: number = 1.5;
    const maxIter: number = 1000;

    for (let py: number = 0; py < n; py++) {
        for (let px: number = 0; px < n; px++) {
            const x0: number = xmin + (xmax - xmin) * px / n;
            const y0: number = ymin + (ymax - ymin) * py / n;
            let x: number = 0.0, y = 0.0;
            let iter: number = 0;

            while (x * x + y * y <= 4.0 && iter < maxIter) {
                const xtemp: number = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter++;
            }
            count += iter;
        }
    }
    return count;
}

function matrixMultiply(n: number): number {
    const a: number[][] = Array.from({ length: n }, () => new Array(n));
    const b: number[][] = Array.from({ length: n }, () => new Array(n));
    const c: number[][] = Array.from({ length: n }, () => new Array(n).fill(0));

    for (let i: number = 0; i < n; i++) {
        for (let j: number = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    }

    for (let i: number = 0; i < n; i++) {
        for (let j: number = 0; j < n; j++) {
            let sum: number = 0;
            for (let k: number = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    return c[Math.floor(n / 2)][Math.floor(n / 2)];
}

function binaryTrees(n: number): number {
    return createTree(n).check();
}

function createTree(n: number): TreeNode {
    return n === 0
        ? new TreeNode(null, null)
        : new TreeNode(createTree(n - 1), createTree(n - 1));
}

class TreeNode {
    private readonly left: TreeNode | null;
    private readonly right: TreeNode | null;
    constructor(left: TreeNode | null, right: TreeNode | null) {
        this.left = left;
        this.right = right;
    }

    check(): number {
        if (this.left === null || this.right === null) {
            return 1;
        }
        return 1 + this.left.check() + this.right.check();
    }
}

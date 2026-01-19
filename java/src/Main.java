void main() {
    System.out.println("Starting benchmarks...\n");

    timeBenchmark("1. Fibonacci(42)", () -> fibonacci(42));
    timeBenchmark("2. Prime Sieve (10M)", () -> primeSieve(10_000_000));
    timeBenchmark("3. Mandelbrot (2000x2000)", () -> mandelbrot(2000));
    timeBenchmark("4. Matrix Multiply (500x500)", () -> matrixMultiply(500));
    timeBenchmark("5. Binary Trees (depth 18)", () -> binaryTrees(18));

    System.out.println("\nDone!");
}

void timeBenchmark(String name, Supplier<Object> action) {
    final Object result;
    long startTime = System.currentTimeMillis();
    result = action.get();
    long elapsedTime = System.currentTimeMillis() - startTime;
    System.out.println(name + ": " + elapsedTime + "ms (result: " + result + ")");
}

long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int primeSieve(int n) {
    final boolean[] isPrime = new boolean[n + 1];
    for (int i = 2; i * i <= n; i++) isPrime[i] = true;

    for (int i = 2; i * i <= n; i++) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= n; i++) isPrime[j] = false;
    }

    int count = 0;

    for (int i = 2; i <= n; i++) if (isPrime[i]) count++;

    return count;
}

int mandelbrot(int n) {
    int count = 0;
    final double xmin = -2.0;
    final double xmax = 1.0;
    final double ymin = -1.5;
    final double ymax = 1.5;
    final int maxIter = 1000;

    for (int py = 0; py < n; py++)
        for (int px = 0; px < n; px++) {
            final double x0 = xmin + (xmax - xmin) * px / n;
            final double y0 = ymin + (ymax - ymin) * py / n;

            double x = 0.0, y = 0.0;
            int iter = 0;

            while (x * x + y * y <= 4.0 && iter < maxIter) {
                var xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter++;
            }

            count += iter;
        }

    return count;
}

double matrixMultiply(int n) {
    final double[][] a = new double[n][n];
    final double[][] b = new double[n][n];
    final double[][] c = new double[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }

    for (var i = 0; i < n; i++)
        for (var j = 0; j < n; j++) {
            double sum = 0;
            for (var k = 0; k < n; k++) sum += a[i][k] * b[k][j];
            c[i][j] = sum;
        }

    return c[n / 2][n / 2];
}

int binaryTrees(int n) {
    return createTree(n).check();
}

TreeNode createTree(int n) {
    return n == 0
            ? new TreeNode(Optional.empty(), Optional.empty())
            : new TreeNode(
            Optional.of(createTree(n - 1)),
            Optional.of(createTree(n - 1)));
}

class TreeNode {
    private final Optional<TreeNode> left;
    private final Optional<TreeNode> right;

    public TreeNode(Optional<TreeNode> left, Optional<TreeNode> right) {
        this.left = left;
        this.right = right;
    }

    public int check() {
        if (left.isEmpty() || right.isEmpty()) return 1;
        return 1 + left.get().check() + right.get().check();
    }
}

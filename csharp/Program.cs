using System.Diagnostics;

Console.WriteLine("Starting benchmarks...\n");

TimeBenchmark("1. Fibonacci(42)", () => Fibonacci(42));
TimeBenchmark("2. Prime Sieve (10M)", () => PrimeSieve(10_000_000));
TimeBenchmark("3. Mandelbrot (2000x2000)", () => Mandelbrot(2000));
TimeBenchmark("4. Matrix Multiply (500x500)", () => MatrixMultiply(500));
TimeBenchmark("5. Binary Trees (depth 18)", () => BinaryTrees(18));

Console.WriteLine("\nDone!");

return;

static void TimeBenchmark(string name, Func<object> action)
{
    var sw = Stopwatch.StartNew();
    var result = action();
    sw.Stop();

    Console.WriteLine($"{name}: {sw.ElapsedMilliseconds}ms (result: {result})");
}

static long Fibonacci(int n)
{
    if (n <= 1) return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

static int PrimeSieve(int n)
{
    var isPrime = new bool[n + 1];
    for (var i = 2; i <= n; i++)
        isPrime[i] = true;

    for (var i = 2; i * i <= n; i++)
    {
        if (!isPrime[i]) continue;
        for (var j = i * i; j <= n; j += i)
            isPrime[j] = false;
    }

    var count = 0;
    for (var i = 2; i <= n; i++)
        if (isPrime[i])
            count++;

    return count;
}

static int Mandelbrot(int n)
{
    var count = 0;
    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.5;
    const double ymax = 1.5;
    const int maxIter = 1000;

    for (var py = 0; py < n; py++)
    for (var px = 0; px < n; px++)
    {
        var x0 = xmin + (xmax - xmin) * px / n;
        var y0 = ymin + (ymax - ymin) * py / n;

        double x = 0.0, y = 0.0;
        var iter = 0;

        while (x * x + y * y <= 4.0 && iter < maxIter)
        {
            var xtemp = x * x - y * y + x0;
            y = 2.0 * x * y + y0;
            x = xtemp;
            iter++;
        }

        count += iter;
    }

    return count;
}

static double MatrixMultiply(int n)
{
    var a = new double[n, n];
    var b = new double[n, n];
    var c = new double[n, n];

    for (var i = 0; i < n; i++)
    for (var j = 0; j < n; j++)
    {
        a[i, j] = i + j;
        b[i, j] = i - j;
    }

    for (var i = 0; i < n; i++)
    for (var j = 0; j < n; j++)
    {
        double sum = 0;
        for (var k = 0; k < n; k++)
            sum += a[i, k] * b[k, j];
        c[i, j] = sum;
    }

    return c[n / 2, n / 2];
}

static int BinaryTrees(int n)
{
    return CreateTree(n).Check();
}

static TreeNode CreateTree(int n)
{
    return n == 0
        ? new TreeNode(null, null)
        : new TreeNode(CreateTree(n - 1), CreateTree(n - 1));
}

internal class TreeNode(TreeNode? left, TreeNode? right)
{
    public int Check()
    {
        if (left == null || right == null)
            return 1;
        return 1 + left.Check() + right.Check();
    }
}

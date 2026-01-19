#include <iostream>
#include <vector>
#include <chrono>
#include <functional>

using namespace std;

class TreeNode {
public:
    TreeNode* left;
    TreeNode* right;

    TreeNode(TreeNode* l, TreeNode* r) : left(l), right(r) {}

    int check() {
        if (left == nullptr || right == nullptr)
            return 1;
        return 1 + left->check() + right->check();
    }

    ~TreeNode() {
        delete left;
        delete right;
    }
};

long fibonacci(int n);
int primeSieve(int n);
int mandelbrot(int n);
double matrixMultiply(int n);
int binaryTrees(int n);
TreeNode* createTree(int n);
template<typename T>
void timeBenchmark(const string& name, function<T()> action);

int main() {
    cout << "Starting benchmarks...\n\n";
    timeBenchmark<long>("1. Fibonacci(42)", []() { return fibonacci(42); });
    timeBenchmark<int>("2. Prime Sieve (10M)", []() { return primeSieve(10'000'000); });
    timeBenchmark<int>("3. Mandelbrot (2000x2000)", []() { return mandelbrot(2000); });
    timeBenchmark<double>("4. Matrix Multiply (500x500)", []() { return matrixMultiply(500); });
    timeBenchmark<int>("5. Binary Trees (depth 18)", []() { return binaryTrees(18); });
    cout << "\nDone!\n";
    return 0;
}

template<typename T>
void timeBenchmark(const string& name, function<T()> action) {
    auto start = chrono::high_resolution_clock::now();
    T result = action();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << name << ": " << elapsed << "ms (result: " << result << ")\n";
}

long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int primeSieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= n; j += i)
            isPrime[j] = false;
    }

    int count = 0;
    for (int i = 2; i <= n; i++)
        if (isPrime[i])
            count++;

    return count;
}

int mandelbrot(int n) {
    int count = 0;
    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.5;
    const double ymax = 1.5;
    const int maxIter = 1000;

    for (int py = 0; py < n; py++) {
        for (int px = 0; px < n; px++) {
            double x0 = xmin + (xmax - xmin) * px / n;
            double y0 = ymin + (ymax - ymin) * py / n;
            double x = 0.0, y = 0.0;
            int iter = 0;

            while (x * x + y * y <= 4.0 && iter < maxIter) {
                double xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter++;
            }
            count += iter;
        }
    }
    return count;
}

double matrixMultiply(int n) {
    vector<vector<double>> a(n, vector<double>(n));
    vector<vector<double>> b(n, vector<double>(n));
    vector<vector<double>> c(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0;
            for (int k = 0; k < n; k++)
                sum += a[i][k] * b[k][j];
            c[i][j] = sum;
        }
    }

    return c[n / 2][n / 2];
}

int binaryTrees(int n) {
    TreeNode* tree = createTree(n);
    int result = tree->check();
    delete tree;
    return result;
}

TreeNode* createTree(int n) {
    return n == 0
        ? new TreeNode(nullptr, nullptr)
        : new TreeNode(createTree(n - 1), createTree(n - 1));
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TreeNode {
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

long fibonacci(int n);
int prime_sieve(int n);
int mandelbrot(int n);
double matrix_multiply(int n);
int binary_trees(int n);
TreeNode* create_tree(int n);
int check_tree(TreeNode* node);
void free_tree(TreeNode* node);
void time_benchmark(const char* name, long (*action)(int), int arg);

int main() {
    printf("Starting benchmarks...\n\n");

    time_benchmark("1. Fibonacci(42)", (long (*)(int))fibonacci, 42);
    time_benchmark("2. Prime Sieve (10M)", (long (*)(int))prime_sieve, 10000000);
    time_benchmark("3. Mandelbrot (2000x2000)", (long (*)(int))mandelbrot, 2000);
    time_benchmark("4. Matrix Multiply (500x500)", (long (*)(int))matrix_multiply, 500);
    time_benchmark("5. Binary Trees (depth 18)", (long (*)(int))binary_trees, 18);

    printf("\nDone!\n");
}

void time_benchmark(const char* name, long (*action)(int), int arg) {
    clock_t start = clock();
    long result = action(arg);
    clock_t end = clock();
    double elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("%s: %.2fms (result: %ld)\n", name, elapsed, result);
}

long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int prime_sieve(int n) {
    bool* is_prime = (bool*)malloc((n + 1) * sizeof(bool));
    for (int i = 0; i <= n; i++)
        is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= n; j += i)
            is_prime[j] = false;
    }

    int count = 0;
    for (int i = 2; i <= n; i++)
        if (is_prime[i])
            count++;

    free(is_prime);
    return count;
}

int mandelbrot(int n) {
    int count = 0;
    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.5;
    const double ymax = 1.5;
    const int max_iter = 1000;

    for (int py = 0; py < n; py++) {
        for (int px = 0; px < n; px++) {
            double x0 = xmin + (xmax - xmin) * px / n;
            double y0 = ymin + (ymax - ymin) * py / n;
            double x = 0.0, y = 0.0;
            int iter = 0;

            while (x * x + y * y <= 4.0 && iter < max_iter) {
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

double matrix_multiply(int n) {
    double** a = (double**)malloc(n * sizeof(double*));
    double** b = (double**)malloc(n * sizeof(double*));
    double** c = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        a[i] = (double*)malloc(n * sizeof(double));
        b[i] = (double*)malloc(n * sizeof(double));
        c[i] = (double*)calloc(n, sizeof(double));
    }

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

    double result = c[n / 2][n / 2];

    for (int i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return result;
}

int binary_trees(int n) {
    TreeNode* tree = create_tree(n);
    int result = check_tree(tree);
    free_tree(tree);
    return result;
}

TreeNode* create_tree(int n) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (n == 0) {
        node->left = NULL;
        node->right = NULL;
    } else {
        node->left = create_tree(n - 1);
        node->right = create_tree(n - 1);
    }
    return node;
}

int check_tree(TreeNode* node) {
    if (node->left == NULL || node->right == NULL)
        return 1;
    return 1 + check_tree(node->left) + check_tree(node->right);
}

void free_tree(TreeNode* node) {
    if (node == NULL) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

import time


def main():
    print("Starting benchmarks...\n")

    time_benchmark("1. Fibonacci(42)", lambda: fibonacci(42))
    time_benchmark("2. Prime Sieve (10M)", lambda: prime_sieve(10_000_000))
    time_benchmark("3. Mandelbrot (2000x2000)", lambda: mandelbrot(2000))
    time_benchmark("4. Matrix Multiply (500x500)", lambda: matrix_multiply(500))
    time_benchmark("5. Binary Trees (depth 18)", lambda: binary_trees(18))

    print("\nDone!")


def time_benchmark(name: str, action):
    start_time: float = time.time()
    result: object = action()
    elapsed_time: float = (time.time() - start_time) * 1000
    print(f"{name}: {elapsed_time}ms (result: {result})")


def fibonacci(n: int) -> int:
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)


def prime_sieve(n: int) -> int:
    is_prime: list[bool] = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, n + 1):
        if i * i > n:
            break
        if not is_prime[i]:
            continue
        for j in range(i * i, n + 1, i):  # Added step parameter i
            is_prime[j] = False

    count: int = 0
    for i in range(2, n + 1):
        if is_prime[i]:
            count += 1
    return count


def matrix_multiply(n: int) -> float:
    a: list[list[float]] = [[0.0] * n for _ in range(n)]
    b: list[list[float]] = [[0.0] * n for _ in range(n)]
    c: list[list[float]] = [[0.0] * n for _ in range(n)]

    for i in range(0, n):
        for j in range(0, n):
            a[i][j] = i + j
            b[i][j] = i - j

    for i in range(0, n):
        for j in range(0, n):
            tot: float = 0
            for k in range(0, n):
                tot += a[i][k] * b[k][j]
            c[i][j] = tot

    return c[n // 2][n // 2]


def binary_trees(n: int) -> int:
    return create_tree(n).check()


def create_tree(n: int) -> TreeNode:
    if n == 0:
        return TreeNode(None, None)
    else:
        return TreeNode(create_tree(n - 1), create_tree(n - 1))


class TreeNode:
    def __init__(self, left: TreeNode | None, right: TreeNode | None):
        self.left: TreeNode | None = left
        self.right: TreeNode | None = right

    def check(self) -> int:
        if self.left is None or self.right is None:
            return 1
        return 1 + self.left.check() + self.right.check()


if __name__ == "__main__":
    main()

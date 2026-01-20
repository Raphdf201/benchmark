package net.raphdf201.benchmark

import kotlin.system.measureTimeMillis

fun main() {
    println("Starting benchmarks...\n")

    timeBenchmark("1. Fibonacci(42)") { fibonacci(42) }
    timeBenchmark("2. Prime Sieve (10M)") { primeSieve(10_000_000) }
    timeBenchmark("3. Mandelbrot (2000x2000)") { mandelbrot(2000) }
    timeBenchmark("4. Matrix Multiply (500x500)") { matrixMultiply(500) }
    timeBenchmark("5. Binary Trees (depth 18)") { binaryTrees(18) }

    println("\nDone!")
}

fun timeBenchmark(name: String, action: () -> Any) {
    var result: Any
    val time = measureTimeMillis {
        result = action()
    }

    println("$name: ${time}ms (result: $result)")
}

fun fibonacci(n: Long): Long {
    if (n <= 1) return n
    return fibonacci(n - 1) + fibonacci(n - 2)
}

fun mandelbrot(n: Int): Int {
    var count = 0
    val xmin = -2.0
    val xmax = 1.0
    val ymin = -1.5
    val ymax = 1.5
    val maxIter = 1000

    for (py in 0 until n) for (px in 0 until n) {
        val x0 = xmin + (xmax - xmin) * px / n
        val y0 = ymin + (ymax - ymin) * py / n

        var x = 0.0
        var y = 0.0
        var iter = 0

        while (x * x + y * y <= 4.0 && iter < maxIter) {
            val xtemp = x * x - y * y + x0
            y = 2.0 * x * y + y0
            x = xtemp
            iter++
        }

        count += iter
    }

    return count
}

fun matrixMultiply(n: Int): Double {
    val a = Array(n) { DoubleArray(n) }
    val b = Array(n) { DoubleArray(n) }
    val c = Array(n) { DoubleArray(n) }

    for (i in 0 until n) for (j in 0 until n) {
        a[i][j] = (i + j).toDouble()
        b[i][j] = (i - j).toDouble()
    }

    for (i in 0 until n) for (j in 0 until n) {
        var sum = 0.0
        for (k in 0 until n) sum += a[i][k] * b[k][j]
        c[i][j] = sum
    }

    return c[n / 2][n / 2]
}

fun binaryTrees(n: Int): Int {
    return createTree(n).check()
}

fun createTree(n: Int): TreeNode {
    return if (n == 0) TreeNode(null, null)
    else TreeNode(createTree(n - 1), createTree(n - 1))
}

class TreeNode(val left: TreeNode?, val right: TreeNode?) {
    fun check(): Int {
        if (left == null || right == null)
            return 1
        return 1 + left.check() + right.check()
    }
}

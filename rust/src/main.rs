use std::time::Instant;

fn main() {
    println!("Starting benchmarks...\n");

    time_benchmark("1. Fibonacci(42)", || Box::new(fibonacci(42)));
    time_benchmark("2. Prime Sieve (10M)", || Box::new(prime_sieve(10_000_000)));
    time_benchmark("3. Mandelbrot (2000x2000)", || Box::new(mandelbrot(2000)));
    time_benchmark("4. Matrix Multiply (500x500)", || {
        Box::new(matrix_multiply(500))
    });
    time_benchmark("5. Binary Trees (depth 18)", || Box::new(binary_trees(18)));

    println!("\nDone!");
}

fn time_benchmark<F>(name: &str, action: F)
where
    F: FnOnce() -> Box<dyn std::fmt::Display>,
{
    let start = Instant::now();
    let result = action();
    let elapsed = start.elapsed();

    println!("{}: {}ms (result: {})", name, elapsed.as_millis(), result);
}

fn fibonacci(n: i64) -> i64 {
    if n <= 1 {
        return n;
    };
    fibonacci(n - 1) + fibonacci(n - 2)
}

fn prime_sieve(n: usize) -> usize {
    let mut is_prime = vec![true; n + 1];

    for i in 2..=n {
        if i * i > n {
            break;
        }
        if !is_prime[i] {
            continue;
        }

        for j in (i * i..=n).step_by(i) {
            is_prime[j] = false;
        }
    }

    is_prime[2..=n].iter().filter(|&&x| x).count()
}

fn mandelbrot(n: i32) -> i32 {
    let mut count = 0;
    const XMIN: f64 = -2.0;
    const XMAX: f64 = 1.0;
    const YMIN: f64 = -1.5;
    const YMAX: f64 = 1.5;
    const MAXITER: i32 = 1000;

    for py in 0..n {
        for px in 0..n {
            let x0 = XMIN + (XMAX - XMIN) * px as f64 / n as f64;
            let y0 = YMIN + (YMAX - YMIN) * py as f64 / n as f64;

            let mut x = 0.0;
            let mut y = 0.0;
            let mut iter = 0;

            while x * x + y * y <= 4.0 && iter < MAXITER {
                let xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                iter += 1;
            }

            count += iter;
        }
    }

    count
}

fn matrix_multiply(n: usize) -> f64 {
    let mut a = vec![vec![0.0; n]; n];
    let mut b = vec![vec![0.0; n]; n];
    let mut c = vec![vec![0.0; n]; n];

    for i in 0..n {
        for j in 0..n {
            a[i][j] = (i + j) as f64;
            b[i][j] = (i as f64) - (j as f64);
        }
    }

    for i in 0..n {
        for j in 0..n {
            let mut sum = 0.0;
            for k in 0..n {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }

    c[n / 2][n / 2]
}

fn binary_trees(n: i32) -> i32 {
    create_tree(n).check()
}

fn create_tree(n: i32) -> TreeNode {
    if n == 0 {
        TreeNode {
            left: None,
            right: None,
        }
    } else {
        TreeNode {
            left: Some(Box::new(create_tree(n - 1))),
            right: Some(Box::new(create_tree(n - 1))),
        }
    }
}

struct TreeNode {
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

impl TreeNode {
    fn check(&self) -> i32 {
        match (&self.left, &self.right) {
            (None, None) => 1,
            (Some(left), Some(right)) => 1 + left.check() + right.check(),
            _ => unreachable!(), // Based on your logic, this case shouldn't happen
        }
    }
}

# Benchmark

i was bored so i coded some benchmarks in some languages that i know

results :

|Language|Fib|Prime sieve|mandelbrot|matrix multiply|binary trees|Variation|
|c|784|30|2937|165|62|no|
|cpp|869|61|2945|175|68|no|
|csharp|1791|38|2961|345|51|no|
|java|1502|72|5168|270|23|no|
|kotlin|1384|75|2954|277|11|jar|
|kotlin|835|27|1562|181|54|native|
|python|63471|1214|199610|15652|262|cpython|
|python|10487|361|7717|8001|122|pypy|
|rust|1091|61|2898|213|64|no|
|typeshit|4328|247|2922|434|54|node|
|typeshit|2563|230|2947|585|49|bun|

times in ms

other info :
c 23 msvc
cpp 26 msvc
csharp 14 dotnet 10
java 25 adoptium jdk
kotlin 2.3.0 adoptium jdk (25)
python 3.14
rust 2024 cargo 1.92.0 target x64-windows-msvc
ts 5.5.3 node 24.12.0 bun 1.3.6 target es2024

plugins {
    kotlin("jvm") version "2.3.0"
    application
}

group = "net.raphdf201.benchmark"
version = "1.0"

repositories {
    mavenCentral()
}

kotlin {
    jvmToolchain(25)
}

application {
    mainClass = "net.raphdf201.benchmark.MainKt"
}

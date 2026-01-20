echo compile the c and cpp versions yourself
cd ./csharp
dotnet build -c Release
cd ../java
./gradlew build
./gradlew installDist
cd ../kotlin
./gradlew build
./gradlew installDist
cd ../rust
cargo build --release
cd ../typescript
pnpm install
pnpm run build

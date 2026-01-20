Write-Output "compile the c and cpp versions yourself"
Set-Location .\csharp
dotnet build -c Release
Set-Location ..\java
.\gradlew build
.\gradlew installDist
Set-Location ..\kotlin
.\gradlew build
.\gradlew installDist
Set-Location ..\rust
cargo build --release
Set-Location ..\typescript
pnpm install
pnpm run build

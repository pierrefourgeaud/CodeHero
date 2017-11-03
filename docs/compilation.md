# How to compile

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Start

```
cd ..
./out/bin/CodeHero
```

Or (on Windows):

```
cd ..
./out/bin/(Release/Debug)/CodeHero.exe
```
## Test

```
cd build
cmake -D_CODEHERO_BUILD_TESTS=ON ..
cmake --build .
../out/bin/CodeHeroSpecs # (You know the drill for Windows)
```

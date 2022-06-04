[![CI](https://github.com/PlatformerTeam/mad/actions/workflows/build_and_run_tests.yml/badge.svg)](https://github.com/PlatformerTeam/mad/actions/workflows/build_and_run_tests.yml)
# MAD
MAD - 2D platformer game with the ability to create your own levels.
## Installation
### Linux
```bash
sudo apt update 
sudo apt-get install libsfml-dev xorg-dev libglu1-mesa-dev
git clone https://github.com/PlatformerTeam/mad.git@release_branch --recursive
mkdir build
cmake -S . -B build -DCMAKE_CXX_COMPILER="g++-10"
cmake --build build/
```
### Mac OS
```bash
brew install sfml
git clone https://github.com/PlatformerTeam/mad.git@release_branch --recursive
mkdir build
cmake -S . -B build -DCMAKE_CXX_COMPILER="clang++" -stdlib=libstdc++
cmake --build build/
```

## Usage

## License
[MIT License](https://github.com/PlatformerTeam/mad/blob/main/LICENSE)

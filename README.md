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
You can create your own level. in order to do this, you need to create two files: **config.json** and text file **map**.\
Map file may contain the following elements: \
| Sign | Meaning |
|:----:|:-------:|
| H    | Hero    |
| E | Enemy - *type 1*) |
| Z | Enemy - *type 2* |
| F | Finish block |
| # | Ground block |
| @ | Unstable block |
| `[` | Begin block |
| _ | Middle block|
| `]` | End block |
| + | Separate block |
| * | Decoration - *type 1* |
| & | Decoration - *type 2* |
| ^ | Decoration - *type 3* |
| . | Empty |


## License
[MIT License](https://github.com/PlatformerTeam/mad/blob/main/LICENSE)

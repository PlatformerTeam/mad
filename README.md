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
| Sign | Meaning              | Description |
|:----:|:--------------------:|:-----------:|
| `H` | Hero                  | The character you control |
| `E` | Enemy - *type 1*)     | An opponent who can attack you |
| `Z` | Enemy - *type 2*      | You can add a second type of enemy |
| `F` | Finish block          | The block with which the level was successfully completed when touched |
| `#` | Ground block          | A monolithic block describing the earth |
| `@` | Unstable block        | A block that the hero can move |
| `[` | Begin block           | The initial block in the block strip |
| `_` | Middle block.         | The finite block in the block strip |
| `]` | End block             | The middle block in the block strip |
| `+` | Separate block        | A block outside the block strip |
| `*` | Decoration - *type 1* | Any object not involved in physics |
| `&` | Decoration - *type 2* | Other type of decoration |
| `^` | Decoration - *type 3* | Other type of decoration |
| `.` | Empty                 | You can also use ` ` |


## License
[MIT License](https://github.com/PlatformerTeam/mad/blob/main/LICENSE)

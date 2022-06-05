[![CI](https://github.com/PlatformerTeam/mad/actions/workflows/build_and_run_tests.yml/badge.svg)](https://github.com/PlatformerTeam/mad/actions/workflows/build_and_run_tests.yml)
# MAD
MAD - 2D platformer game with the ability to create your own levels.
![](https://github.com/PlatformerTeam/mad/blob/main/pictures/default.png)
## Features
* Opportunity to configurate own levels
  * Debug mode to set up physics
  * Blocks - 7 types
  * Backgrounds - any count of layers with custom parallax ratios
  * Decoration - 3 types
  * Mobs
    * A lot of types of action
    * Individual customization for each action - frame time, scale and other
  * Camera 
    * Smoothness
    * Types of following - forward and backward
    * Zoom
    * Location regarding the character
* Opportunity to create level map using text file
* Opportunity to share your levels using database
* Complete games with 3 levels
* An expandable game capable of turning into an open-source
## Installation
### Dependencies and submodules
- [SFML](https://www.sfml-dev.org)
- [posgresql](https://www.postgresql.org)
- [Box2D](https://github.com/erincatto/box2d)
- [Googletest](https://github.com/google/googletest)
- [Imgui](https://github.com/ocornut/imgui)
- [Imgui-sfml](https://github.com/eliasdaler/imgui-sfml)
- [Json](https://github.com/nlohmann/json)
- [libpqxx](https://github.com/jtv/libpqxx)
- [spdlog](https://github.com/gabime/spdlog)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
### Linux
```bash
sudo apt update 
sudo apt-get install libsfml-dev xorg-dev libglu1-mesa-dev postgresql-server-dev-all
git clone https://github.com/PlatformerTeam/mad.git@release_branch --recursive
mkdir build
cmake -S . -B build -DCMAKE_CXX_COMPILER="g++-10"
cmake --build build/
```
### Mac OS
If necessary, install [Homebrew](https://brew.sh).
```bash
brew install sfml postgresql
git clone https://github.com/PlatformerTeam/mad.git@release_branch --recursive
mkdir build
cmake -S . -B build -DCMAKE_CXX_COMPILER="clang++" -stdlib=libstdc++
cmake --build build/
```
### Connection to database
```bash 
sudo -i -u postgres
createuser -P --interface
# here enter your username and empty password
createdb *username* # your username from the top line
createdb mad
```

## Run game
### Game with default levels
```bash
./game_database_example
```
### Game with custom levels
Look [`Upload levels`](https://github.com/PlatformerTeam/mad/blob/create-readme/README.md#upload-levels)

## Usage
### Create Levels
You can create your own level. in order to do this, you need to create two files: `config.json` and text file `map`.\
`Map` file may contain the following elements: 
| Sign | Meaning              | Description |
|:----:|:--------------------:|:-----------:|
| `H` | Hero                  | The character you control |
| `E` | Enemy - *type 1*      | An opponent who can attack you |
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
| `.` | Empty                 | You can also use  ` ` |

`Config.json` prototype: 
```json
{
  "name" : "level_01",
  "animated_resources" : "../../game/resources/animated/",
  "block" : 10.0,
  "static_resources" : "../../game/resources/static/block_01",
  "decoration_resources" : "../../game/resources/decoration/decoration_01",
  "camera": {
    "position" : {
      "x" : 10.0,
      "y" : 10.0
    },
    "smoothness": 0.05,
    "zoom": 0.1,
    "follow_type" : "forward",
    "minimal_distance" : 7.0,
    "part_of_window" : 0.25
  },
  "background" : {
    "source" : "../../game/resources/background/background_01",
    "parallax_ratios" : [0.95, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65]
  },
  "texture" : {
    "unstable_block" : "unstable_block.png",
    "ground_block" : "ground_block.png",
    "finish_block" : "finish_block.png",
    "begin_block" : "begin_block.png",
    "middle_block" : "middle_block.png",
    "end_block" : "end_block.png",
    "separate_block" : "separate_block.png"
  },
  "decoration" : {
    "decoration_01" : {
      "source" : "arrow.png",
      "scale" : 1,
      "delta_x" : 0,
      "delta_y" : 20
    } // You can add other decorations
  } 
  "hero" : {
    "source" : "hero",
    "animated" : {
      "size_width": 5.5,
      "size_height": 9,
      "size_scale": 0.3,
      "delta_x" : 0,
      "delta_y" : 3,
      "actions" : {
        "idle" : {
          "source": "hero_idle",
          "type": "several_files",
          "delta_time": 200
        },
        "run" : {
          "source": "hero_run",
          "type": "several_files",
          "delta_time": 130
        } // You can add other actions
      }
    }
  },
  "enemy" : {
    "source" : "enemy",
    "animated" : {
      "size_width": 5.5,
      "size_height": 5,
      "size_scale": 0.3,
      "delta_x" : 0,
      "delta_y" : 3,
      "actions" : {
        "idle" : {
          "source": "enemy_idle",
          "type": "several_files",
          "delta_time": 200
        },
        "run" : {
          "source": "enemy_run",
          "type": "several_files",
          "delta_time": 130
        } // You can add other actions
      }
    }
  }
}
```
To set up physics you may turn on `DEBUG_MODE`. To enable it, you need to **build** a project with a flag `-DDEBUG_MODE`: \
For instance: \
**Mac OS**
```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER="clang++" -stdlib=libstdc++ -DDEBUG_MODE
```
**Linux**
```bash
cmake -S . -B build -DCMAKE_CXX_COMPILER="g++-10" -DDEBUG_MODE
```
### Upload levels
To add levels in database you must put a directory with your level in a directory `resources`. After that you must **run server**.
```bash
./simple-server
```
Using server window you must add your level - **enter level name** and **start server**.
![](https://github.com/PlatformerTeam/mad/blob/main/pictures/server.png) \
To launch added levels run client:
```bash
./simple-client
```
## License
[MIT License](https://github.com/PlatformerTeam/mad/blob/main/LICENSE)

# MAD Code Style Conventions

Almost all rules are formalized at the [.clang-format](../.clang-format), and
[ide/intellij_code_style.xml](../ide/intellij_code_style.xml)
(if you are using CLion for the development).
This rules will be repeated here and some other
conventions will be formalized.

## Naming

* Namespaces: lowercase
* Types (classes, aliases, structs, etc.): PascalCase
* Variables: snake_case
* Struct's members: snake_case
* Class's members: m_snake_case
* Methods: snake_case
* Private methods: m_snake_case
* Functions: snake_case
* Source files: PascalCase.cpp
* Header files: PascalCase.hpp
* Macros: SCREAMING_SNAKE_CASE
* Enums: PascalCase
* Enum elements: PascalCase

## Classes & Structures

Since C++ provide us both `struct` and `class`
keywords, lets define when and how should we use them.

- `struct`. Structures represent some set of
immutable information. It does not contain
private members. All members of `struct`
should be marked `const`. It may have
several methods or operators, if necessary.
- `class`. Classes should be used in
all other cases. If some type has a
lot of functionality, it has complicated
state - it is a class. Class does not contain
public fields.

## Header guards

We use combination of `#ifndef, #define, #endif`.
The defining macro should have a following structure:
`MAD_${PROJECT_REL_PATH}_${FILE_NAME}_${EXT}`. And
closing `#endif` should contain an inline comment,
which describes the closing macro.

## Includes order

There are three groups of includes:

- Class header
- Project API
- Project's dependencies
- C++ standard library

They should be placed into the file in this
order. And each group should be divided from
another by an empty line. And in each
group includes should be ordered by their name.
And after goes header associated with the
cpp file.
For example:

```c++
#include "Enemy.hpp"

#include <core/abstract/Renderable.hpp>
#include <core/visual/Camera.hpp>
#include <npc/Turtle.hpp>

#include <boost/config.hpp>
#include <box2d/box2d.h>
#include <box2d/b2_timer.h>
#include <imgui/imgui.h>

#include <cassert>
#include <iosteram>
#include <vector>
```

There will be a lot of source files in our
project. And in order to reduce compilation
time, we need to use forward declarations, when possible.
For example, if in the header file we only
store a pointer at some other object, we
don't need to actually `#include` this file.

**Wrong**
```c++
#include <core/entity/Entity.hpp>

namespace core {
    class A {
    private:
        std::shared_ptr<Entity> m_entity;    
    };
}
```

Instead, we could write something like

**Correct**
```c++

// Forward declarations
namespace core {
    class Entity;
}

namespace core {
    class A {
    private:
        std::shared_ptr<Entity> m_entity;    
    };
}
```

In this case, we won't need to rebuild this file,
each time when `Entity.hpp` is modified.

## Namespaces

We have one shared namespace for the whole
project: `mad`. And each directory, which is
a direct children of the root directory,
also has a separate namespace, for example:

- `::mad::core` for the files in the [core](./core)
directory
- `::mad::game` for the files in the [game](./game)
directory

### Example

- **core/some/path/Object.hpp**
```c++
#ifndef MAD_CORE_SOME_PATH_OBJECT_HPP
#define MAD_CORE_SOME_PATH_OBJECT_HPP

#include <vector>

#include <imgui/imgui.h>


namespace core {
    class Object {
    public:
        enum Type {
            Default,
            SomeOther,
        };
        
        struct Info {
            const std::string stuff;
        };
        
    public:
        explicit Object(std::size_t size,
                        std::string name);
        
        void foo() const noexcept;
        
    private:
        std::size_t m_size{};
        std::string m_name{};
    };
}

#endif// MAD_CORE_SOME_PATH_OBJECT_HPP
```

- **core/some/path/Object.cpp**

```c++
#include "Object.hpp"

#include <iosteram>


namespace core {
    Object::Object(std::size_t size,
                   std::string name)
        : m_size(size),
          m_name(std::move(name)) {
    }
    
    void Object::foo() const noexcept {
        std::cout << "foo" << std::endl;
    }
}
```

<a name="readme-top"></a>

<div align="center">
  <h2 align="center">ICP project</h2>

  <p align="center">
    Project for ICP course at FIT VUT university in Brno
  </p>
</div>

<br/>

### Table of contents

  <li><a href="#installation">Installation</a></li>
  <li><a href="#codeguide">Codeguide</a></li>
  <li><a href="#authors">Authors</a></li>

## Installation

1. Clone the repo

   ```sh
   git clone https://github.com/Mirek321/ICP-Project
   ```

2. CD to the cloned directory

   ```sh
   cd ICP-Project
   ```

3. Compile

   ```sh
   make
   ```

4. Run

   ```sh
   make run
   ```

## Codeguide

- Code names and comments in English
- Git commit messages in English prefixed
- New branch per new issue. Name of the branch format:  issue-issueID-issueName, example: issue-40-get-sthit-done
  
```cpp
// Variables, function parameters, class members (snake_case)
const std::string snake_case_variable;
void function(int snake_case1, const std::string& snake_case2);

// Enums, structs, classes, and types (PascalCase, values: SCREAMING_SNAKE_CASE)
enum class TokenType
{
    EMPTY,
    PLUS,
    UNKNOWN,
    KEYWORD,
    ...
};

struct Token
{
    TokenType type;
    TokenAttribute attribute;
};

class Scanner
{
public:
    Token get_token();
};

// Function names (snake_case with curly braces on next line)
int function_name(...)
{
    ...
}

// Member function names (snake_case, prefixed with class/module name)
Token Scanner::get_token()
{
    ...
}

// Includes (C++ standard libraries first, then third-party, then project headers)
#include <iostream>
#include <vector>

#include "scanner.h"

// Header guards (uppercase snake case with prefix `_` and suffix `_HPP`)
#ifndef _MODULE_NAME_HPP
#define _MODULE_NAME_HPP

#endif // _MODULE_NAME_HPP

// Documentation comments
/**
 * @brief Brief description of function
 * @param token Lexer token
 * @return Describe return value
 */
int function_name(Token token, ...)
{
    ...
}

/**
 * @enum TokenType
 * @brief Type of token
 */
enum class TokenType
{
    EMPTY,   ///< Empty
    PLUS,    ///< +
    UNKNOWN, ///< Unknown
    KEYWORD, ///< Keyword
    ...
};

/**
 * @struct Token
 * @brief Representation of a single token
 */
struct Token
{
    TokenType type;          ///< Type of token
    TokenAttribute attribute; ///< Attribute of given token
};

/**
 * @file scanner.cpp
 * @brief Lexical analyzer (scanner) implementation
 * @author Miroslav Basista <xbasism0000@stud.fit.vutbr.cz>
 * @author ...
 */


```

## Authors

- Miroslav Bašista <xbasism00@stud.fit.vutbr.cz>

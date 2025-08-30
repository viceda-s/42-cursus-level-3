# Minishell Project Structure Guide

## Complete Project Structure

```
minishell/
├── Makefile
├── .gitignore
├── README.md
├── en.subject.pdf              # Project subject in English
├── minishell                   # Compiled executable
├── libft/                      # Libft library (already exists on user's computer)
│   ├── Makefile
│   ├── include/                # Main libft header
│   │   └── libft.h
│   ├── src/                    # Integrated libft functions
│   │   ├── char/               # Character validation functions
│   │   ├── conversion/         # Type conversion functions
│   │   ├── fd/                 # File descriptor functions
│   │   ├── ft_printf/          # Printf implementation
│   │   ├── gnl/                # Get Next Line
│   │   ├── list/               # Linked list functions
│   │   ├── memory/             # Memory management functions
│   │   └── string/             # String manipulation functions
│   ├── obj/                    # Object files for libft
│   └── libft.a                 # Compiled library
├── inc/                        # Main project headers
│   ├── minishell.h             # Main header
│   ├── lexer.h                 # Lexer definitions
│   ├── parser.h                # Parser definitions
│   ├── executor.h              # Executor definitions
│   └── builtins.h              # Built-in commands definitions
├── src/                        # Main source code
│   ├── main.c                  # Program entry point
│   ├── init.c                  # Shell initialization
│   ├── prompt.c                # Prompt management
│   ├── signals.c               # Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
│   ├── cleanup.c               # Memory and resource cleanup
│   ├── utils.c                 # General utilities
│   ├── lexer/                  # Lexical analysis (tokenization)
│   │   ├── lexer.c             # Main lexer function
│   │   ├── tokenizer.c         # Input tokenization
│   │   ├── tokenizer_utils.c   # Tokenizer utilities
│   │   ├── token_utils.c       # Token utilities
│   │   └── quote_handler.c     # Single and double quote handling
│   ├── parser/                 # Syntax analysis
│   │   ├── parser.c            # Main parser function
│   │   ├── parser_new.c        # New parser implementation
│   │   ├── ast_builder.c       # Abstract Syntax Tree construction
│   │   ├── ast_utils.c         # AST utilities
│   │   ├── syntax_checker.c    # Syntax verification
│   │   ├── syntax_utils.c      # Syntax utilities
│   │   ├── parse_helpers.c     # Parser helper functions
│   │   └── parse_utils.c       # Parser utilities
│   ├── expander/               # Variable expansion
│   │   ├── expander.c          # Main expander function
│   │   ├── expander_utils.c    # Expander utilities
│   │   ├── env_expansion.c     # Environment variable expansion
│   │   └── exit_code.c         # $? handling
│   ├── executor/               # Command execution
│   │   ├── executor.c          # Main execution function
│   │   ├── command_exec.c      # External command execution
│   │   ├── arg_expansion.c     # Argument expansion
│   │   ├── pipe_handler.c      # Pipe management
│   │   ├── redirect_handler.c  # Redirection management
│   │   ├── redirect_utils.c    # Redirection utilities
│   │   ├── heredoc.c          # << (heredoc) implementation
│   │   ├── process_manager.c   # Process management (fork, wait)
│   │   ├── path_resolver.c     # Path resolution
│   │   └── handle_error.c      # Error handling
│   ├── builtins/               # Built-in commands
│   │   ├── builtin_handler.c   # Built-in identification and calling
│   │   ├── echo.c              # echo command
│   │   ├── cd.c                # cd command
│   │   ├── pwd.c               # pwd command
│   │   ├── export.c            # export command
│   │   ├── export_utils.c      # export utilities
│   │   ├── unset.c             # unset command
│   │   ├── env.c               # env command
│   │   └── exit.c              # exit command
│   ├── environment/            # Environment variable management
│   │   ├── env_manager.c       # Main environment management
│   │   ├── env_utils.c         # Environment utilities
│   │   └── path_resolver.c     # Path resolution ($PATH)
│   └── utils/                  # General utilities
│       ├── error_handler.c     # Error management
│       ├── memory_utils.c      # Memory utilities
│       ├── string_utils.c      # String utilities
│       └── debug.c             # Debug functions (optional)
├── bonus/                      # Bonus features (if implemented)
│   ├── logical_ops.c           # Logical operators && and ||
│   ├── parentheses.c           # Parentheses management
│   └── advanced_wildcards.c    # Advanced wildcards
└── obj/                        # Object files (created by Makefile)
    ├── cleanup.o
    ├── init.o
    ├── main.o
    ├── prompt.o
    ├── signals.o
    ├── utils.o
    ├── builtins/               # Built-in object files
    ├── environment/            # Environment object files
    ├── executor/               # Executor object files
    ├── expander/               # Expander object files
    ├── lexer/                  # Lexer object files
    ├── parser/                 # Parser object files
    └── utils/                  # Utils object files
```

## Main Component Descriptions

### 1. LEXER (Lexical Analysis)
- **Function**: Converts input string into tokens
- **Responsibilities**:
  - Identifies words, operators, redirections
  - Handles single and double quotes
  - Removes unnecessary spaces
- **Example**: `"echo hello | grep h"` → `[WORD, WORD, PIPE, WORD, WORD]`

### 2. PARSER (Syntax Analysis)
- **Function**: Builds an Abstract Syntax Tree (AST)
- **Responsibilities**:
  - Verifies command syntax
  - Organizes hierarchical command structure
  - Identifies pipes, redirections, commands
  - Detects syntax errors

### 3. EXPANDER (Expansion)
- **Function**: Expands variables and wildcards
- **Responsibilities**:
  - Expands environment variables ($VAR)
  - Expands exit code ($?)
  - Handles wildcards (*) if implemented (bonus)
  - Removes quotes after expansion

### 4. EXECUTOR (Execution)
- **Function**: Executes commands based on the AST
- **Responsibilities**:
  - Manages processes (fork/exec)
  - Implements pipes and redirections
  - Calls built-ins when necessary
  - Manages file descriptors

### 5. BUILT-INS
- **Function**: Internal shell commands
- **Mandatory commands**:
  - `echo` (with -n option)
  - `cd` (relative or absolute path only)
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options or arguments)
  - `exit` (no options)
- **Characteristics**: Executed in main process (no fork)

### 6. ENVIRONMENT
- **Function**: Environment variable management
- **Responsibilities**:
  - Inheritance from parent process
  - Modifications via export/unset
  - PATH resolution for executables

## Mandatory Features

### Interface
- ✅ Show prompt when waiting for command
- ✅ Functional history
- ✅ Search and launch executables (PATH, relative/absolute path)

### Parsing and Syntax
- ✅ Don't interpret unclosed quotes
- ✅ Don't interpret unrequired special characters (\, ;)
- ✅ Handle single quotes (') - prevents metacharacter interpretation
- ✅ Handle double quotes (") - prevents interpretation except $

### Redirections
- ✅ `<` redirect input
- ✅ `>` redirect output
- ✅ `<<` heredoc with delimiter
- ✅ `>>` redirect output in append mode

### Pipes and Variables
- ✅ Implement pipes (`|`)
- ✅ Handle environment variables (`$VAR`)
- ✅ Handle `$?` (exit code)

### Signals
- ✅ `ctrl-C` - new prompt on new line (interactive mode)
- ✅ `ctrl-D` - exit shell
- ✅ `ctrl-\` - do nothing

### Global Variable
- ⚠️ **IMPORTANT**: Use only ONE global variable to indicate received signal
- ⚠️ This variable must contain ONLY the signal number
- ⚠️ "Norm" structures in global scope are **FORBIDDEN**

## Bonus Features

### Logical Operators
- ✅ `&&` and `||` with parentheses for priorities

### Wildcards
- ✅ `*` must work for current directory

**⚠️ WARNING**: Bonus features are only evaluated if the mandatory part is **PERFECT**

## Getting Started Commands

### 1. Create initial structure
```bash
mkdir minishell
cd minishell
mkdir -p src/{lexer,parser,expander,executor,builtins,environment,utils}
mkdir -p inc bonus tests obj
```

### 2. Copy libft
```bash
# Assuming libft is in ~/libft
cp -r ~/libft ./libft
```

### 3. Create basic files
```bash
touch Makefile
touch inc/{minishell.h,lexer.h,parser.h,executor.h,builtins.h}
touch src/main.c src/init.c src/prompt.c src/signals.c src/cleanup.c
```

### 4. Configure git
```bash
git init
echo "obj/" > .gitignore
echo "minishell" >> .gitignore
echo ".DS_Store" >> .gitignore
```

## Implementation Tips

### Suggested Development Order

1. **Initial setup**
   - Functional Makefile
   - Basic structures
   - Shell initialization

2. **Basic prompt**
   - Functional readline
   - Main loop
   - Basic signal handling

3. **Lexer**
   - Simple tokenization
   - Quote handling
   - Operator identification

4. **Simple built-ins**
   - echo, pwd, env
   - exit
   - basic cd

5. **Basic parser**
   - Simple commands without pipes
   - Syntax checking

6. **Basic executor**
   - Simple command execution
   - Built-ins vs external

7. **Environment variables**
   - Basic expansion
   - export/unset
   - $?

8. **Redirections**
   - <, >, >>
   - Heredoc (<<)

9. **Pipes**
   - Simple pipes
   - Multiple pipes

10. **Refinements**
    - Error handling
    - Memory leaks
    - Extensive testing

### Important Concepts

#### Shell Process
1. **Read** user input
2. **Tokenize** (lexer)
3. **Parse** syntax (parser)
4. **Expand** variables (expander)
5. **Execute** commands (executor)
6. **Repeat**

#### Memory Management
- Always check malloc returns
- Free all allocated memory
- Use valgrind to check leaks
- Implement cleanup functions

#### File Descriptors
- 0: stdin
- 1: stdout
- 2: stderr
- Always dup/dup2 before modifying
- Restore original FDs after use

## Useful Resources

### Allowed Functions
- **readline**: `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`
- **I/O**: `printf`, `write`, `read`, `open`, `close`
- **Memory**: `malloc`, `free`
- **Processes**: `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `execve`
- **Signals**: `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`
- **System**: `access`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`
- **Pipes**: `dup`, `dup2`, `pipe`
- **Directories**: `opendir`, `readdir`, `closedir`
- **Errors**: `strerror`, `perror`
- **Terminal**: `isatty`, `ttyname`, `ttyslot`, `ioctl`, `tcsetattr`, `tcgetattr`
- **Termcap**: `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`
- **Environment**: `getenv`, `exit`

### Recommended Tests
```bash
# Basic commands
echo hello
pwd
env

# Pipes
ls | grep txt
cat file | head -5 | tail -2

# Redirections
echo hello > file
cat < file
echo world >> file

# Variables
export TEST=hello
echo $TEST
echo $?

# Built-ins
cd /tmp
pwd
export PATH=/bin:/usr/bin
unset TEST

# Quotes
echo "hello world"
echo 'hello $USER'
echo "hello $USER"

# Signals
# Test Ctrl+C, Ctrl+D, Ctrl+\ in different situations
```

## 42 Norm

### Important Rules
- Maximum 25 lines per function
- Maximum 80 columns per line
- Maximum 4 parameters per function
- Maximum 5 variables per function
- Indentation with 4 spaces (tabs)
- Mandatory headers in all files
- Variable names in snake_case
- Structures start with s_
- Typedefs start with t_
- Globals start with g_

### Mandatory Makefile
- Rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- Must not relink unnecessarily
- Must compile libft automatically
- Mandatory flags: `-Wall -Wextra -Werror`

## Conclusion

This structure provides a solid foundation for developing the Minishell project. The modular organization facilitates maintenance, debugging, and collaboration. Remember to:

1. **Start simple** and increment features
2. **Test constantly** each new functionality
3. **Check the norm** regularly
4. **Manage memory** carefully
5. **Document** code appropriately

The Minishell project is complex, but with this organized structure and incremental development, it will be more manageable and successful.

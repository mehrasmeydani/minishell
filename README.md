# Minishell

A lightweight Unix shell implementation written in C.  This project recreates basic bash functionality, handling command execution, pipes, redirections, environment variables, and built-in commands.

## What This Does

Minishell is a command-line interpreter that reads user input, parses it, and executes commands just like bash. It supports complex command pipelines, input/output redirection, heredocs, environment variable expansion, and signal handling.

## How It Works

### Main Loop

The shell runs in a continuous loop that:
1. Displays a prompt (`minishell>`)
2. Reads user input using readline
3. Parses the input into tokens
4. Expands variables and removes quotes
5. Executes the commands
6. Repeats

### Parsing Pipeline

The input goes through several stages: 

**Tokenization** (`mini_split. c`)
- Splits input on spaces while respecting quotes
- Handles single quotes, double quotes, and escape sequences

**Lexical Analysis** (`lexer.c`)
- Separates commands by pipe symbols (`|`)
- Identifies and extracts redirection operators (`<`, `>`, `<<`, `>>`)
- Creates a linked list of command nodes, each containing:  
  - Command and arguments
  - Associated redirections

**Expansion** (`expansion/`)
- Expands environment variables (`$VAR`, `$? `)
- Handles quote removal
- Processes wildcards (if implemented)
- Different behavior inside single vs double quotes

**Heredoc Processing** (`heredoc.c`)
- Reads multi-line input until delimiter
- Creates temporary files in `/tmp/`
- Expands variables in heredoc content (unless delimiter is quoted)

### Execution Engine

The execution system is in the `pipex/` directory and handles: 

**Command Lookup** (`command_check.c`, `path_construct.c`)
- Searches for executables in PATH directories
- Handles absolute and relative paths
- Checks file permissions

**Process Management** (`child_spawning.c`)
- Forks child processes for each command in a pipeline
- Uses only two pipe file descriptors (alternating between them)
- Waits for all children to complete

**Pipe Handling** (`pipe_dup.c`)
- Connects commands with pipes
- Duplicates file descriptors for stdin/stdout redirection
- Closes unused pipe ends

**Redirections** (`file_check.c`)
- Handles input redirection (`<`)
- Handles output redirection (`>`)
- Handles append mode (`>>`)
- Handles heredocs (`<<`)
- Opens files with appropriate permissions
- Applies redirections left-to-right

### Built-in Commands

The shell implements these built-ins (`builtins/`):

- `echo` - with `-n` flag support
- `cd` - change directory (relative and absolute paths)
- `pwd` - print working directory
- `export` - set environment variables
- `unset` - remove environment variables
- `env` - display environment variables
- `exit` - exit the shell with status code

Built-ins run in the parent process when they're the only command (no pipes), otherwise they fork like external commands.

### Environment Variables

**Storage** (`env_var.c`)
- Maintains environment as an array of strings
- Stores both raw format (`VAR=value`) and parsed format
- Updates dynamically with `export` and `unset`

**Expansion** (`expand.c`)
- `$VAR` expands to variable value
- `$?` expands to last exit status
- Variables don't expand in single quotes
- Variables expand in double quotes and unquoted text

### Signal Handling

- `Ctrl+C` (SIGINT): Displays new prompt, doesn't exit
- `Ctrl+\` (SIGQUIT): Ignored in interactive mode
- `Ctrl+D` (EOF): Exits the shell cleanly

### Memory Management

The codebase uses custom cleanup functions:  
- `lex_clear()` - frees lexer linked list
- `redirect_clear()` - frees redirection list
- `ft_free()` - frees string arrays
- `free_env()` - frees environment variables
- Proper cleanup on errors and exit

### Data Structures

**Main Shell Structure** (`t_minishell`)
```c
typedef struct s_minishell {
    char        *in;          // Raw input string
    char        **out;        // Tokenized output
    t_lex       *lex;         // Linked list of commands
    t_expand    expd;         // Expansion data
    t_env       env;          // Environment variables
    int         error_code;   // Last command exit status
} t_minishell;
```

**Command Node** (`t_lex`)
```c
typedef struct s_lex {
    char            **cmd;     // Command and arguments
    t_redirect      *redic;    // Redirections for this command
    struct s_lex    *next;     // Next command in pipeline
} t_lex;
```

**Redirection** (`t_redirect`)
```c
typedef struct s_redirect {
    char                *name;          // Filename
    int                 fd;             // File descriptor
    char                *input;         // Heredoc content
    int                 input_expand;   // Whether to expand heredoc
    t_redir_type        level;          // Type:  INFILE/OUTFILE/HEREDOC/APPEND
    struct s_redirect   *next;          // Next redirection
} t_redirect;
```

## Building

```bash
make
```

This compiles the shell and the included `libft` library. The Makefile includes:  
- Compilation with `-Wall -Wextra -Werror`
- Linking with readline library
- Clean targets (`clean`, `fclean`, `re`)

## Usage

```bash
./minishell
```

Once running, you can use it like bash: 

```bash
minishell> echo Hello World
Hello World

minishell> ls -la | grep minishell

minishell> cat < input.txt | grep pattern > output.txt

minishell> cat << EOF
> line 1
> line 2
> EOF

minishell> export MY_VAR=test
minishell> echo $MY_VAR
test

minishell> exit
```

## Project Structure

```
.
├── header/           # Header files
│   ├── minishell.h   # Main header
│   ├── execution. h   # Execution functions
│   ├── lexer.h       # Lexer structures
│   ├── redirect.h    # Redirection structures
│   └── expand.h      # Expansion structures
├── srcs/             # Source files
│   ├── main.c
│   ├── lexer.c
│   ├── expand.c
│   ├── my_read.c
│   ├── builtin.c
│   ├── builtins/     # Built-in commands
│   ├── pipex/        # Execution engine
│   ├── lexer_tools/  # Lexer utilities
│   ├── redir_tools/  # Redirection utilities
│   ├── expand_tools/ # Expansion utilities
│   └── expansion/    # Variable expansion
├── libft/            # Custom C library
└── Makefile
```

## Technical Details

- Uses `readline` for input handling with history support
- Implements quote handling (single, double)
- Supports escape sequences
- Proper error handling and exit codes
- Signal-safe global variable for interrupt handling
- No memory leaks (proper cleanup on all paths)
- Fork/exec model for external commands
- Efficient pipe management (reuses file descriptors)

## Credits

- **Parsing & Lexing**: [mehrasmeydani](https://github.com/mehrasmeydani)
- **Execution & Pipeline Management**: [Motheraudio](https://github.com/Motheraudio)

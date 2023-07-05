# 42sh
Welcome to **42sh**, our advanced shell interpreter. Designed with a focus on robustness and ease of use, 42sh provides a powerful and intuitive interface for command execution and shell environment management.

## Table of Contents
- [How 42sh Works](#how-42sh-works)
- [Features](#features)
- [Monitoring of Shell Variables](#monitoring-of-shell-variables)
- [Job Control and Signal Monitoring](#job-control-and-signal-monitoring)
- [History Management](#history-management)
- [Alias Management and Hash Table Interaction](#alias-management-and-hash-table-interaction)
- [Check File Types and Compare Values](#check-file-types-and-compare-values)
- [Inhibitors](#inhibitors)
- [Conclusion](#conclusion)
- [Features and Contributors](#features-and-contributors)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)

## How 42sh Works

When a command is entered into 42sh, it undergoes several stages of processing:

**Lexical Analysis**: Initially, the shell performs a lexical analysis on the input. This phase involves converting a sequence of characters into meaningful sequences, known as lexemes. During this process, 42sh reads the stream of characters that make up the command, grouping them into lexemes. For each lexeme, 42sh generates a token in the form of (token-name, attribute-value), which is then passed on to the next phase—syntactic analysis.

**Syntactic Analysis**: The subsequent phase is syntactic analysis, also referred to as parsing. In this stage, 42sh utilizes the tokens produced by the lexical analysis to construct a tree-like intermediate representation that illustrates the grammatical structure of the command. This representation is typically an Abstract Syntax Tree (AST), where each interior node signifies an operation, and the node's children represent the operation's arguments.

**Execution**: Once the command has been parsed into an AST, 42sh functions as an interpreter to execute the command. An interpreter is a computer program that directly executes instructions written in a programming or scripting language, without the need for these instructions to have been previously compiled into a machine language program. In this context, 42sh interprets the AST and executes the command as per the interpretation.

## Features

This README provides an overview of the various capabilities of 42sh, including:

- [Shell variable](https://www.gnu.org/software/bash/manual/html_node/Shell-Variables.html) monitoring
- [Job control](https://www.gnu.org/software/bash/manual/html_node/Job-Control-Basics.html)
- History management
- Alias management
- [Hash table](https://en.wikipedia.org/wiki/Hash_table) interaction
- Built-in test operators

42sh is built on top of Mike's and Jakke's [21sh](https://github.com/mike-ninja/21sh), with each member of the group responsible for one modular part and fulfilling mandatory requirements. This collaboration has resulted in a reliable shell interpreter that caters to the needs of both novice and experienced users.

## Monitoring of Shell Variables

42sh offers complete monitoring of shell variables, allowing users to:

- Create and export internal variables to the environment using the built-in `export` command.
  ```bash
  export VAR_NAME="Hello, World!"
  echo $VAR_NAME # Outputs: Hello, World!
  ```
- List all shell internal variables with the `set` command, without any additional options required.
  ```bash
  set # Lists all shell internal variables.
  ```
- Revoke internal and environment variables with the `unset` command.
  ```bash
  unset VAR_NAME
  echo $VAR_NAME # Outputs nothing as VAR_NAME is unset.
  ```

42sh also supports environment variable creation for unique commands, such as `HOME=/tmp cd`, enhancing shell environment management.

## Job Control and Signal Monitoring

42sh provides job control monitoring with built-ins `jobs`, `fg`, `bg`, and the `&` operator. The shell interpreter also correctly monitors all signals, ensuring a smooth user experience.
```bash
sleep 100 & # Starts a job in the background.
jobs # Lists the jobs.
```
## History Management

42sh features complete history management capabilities, allowing users to:

- Access their command history and perform expansions using `!!`, `!word`, `!number`, and `!-number` syntax.
  ```bash
  echo hello # Outputs: hello
  !! # Outputs: hello
  ```
- Save command history to a file for usage over multiple sessions.
- Perform incremental search in the history with `CTRL-R`.

The built-in `fc` command supports all POSIX options.

## Alias Management and Hash Table Interaction

42sh provides easy alias management with built-ins `alias` and `unalias`, simplifying the process of creating and removing aliases. Furthermore, 42sh provides a hash table and built-in `hash` to interact with it, facilitating the management of frequently used commands.
```bash
alias ll="ls -lah" # Creates an alias 'll' for the command 'ls -lah'.
ll # Executes 'ls -lah'.
```
## Check File Types and Compare Values

42sh includes a built-in `test` with a comprehensive set of operators, facilitating file type checks and value comparisons.

## Inhibitors

42sh provides complete handling of inhibitors, including `"` (double quote), `'` (simple quote) and `\`, ensuring that users can execute commands with confidence.
```bash
echo "This is a \"quoted\" word." # Outputs: This is a "quoted" word.
```
## Conclusion
42sh is a powerful tool with a comprehensive set of features that allow users to execute commands and manage their shell environment effortlessly. Whether you're a seasoned user or new to the shell environment, 42sh offers a seamless and efficient user experience.

## Features and Contributors
Here, we outline who contributed to each major feature of 42sh:

- **Job Control Monitoring**: The 42sh shell includes built-in commands like `jobs`, `fg`, `bg`, and the `&` operator for job control. This feature, contributed by [Mike](https://github.com/mike-ninja), [Jakke](https://github.com/Zakki-coder), and [Max](https://github.com/maxrantil), allows users to manage and monitor processes running in the shell.

- **Exit Code Access**: Our shell provides the `?$` expansion for accessing the exit status of the last executed command, making error handling more intuitive. This feature is the work of [Mike](https://github.com/mike-ninja).

- **Termcaps Implementation**: 42sh supports terminal capabilities (Termcaps) to ensure compatibility with various terminal types. This feature was implemented by [Mike](https://github.com/mike-ninja) and [Max](https://github.com/maxrantil).

- **Logical Operators**: The shell supports the logical operators "&&" (AND) and "||" (OR) for command chaining and control flow. This feature was contributed by [Jakke](https://github.com/Zakki-coder).

- **Internal Shell Variables Monitoring**: The shell tracks the state of internal shell variables, providing the user with useful information about the shell's status. This feature is credited to [Miika](https://github.com/MiikaViini).

- **Built-in Commands**: 42sh includes various built-in commands, such as `cd`, `echo`, `exit`, and `type`, contributed by [Simo](https://github.com/nuuskamuikkusenhattu).

- **POSIX Compliance**: Each built-in command conforms to POSIX standards, with exceptions only in explicit cases like `set` or `unset`. This adherence to standards was ensured by [Simo](https://github.com/nuuskamuikkusenhattu).

- **Inhibitors Handling**: The shell properly handles inhibitors, including `"` (double quote), `'` (single quote) and `\`, allowing users to accurately use these special characters in their commands. This was implemented by [Mike](https://github.com/mike-ninja).

- **Signal Monitoring**: 42sh properly handles all signals, ensuring a smooth and safe user experience. This functionality was contributed by [Mike](https://github.com/mike-ninja).

- **Tilde Expansion and Additional Parameter Formats**: The shell supports tilde expansion and various parameter formats for a flexible and user-friendly experience, thanks to [Miika](https://github.com/MiikaViini).

- **Alias Management**: 42sh includes built-ins `alias` and `unalias` to easily create and manage command shortcuts. This feature was contributed by [Roope](https://github.com/jungleistx).

- **Hash Table Interaction**: The shell provides a built-in hash table and a `hash` command for interaction, simplifying command execution and storage. This feature is brought to you by [Max](https://github.com/maxrantil).

- **Built-in `test` Command**: The shell includes a built-in `test` command with various operators for file type checks and value comparisons, implemented by [Max](https://github.com/maxrantil) and [Jakke](https://github.com/Zakki-coder).

- **History Management**: 42sh provides comprehensive history management, including expansions and built-in `fc` with all POSIX options. This was achieved by [Max](https://github.com/maxrantil).

- **Incremental Search**: Users can perform incremental search in the command history using `CTRL-R`, thanks to [Mike](https://github.com/mike-ninja), 42sh provides an incremental search in the command history using the CTRL-R shortcut, enabling users to find and execute previous commands more efficiently.

- **Automated Tester Development**: For quality assurance, an automated tester was developed by [Jakke](https://github.com/Zakki-coder), ensuring the shell functions as expected.

[![](https://avatars.githubusercontent.com/u/86000260?size=100)](https://github.com/maxrantil)
[![](https://avatars.githubusercontent.com/u/79006614?size=100)](https://github.com/Zakki-coder)
[![](https://avatars.githubusercontent.com/u/80318201?size=100)](https://github.com/jungleistx)
[<img src="https://avatars.githubusercontent.com/u/22212540" width="10%" height="10%" />](https://github.com/nuuskamuikkusenhattu)
[![](https://avatars.githubusercontent.com/u/57210997?size=100)](https://github.com/mike-ninja)
[![](https://avatars.githubusercontent.com/u/48917337?size=100)](https://github.com/MiikaViini)

## Prerequisites

Before installing and running 42sh, ensure you have the following:

-  A Unix-like operating system (MacOS, Linux, BSD)
-  GNU Compiler Collection (GCC) or similar compiler
-  GNU make
-  Basic knowledge of shell scripting and command-line interfaces
    
## Installation

Download the source code:
```bash
git clone https://github.com/maxrantil/42sh.git
cd 42sh
```

Compile and run:

```bash
make
./42sh
```

## Usage

After compiling the shell, you can start it with the ./42sh command. Here are some examples of how to use 42sh:

```bash
# Change directory
cd /path/to/directory

# List files
ls -l

# Use built-in text editor
nano file.txt
```
For more advanced usage, refer to the [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html).

## Contributing

We welcome contributions from the community. If you'd like to contribute, please follow these steps:

-    Fork the repository to your own GitHub account.
-    Clone the forked repository to your local machine.
-    Make your changes and commit them to your forked repository.
-    Submit a pull request with your changes.

Please make sure your code has no syntax errors and is in line with our project's coding style before submitting a pull request.

This shell is designed to prevent crashes (such as segmentation faults or bus issues) and memory leaks. If you encounter any such problems, or if you have suggestions or feedback, please kindly create an issue or PR.

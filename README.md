# 42sh
### Final Project in the Unix Branch at Hive Helsinki

Our shell interpreter, **42sh**, is a robust tool that enables users to execute commands and manage their shell environment with ease. This README provides an overview of the various capabilities of 42sh, including:

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

## Installation
We recommend using MacOS or Linux to compile and run this software.

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

This shell is designed to prevent crashes (such as segmentation faults or bus issues) and memory leaks. If you encounter any such problems, or if you have suggestions or feedback, please kindly create an issue or PR.

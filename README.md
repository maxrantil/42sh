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
  ```
- List all shell internal variables with the `set` command, without any additional options required.
- Revoke internal and environment variables with the `unset` command.
  ```bash
  unset VAR_NAME
  ```

42sh also supports environment variable creation for unique commands, such as `HOME=/tmp cd`, enhancing shell environment management.

## Job Control and Signal Monitoring

42sh provides job control monitoring with built-ins `jobs`, `fg`, `bg`, and the `&` operator. The shell interpreter also correctly monitors all signals, ensuring a smooth user experience.

## History Management

42sh features complete history management capabilities, allowing users to:

- Access their command history and perform expansions using `!!`, `!word`, `!number`, and `!-number` syntax.
- Save command history to a file for usage over multiple sessions.
- Perform incremental search in the history with `CTRL-R`.

The built-in `fc` command supports all POSIX options.

## Alias Management and Hash Table Interaction

42sh provides easy alias management with built-ins `alias` and `unalias`, simplifying the process of creating and removing aliases. Furthermore, 42sh provides a hash table and built-in `hash` to interact with it, facilitating the management of frequently used commands.

## Check File Types and Compare Values

42sh includes a built-in `test` with a comprehensive set of operators, facilitating file type checks and value comparisons.

## Inhibitors

42sh provides complete handling of inhibitors, including `"` (double quote), `'` (simple quote) and `\`, ensuring that users can execute commands with confidence.

## Conclusion
42sh is a powerful tool with a comprehensive set of features that allow users to execute commands and manage their shell environment effortlessly. Whether you're a seasoned user or new to the shell environment, 42sh offers a seamless and efficient user experience.

## Features and Contributors
Here, we outline who contributed to each major feature of 42sh:

- **Job control monitoring, with built-ins jobs, fg, bg and the & operator** - [Mike](https://github.com/mike-ninja), [Jakke](https://github.com/Zakki-coder) & [Max](https://github.com/maxrantil)
- **Exit code access via $? expansion** - [Mike](https://github.com/mike-ninja)
- **Termcaps implementation** - [Mike](https://github.com/mike-ninja) & [Max](https://github.com/maxrantil)
- **The following logical operators "&&" and "||"** - [Jakke](https://github.com/Zakki-coder)
- **Monitoring of intern shell variables** - [Miika](https://github.com/MiikaViini)
- **Builtins cd, echo, exit, type** - [Simo](https://github.com/nuuskamuikkusenhattu)
- **Each built-in must have the announced options by POSIX standard, except for explicit cases as set or unset** - [Simo](https://github.com/nuuskamuikkusenhattu)
- **Inhibitors ” (double quote), ’ (simple quote) and \ handling** - [Mike](https://github.com/mike-ninja)
- **A correct monitoring of all signals** - [Mike](https://github.com/mike-ninja)
- **Tilde expansion and additional parameter formats** - [Miika](https://github.com/MiikaViini)
- **Alias management via built-ins alias and unalias** - [Roope](https://github.com/jungleistx)
- **A hash table and built-in hash for interaction** - [Max](https://github.com/maxrantil)
- **The built-in test with the following operators** - [Max](https://github.com/maxrantil) & [Jakke](https://github.com/Zakki-coder)
- **Complete management of the history, including expansions and built-in fc with all POSIX options** - [Max](https://github.com/maxrantil)
- **Incremental search in the history with CTRL-R** - [Mike](https://github.com/mike-ninja)
- **Automated tester development** - [Jakke](https://github.com/Zakki-coder)

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

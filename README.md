# 42sh
### Last project in inner circle of Unix -branch at Hive Helsinki

Our shell interpreter, 42sh, is a powerful tool that allows users to execute commands and manage their shell environment with ease. With its comprehensive set of features, 42sh provides a seamless and efficient user experience. In this README, we will explore the various capabilities of 42sh, including the monitoring of shell variables, job control, history management, alias management, hash table interaction, and built-in test operators.

Additionally, it's worth noting that 42sh was built on top of Mikes and Jakkes [21sh](https://github.com/mike-ninja/21sh), with each member of the group responsible for one modular part and something from the mandatory requirements. This collaboration resulted in a robust and reliable shell interpreter tailored to the needs of both novice and experienced users.

#
### Monitoring of shell variables:

42sh provides complete monitoring of shell variables, including the ability to create and export intern variables to the environment using the built-in export command. With the set command, users can easily list all shell intern variables without any additional options required. Additionally, 42sh allows for the revocation of intern and environment variables with the unset command. The shell interpreter also supports environment variable creation for unique commands, such as `HOME=/tmp cd`, making it easy to manage the shell environment. Users can perform simple parameter expansions with the syntax `${}`, including access to the exit code of the previous command via the expansion `${?}`. Additionally, 42sh supports tilde expansion and additional parameter formats, including `${parameter:-word}`, `${parameter:=word}`, `${parameter:?word}`, `${parameter:+word}`, `${#parameter}`, `${parameter%}`, `${parameter%%}`, `${parameter#}`, and `${parameter##}`.

#
### Job control and signal monitoring:

42sh provides job control monitoring with built-ins `jobs`, `fg`, `bg`, and the `&` operator. The shell interpreter also correctly monitors all signals, ensuring a smooth and seamless user experience.

#
### History management:

With complete history management capabilities, 42sh allows users to easily access their command history and perform various expansions using `!!`, `!word`, `!number`, and `!-number` syntax. Users can also save their command history to a file for use across multiple sessions. The built-in `fc` command supports all POSIX options, and users can perform incremental search in the history with `CTRL-R`.

#
### Alias management and hash table interaction:

42sh allows for easy alias management with built-ins `alias` and `unalias`, making it easy to create and remove aliases as needed. Additionally, 42sh provides a hash table and built-in `hash` to interact with it, making it easy to manage frequently used commands.

#
### Check file types and compare values:

42sh provides a built-in `test` with a comprehensive set of operators, including `-b`, `-c`, `-d`, `-e`, `-f`, `-g`, `-L`, `-p`, `-r`, `-S`, `-s`, `-u`, `-w`, `-x`, `-z`, `=`, `!=`, `-eq`, `-ne`, `-ge`, `-lt`, `-le`, and `!`. The shell interpreter also supports the use of a simple operand without an operator.

#
### Inhibitors:

Finally, 42sh provides complete handling of inhibitors, including `"` (double quote), `'` (simple quote) and `\` and ensuring that users can execute commands with confidence.

#
### Conclusion:
With its comprehensive set of features, 42sh is a powerful tool that allows users to execute commands and manage their shell environment with ease. Whether you're a seasoned user or new to the shell environment, 42sh provides a seamless and efficient user experience.

## Contributors


[![](https://avatars.githubusercontent.com/u/86000260?size=100)](https://github.com/maxrantil)
[![](https://avatars.githubusercontent.com/u/79006614?size=100)](https://github.com/Zakki-coder)
[![](https://avatars.githubusercontent.com/u/80318201?size=100)](https://github.com/jungleistx)
[<img src="https://avatars.githubusercontent.com/u/22212540" width="10%" height="10%" />](https://github.com/nuuskamuikkusenhattu)
[![](https://avatars.githubusercontent.com/u/57210997?size=100)](https://github.com/mike-ninja)
[![](https://avatars.githubusercontent.com/u/48917337?size=100)](https://github.com/MiikaViini)

#
### Installation
We recommend using MacOS or Linux to compile and run this software.

Download the source code:
```bash
git clone [https://github.com/maxrantil/42sh.git](https://github.com/maxrantil/42sh.git); cd 42sh
```
Compile and run:
```bash
make; ./42sh
```

This shell is designed to prevent crashes (such as segmentation faults or bus issues) and memory leaks. If you encounter any such problems, please kindly create an issue or PR.

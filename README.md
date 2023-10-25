# 42-Minishell
42-Cursus : Minishell
# Minishell - A Simple Unix Shell

## Description
**Minishell** is a basic Unix shell that provides a simple command-line interface for executing commands and managing processes. It offers a set of core features required for a functional shell, including command execution, redirection, pipes, and built-in commands.

## Table of Contents
- [Mandatory Part](#mandatory-part)
- [Supported Features](#supported-features)
- [How to Use](#how-to-use)
- [Built-In Commands](#built-in-commands)
- [Signals Handling](#signals-handling)

### Mandatory Part

### Supported Features
**Minishell** supports the following features:
- Displaying a prompt when waiting for a new command.
- Working history with up/down arrow keys.
- Searching and launching the right executable based on the PATH variable.
- Handling single quotes ('), preventing shell interpretation of metacharacters.
- Handling double quotes (") while allowing the interpretation of `$` (dollar sign).
- Implementing redirections: `<`, `>`, `<<`, and `>>`.
- Implementing pipes (|) to connect command output to the input of the next command.
- Handling environment variables ($ followed by a sequence of characters) for expansion.
- Handling `$?` to expand to the exit status of the most recently executed foreground pipeline.
- Handling ctrl-C, ctrl-D, and ctrl-\ as in bash.
- Implementing built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

### How to Use
1. Clone the repository.
2. Run `make` to compile the `minishell` executable.
3. Execute `./minishell` to start the shell.
4. Enter commands, use built-ins, and enjoy the shell.

### Built-In Commands
- `echo`: Supports the `-n` option.
- `cd`: Accepts a relative or absolute path.
- `pwd`: No options required.
- `export`: No options required.
- `unset`: No options required.
- `env`: No options or arguments required.
- `exit`: No options required.

### Signals Handling
**Minishell** handles signals such as ctrl-C, ctrl-D, and ctrl-\ as follows:
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits the shell.
- ctrl-\ does nothing.

## Authors
- Souhail && Abdelghani

# Minishell

42 | minishell
*This project has been created as part of the 42 curriculum by amartel, jdessoli*

[![wakatime](https://wakatime.com/badge/user/1c291166-2001-49b1-85d5-2e496934f6a6/project/3fa2f1f8-5f97-41ca-8fae-14543d4f8c45.svg)](https://wakatime.com/badge/user/1c291166-2001-49b1-85d5-2e496934f6a6/project/3fa2f1f8-5f97-41ca-8fae-14543d4f8c45)

## Description
Minishell is a simplified Unix shell inspired by Bash.  
The goal is to understand how a shell works by implementing parsing, tokenization, process execution, pipes, and environment handling under strict constraints.

The project focuses on reproducing core Bash behavior while maintaining a clean and modular architecture.

## Instructions

### Compilation

    - make
    - meson

## Resources

- peer to peer with other really sweet 42 students, in order to get what's expected and what to be careful of.

- Online documents to understand how to structure a group project properly, and how bash works

- AI usage: helping with core concept understanding and unit testing

### Macos issue (Meson)

If `libreadline` is not found in pkg-config, at first check if it's already installed with this command:

```bash
pkg-config --libs readline
```

If it returns something like `-L/opt/homebrew/Cellar/readline/8.3.3/lib -lreadline` then you can add libreadline to your PKG_CONFIG_PATH:

```bash
echo 'export PKG_CONFIG_PATH="/opt/homebrew/opt/readline/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.zshrc
echo 'export PKG_CONFIG_PATH="/opt/homebrew/opt/readline/lib/pkgconfig:$PKG_CONFIG_PATH"' >> ~/.bashrc
source ~/.bashrc
source ~/.zshrc
```

otherwise, you can install it with Homebrew:

```bash
brew install readline
```

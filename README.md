# Minishell

42 | minshell
*This project has been created as part of the 42 curriculum by amartel, jdessoli*

[![wakatime](https://wakatime.com/badge/user/1c291166-2001-49b1-85d5-2e496934f6a6/project/3fa2f1f8-5f97-41ca-8fae-14543d4f8c45.svg)](https://wakatime.com/badge/user/1c291166-2001-49b1-85d5-2e496934f6a6/project/3fa2f1f8-5f97-41ca-8fae-14543d4f8c45)

## to check

- [ ] run into minishell `program recived SIGfault`
- [ ] `echo "'$a' + "$a""` -> `echo '$a'`
- [ ] strace (command)

## parsing

- [ ] make redirection
- [ ] make heredoc

## expand

## built-in

- [x] env
- [ ] pwd
- [ ] cd
- [ ] export
- [ ] unset
- [ ] exit
- [ ] echo
  - [ ] `-n`

## built-in logic

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

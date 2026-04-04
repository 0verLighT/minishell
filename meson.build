project(
  'minishell',
  'c',
  version : '0.1',
  license : 'MIT',
  default_options : ['warning_level=3']
)

includes = [include_directories('includes')]

sources = files(
  'src/main.c',
  'src/ctx/init.c',
  'src/built-in/env.c',
  'src/signals/check_sig.c',
  'src/signals/signal.c',
  'src/utils/ft_getenv.c',
  'src/utils/free_env.c',
  'src/input/fish.c',
  'src/builtin/helper/builtin_utils.c',
  'src/builtin/helper/cd_utils.c',
  'src/builtin/helper/exit_utils.c',
  'src/builtin/helper/export_utils.c',
  'src/builtin/ft_cd.c',
  'src/builtin/ft_echo.c',
  'src/builtin/ft_env.c',
  'src/builtin/ft_exit.c',
  'src/builtin/ft_export.c',
  'src/builtin/ft_pwd.c',
  'src/builtin/ft_unset.c',
)

deps = [
  dependency('libft'),
  dependency('readline')
]

executable(
  'minishell',
  sources,
  include_directories : includes,
  dependencies: deps
)

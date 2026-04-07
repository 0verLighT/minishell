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
  'src/exec/exec_builtin.c',
  'src/exec/exec_builtin_helper.c',
  'src/exec/exec_cmd.c',
  'src/exec/exec_core.c',
  'src/exec/exec_external.c',
  'src/exec/exec_logical.c',
  'src/exec/exec_pipe.c',
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

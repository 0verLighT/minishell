project(
  'minishell',
  'c',
  version : '0.1',
  license : 'MIT',
  default_options : ['warning_level=3']
)

includes = include_directories('includes')

sources = files(
  'src/builtin/ft_cd.c',
  'src/builtin/ft_echo.c',
  'src/builtin/ft_env.c',
  'src/builtin/ft_env.c',
  'src/builtin/ft_exit.c',
  'src/builtin/ft_export.c',
  'src/builtin/ft_pwd.c',
  'src/builtin/ft_unset.c',
  'src/builtin/helper/builtin_utils.c',
  'src/builtin/helper/cd_utils.c',
  'src/builtin/helper/exit_utils.c',
  'src/builtin/helper/export_utils.c',
  'src/ctx/init.c',
  'src/exec/exec_builtin.c',
  'src/exec/exec_builtin_helper.c',
  'src/exec/exec_cmd.c',
  'src/exec/exec_core.c',
  'src/exec/exec_external.c',
  'src/exec/exec_logical.c',
  'src/exec/exec_pipe.c',
  'src/exec/exec_redir.c',
  'src/main.c',
  'src/parser/ast_node_helper.c',
  'src/parser/parse_command.c',
  'src/parser/parse_command_helper.c',
  'src/parser/parser_free.c',
  'src/parser/pipe_parse.c',
  'src/parser/redirection_create.c',
  'src/parser/redirection_parse.c',
  'src/parser/redirection_utils.c',
  'src/parser/simple_command_utils.c',
  'src/parser/token_cursor.c',
  'src/signals/signal.c',
  'src/tokenizer/init_type_tokens.c',
  'src/tokenizer/tokenizer.c',
  'src/tokenizer/tokenizer_utils.c',
  'src/utils/free_env.c',
  'src/utils/ft_getenv.c',
  'src/utils/ft_isoperator.c',
)

add_global_arguments('-g3', language : 'c')

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

project(
  'minishell',
  'c',
  version : '0.1',
  license : 'MIT',
  default_options : ['warning_level=3']
)

includes = include_directories('includes')

sources = files(
  'src/built-in/env.c',
  'src/ctx/init.c',
  'src/main.c',
  'src/parser/ast_node_helper.c',
  'src/parser/clean_up.c',
  'src/parser/parse_command_helper.c',
  'src/parser/parse_simple_command.c',
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

project('minishell', 'c')

includes = [include_directories('includes')]

files = [
	'src/main.c',
]

deps = [
	dependency('libft'),
	dependency('readline')
]

executable('minishell', files, include_directories : includes, dependencies: deps)
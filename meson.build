project(
	'minishell',
	'c',
	version : '0.1',
	license : 'MIT',
	default_options : ['warning_level=3']
)

includes = [include_directories('includes')]

files = [
	'src/main.c',
]

deps = [
	dependency('libft'),
	dependency('readline')
]

executable('minishell', files, include_directories : includes, dependencies: deps)
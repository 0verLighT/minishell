project('minishell', 'c')

cc = meson.get_compiler('c')

includes = [include_directories('includes')]

files = [
	'src/main.c',
]

readline_dep = dependency('readline', required: false)

# MacOs -> Homebrew
if not readline_dep.found()
	readline_lib = cc.find_library('readline', 
		dirs: ['/opt/homebrew/opt/readline/lib']
	)
	readline_inc = include_directories('/opt/homebrew/opt/readline/include')
	readline_dep = declare_dependency(
		dependencies: readline_lib, 
		include_directories: readline_inc
	)
endif

deps = [
	dependency('libft'),
	readline_dep
]

executable('minishell', files, include_directories : includes, dependencies: deps)
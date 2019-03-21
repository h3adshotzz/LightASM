lib_sources = [
	'token.c',
	'log.c',
	'string.c',
	'node.c',
	'parser.c',
]

lasmc_inc = include_directories('.')
lasmc_lib = library('lasmc', lib_sources, dependencies: [glib_dep, gio_dep])
lasmc_dep = declare_dependency(link_with: lasmc_lib,
                               include_directories: lasmc_inc)

lasmc = executable('lasmc', 'main.c',
                   dependencies: [glib_dep, gio_dep, lasmc_dep])

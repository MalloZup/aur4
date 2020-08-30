default: build

build:
	 gcc  -Wall -Werror -g  aura.c -o aura `pkg-config --cflags --libs libsystemd`

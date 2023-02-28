all: main.c
    gcc -Wall -Werror -o app main.c
    ./app

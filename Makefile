SOURCES_CLIENT = sources/client/ft_client.c
OBJECTS_CLIENT = ${SOURCES_CLIENT:.c=.o}

SOURCES_SERVER = sources/server/ft_server.c
OBJECTS_SERVER = ${SOURCES_SERVER:.c=.o}

NAME_CLIENT = client
NAME_SERVER = server

COMPILE = clang
REMOVE = rm -f

COMPILATION_FLAGS = -Wall -Wextra -Werror

.c.o:
	${COMPILE} ${COMPILATION_FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME_CLIENT} ${NAME_SERVER}

${NAME_CLIENT}: ${OBJECTS_CLIENT}
	${COMPILE} -o ${NAME_CLIENT} ${OBJECTS_CLIENT}

${NAME_SERVER}: ${OBJECTS_SERVER}
	${COMPILE} -o ${NAME_SERVER} ${OBJECTS_SERVER}

clean:
	${REMOVE} ${OBJECTS_CLIENT} ${OBJECTS_SERVER}

fclean: clean
	${REMOVE} ${NAME_CLIENT} ${NAME_SERVER}

re: fclean all

.PHONY: all clean fclean re

all: philo

philo:
	cc -Wall -Wextra -Werror -lpthread  philo.c utils.c ex_utils.c -o philo

clean:
	rm -f philo

fclean: clean

re: fclean all


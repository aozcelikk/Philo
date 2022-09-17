CC					=	gcc #-fsanitize=thread -g #-fsanitize=address
CFLAGS				=	-Wall -Wextra -Werror #-pthread
NAME				=	philo
RM					=	rm -rf

RESET			=	\033[0m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
RED				=	\033[31m

SOURCE			=	error_check.c philo.c utils.c mutex.c philo_status.c \
					utils_dinner.c 


OBJECT			=	${SOURCE:.c=.o}

all:				$(NAME)

$(NAME):			$(OBJECT)
					@$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)
					@echo "$(BLUE)!!!....Done....!!!$(RESET)"

clean:				
					@$(RM) $(OBJECT)
					@echo "$(RED)!!!....Cleaned....!!!$(RESET)"

fclean:				clean
					@$(RM) philo
					@echo "$(RED)!!!....Full Cleaned....!!!$(RESET)"

re:					fclean $(NAME)

sil:				$(NAME) clean 
					@echo $(shell clear)

.PHONY:				all clean fclean re bonus
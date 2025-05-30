################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := libftprintf.a
CC        := cc
FLAGS    := -Wall -Wextra -Werror 
AR		:= ar 
ARFLAGS	:= rcs
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS		:=			srcs/buf_utils.c \
                    	srcs/parser.c \
                        srcs/printf.c \
                        srcs/render_num_utils_b.c \
                        srcs/render_num_utils.c \
                        srcs/render_num.c \
                        srcs/render_str_utils.c \
                        srcs/render_str.c \
                        srcs/render.c \
                        srcs/utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I. -fPIC

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${AR} ${ARFLAGS} ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re

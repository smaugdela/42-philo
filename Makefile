# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 15:00:41 by smagdela          #+#    #+#              #
#    Updated: 2022/01/11 16:06:28 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
#	VARIABLES	#
#################

NAME	=	philo

INCD	=	includes/
SRCD	=	sources/
OBJD	=	objects/
BONUSD	=	bonus/
BONUSSD	=	${BONUSD}sources/
BONUSOD	=	${BONUSD}objects/

SRCS	=	main.c parsing.c philo.c utils.c utils_2.c maieutique.c 
BONUS 	=
OBJS	:=	${addprefix ${OBJD},${SRCS:.c=.o}}
DEPS	:=	${addprefix ${OBJD},${SRCS:.c=.d}}
SRCS	:=	${addprefix ${SRCD},${SRCS}}
BONUSO	:=	${addprefix ${BONUSOD},${BONUS:.c=.o}}
BONUS	:=	${addprefix ${BONUSSD},${BONUS}}

CC	=	clang
CFLAGS	=	-Wall -Wextra -Werror
LIBSMK	=	make -C

###################
#	FANCY STUFF   #
###################

GREEN	=	\033[0;32m
RED		=	\033[1;31m
NC		=	\033[0m

WHALE	=	"\n${GREEN}       ::: \n     ___:____     |^\/^| \n   ,'        '.    \  / \n   |  O        \___/  | \n ~^~^~^~^~^~^~^~^~^~^~^~^~\n \n Compilation Successful!	${NC}\n"
NUKE	=	"\n${RED}     _.-^^---....,,--       \n _--                  --_  \n<                        >)\n|                         | \n \._                   _./  \n    '''--. . , ; .--'''       \n          | |   |             \n       .-=||  | |=-.   \n       '-=£€%&%€£=-'   \n          | ;  :|     \n _____.,-£%&€@%£&£~,._____${NC}\n\n"

#############
#	RULES	#
#############

all:	${NAME}

${NAME}:	 ${OBJS}
	${CC} -pthread ${CFLAGS} ${OBJS} -o ${NAME}
	@echo ${WHALE}

${OBJD}%.o:	${SRCD}%.c
	mkdir -p ${OBJD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -MMD $<

bonus:	${NAME}_bonus

${NAME}_bonus :  ${BONUSO}
	${CC} -pthread ${CFLAGS} ${BONUSO} -o ${NAME}_bonus
	@echo ${WHALE}

${BONUSOD}%.o:	${BONUSSD}%.c
	mkdir -p ${BONUSOD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -MMD $<

clean:
	-rm -rf ${OBJD} ${BONUSOD} ${DEPD}

fclean:	clean
	-rm ${NAME} ${NAME}_bonus
	@echo ${NUKE}

re:		fclean all

norm:
	norminette ${SRCS} ${BONUS} ${INCD}

.PHONY : re all bonus clean fclean norm

-include ${DEPS}

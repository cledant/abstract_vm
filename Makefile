# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cledant <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:40:13 by cledant           #+#    #+#              #
#    Updated: 2017/05/16 19:52:15 by cledant          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = g++

CFLAGS = --std=c++11 -Werror -Wall -Wextra -Wconversion -O2

OBJ_DIR_NAME = obj

INCLUDES = ./includes

SRCS  = AFactory.cpp AStack.cpp CommandQueue.cpp Env.cpp OperandDouble.cpp \
		OperandFactory.cpp OperandFloat.cpp OperandInt16.cpp OperandInt32.cpp \
		OperandInt8.cpp Parser.cpp Stack.cpp Token.cpp main.cpp

SRCS_PATH = ./srcs

OBJ = $(SRCS:%.cpp=$(OBJ_DIR_NAME)/%.o)

NAME = abstract_vm

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR_NAME)/%.o : $(SRCS_PATH)/%.cpp
	mkdir -p $(OBJ_DIR_NAME)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDES)

clean :
	rm -rf $(OBJ_DIR_NAME)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -MMD -MP -g

INCLUDES = -I includes/ -I minilibx-linux/

NAME = connect4

SRCS =	src/main.cpp\
		src/Game.cpp

OBJDIR = obj
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.cpp=$(OBJDIR)/%.d)

MLX = minilibx-linux/libmlx.a

all: minilibx $(MLX) $(NAME)

run:
	./$(NAME)

re: fclean all

$(MLX):
	@make -C minilibx-linux all

$(NAME): $(OBJS)
	@echo Compiling $(NAME)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(MLX) -lXext -lX11 -lm -lz

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C ../libft clean
	@make -C minilibx-linux clean
	@echo Cleaning objects
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C ../libft fclean
	@echo Cleaning $(NAME)
	@rm -rf $(NAME)

minilibx:
	@if ls | grep -q "minilibx-linux"; then \
		echo "\033[32;1;4mminilibx-linux Found\033[0m"; \
	else \
		echo "\033[31;1;4mminilibx-linux Not Found\033[0m"; \
		echo "\033[31;1mDownloading minilibx-linux from github \033[0m"; \
		git clone https://github.com/42paris/minilibx-linux.git minilibx-linux; \
	fi

.PHONY: all clean fclean run re

-include $(DEPS)

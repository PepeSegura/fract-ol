MAKEFLAGS	= --no-print-directory --silent

NAME	 = fractol

CFLAGS	 =	-Wextra -Wall -Werror #-Wunreachable-code
CFLAGS	 += -I inc
CFLAGS	 += -I libft
CFLAGS	 += -O3

DEBUG	 =	#-g3 -fsanitize=address

CPPFLAGS =	-MMD

LIBMLX	= ./libs/MLX42
LIBFT	= ./libs/libft

HEADERS = -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc

LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS	+=	$(LIBFT)/libft.a


SRCS =								\
		srcs/main.c					\
									\
		srcs/fractals/julia.c		\
		srcs/fractals/mandelbrot.c	\
									\
		srcs/t_complex/t_complex.c	\
									\
		srcs/mlx/mlx_tools.c		\
		srcs/mlx/hooks.c			\
									\
		srcs/other/errors.c			\


OBJS = $(patsubst srcs/%.c, objs/srcs/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: libmlx libft $(NAME)

libmlx:
	@cmake -DDEBUG=1 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "Linking: $(NAME)\n"

objs/srcs/%.o: ./srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf objs
	@rm -rf $(LIBMLX)/build
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME) objs

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re libmlx libft

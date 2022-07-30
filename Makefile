override NAME = miniRT
TEST = test
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g
override CC = gcc

# Libft submodule
override LIBFTDIR = ./libft
override LIBFT = $(LIBFTDIR)/libft.a

# Minilibx submodule
override MINILBXDIR = ./minilibx
override MINILBX = $(MINILBXDIR)/libmlx.a

override SRCDIR = src
override OBJDIR = obj
override TESTDIR = Tests

override INCLUDES = -I$(MINILBXDIR) -I$(LIBFTDIR)/headers

override LDLIBS = -lm -lmlx -lX11 -lbsd -lXext -lft
override LDFLAGS = -L$(MINILBXDIR) -L$(LIBFTDIR)

override define VPATH
	$(SRCDIR)
	$(SRCDIR)/vectors
	$(SRCDIR)/ray
	$(SRCDIR)/canvas
	$(SRCDIR)/camera
	$(TESTDIR)
endef

override define SRC
	main.c
	tuples.c
	tuples_operations.c
	matrix.c
	matrices_operations.c
	more_tuples_operations.c
	determinants_and_cofactors.c
	inverse_matrix.c
	transformations.c
	raycast.c
	canvas.c
	colors.c
	camera.c
endef

override define SRC_TEST
	$(filter-out main.c,$(SRC))
	tst_tuples.c
	tst_matrix.c
	tst_tranformations.c
	utils_tests.c
	tst_raycast.c
	tst_canvas.c
	tst_camera.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
override OBJTEST = $(SRC_TEST:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(MINILBX) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(MINILBX):
	$(MAKE) -C $(MINILBXDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(MAKE) clean -C $(MINILBXDIR)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

test: $(OBJDIR) $(OBJTEST) $(LIBFT)
	$(CC) $(OBJTEST) $(LDFLAGS) -o $(TEST) -lcriterion -lm -lft
	./$(TEST)
	@$(MAKE) fclean 1> /dev/null

.PHONY: all clean fclean re

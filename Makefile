override NAME = miniRT
TEST = test
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g
override CC = gcc


override MINILBXDIR = ./minilibx
override MINILBX = $(MINILBXDIR)/libmlx.a
override SRCDIR = src
override OBJDIR = obj
override TESTDIR = Tests

override LDLIBS = -lm -lmlx -lX11 -lbsd -lXext
override LDFLAGS = -L$(MINILBXDIR)

override define VPATH
	$(SRCDIR)
	$(TESTDIR)
endef

override define SRC
	main.c
	tuples.c
	tuples_operations.c
	cross_product_tuples.c
	colors.c
endef

override define SRC_TEST
	$(filter-out main.c,$(SRC))
	tst_tuples.c
	tst_colors.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
override OBJTEST = $(SRC_TEST:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(MINILBX)
	$(CC) $(CFLAGS) -I$(MINILBXDIR) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(MINILBXDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(MINILBX):
	$(MAKE) -C $(MINILBXDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(MAKE) clean -C $(MINILBXDIR)

re: fclean all

test: $(OBJDIR) $(OBJTEST)
	$(CC) $(OBJTEST) -o $(TEST) -lcriterion -lm
	./$(TEST)
	@$(MAKE) fclean 1> /dev/null

.PHONY: all clean fclean re

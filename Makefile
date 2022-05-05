override NAME = miniRT
TEST = test
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g
override CC = gcc

override LDLIBS = -lm

override SRCDIR = src
override OBJDIR = obj
override TESTDIR = Tests

override define VPATH
	$(SRCDIR)
	$(TESTDIR)
endef

override define SRC
	main.c
	tuples.c
	tuples_operations.c
endef

override define SRC_TEST
	$(filter-out main.c,$(SRC))
	tst_tuples.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
override OBJTEST = $(SRC_TEST:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDLIBS)

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)

re: fclean all

test: $(OBJDIR) $(OBJTEST)
	$(CC) $(OBJTEST) -o $(TEST) -lcriterion -lm
	./$(TEST)
	@$(MAKE) fclean 1> /dev/null

.PHONY: all clean fclean re

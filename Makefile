override NAME = miniRT
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g
override CC = gcc


override SRCDIR = src
override OBJDIR = obj

override define VPATH
	$(SRCDIR)
endef

override define SRC
	main.c
endef

override OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

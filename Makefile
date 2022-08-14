override NAME = miniRT
TEST = test
RM = rm -rf
override CFLAGS = -Wall -Wextra -Werror -g3
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
	$(SRCDIR)/objects
	$(SRCDIR)/intersections
	$(SRCDIR)/phong_reflection_model
	$(SRCDIR)/world
	$(SRCDIR)/shadows
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
	object.c
	material.c
	intersections.c
	utils_intersections.c
	utils_lights.c
	lights.c
	world.c
	bubblesort.c
	computations.c
	shadows.c
	view_transformation.c
	render.c
	plane_methods.c
	sphere_methods.c
	cylinders_methods.c
	cylinders_methods_2.c
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
	tst_normals.c
	tst_reflection.c
	tst_colors.c
	tst_lights.c
	tst_shadows.c
	tst_world.c
	tst_computations.c
	tst_view_transformation.c
	tst_bubblesort.c
	tst_plane.c
	tst_cylinders.c
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

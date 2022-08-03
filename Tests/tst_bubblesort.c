#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdio.h>
#include "../src/intersections/intersections.h"


#define EPISLON 0.00001

Test(bubbleSort, expected_sorted_list_with_three_elements)
{
	struct s_intersect	*head = NULL;
	add_back(&head, new_intersect(2, NULL));
	add_back(&head, new_intersect(1, NULL));
	add_back(&head, new_intersect(8, NULL));
	bubblesort(head);
	int i = 0;
	double expected[] = {1, 2, 8};
	for (struct s_intersect *tmp = head; tmp; tmp = tmp->next) {
		cr_assert_float_eq(tmp->t, expected[i], EPISLON);
		++i;
	}
}

Test(bubblesort, expected_sorted_list_with_four)
{
	struct s_intersect	*head = NULL;
	add_back(&head, new_intersect(4.5, NULL));
	add_back(&head, new_intersect(5.5, NULL));
	add_back(&head, new_intersect(4, NULL));
	add_back(&head, new_intersect(6.5, NULL));
	bubblesort(head);
	int i = 0;
	double expected[] = {4, 4.5, 5.5, 6.5};
	for (struct s_intersect *tmp = head; tmp; tmp = tmp->next) {
		cr_assert_float_eq(tmp->t, expected[i], EPISLON);
		++i;
	}

}

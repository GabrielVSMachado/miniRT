#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "../src/miniRT.h"
#include <stdio.h>


#define EPISLON 0.00001

Test(bubbleSort, expected_sorted_list_with_three_elements)
{
	t_xs	*head = init_xs();
	intersections(head, intersection(2, NULL));
	intersections(head, intersection(1, NULL));
	intersections(head, intersection(8, NULL));
	bubblesort(head);
	int i = 0;
	float expected[] = {1, 2, 8};
	for (t_intersect *tmp = head->fnode; tmp; tmp = tmp->next) {
		cr_assert_float_eq(tmp->t, expected[i], EPISLON);
		++i;
	}
}

Test(bubblesort, expected_sorted_list_with_four)
{
	t_xs	*head = init_xs();
	intersections(head, intersection(4.5, NULL));
	intersections(head, intersection(5.5, NULL));
	intersections(head, intersection(4, NULL));
	intersections(head, intersection(6.5, NULL));
	bubblesort(head);
	int i = 0;
	float expected[] = {4, 4.5, 5.5, 6.5};
	for (t_intersect *tmp = head->fnode; tmp; tmp = tmp->next) {
		cr_assert_float_eq(tmp->t, expected[i], EPISLON);
		++i;
	}

}

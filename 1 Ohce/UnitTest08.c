// Sean Szumlanski
// COP 3502, Spring 2018

// ==================
// Ohce: UnitTest08.c
// ==================
// This test case is a simple boundary check to help ensure the hoursSpent()
// function is implemented correctly.
//
// For instructions on compiling your program with this source code, please see
// the assignment PDF.


#include <stdio.h>

double hoursSpent(void);

int unit_test(void)
{
	if (hoursSpent() <= 0.0)
		printf("fail whale :(\n");
	else
		printf("Hooray!\n");

	return 0;
}

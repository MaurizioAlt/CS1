// Sean Szumlanski
// COP 3502, Spring 2018

// nqueens.c
// =========
// Backtracking solution to the N-Queens problem. Finds the number of ways to
// place N queens on an NxN chess board such that none of the queens can attack
// one another, and prints out all those chess boards.


#include <stdio.h>
#include <stdlib.h>

void printBoard(int *whichRow, int n)
{
	int row, col;

	for (row = 0; row < n; row++)
	{
		for (col = 0; col < n; col++)
		{
			printf("%c", (whichRow[col] == row) ? 'Q' : '.');
		}
		printf("\n");
	}

	printf("\n");
}

int allTheQueensAreSafe(int *whichRow, int n, int currentCol)
{
	// TODO: Write a function that returns 1 if all the queens represented by
	// this array are safe (i.e., none of them can attack one another).
	// Otherwise, return 0. For an explanation of these parameters, see the
	// backtrack() and nqueens() functions below.
}

int backtrack(int *whichRow, int n, int col)
{
	int row, total = 0;

	// Base case. If we get to a point where col == n, that means we've
	// successfully thrown down n queens. We print the solution and return 1 to
	// indicate that we have found 1 solution at the end of this branch.
	if (col == n)
	{
		printBoard(whichRow, n);
		return 1;
	}

	// Note: Typically, we would also check to be sure that this state is not
	// one we have seen before, and if it were, we would return immediately.
	// However, the process I'm using below to generate new states never has the
	// ability to generate the same state more than once, so we don't need to
	// check for that here.

	// Now we generate all possible branches by attemping to place the queen in
	// each row for this particular column.
	for (row = 0; row < n; row++)
	{
		// Make a move. (Place the queen at this particular row.)
		whichRow[col] = row;

		// Make a recursive call. Note that we only make this recursive call if
		// none of the queens can attack one another. In backtracking, we never
		// explore branches that we know to be infeasible. (This call to
		// allTheQueensAreSafe() does not have to be done here, though. It could
		// instead be used in an additional base case where we return
		// immediately if not all the queens are safe.)
		if (allTheQueensAreSafe(whichRow, n, col))
			total += backtrack(whichRow, n, col + 1);

		// At this point, we would typically undo the move we made above (the
		// state change that took place before the recursive call). However, in
		// this case, that will be undone in the next iteration of the for-loop,
		// so there's nothing for us to explicitly undo here.
	}

	// We've been keeping track of how many solutions were discovered along the
	// many recursive branches we explored. Let's now return that total.
	return total;
}

int nqueens(int n)
{
	// The whichRow array will indicate the row in which a queen is placed for
	// each column. The column serves as an index to the array, and the value at
	// that position tells us the row where the queen is located for that
	// column.
	//
	// For example, consider the following 4x4 board with 4 queens:
	//
	//   ..Q.
	//   Q...
	//   ...Q
	//   .Q..
	//
	// The queen in column 0 is in row 1.
	// The queen in column 1 is in row 3.
	// The queen in column 2 is in row 0.
	// The queen in column 3 is in row 2.
	//
	// Thus, our array would look like this: {1, 3, 0, 2}

	int *whichRow = malloc(sizeof(int) * n);
	return backtrack(whichRow, n, 0);

	// WARNING: This has a memory leak. (lol)
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Proper syntax: %s <n>\n", argv[0]);
		exit(1);
	}

	printf("%d\n", nqueens(atoi(argv[1])));
	return 0;
}

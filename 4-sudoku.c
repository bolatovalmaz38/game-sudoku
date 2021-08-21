#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum {NOT_FOUND = 0, FOUND = 1};
int check_row(int m[9][9], int k, int i)
{
	int c, cnt = 0;
	for (c = 0; c < 9; c++)
		if (m[i][c] == k)
			cnt++;
	return cnt == 0;
}
int check_col(int m[9][9], int k, int j)
{
	int c, cnt = 0;
	for (c = 0; c < 9; c++)
		if (m[c][j] == k)
				cnt++;
	return cnt == 0;
}
int check_cell(int m[9][9], int k, int i, int j)
{
	int cnt = 0, ki, kj, min_i, min_j;
	min_i = i / 3 * 3;
	min_j = j / 3 * 3;
	for (ki = 0; ki < 3; ki++)
		for(kj = 0; kj < 3; kj++)
			if (m[min_i + ki][min_j + kj] == k)
				cnt++;
	return cnt == 0;
}
int check(int m[9][9], int k, int i, int j)
{
	return check_row(m, k, i) && check_col(m, k, j) && check_cell(m, k, i, j);
}
int solve(int m[9][9], int n)
{
	int i, j, k;
	if (n == 81)
		return FOUND;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (m[i][j] == 0)
			{
				for (k = 1; k < 10; k++)
				{
					if (check(m, k, i, j))
					{
						m[i][j] = k;
						if (solve(m, n + 1))
							return FOUND;
					}
				}
				m[i][j] = 0;
				return NOT_FOUND;
			}
		}
	}	
	return NOT_FOUND;
}
int main(int argc, char **argv)
{
	int m[9][9], i, j, n, cnt = 0;
	if (argc > 1)
	{
		FILE *f;
		f = fopen(argv[1], "r");
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++)
			{
				fscanf(f, "%d", &m[i][j]);
				if (m[i][j] != 0)
					cnt++;
			}
		fclose(f);
	}
	else
	{
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++)
			{
				scanf("%d", &m[i][j]);
				if (m[i][j] != 0)
					cnt++;
			}
	}
	n = cnt;
	if (solve(m, n) == FOUND)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
				printf("%d ", m[i][j]);
			putchar('\n');
		}
	}
	else
		printf("no solution\n");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int  score;   /* Globals */
double V[21];
char in[20];

int user(void)
{
	int i = 0;
	while (i != 1 && i != 2) {
		printf("We are at %-2d, add 1 or 2 ? ", score);
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	return(i);
}


int computer(void)
{
	int action;
	double best = 0;
	double value, v1, v2;

	for (int a = 1; a <= 2; a++)
	{
		if (score + a > 20) {
			continue;
		}


		if (score + a == 20) {
			value = 1;
		}
		else {
			v1 = (score + a + 1 >= 20) ? 0 : V[score + a + 1];
			v2 = (score + a + 2 >= 20) ? 0 : V[score + a + 2];
			value = min(v1, v2);
		}

		if (value > best) {
			best = value;
			action = a;
		}
	}

	printf("We are at %-2d Computer adds %d\n", score, action);
	return action;
}

void compute_V(void) {

	for (int s = 0; s < 20; s++) {
		V[s] = 0;
	}

	V[20] = 1;

	double deltaV, best, v1, v2;
	do {
		deltaV = 0;

		for (int s = 19; s >= 0; s--) {

			best = 0; // worst case user wins

			// computer's turn
			for (int a = 1; a <= 2; a++) {
				int next_s = s + a;

				if (next_s > 20) {
					// invalid action
					continue;
				}
				if (next_s == 20) {
					// computer wins
					best = 1;
					break;
				}
				// user's turn
				v1 = (next_s + 1 >= 20) ? 0 : V[next_s + 1];
				v2 = (next_s + 2 >= 20) ? 0 : V[next_s + 2];
				best = max(best, min(v1, v2));

			}
			// track maximum change
			deltaV = max(abs(best - V[s]), deltaV);

			V[s] = best;
		}
		// repeat until convergence
	} while (deltaV > 1e-6);

	printf("State values: \n");
	for (int s = 0; s <= 20; s++) {
		printf("V[%2d] = %.6f \n", s, V[s]);
	}

}


int computer2(void) {
	int action;

	if (score % 3 == 1) action = 1;
	else if (score % 3 == 0) action = 2;
	else action = rand() % 2 + 1;

	printf("We are at %-2d Computer2 adds %d\n", score, action);

	return action;
}


int main(void)
{
	srand(time(NULL));
	int i;
	printf(" Who says first 20 \n \n");
	printf(" Precomputing values... \n");
	compute_V();
	printf(" Values computed. Let's play ! \n\n");

	score = 0;
	i = 0;
	while (i != 1 && i != 2) {
		printf("Who goes first: you=1 computer=2 ? ");
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	if (i == 2) score = computer();
	while (score <= 20) {
		score = score + user();
		if (score >= 20) { printf(" YOU WIN !!\n "); break; };
		score = score + computer();
		if (score >= 20) { printf(" I WIN !! \n "); break; };
	};
	return(0);
}


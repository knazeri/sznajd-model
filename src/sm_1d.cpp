#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "sm.h"



SimulationResult simulate_sm1d(int domain, double init_yes_density, int tmax, int log_interval, SznajdModel model, bool verbose) {

	int t = 0;
	int iteration = 0;
	double yes = 0;
	double N = domain;
	Agent* agents = new Agent[domain];
	SimulationResult result;
	FILE *f_pos = nullptr, *f_hmap = nullptr, *f_data = nullptr;

	result.changed = new int[tmax] {0};
	result.decision_time = new int[tmax] {0};

	if (verbose)
	{
		f_pos = fopen("results\\sm1d_positions.xyz", "w");
		f_hmap = fopen("results\\sm1d_heatmap.dat", "w");
		f_data = fopen("results\\sm1d_data.dat", "w");
	}

	// initialization
	for (int i = 0; i < domain; i++)
	{
		double p = rand() * (1.0 / RAND_MAX);

		agents[i].x = i;
		agents[i].opinion = p < init_yes_density ? 1 : -1;
	}

	while (t <= tmax)
	{
		result.time = t;

		for (int step = 0; step < domain; step++)
		{
			iteration++;

			// randomly select two people
			int i1 = (int)((domain - 1) * (rand() * (1.0 / RAND_MAX)));
			int i2 = (i1 + 1) % domain;
			int i3 = (i1 + 2) % domain;
			int i0 = i1 == 0 ? domain - 1 : i1 - 1;

			int s1 = agents[i1].opinion;
			int s2 = agents[i2].opinion;
			int decision_time = 0;

			// social validation
			if (s1 == s2)
			{
				agents[i0].change_opinion(s1, t, result.decision_time);
				agents[i3].change_opinion(s1, t, result.decision_time);
			}
			// opposite case
			else
			{
				if (model == MODEL_REGULAR)
				{
					agents[i0].change_opinion(s2, t, result.decision_time);
					agents[i3].change_opinion(s1, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[i0].change_opinion(s1, t, result.decision_time);
					agents[i3].change_opinion(s2, t, result.decision_time);
				}
			}

			if ((iteration % log_interval) == 0)
			{
				double changed = 0;
				yes = 0;

				if (verbose)
				{
					fprintf(f_pos, "%i\n", domain);
					fprintf(f_pos, "title\n");
				}

				for (int i = 0; i < domain; i++)
				{
					Agent p = agents[i];

					if (p.is_changed)
					{
						changed++;
						result.changed[t] = changed;
					}

					if (p.opinion == 1)
						yes += p.opinion;

					if (verbose)
					{
						fprintf(f_hmap, "%d ", (int)((p.opinion + 1) / 2));
						fprintf(f_pos, "a%i %f %f %d\n", i, p.x, p.y, p.opinion);
					}
				}

				result.yes_ratio = yes / domain;

				if (verbose)
				{
					fprintf(f_hmap, "\n");
					fprintf(f_data, "%d %f %f\n", iteration, (N - changed) / N, yes / N);
				}

				if (yes == 0)
				{
					result.state = CONSENSUS_NO;
					delete[] agents;
					return result;
				}

				else if (yes == N)
				{
					result.state = CONSENSUS_YES;
					delete[] agents;
					return result;
				}

				if (verbose && iteration % 1000 == 0)
					printf("iteration: %d, yes: %f\n", iteration, yes / N);
			}
		}

		t++;
	}

	delete[] agents;
	return result;
}


void simulate_steady_state_1d(int domain, int tmax, SznajdModel model) {
	const double simulations = 1000;
	FILE *f_state = fopen("results\\sm1d_steady.dat", "w");
	FILE *f_relaxation = fopen("results\\sm1d_relaxation.dat", "w");

	for (double concentration = 0.05; concentration < 1; concentration += 0.05)
	{
		double consensusYes = 0;
		double consensusNo = 0;
		double stalemate = 0;
		double relaxation_time = 0;

		srand(0);
		printf("concentration: %f\n", concentration);

		for (int i = 0; i < simulations; i++)
		{
			if (i % ((int)(simulations / 10)) == 0)
				printf("simulation: %d\n", i);

			SimulationResult res = simulate_sm1d(domain, concentration, tmax, domain, model, false);

			relaxation_time += res.time;

			switch (res.state)
			{
			case CONSENSUS_YES:
				consensusYes++;
				break;
			case CONSENSUS_NO:
				consensusNo++;
				break;
			case STALEMATE:
				stalemate++;
				break;
			}
		}

		fprintf(f_relaxation, "%f %f\n", concentration, relaxation_time);
		fprintf(f_state, "%f %f %f %f\n", concentration, consensusYes / simulations, consensusNo / simulations, stalemate / simulations);
	}

	fclose(f_state);
	fclose(f_relaxation);
}


void simulate_decision_change_1d(int domain, double init_yes_density, int tmax, SznajdModel model) {
	const double simulations = 10;
	double* changed = new double[tmax] { 0 };

	FILE *f_steps = fopen("results\\sm1d_decision_change.dat", "w");

	// run simulations for a number of times and take the average
	for (int i = 0; i < simulations; i++)
	{
		if (i % ((int)(simulations / 10)) == 0)
			printf("simulation: %d\n", i);

		SimulationResult res = simulate_sm1d(domain, init_yes_density, tmax, domain, model, false);

		for (int j = 0; j < tmax; j++)
		{
			changed[j] += res.changed[j < res.time ? j : (res.time - 1)];
		}
	}

	for (int j = 0; j < tmax; j++)
	{
		fprintf(f_steps, "%d %f\n", j, domain - changed[j] / simulations);
	}

	fclose(f_steps);
	delete[] changed;
}


void simulate_decision_time_1d(int domain, double init_yes_density, int tmax, SznajdModel model) {
	const double simulations = 1000;
	int* decision_time = new int[tmax] { 0 };

	FILE *f_decision = fopen("results\\sm1d_decision_time.dat", "w");

	// run simulations for a number of times and take the average
	for (int i = 0; i < simulations; i++)
	{
		if (i % ((int)(simulations / 10)) == 0)
			printf("simulation: %d\n", i);

		SimulationResult res = simulate_sm1d(domain, init_yes_density, tmax, domain, model, false);

		// iterate only for the total simulation steps
		for (int j = 0; j < res.time; j++)
		{
			decision_time[j] += res.decision_time[j];
		}
	}

	for (int j = 0; j < tmax; j++)
	{
		fprintf(f_decision, "%d %d\n", j, decision_time[j]);
	}

	fclose(f_decision);
	delete[] decision_time;
}


void simulate_magnetization_1d(int domain, double init_yes_density, SznajdModel model) {
	const double simulations = 100;
	FILE *f_mtime = fopen("results\\sm1d_magnetization.dat", "w");

	for (int time = 2000; time < 4000; time += 50)
	{
		double magnetization = 0;

		srand(0);
		printf("time: %d\n", time);

		for (int i = 0; i < simulations; i++)
		{
			if (i % ((int)(simulations / 10)) == 0)
				printf("simulation: %d\n", i);

			SimulationResult res = simulate_sm1d(domain, init_yes_density, time, domain, model, false);

			magnetization += res.yes_ratio;
		}

		fprintf(f_mtime, "%d %f\n", time, magnetization / simulations);
	}

	fclose(f_mtime);
}
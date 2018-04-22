#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "sm.h"



SimulationResult simulate_sm2d(int domain, double init_yes_density, int tmax, int log_interval, SznajdModel model, UpdateRule2D rule, SimOptions opt, bool verbose) {

	int t = 0;
	int iteration = 0;
	double yes = 0;
	double N = domain * domain;
	SimulationResult result;
	FILE *f_pos = nullptr, *f_exp = nullptr, *f_hmap = nullptr, *f_data = nullptr;

	result.changed = new int[tmax] {0};
	result.decision_time = new int[tmax] {0};

	Agent** agents = new Agent*[domain];

	if (verbose)
	{
		f_pos = fopen("results\\sm2d_positions.xyz", "w");
		f_exp = fopen("results\\sm2d_exposure.xyz", "w");
		f_hmap = fopen("results\\sm2d_heatmap.dat", "w");
		f_data = fopen("results\\sm2d_data.dat", "w");
	}

	// initialization
	for (int i = 0; i < domain; i++)
	{
		agents[i] = new Agent[domain];

		for (int j = 0; j < domain; j++)
		{
			double p_opinion = rand() * (1.0 / RAND_MAX);
			double p_expose = rand() * (1.0 / RAND_MAX);

			agents[i][j].x = i;
			agents[i][j].y = j;

			// randomly set agent's opinion 
			agents[i][j].opinion = p_opinion < init_yes_density ? 1 : -1;
			agents[i][j].exposed = p_expose < opt.initial_exposure_density;
		}
	}

	while (t <= tmax)
	{
		result.time = t;

		for (int step = 0; step < N; step++)
		{
			iteration++;

			// randomly select 2x2 panel

			int row1 = (int)((domain - 1) * (rand() * (1.0 / RAND_MAX)));
			int row2 = (row1 + 1) % domain;
			int row3 = (row1 + 2) % domain;
			int row0 = row1 == 0 ? domain - 1 : row1 - 1;

			int col1 = (int)((domain - 1) * (rand() * (1.0 / RAND_MAX)));
			int col2 = (col1 + 1) % domain;
			int col3 = (col1 + 2) % domain;
			int col0 = col1 == 0 ? domain - 1 : col1 - 1;

			int s11 = agents[row1][col1].opinion;
			int s12 = agents[row1][col2].opinion;
			int s21 = agents[row2][col1].opinion;
			int s22 = agents[row2][col2].opinion;

			// share news if exposed to news
			Agent agent = agents[row1][col1];
			if (agent.exposed)
			{
				double p_share = rand() * (1.0 / RAND_MAX);

				if ((agent.opinion == 1 && p_share < opt.agree_share_prob) ||
					(agent.opinion == -1 && p_share < opt.disagree_share_prob))
				{
					// randomly share news to one of the neighbors
					int neighbor = (int)(rand() * (3.0 / RAND_MAX)) + 1;
					switch (neighbor)
					{
					case 1:
						agents[row0][col1].exposed = true;
						break;
					case 2:
						agents[row1][col2].exposed = true;
						break;
					case 3:
						agents[row2][col1].exposed = true;
						break;
					default:
						agents[row1][col0].exposed = true;
						break;
					}
				}
			}


			if (rule == STAUFFER)
			{
				// all parallel
				if (s11 == s12 && s12 == s21 && s21 == s22)
				{
					agents[row0][col1].change_opinion(s11, t, result.decision_time);
					agents[row0][col2].change_opinion(s11, t, result.decision_time);
					agents[row1][col0].change_opinion(s11, t, result.decision_time);
					agents[row1][col3].change_opinion(s11, t, result.decision_time);
					agents[row2][col0].change_opinion(s11, t, result.decision_time);
					agents[row2][col3].change_opinion(s11, t, result.decision_time);
					agents[row3][col1].change_opinion(s11, t, result.decision_time);
					agents[row3][col2].change_opinion(s11, t, result.decision_time);
				}
				else if (model == MODEL_REGULAR)
				{
					agents[row0][col1].change_opinion(s21, t, result.decision_time);
					agents[row0][col2].change_opinion(s22, t, result.decision_time);
					agents[row1][col0].change_opinion(s12, t, result.decision_time);
					agents[row1][col3].change_opinion(s11, t, result.decision_time);
					agents[row2][col0].change_opinion(s22, t, result.decision_time);
					agents[row2][col3].change_opinion(s21, t, result.decision_time);
					agents[row3][col1].change_opinion(s11, t, result.decision_time);
					agents[row3][col2].change_opinion(s12, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[row0][col1].change_opinion(s11, t, result.decision_time);
					agents[row0][col2].change_opinion(s12, t, result.decision_time);
					agents[row1][col0].change_opinion(s11, t, result.decision_time);
					agents[row1][col3].change_opinion(s12, t, result.decision_time);
					agents[row2][col0].change_opinion(s21, t, result.decision_time);
					agents[row2][col3].change_opinion(s22, t, result.decision_time);
					agents[row3][col1].change_opinion(s21, t, result.decision_time);
					agents[row3][col2].change_opinion(s22, t, result.decision_time);
				}
				else
				{
					agents[row0][col1].change_opinion_external(opt, t, result.decision_time);
					agents[row0][col2].change_opinion_external(opt, t, result.decision_time);
					agents[row1][col0].change_opinion_external(opt, t, result.decision_time);
					agents[row1][col3].change_opinion_external(opt, t, result.decision_time);
					agents[row2][col0].change_opinion_external(opt, t, result.decision_time);
					agents[row2][col3].change_opinion_external(opt, t, result.decision_time);
					agents[row3][col1].change_opinion_external(opt, t, result.decision_time);
					agents[row3][col2].change_opinion_external(opt, t, result.decision_time);
				}
			}
			else if (rule == GALAM)
			{
				// first row
				if (s11 == s12) {
					agents[row1][col0].change_opinion(s11, t, result.decision_time);
					agents[row1][col3].change_opinion(s11, t, result.decision_time);
				}
				else if (model == MODEL_REGULAR)
				{
					agents[row1][col0].change_opinion(s21, t, result.decision_time);
					agents[row1][col3].change_opinion(s11, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[row1][col0].change_opinion(s11, t, result.decision_time);
					agents[row1][col3].change_opinion(s12, t, result.decision_time);
				}
				else
				{
					agents[row1][col0].change_opinion_external(opt, t, result.decision_time);
					agents[row1][col3].change_opinion_external(opt, t, result.decision_time);
				}


				// second row
				if (s21 == s22) {
					agents[row2][col0].change_opinion(s22, t, result.decision_time);
					agents[row2][col3].change_opinion(s22, t, result.decision_time);
				}
				else if (model == MODEL_REGULAR)
				{
					agents[row2][col0].change_opinion(s22, t, result.decision_time);
					agents[row2][col3].change_opinion(s21, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[row2][col0].change_opinion(s21, t, result.decision_time);
					agents[row2][col3].change_opinion(s22, t, result.decision_time);
				}
				else
				{
					agents[row2][col0].change_opinion_external(opt, t, result.decision_time);
					agents[row2][col3].change_opinion_external(opt, t, result.decision_time);
				}


				// first col
				if (s11 == s21) {
					agents[row0][col1].change_opinion(s11, t, result.decision_time);
					agents[row3][col1].change_opinion(s11, t, result.decision_time);
				}
				else if (model == MODEL_REGULAR)
				{
					agents[row0][col1].change_opinion(s21, t, result.decision_time);
					agents[row3][col1].change_opinion(s11, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[row0][col1].change_opinion(s11, t, result.decision_time);
					agents[row3][col1].change_opinion(s21, t, result.decision_time);
				}
				else
				{
					agents[row0][col1].change_opinion_external(opt, t, result.decision_time);
					agents[row3][col1].change_opinion_external(opt, t, result.decision_time);
				}


				// second col
				if (s12 == s22) {
					agents[row0][col2].change_opinion(s22, t, result.decision_time);
					agents[row3][col2].change_opinion(s22, t, result.decision_time);
				}
				else if (model == MODEL_REGULAR)
				{
					agents[row0][col2].change_opinion(s22, t, result.decision_time);
					agents[row3][col2].change_opinion(s12, t, result.decision_time);
				}
				else if (model == MODEL_MODIFIED)
				{
					agents[row0][col2].change_opinion(s12, t, result.decision_time);
					agents[row3][col2].change_opinion(s22, t, result.decision_time);
				}
				else
				{
					agents[row0][col2].change_opinion_external(opt, t, result.decision_time);
					agents[row3][col2].change_opinion_external(opt, t, result.decision_time);
				}
			}
			if ((iteration % log_interval) == 0)
			{
				double changed = 0;
				int counter = 0;
				yes = 0;

				if (verbose)
				{
					fprintf(f_pos, "%i\n", domain * domain);
					fprintf(f_pos, "title\n");

					fprintf(f_exp, "%i\n", domain * domain);
					fprintf(f_exp, "title\n");
				}

				for (int i = 0; i < domain; i++)
				{
					for (int j = 0; j < domain; j++)
					{
						Agent p = agents[i][j];

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

							fprintf(f_pos, "a%i %f %f %f\n", counter, p.x, p.y, p.opinion == -1 ? -.01 : 0);
							fprintf(f_exp, "a%i %f %f %f\n", counter, p.x, p.y, p.exposed ? .1 : 0);
						}
						counter++;
					}
				}

				result.yes_ratio = yes / N;

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


void simulate_steady_state_2d(int domain, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt) {
	const double simulations = 300;
	FILE *f_state = fopen("results\\sm2d_steady.dat", "w");
	FILE *f_yes = fopen("results\\sm2d_yes.dat", "w");
	FILE *f_relaxation = fopen("results\\sm2d_relaxation_50.dat", "w");

	for (double concentration = 0.05; concentration < 1; concentration += 0.05)
	{
		double consensusYes = 0;
		double consensusNo = 0;
		double stalemate = 0;
		double relaxation_time = 0;
		double yes = 0;

		srand(0);
		printf("concentration: %f\n", concentration);

		for (int i = 0; i <= simulations; i++)
		{
			if (i % ((int)(simulations / 10)) == 0)
				printf("simulation: %d\n", i);

			SimulationResult res = simulate_sm2d(domain, concentration, tmax, domain*domain, model, rule, opt, false);

			relaxation_time += res.time;
			yes += res.yes_ratio;

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

		fprintf(f_yes, "%f %f\n", concentration, yes / simulations);
		fprintf(f_relaxation, "%f %f\n", concentration, relaxation_time);
		fprintf(f_state, "%f %f %f %f\n", concentration, consensusYes / simulations, consensusNo / simulations, stalemate / simulations);
	}

	fclose(f_state);
	fclose(f_yes);
	fclose(f_relaxation);
}


void simulate_decision_change_2d(int domain, double init_yes_density, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt) {
	const double simulations = 500;
	double* changed = new double[tmax] { 0 };

	FILE *f_steps = fopen("results\\sm2d_decision_change.dat", "w");

	// run simulations for a number of times and take the average
	for (int i = 0; i <= simulations; i++)
	{
		if (i % ((int)(simulations / 10)) == 0)
			printf("simulation: %d\n", i);

		SimulationResult res = simulate_sm2d(domain, init_yes_density, tmax, domain*domain, model, rule, opt, false);

		for (int j = 0; j < tmax; j++)
		{
			changed[j] += (j < res.time ? res.changed[j] : domain * domain);
		}
	}

	for (int j = 0; j < tmax; j++)
	{
		fprintf(f_steps, "%d %f\n", j, (domain * domain) - changed[j] / simulations);
	}

	fclose(f_steps);
	delete[] changed;
}


void simulate_decision_time_2d(int domain, double init_yes_density, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt) {
	const double simulations = 1000;
	int* decision_time = new int[tmax] { 0 };

	FILE *f_decision = fopen("results\\sm2d_decision_time.dat", "w");

	// run simulations for a number of times and take the average
	for (int i = 0; i <= simulations; i++)
	{
		if (i % ((int)(simulations / 10)) == 0)
			printf("simulation: %d\n", i);

		SimulationResult res = simulate_sm2d(domain, init_yes_density, tmax, domain*domain, model, rule, opt, false);

		// iterate only for the total simulation steps
		for (int j = 0; j < res.time; j++)
		{
			decision_time[j] += res.decision_time[j];
		}
	}

	for (int j = 0; j < tmax; j++)
	{
		fprintf(f_decision, "%d %d\n", j + 1, decision_time[j]);
	}

	fclose(f_decision);
	delete[] decision_time;
}


void simulate_magnetization_2d(int domain, double init_yes_density, SznajdModel model, UpdateRule2D rule, SimOptions opt) {
	const double simulations = 100;
	FILE *f_mtime = fopen("results\\sm2d_magnetization.dat", "w");

	for (int time = 100; time < 5000; time += 100)
	{
		double magnetization = 0;

		srand(0);
		printf("time: %d\n", time);

		for (int i = 0; i <= simulations; i++)
		{
			if (i % ((int)(simulations / 10)) == 0)
				printf("simulation: %d\n", i);

			SimulationResult res = simulate_sm2d(domain, init_yes_density, time, domain, model, rule, opt, false);

			magnetization += res.yes_ratio;
		}

		fprintf(f_mtime, "%d %f\n", time, magnetization / simulations);
	}

	fclose(f_mtime);
}


void simulate_relaxation_time_2d(SznajdModel model, UpdateRule2D rule, SimOptions opt) {
	const double simulations = 300;
	FILE *f_relaxation = fopen("results\\sm2d_domain_relaxation.dat", "w");

	for (int domain = 10; domain < 120; domain += 10)
	{
		double relaxation_time = 0;

		srand(0);
		printf("domain: %d\n", domain);

		for (int i = 0; i <= simulations; i++)
		{
			if (i % ((int)(simulations / 10)) == 0)
				printf("simulation: %d\n", i);

			SimulationResult res = simulate_sm2d(domain, 0.5, 50000, domain*domain, model, rule, opt, false);
			if (res.state == STALEMATE)
				printf("=======================stalemate: %d\n", domain);

			relaxation_time += res.time;
		}

		fprintf(f_relaxation, "%d %f\n", domain, relaxation_time);
	}

	fclose(f_relaxation);
}
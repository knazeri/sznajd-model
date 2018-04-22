#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"


// Declares Sznajd model types: Regular(2000), Modified (2004) or None
enum SznajdModel {
	MODEL_REGULAR,
	MODEL_MODIFIED,
	MODEL_NONE
};


// Sznajd model 2d update rule: 4 agents (Stauffer), 2 agents (Galam)
enum UpdateRule2D {
	STAUFFER,
	GALAM
};


// Sznajd model steady state: all-yes, all-no, stalemate
enum SteadyState {
	CONSENSUS_YES,
	CONSENSUS_NO,
	STALEMATE
};


// Represents simulation options
struct SimOptions {
	int default_opinion;
	double initial_exposure_density;	// initial density of news
	double agree_share_prob;			// probability to share the news when agree
	double disagree_share_prob;			// probability to share the news when disagree
	double affect_prob;					// probability to get affected by the news

	SimOptions(double density, double p_agree, double p_disagre, double p_affect)
		: default_opinion(1), initial_exposure_density(density), agree_share_prob(p_agree), disagree_share_prob(p_disagre), affect_prob(p_affect) { }
};



// An agent represents a person in a closed community
struct Agent {
	double x;		// agent's x coordinate on a 2d lattice
	double y;		// agent's y coordinate on a 2d lattice
	int opinion;	// agent's opinion: (-1, 1)
	bool exposed;	// agent is exposed to external field

	bool is_changed;	// determines whether agent's opinion is changed
	int change_time;	// the time it takes for the agent to change decision

	// change agent's opinion
	bool change_opinion(int val, int time, int* decision_times) {
		if (opinion != val) {
			opinion = val;
			is_changed = true;

			if (change_time != -1 && time != change_time)
				decision_times[time - change_time]++;

			change_time = time;
			return true;
		}

		return false;
	}

	// chnage agent's opinion based on external field
	bool change_opinion_external(SimOptions opt, int time, int* decision_times)
	{
		if (exposed && (rand() * (1.0 / RAND_MAX)) < opt.affect_prob)
		{
			change_opinion(opt.default_opinion, time, decision_times);
			return true;
		}

		return false;
	}

	Agent() : x(0), y(0), opinion(-1), exposed(0), is_changed(false), change_time(-1) { }
};


// Represents the result of the simulation
struct SimulationResult {
	int time;			// total time it takes to reach full concensus or stalemate
	SteadyState state;	// final state of the simulation
	double yes_ratio;	// ratio of the "yes" at the end of the simulation
	int* changed;		// number of agents changed their decision at each time-step
	int* decision_time; // decision times at each time-step

	SimulationResult() : time(0), state(STALEMATE), yes_ratio(0), changed(nullptr), decision_time(nullptr) { }
};



SimulationResult simulate_sm1d(int domain, double init_yes_density, int tmax, int log_interval, SznajdModel model, bool verbose);
void simulate_steady_state_1d(int domain, int tmax, SznajdModel model);
void simulate_decision_change_1d(int domain, double init_yes_density, int tmax, SznajdModel model);
void simulate_decision_time_1d(int domain, double init_yes_density, int tmax, SznajdModel model);
void simulate_magnetization_1d(int domain, double init_yes_density, SznajdModel model);



SimulationResult simulate_sm2d(int domain, double init_yes_density, int tmax, int log_interval, SznajdModel model, UpdateRule2D rule, SimOptions opt, bool verbose);
void simulate_steady_state_2d(int domain, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt);
void simulate_decision_change_2d(int domain, double init_yes_density, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt);
void simulate_decision_time_2d(int domain, double init_yes_density, int tmax, SznajdModel model, UpdateRule2D rule, SimOptions opt);
void simulate_magnetization_2d(int domain, double init_yes_density, SznajdModel model, UpdateRule2D rule, SimOptions opt);
void simulate_relaxation_time_2d(SznajdModel model, UpdateRule2D rule, SimOptions opt);
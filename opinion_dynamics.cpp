// Opinion Dynamics
// Kamyar Nazeri - 100633486 - April 2018

#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "sm.h"


const int DOMAIN_1D = 60;		// 1d lattice size
const int DOMAIN_2D = 50;		// 1d lattice size
const int TMAX = 15000;			// simulation time
const double INIT_YES = 0.5;	// init density of 'yes'
const int LOG_INTERVAL = 100;	
const SimOptions opt = SimOptions(.1, .6, .6, 0.18);


int main()
{
	srand(time(NULL));

	// 1d and 2d simulations
	simulate_sm1d(DOMAIN_1D, INIT_YES, TMAX, LOG_INTERVAL, MODEL_MODIFIED, true);
	simulate_sm2d(DOMAIN_2D, INIT_YES, TMAX, LOG_INTERVAL, MODEL_NONE, STAUFFER, opt, true);

	// the following simulations are performed multiple times 
	// and the average is taken to present smooth plots

	// simulates the magnetization 
	simulate_steady_state_2d(DOMAIN_2D, TMAX, MODEL_NONE, STAUFFER, opt);

	// simulates steady state in the model with the presence of an external field
	simulate_decision_change_2d(DOMAIN_2D, INIT_YES, TMAX, MODEL_NONE, STAUFFER, opt);

	// simulates the distribution of decision time
	simulate_decision_time_2d(DOMAIN_2D, INIT_YES, TMAX, MODEL_NONE, STAUFFER, opt);

	// simulates the magnetization with the presence of an external field
	simulate_magnetization_2d(DOMAIN_2D, INIT_YES, MODEL_NONE, STAUFFER, opt);

	// simulates relaxation time for different values of domain size
	simulate_relaxation_time_2d(MODEL_NONE, STAUFFER, opt);


	return 0;
}
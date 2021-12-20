package supermarket;

// ExternalWorld models the arrival of carts to the supermarket.
// Interarrival times are distributed as an exponential or constant (for debugging). 
// Each cart has a corresponding service time, which depends on the amount 
// of items inside the cart. 
// Service time are distributed as exponential, lognormal or constant (for debugging).
simple ExternalWorld
{
	parameters:
        // Distribution parameters
        double arrival_mean = default(1);
        double service_mean = default(1);
        double service_std_deviation = default(1);
        
        int arrival_distribution = default(0); // 0 exponential else constant
        int service_distribution = default(0); // 0 exponential, 1 lognormal, else constant
        
        // Enable/disable logging
        bool logging = default(false);
        
	gates:
		output out;
}

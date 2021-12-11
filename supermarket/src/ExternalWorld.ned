package supermarket;

simple ExternalWorld
{
	parameters:
        // Distribution parameters
        double arrival_mean = default(1);
        int service_distribution = default(1);
        double service_mean = default(1);
        double service_std_deviation = default(1);   
        
	gates:
        output out;
}

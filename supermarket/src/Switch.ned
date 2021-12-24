package supermarket;

simple Switch
{
	parameters:
        double percentage_quick_tills;
        int number_of_tills;
        int quick_checkout_threshold = default(10);
        bool optimized_routing = default(true);

        bool logging = default(false);
        
	gates:
	    input in;
		output standard_out[];
		output quick_out[];
}

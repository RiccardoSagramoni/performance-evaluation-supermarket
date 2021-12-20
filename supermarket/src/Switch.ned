package supermarket;

simple Switch
{
	parameters:
        int quick_checkout_threshold = default(10);
        double percentage_quick_tills = default(0.2);
        int number_of_tills = default(10);

        bool logging = default(false);
        
	gates:
	    input in;
		output standard_out[];
		output quick_out[];
}

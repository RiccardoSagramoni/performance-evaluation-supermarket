package supermarket;

simple Switch{
	
	parameters:
        int quick_checkout_threshold = default(10);
        double percentage_quick_tills = default(0.2);
        int number_of_tills = default(10);

        bool logging = default(false);
        
	gates:
	    input in;
		output standard_out[number_of_tills - floor(percentage_quick_tills - number_of_tills)];
		output quick_out[floor(percentage_quick_tills - number_of_tills)];
}

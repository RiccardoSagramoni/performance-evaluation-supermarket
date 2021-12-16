package supermarket;

simple ExternalWorld{
	
	parameters:
        
        int quick_checkout_threshold = default(10);
        int percentage_quick_tills = default(0.2);
        int number_of_tills = default(10);
        bool console_log = default(false);
        
	gates:
	    input in;
		output out[number_of_tills];
}

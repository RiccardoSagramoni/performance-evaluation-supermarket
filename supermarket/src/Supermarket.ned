package supermarket;

module Supermarket
{
    parameters:
        double percentage_quick_tills;
        int number_of_tills;
        
        int standard_tills_size = number_of_tills - int(floor(percentage_quick_tills * number_of_tills));
        int quick_tills_size = int(floor(percentage_quick_tills * number_of_tills));

    gates:
        input in;

    submodules:
        standard_tills[standard_tills_size]: Till if standard_tills_size > 0;
        quick_tills[quick_tills_size]: Till if quick_tills_size > 0;
        switch: Switch;
        
    connections:
   		in --> switch.in;
   		for i=0..standard_tills_size-1, if exists(standard_tills) {
	       	switch.standard_out++ --> standard_tills[i].in;
		}
		for i=0..sizeof(quick_tills)-1, if exists(quick_tills) {
			switch.quick_out++ --> quick_tills[i].in;
		}
}





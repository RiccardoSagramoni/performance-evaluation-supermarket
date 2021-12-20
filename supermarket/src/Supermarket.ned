package supermarket;

module Supermarket
{
    parameters:
        double percentage_quick_tills = default(0.3);
        int number_of_tills = default(10);

    gates:
        input in;

    submodules:
        standard_tills[number_of_tills - floor(percentage_quick_tills * number_of_tills)]: Till;
        quick_tills[floor(percentage_quick_tills * number_of_tills)]: Till;
        switch: Switch;
        
    connections:
   		in --> switch.in;
   		for i=0..sizeof(quick_tills)-1 {
      		switch.quick_out[i] --> quick_tills[i].in;
		}
		for i=0..sizeof(standard_tills)-1 {
	       	switch.standard_out[i] --> standard_tills[i].in;
		}
}





//module Supermarket
//{
//    parameters:
//        double p = default(0.3);
//        int n = default(10);
//    gates:
//        input in[n];
//    submodules:
//        tills[n]: Till;
//}




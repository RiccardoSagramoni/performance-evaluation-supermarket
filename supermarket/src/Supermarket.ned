package supermarket;

module Supermarket
{
    parameters:
        double p = default(1/7);
        int n = default(7);
    gates:
        input in[n];
    submodules:
        standard_tills[ceil((1-p) * n)]: Till;
        quick_tills[floor(p * n)]: Till;
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



//package supermarket;
//
//module Supermarket
//{
//    gates:
//        input in[];
//    submodules:
//        //you will set the percentage p using a general global parameter and then change the type of some tills to isQuick=true by behavior
//        tills[sizeof(in)]: Till;
//}
//

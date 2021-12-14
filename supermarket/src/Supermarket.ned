package supermarket;

module Supermarket
{
    parameters:
        int p;
        int n;
    gates:
        input in[n];
    submodules:
        tills[n]: Till;
}



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

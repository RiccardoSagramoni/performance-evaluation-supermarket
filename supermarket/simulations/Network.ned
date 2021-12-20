package supermarket.simulations;

import supermarket.ExternalWorld;
import supermarket.Supermarket;


network Network
{
    @display("bgb=428,201");
    submodules:
        externalWorld: ExternalWorld {
            @display("p=124,92");
        }
        supermarket: Supermarket {
            @display("p=284,92");
        }
    connections:
        externalWorld.out --> supermarket.in;
}

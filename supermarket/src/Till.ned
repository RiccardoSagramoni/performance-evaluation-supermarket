package supermarket;

//
// TODO auto-generated module
//
simple Till
{
    parameters:
        @signal [responseTime];
        @statistic [responseTimeStat] (source="responseTime"; record=mean, vector);
        bool is_quick = default(false);
    gates:
        input in;
        output out;
}

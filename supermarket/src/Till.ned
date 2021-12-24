package supermarket;

simple Till
{
    parameters:
        @signal [response_time];
        @signal [number_of_jobs];
        @statistic [response_time_stat] (source="response_time"; record=mean, vector);
        @statistic [number_of_jobs_stat] (source="number_of_jobs"; record=mean, vector);
		
        bool is_quick = default(false);
        bool logging = default(false);
   
    gates:
        input in;
}

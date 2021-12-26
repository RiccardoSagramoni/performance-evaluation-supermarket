package supermarket;

simple Till
{
    parameters:
        @signal [number_of_jobs];
        @statistic [number_of_jobs_stat] (source="number_of_jobs"; record=vector);

        @signal [number_of_jobs_queue];
        @statistic [number_of_jobs_queue_stat] (source="number_of_jobs_queue"; record=vector);

        @signal [response_time];
        @statistic [response_time_stat] (source="response_time"; record=mean,vector);
		
        @signal [waiting_time];
        @statistic [waiting_time_stat] (source="waiting_time"; record=mean,vector);

        bool is_quick = default(false);
        bool logging = default(false);
   
    gates:
        input in;
}

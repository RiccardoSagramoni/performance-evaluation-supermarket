import pandas
import numpy
import numpy_ext
import os

def weighted_avg (values, time_diff):
	w = time_diff / numpy.sum(time_diff)
	return numpy.average(values, weights=w)

def weighted_variance(values, time_diff):
	w = time_diff / numpy.sum(time_diff)
	average = numpy.average(values, weights=w)
	return numpy.average((values-average)**2, weights=w)



# Read CSV
df = pandas.read_csv(os.path.join(os.path.dirname(__file__), 'input.csv'), sep=';')

result_df = pandas.DataFrame()

## Scroll the average
for i in range (0, len(df.columns), 2):
	index = str(int(i/2))
	print("i: " + index)

	# Extract TIMESTAMPS
	time_df = pandas.DataFrame(df.iloc[:, i])
	time_df = time_df.dropna()
	time_df.columns = ['time']
	time = time_df.time.values
	
	time_period = time[-1] - time[0]

	time_diff = []
	
	# Calculate weights
	for j in range(len(time) - 1):
		time_diff.append((time[j+1] - time[j]) / time_period)

	# Convert weights to nparray
	time_diff = numpy.asarray(time_diff, dtype=numpy.float64)


	# Extract JOBS
	jobs = pandas.DataFrame(df.iloc[:, i+1]).dropna()
	jobs.columns = ['j']
	jobs.drop(jobs.tail(1).index, inplace=True)
	jobs['td'] = time_diff
		
	# Rolling mean
	mean_jobs = numpy_ext.rolling_apply(weighted_avg, 10, jobs.j.values, jobs.td.values)
	var_jobs = numpy_ext.rolling_apply(weighted_variance, 10, jobs.j.values, jobs.td.values)



	this_df = pandas.DataFrame([time, mean_jobs, var_jobs]).T
	this_df.columns = ['time ' + index, 'mean ' + index, 'variance ' + index]
	result_df = pandas.concat([result_df, this_df], axis=1)


## Export result
result_df.to_csv(os.path.join(os.path.dirname(__file__), "output.csv"), sep=';')

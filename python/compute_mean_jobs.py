import pandas as pd
import numpy as np
from scipy.stats import t
import math

def weighted_avg_and_std(values, weights):
    """
    Return the weighted average and standard deviation.

    values, weights -- Numpy ndarrays with the same shape.
    """
    average = np.average(values, weights=weights)
    # Fast and numerically precise:
    variance = np.average((values-average)**2, weights=weights)
    return (average, math.sqrt(variance))


def compute_confidence_interval(alpha, std, size):
	t_crit = np.abs(t.ppf((1 - alpha) / 2, size - 1))
	return std * t_crit / np.sqrt(size)








df = pd.read_csv('results.csv', sep=';')

mean_list = []
std_list = []
conf_list = []
  
#print(df)
for i in range (0, len(df.columns), 2):
	print("i: " + str(i/2))

	# Extract TIMESTAMPS
	x = pd.DataFrame(df.iloc[:, i])
	x = x.dropna()
	time = x.values

	time_period = time[-1] - time[0]
	weights = []
	
	# Calculate weights
	for j in range(len(time) - 1):
		weights.append((time[j+1] - time[j]) / time_period)

	# Convert weights to nparray
	weights = np.asarray(weights)

	# Extract JOBS
	x = pd.DataFrame(df.iloc[:, i+1])
	x = x.dropna()
	jobs = x.values

	# Compute mean and std
	[mean, std] = weighted_avg_and_std(jobs[:-1], weights)
	conf_int = compute_confidence_interval(0.99, std, len(jobs) - 1)
	mean_list.append(mean)
	std_list.append(std)
	conf_list.append(conf_int)

csv_data = {}
csv_data['mean'] = mean_list
csv_data['std'] = std_list
csv_data['conf_int'] = conf_list
data = pd.DataFrame(data=csv_data)
data.to_csv("data.csv")

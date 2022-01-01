import pandas as pd
import numpy as np
from scipy.stats import norm
import math
import os.path

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
	"""
	Returns the confidence interval for a population mean, using a normal distribution.

	Args:
		alpha: The significance level used to compute the confidence level. The confidence level equals 100*(1 - alpha)%, or in other words, an alpha of 0.05 indicates a 95% confidence level.
		std: The population standard deviation for the data range and is assumed to be known.
		size: The sample size
	"""
	return std * norm.ppf(1 - alpha/2) / np.sqrt(size)




df = pd.read_csv(os.path.join(os.path.dirname(__file__), 'input.csv'), sep=';')

mean_list = []
std_list = []
conf_list = []
  
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
	jobs = x.values[:-1]

	# Compute mean and std
	[mean, std] = weighted_avg_and_std(jobs, weights)
	conf_int = compute_confidence_interval(0.05, std, len(jobs))
	mean_list.append(mean)
	std_list.append(std)
	conf_list.append(conf_int)

csv_data = {}
csv_data['mean'] = mean_list
csv_data['std'] = std_list
csv_data['conf_int'] = conf_list
data = pd.DataFrame(data=csv_data)
data.to_csv(os.path.join(os.path.dirname(__file__), "output.csv"), sep=';')

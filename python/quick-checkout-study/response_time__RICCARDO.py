import pandas as pd
import numpy as np
import os
import os.path
import math
from scipy.stats import norm

def compute_avg_and_std(values):
    """
    Return the mean and standard deviation.

    values, weights -- Numpy ndarrays with the same shape.
    """
    mean = np.mean(values)
    variance = np.mean((values - mean) ** 2)
    return (mean, math.sqrt(variance))



def compute_confidence_interval(alpha, std, size):
    """
    Returns the confidence interval for a population mean, using a normal distribution.

    Args:
        alpha: The significance level used to compute the confidence level. The confidence level equals 100*(1 - alpha)%, or in other words, an alpha of 0.05 indicates a 95% confidence level.
        std: The population standard deviation for the data range and is assumed to be known.
        size: The sample size
    """
    return std * norm.ppf(1 - alpha / 2) / np.sqrt(size)



# Compute the mean response time for 5 replicas
def execute (input, input_folder, output, output_folder):
	mean_list=[]
	conf_list=[]
	values=[]
	reps_values = [[], [], [], [], []]

	df = pd.read_csv(os.path.join(input_folder, input), sep=';')

	# Divide the columns in 5 "buckets", one for each replica
	for i in range(0, len(df.columns), 2):
		if df.columns[i].find("#0") != -1:
			reps_values[0] = reps_values[0] + df.iloc[:, i + 1].values.tolist()
		elif df.columns[i].find("#1") != -1:
			reps_values[1] = reps_values[1] + df.iloc[:, i + 1].values.tolist()
		elif df.columns[i].find("#2") != -1:
			reps_values[2] = reps_values[2] + df.iloc[:, i + 1].values.tolist()
		elif df.columns[i].find("#3") != -1:
			reps_values[3] = reps_values[3] + df.iloc[:, i + 1].values.tolist()
		elif df.columns[i].find("#4") != -1:
			reps_values[4] = reps_values[4] + df.iloc[:, i + 1].values.tolist()
		else:
			exit("error")

	csv_data = {}
	total_jobs = [pd.DataFrame(reps_values[0]), pd.DataFrame(reps_values[1]), pd.DataFrame(reps_values[2]),
				pd.DataFrame(reps_values[3]), pd.DataFrame(reps_values[4])]

	# Compute the mean for each repetition/replica
	for i in range(0, 5):
		total_jobs[i] = total_jobs[i].dropna()
		[mean, std] = compute_avg_and_std(total_jobs[i].values)
		conf_int = compute_confidence_interval(0.05, std, len(total_jobs[i]))
		mean_list.append(mean)
		conf_list.append(conf_int)

	mean_df = pd.DataFrame(mean_list)
	final_mean = mean_df.mean()

	csv_data = {}
	csv_data['mean'] = final_mean
	data = pd.DataFrame(data=csv_data)
	data.to_csv(os.path.join(output_folder, output), sep=';', index=False)
## end


PREFIX = ""
SUFFIX = ".csv"
INPUT_FOLDER = "low"
OUTPUT_FOLDER = "output_" + INPUT_FOLDER

# Change execution directory to the one with the .py file
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Compute the mean response/waiting time for all csv files in the input_folder
for filename in os.listdir(INPUT_FOLDER):
	if not filename.endswith('.csv'):
		continue
	
	# Extract the name
	name = filename.removeprefix(PREFIX).removesuffix(SUFFIX)
	print(filename)
	execute(filename, INPUT_FOLDER, 'output-' + name + '.csv', OUTPUT_FOLDER)
## end for

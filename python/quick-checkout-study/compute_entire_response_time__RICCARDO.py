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
	df = pd.read_csv(os.path.join(input_folder, input), sep=';')
	mean_list=[]
	std_list=[]
	conf_list=[]
	values=[]

	total_jobs=pd.DataFrame(data=[])
	for i in range(0, len(df.columns), 2):
		#print("i: " + str(i / 2))
		values = values + df.iloc[:, i+1].values.tolist()

	# Compute mean and std
	total_jobs = pd.DataFrame(values)
	total_jobs = total_jobs.dropna()
	[mean, std] = compute_avg_and_std(total_jobs.values)
	conf_int = compute_confidence_interval(0.05, std, len(total_jobs))
	mean_list.append(mean)
	std_list.append(std)
	conf_list.append(conf_int)


	csv_data = {}
	csv_data['mean'] = mean_list
	csv_data['std'] = std_list
	csv_data['conf_int'] = conf_list
	data = pd.DataFrame(data=csv_data)
	data.to_csv(os.path.join(output_folder, output), sep=';')
## end


PREFIX = ""
SUFFIX = ".csv"
INPUT_FOLDER = "mid"
OUTPUT_FOLDER = "output"

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

#merge_csv(OUTPUT_FOLDER)

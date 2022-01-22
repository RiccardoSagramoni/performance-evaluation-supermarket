import pandas as pd
import numpy as np
from scipy.stats import norm
import math
import os.path


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


df = pd.read_csv(os.path.join(os.path.dirname(__file__), "./../supermarket/prova_2.csv"), sep=';')
total_jobs = pd.DataFrame()
mean_list=[]
std_list=[]
conf_list=[]
values=[]
total_jobs=pd.DataFrame(data=[])
for i in range(0, len(df.columns), 2):
    print("i: " + str(i / 2))
    values = values + df.iloc[:, i+1].values.tolist()

# Compute mean and std
total_jobs = pd.DataFrame(values)
total_jobs = total_jobs.dropna()
[mean, std] = compute_avg_and_std(total_jobs.values)
conf_int = compute_confidence_interval(0.01, std, len(total_jobs))
mean_list.append(mean)
std_list.append(std)
conf_list.append(conf_int)


csv_data = {}
csv_data['mean'] = mean_list
csv_data['std'] = std_list
csv_data['conf_int'] = conf_list
print(csv_data)
data = pd.DataFrame(data=csv_data)
data.to_csv(os.path.join(os.path.dirname(__file__),
                         "./../supermarket/try_for_python_out.csv"), sep=';')


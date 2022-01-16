import pandas as pd
import numpy as np
from scipy.stats import norm
import math
import os.path
import sys

df = pd.read_csv(os.path.join(os.path.dirname(__file__), "./../supermarket/2kr/P=-1_K=-1_AM=-1_SM=-1/response_time.csv"), sep=';')
# one set of values for each repeat
reps_values = [[], [], [], [], []]
first = [0, 0, 0, 0, 0]
mean_list = []
conf_list = []
std_list = []


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
        sys.exit("error")

csv_data = {}
total_jobs = [pd.DataFrame(reps_values[0]), pd.DataFrame(reps_values[1]), pd.DataFrame(reps_values[2]),
              pd.DataFrame(reps_values[3]), pd.DataFrame(reps_values[4])]

#compute the mean, std, conf_int for each repetition
for i in range(0, 5):
    total_jobs[i] = total_jobs[i].dropna()
    [mean, std] = compute_avg_and_std(total_jobs[i].values)
    conf_int = compute_confidence_interval(0.01, std, len(total_jobs[i]))
    mean_list.append(mean)
    std_list.append(std)
    conf_list.append(conf_int)

#print(total_jobs[0]) gli index che stampa sono quelli delle vecchie righe che sono rimaste dopo il dropna
csv_data["mean"] = mean_list
csv_data["std"] = std_list
csv_data["conf_int"] = conf_list
data = pd.DataFrame(data=csv_data)
data.to_csv(os.path.join(os.path.dirname(__file__),
                         "./../supermarket/2kr/P=-1_K=-1_AM=-1_SM=-1/response_time_out.csv"), sep=';')

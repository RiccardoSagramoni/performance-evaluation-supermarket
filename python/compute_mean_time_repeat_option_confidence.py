import pandas as pd
import numpy as np
from scipy.stats import norm
import math
import os.path
import sys


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

#get the means of each replica (al the data of the tills are merged)
def get_replicas_means(replicas_values):
    means = []
    for i in range(len(replicas_values)):
        df_replica=pd.DataFrame(replicas_values[i])
        df_replica=df_replica.dropna()
        means.append(np.mean(df_replica.values))
    return means


option1 = ["$0=0.1", "$0=0.2", "$0=0.3", "$0=0.4", "$0=0.5", "$0=0.6", "$0=0.7", "$0=0.8", "$0=0.9"]
option2 = ["$1=6", "$1=15", "$1=45", "$1=60"]
replica = []
for i in range(0, 34):
    replica.append("#"+str(i))
dir = "./../supermarket/experiments_confidence/"
case = "LOW"
metric = "waiting_time"
directory_contents = os.listdir(dir)
config_mean_std = []

for i in range(len(option2)):
    config_mean_std.append([])
    for j in range(len(option1)):
        config_mean_std[i].append([])

df = pd.read_csv(os.path.join(os.path.dirname(__file__), dir+"/"+case+"/"+"/"+metric+"_"+case+".csv"), sep=';')

#i is K and j is p
for i in range(len(option2)):
    for j in range(len(option1)):
        print(option2[i] + " " + option1[j] + "\n")
        replicas_values = []
        for replica in range(35):
            replicas_values.append([])
        #merging all the values of the tills together for each repetition (max 99 replicas)
        for index in range(0, len(df.columns), 2):
                if df.columns[index].find(option1[j])!=-1 and df.columns[index].find(option2[i])!=-1:
                    replica_index = int(df.columns[index].split("#")[1][0]+df.columns[index].split("#")[1][1])
                    replicas_values[replica_index] = replicas_values[replica_index] + df.iloc[:, index + 1].values.tolist()
        #mean of each replica
        replicas_means = get_replicas_means(replicas_values)
        #mean of the replica's means + confidence interval
        alpha = 0.05
        mean = np.mean(replicas_means)
        std = math.sqrt(
            np.mean((replicas_means - mean) ** 2))
        conf_int = std * norm.ppf(1 - alpha / 2) / np.sqrt(len(replicas_means))
        #appending the confidence interval and the mean of i,j config
        config_mean_std[i][j] = [mean, conf_int]

#create the csv for the final data
csv_data = {}
for i in range(len(option2)):
    csv_data[option2[i]] = []
    csv_data[option2[i] + " conf_int"] = []
    for j in range(len(option1)):
        csv_data[option2[i]].append(config_mean_std[i][j][0]) #column means
        csv_data[option2[i]+" conf_int"].append(config_mean_std[i][j][1]) #column conf_int

data = pd.DataFrame(data=csv_data)
data.to_csv(os.path.join(os.path.dirname(__file__),
                                 dir+"/"+case+"/"+"/"+metric+"_"+case+"_out.csv"), sep=';')
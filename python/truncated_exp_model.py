# DOESN'T WORK!!!

from scipy.stats import expon
import math

ARRIVAL_MEAN = 10
SERVICE_MEAN = 8
NUMBER_OF_TILLS = 10
PERCENTAGE_OF_QUICK_TILLS = 3 / NUMBER_OF_TILLS
THRESHOLD = 3

arrival_rate = 1 / ARRIVAL_MEAN
service_rate = 1 / SERVICE_MEAN

# Quick tills
num_quick_till = NUMBER_OF_TILLS * PERCENTAGE_OF_QUICK_TILLS
prob_till = expon.cdf(THRESHOLD, scale=SERVICE_MEAN) / num_quick_till
quick_till_arrival_mean = ARRIVAL_MEAN / prob_till

k = THRESHOLD / SERVICE_MEAN
E_X = SERVICE_MEAN * (1 - (k + 1) * math.exp(-k)) / (1 - math.exp(-k))
E_X2 = 2 * SERVICE_MEAN**2 * (1 - 0.5 * (k**2 + 2 * k + 2) * math.exp(-k)) / (1 - math.exp(-k))
VarX = E_X2 - E_X**2

rho = E_X / quick_till_arrival_mean
print (rho)

mean_number_of_jobs = rho + (rho**2 + (1 / quick_till_arrival_mean)**2 * VarX) / (2 * (1 - rho))
print(mean_number_of_jobs)

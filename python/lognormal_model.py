import math

ARRIVAL_MEAN = 1 # 1/lambda
SERVICE_LOG_MEAN = 1 # 1/mu
SERVICE_LOG_VAR = 0.5**2 # sigma**2
NUMBER_OF_TILLS = 4

arrival_rate = (1 / ARRIVAL_MEAN) / NUMBER_OF_TILLS

service_mean =  math.exp(SERVICE_LOG_MEAN + SERVICE_LOG_VAR/2)
service_var = (math.exp(SERVICE_LOG_VAR) - 1) * math.exp(2 * SERVICE_LOG_MEAN + SERVICE_LOG_VAR)

rho = arrival_rate * service_mean
if (rho >= 1):
	print('Error: rho >= 1 (' + str(rho) + ')')
	exit()

E_N = rho + (rho**2 + arrival_rate**2 * service_var) / (2 * (1 - rho))
print('Mean number of jobs: ' + str(E_N))

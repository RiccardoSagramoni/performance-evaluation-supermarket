import pandas as pd
import numpy as np
import os
import os.path

# Compute the mean response time for 5 replicas
def execute (input, input_folder, output, output_folder):
	# one set of values for each repeat
	reps_values = [[], [], [], [], []]
	mean_list = []

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
		mean = np.mean(total_jobs[i].values)
		mean_list.append(mean)

	# Export data to csv
	csv_data["mean"] = mean_list
	data = pd.DataFrame(data=csv_data)
	data.to_csv(os.path.join(output_folder, output), sep=';')
## end


# Merge the generated csv in a single one, in order to simplify
# the analysis on Excel
def merge_csv (folder):
	i = 0
	data_list = []

	# Create a list with all the "mean" columns
	for filename in os.listdir(folder):
		if not filename.endswith('.csv'):
			continue
		
		this_data = pd.read_csv(os.path.join(folder, filename), sep=';')
		this_data = this_data.drop(this_data.columns[0], axis=1)
		this_data.columns = [filename.removeprefix('output-').removesuffix('.csv')]
		data_list.append(this_data)
	## end for
	
	# Concatenate the extracted columns
	data = pd.concat(data_list, axis = 1)

	if (is_lognormal_with_wrong_sort_order):
		col = []
		# In our system last factor (std_deviation) is wrongly sorted (1.75 is before 1), 
		# so we must switch each odd column with the following one
		for i in range(0, len(data.columns), 2):
			col.append(data.columns[i+1])
			col.append(data.columns[i])
		## end for

		# Apply the fix and dump the data    
		data = data.reindex(columns=col)
	
	data.to_csv('output.csv', sep=';')


is_lognormal_with_wrong_sort_order = True

PREFIX = "an_2kr-"
SUFFIX = ".csv"
INPUT_FOLDER = "csv"
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

merge_csv(OUTPUT_FOLDER)

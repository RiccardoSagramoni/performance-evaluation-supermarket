import csv
import os
import os.path

v = [-1, 1]
os.chdir(os.path.dirname(os.path.abspath(__file__)))

# Write the sign matrix for the factorial analysis
# This configuration is for 5 factors
with open("sign.csv", "w", newline='') as file:
	writer = csv.writer(file, delimiter=";")

	writer.writerow(['A', 'B', 'C', 'D', 'E'])

	for A in v:
		for B in v:
			for C in v:
				for D in v:
					for E in v:
						writer.writerow([A, B, C, D, E])

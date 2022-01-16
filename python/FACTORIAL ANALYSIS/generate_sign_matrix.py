import csv

v = [-1, 1]

with open("sign.csv", "w", newline='') as file:
	writer = csv.writer(file, delimiter=";")

	writer.writerow(['A', 'B', 'C', 'D', 'E'])

	for A in v:
		for B in v:
			for C in v:
				for D in v:
					for E in v:
						writer.writerow([A, B, C, D, E])

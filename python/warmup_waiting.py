import pandas
import os

# Read CSV
df = pandas.read_csv(os.path.join(os.path.dirname(__file__), 'input.csv'), sep=';')

result_df = pandas.DataFrame()

## Scroll the average
for i in range (0, len(df.columns), 2):
	index = str(int(i/2))
	print("i: " + index)

	# Extract data
	data = pandas.DataFrame(df.iloc[:, i+1]).dropna()
	data.columns = ['j']
	data.drop(data.tail(1).index, inplace=True)
		
	# Rolling mean
	mean = data.rolling(10).mean()
	variance = data.rolling(10).var()

	mean_df = pandas.DataFrame(mean)
	mean_df.columns = ['mean ' + index]
	var_df = pandas.DataFrame(variance)
	var_df.columns = ['variance ' + index]
	result_df = pandas.concat([result_df, mean_df, var_df], axis=1)


## Export result
result_df.to_csv(os.path.join(os.path.dirname(__file__), "output.csv"), sep=';')
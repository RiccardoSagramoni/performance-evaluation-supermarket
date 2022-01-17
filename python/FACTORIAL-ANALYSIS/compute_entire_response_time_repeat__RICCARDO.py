import pandas as pd
import numpy as np
import os
import os.path


def execute (input, input_folder, output, output_folder):
    # one set of values for each repeat
    reps_values = [[], [], [], [], []]
    mean_list = []

    df = pd.read_csv(os.path.join(input_folder, input), sep=';')

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

    #compute the mean, std, conf_int for each repetition
    for i in range(0, 5):
        total_jobs[i] = total_jobs[i].dropna()
        mean = np.mean(total_jobs[i].values)
        mean_list.append(mean)

    csv_data["mean"] = mean_list
    data = pd.DataFrame(data=csv_data)
    data.to_csv(os.path.join(output_folder, output), sep=';')
## end



def merge_csv (folder):
    i = 0
    data_list = []

    for filename in os.listdir(folder):
        if not filename.endswith('.csv'):
            continue
        
        this_data = pd.read_csv(os.path.join(folder, filename), sep=';')
        this_data = this_data.drop(this_data.columns[0], axis=1)
        this_data.columns = [filename.removeprefix('output-').removesuffix('.csv')]
        data_list.append(this_data)
    ## end for
    
    data = pd.concat(data_list, axis = 1)

    col = []
    for i in range(0, len(data.columns), 2):
        col.append(data.columns[i+1])
        col.append(data.columns[i])
    ## end for
    data = data.reindex(columns=col)

    data.to_csv('output.csv', sep=';')



PREFIX = "an_2kr-"
SUFFIX = ".csv"
INPUT_FOLDER = "csv"
OUTPUT_FOLDER = "output"

os.chdir(os.path.dirname(os.path.abspath(__file__)))

for filename in os.listdir(INPUT_FOLDER):
    name = filename.removeprefix(PREFIX).removesuffix(SUFFIX)
    print(filename)
    execute(filename, INPUT_FOLDER, 'output-' + name + '.csv', OUTPUT_FOLDER)
## end for

merge_csv(OUTPUT_FOLDER)
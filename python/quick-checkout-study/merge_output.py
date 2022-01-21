# -*- coding: utf-8 -*-
"""
Created on Sat Jan 12 06:56:16 2019

@author: Chris
"""
#credited:
#https://stackoverflow.com/questions/9234560/find-all-csv-files-in-a-directory-using-python/12280052

import os
import glob
from telnetlib import OUTMRK
import pandas as pd

OUTPUT_FOLDER = 'output_low' #edit!

#set working directory
os.chdir(os.path.dirname(os.path.abspath(__file__)) + '\\' + OUTPUT_FOLDER)

#find all csv files in the folder
#use glob pattern matching -> extension = 'csv'
#save result in list -> all_filenames
extension = 'csv'
all_filenames = [i for i in glob.glob('*.{}'.format(extension))]
#print(all_filenames)

#combine all files in the list
combined_csv = pd.concat([pd.read_csv(f, sep=';') for f in all_filenames ])

#export to csv
os.chdir('..')
combined_csv.to_csv(OUTPUT_FOLDER + ".csv", index=False, sep=';')

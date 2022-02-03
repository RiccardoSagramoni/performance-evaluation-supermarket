# Put this script inside the folder with the .vec files

# Edit the regex for the files ("for FILE in study_percentage_lognormal\-*#0.vec") 
# and the name of statistics ("-f "waiting_time_stat:vector"), if needed

# Name the omnetpp.ini configuration as study_percentage_lognormal-GRADE where `GRADE` is {LOW, MID, HIGH}

for FILE in study_percentage_lognormal\-*#0.vec
do
	name=$(echo $FILE | sed 's/-#.*.vec//') # black magic, do not touch it
	IFS="-" read s1 s2 s3 s4 <<< $FILE # extract string from separators `-`

	scavetool export --type v -o $s2-$s3.csv -F CSV-S -v -x precision=14 -x separator=semicolon -f "waiting_time_stat:vector" $name-*.vec
done


# Put this script inside the folder with the .vec files

# Edit the regex for the files ("for FILE in an_2kr-*#0.vec") 
# and the name of statistics ("-f "waiting_time_stat:vector"), if needed

for FILE in an_2kr-*#0.vec
do
	name=$(echo $FILE | sed 's/-#.*.vec//')
	scavetool export --type v -o $name.csv -F CSV-S -v -x precision=14 -x separator=semicolon -f "waiting_time_stat:vector" $name-*.vec
done


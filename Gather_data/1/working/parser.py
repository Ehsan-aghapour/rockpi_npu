# instead of extracting counter infos from events.xml use all_counters.xml
# This file contains all info of counters that are captured (Also with keys) and write info in counters.csv
import xml.etree.ElementTree as ET
input_name='all_counters.xml'
output_name='counters.csv'
root=ET.parse(input_name).getroot()

cnts=[]
keys=[]


for counter in root.iter('counter'):
	#1
	#keys=list(set(keys) | set(counter.attrib.keys()))
	#2
	#keys=list(set().union(keys, counter.attrib.keys()))
	#3

	print('\n\n\n\n')
	print(keys)
	keys=keys+list(counter.attrib.keys())
	keys = dict.fromkeys(keys)
	keys=list(keys)
	print(keys)
	
	'''keys=list(set(keys))
	print(keys)'''
	cnts.append(counter.attrib)
	
f=open(output_name,'w')

for k in keys:
	f.write(k+',')
f.write('\n')

for counter in cnts:
	for k in keys:
		attr=counter.get(k,'-')
		attr=attr.replace(',','.')
		f.write(attr)
		f.write(',')
	f.write('\n')

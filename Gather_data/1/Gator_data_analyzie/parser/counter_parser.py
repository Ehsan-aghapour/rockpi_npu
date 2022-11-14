capfile=open('captured.xml','r')
caplines=capfile.readlines()

cfgfile=open('configuration.xml','r')
cfglines=cfgfile.readlines()

evfile=open('events.xml','r')
evlines=evfile.readlines()

mpfile=open('counters_mapping.csv','r')
mplines=mpfile.readlines()

"""
p={}
for line in caplines:
	c=line.find('key=')
	if c>-1:
		k=int(line.split('key=')[-1].split('"')[1],16)
		p[k]={}
		p[k]['key']=line.split('key=')[-1].split('"')[1]
		p[k]['type']=line.split('type=')[-1].split('"')[1]
		for l in evlines:
			c=l.find('counter="'+p[k]['type'])
			if c>-1:
				p[k]['title']=l.split('title=')[-1].split('"')[1]
				p[k]['name']=l.split('name=')[-1].split('"')[1]
				p[k]['description']=l.split('description=')[-1].split('"')[1]
"""

start53_cnt_events=-2
end53_cnt_events=-2
for i,line in enumerate(evlines):
	if end53_cnt_events==-2:
		t=line.find('<counter_set name="ARMv8_Cortex_A53_cnt"')
		if t>-1:
			start53_cnt_events=i
			end53_cnt_events=-1
	else:
		if end53_cnt_events==-1:
			t=line.find('<counter_set')
			if t>-1:
				end53_cnt_events=i
				break
		


start73_cnt_events=-2
end73_cnt_events=-2
for i,line in enumerate(evlines):
	if end73_cnt_events==-2:
		t=line.find('<counter_set name="ARMv8_Cortex_A73_cnt"')
		if t>-1:
			start73_cnt_events=i
			end73_cnt_events=-1
	else:
		if end73_cnt_events==-1:
			t=line.find('<counter_set')
			if t>-1:
				end73_cnt_events=i
				break
		


			

p={}
for line in caplines:
	c=line.find('key=')
	if c>-1:
		k=int(line.split('key=')[-1].split('"')[1],16)
		p[k]={}
		p[k]['key']=line.split('key=')[-1].split('"')[1]
		p[k]['type']=line.split('type=')[-1].split('"')[1]
		event=int(line.split('event=')[-1].split('"')[1],16)
		p[k]['event']=line.split('event=')[-1].split('"')[1]
		
		found=0
		for l in evlines:
			findcounter=l.find('counter="'+p[k]['type']+'"')
			if findcounter>0 :
				for element in l.split('" '):
					pair=element.split('=')					
					if len(pair)==2:
						p[k][pair[0].split(' ')[-1]]=pair[1][1:]
				found=1
				break

		if(found==0):
			print(p[k])
			if p[k]['type'][0:-1]=="ARMv8_Cortex_A53_cnt":
				f1='event="'+p[k]['event'][0:2]+'0'+p[k]['event'][2:]+'"'
				f2='event="'+p[k]['event']+'"'
				for j in range(start53_cnt_events,end53_cnt_events):
					if evlines[j].find(f1)>-1 or evlines[j].find(f2)>-1 :
						print("finded")
						print(j)
						print(evlines[j])
						for element in evlines[j].split('" '):
							pair=element.split('=')					
							if len(pair)==2:
								p[k][pair[0].split(' ')[-1]]=pair[1][1:]
						break

			if p[k]['type'][0:-1]=="ARMv8_Cortex_A73_cnt":
				f1='event="'+p[k]['event'][0:2]+'0'+p[k]['event'][2:]+'"'
				f2='event="'+p[k]['event']+'"'
				for j in range(start73_cnt_events,end73_cnt_events):
					if evlines[j].find(f1)>-1 or evlines[j].find(f2)>-1 :
						print("finded")
						print(j)
						print(evlines[j])
						for element in evlines[j].split('" '):
							pair=element.split('=')					
							if len(pair)==2:
								p[k][pair[0].split(' ')[-1]]=pair[1][1:]
						break

'''
			
			else:	
				print(c)
				c+=1
				start=0
				for ll in evlines:
					if start==0:
						if ll.find('<counter_set name="'+p[k]['type'][0:-1])>-1:
							print("started")
							start=1
					else:
						print(ll[0:100])
						if ll.find('event="'+p[k]['event'])>-1:
							print("finded")
							for element in ll.split('" '):
								pair=element.split('=')					
								if len(pair)==2:
									p[k][pair[0].split(' ')[-1]]=pair[1][1:]
							break;
		
'''

#rm("counters_info.csv")




ts=[]
for c in p:
	for title in p[c]:
		ts.append(title)

titles=list(dict.fromkeys(ts)) 


mp={}
for l in mplines:
	pair=l.split(',')
	if len(pair)==2:
		mp[int(pair[0])]=pair[1][0:-1]


f=open('counters_info.csv','w')
f.write('my_key,int_key,')
for title in titles:
	f.write(title+',')



for counter in p:
	f.write('\n')
	f.write(str(mp[counter])+',')
	f.write(str(counter)+',')
	for title in titles:
		if title in p[counter]:			
			f.write(p[counter][title]+',')
		else:
			f.write(' ,')


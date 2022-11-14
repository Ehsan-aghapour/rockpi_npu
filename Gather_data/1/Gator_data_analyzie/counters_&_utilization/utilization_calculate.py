import csv

f = open("bv2.csv");
p=csv.reader(f)
pl=list(p)

pl=pl[1:]
#convert 2d list to int

rows=[list(map(int,i)) for i in pl]

'''
kkcore=[None]*8
kkcore[0]=[line for line in kk if line[0]==0]
kkcore[1]=[line for line in kk if line[0]==1]
kkcore[2]=[line for line in kk if line[0]==2]
kkcore[3]=[line for line in kk if line[0]==3]
kkcore[4]=[line for line in kk if line[0]==4]
kkcore[5]=[line for line in kk if line[0]==5]
kkcore[6]=[line for line in kk if line[0]==6]
kkcore[7]=[line for line in kk if line[0]==7]
'''

cores=[[line for line in rows if line[0]==core] for core in range(0,8)]

pids=[[line[2] for line in cores[i]] for i in range(0,8)]

upids=[list(dict.fromkeys(pids[i])) for i in range(0,8)]
#pids=[[l[2] for l in pid] for pid in kkcore]

core=cores[0]
core=core[0:-1]
upid=upids[0]

for i in range(0,len(core)):
	core[i][1]=(core[i][1]-1908316)/1000000

endtime=int(core[-1][1])

#use=[[None]*(max(upid)+1)]*(endtime+1)

#use=[[0]*(endtime+1)]*(max(upid)+1)
idle=[0 for i in range(endtime+1)]

t=2;
for i in range(1,len(core)):
	if core[i][2]==0:
		t=int(core[i][1])
		if core[i+1][1]<(t+1):
			idle[t]+=core[i+1][1]-core[i][1]
		else:
			idle[t]+=(t+1)-core[i][1]
			idle[int(core[i+1][1])]+=core[i+1][1]-int(core[i+1][1])
			for m in range(t+1,int(core[i+1][1])):
				idle[m]=1


index=1
t=2
while True:
	if core[index][1]<t:
		index+=1
	else:
		if core[index-1][2]==0:
			idle[int(core[index][1])]+=int(core[index][1])-core[index][1]
		e
		

use = [[0 for i in range(endtime+1)] for j in range(max(upid)+1)]
t=2
for i in range(1,len(core)):
	print(i,t)
	if core[i-1][1] < t:
		if core[i][1] < t:
			i+=1
			print("0",i,t,use[core[i][2]][t])
		else:
			if core[i][1] < t+1 :
				use[core[i][2]][t]+=core[i][1]-t
				print("1",i,t,use[core[i][2]][t])
			else:				
				while((t+1)<core[i][1]):
					use[core[i][2]][t]+=1
					print("2",i,use[core[i][2]][t])
					t+=1
				use[core[i][2]][t]+=core[i][1]-t
				print("3",i,t,use[core[i][2]][t])
	else:
		if core[i][1]<t+1:
			use[core[i][2]][t]+=core[i][1]-core[i-1][1]
			print("4",i,t,use[core[i][2]][t])
		else:
			use[core[i][2]][t]+=(t+1)-core[i-1][1]
			print("5",i,t,use[core[i][2]][t])
			t=t+1
			while core[i][1]>t+1:
				use[core[i][2]][t]+=1
				print("6",i,t,use[core[i][2]][t])
				t+=1
			use[core[i][2]][t]+=core[i][1]-t
			print("7",i,t,use[core[i][2]][t])
	#input("next")


with open("out.csv", "w") as csv_file:
     writer = csv.writer(csv_file, delimiter=',')
     for l in core:
             writer.writerow(l)



for i in range(0,len(use)):
	for j in range(0,len(use[i])):
		if use[i][j]==
		if pt[

strttime=2









use=[None]*len(upids[0])


pids=[ l[2] for l in kk]
upids=list(dict.fromkeys(pids))
uts=[None]*len(upids)

results=p[2::4];
value = list(map(int, results));
value.sort();
o= open("keys.txt", "a")
for v in value:
	o.write('{}\n'.format(v));
o.close();

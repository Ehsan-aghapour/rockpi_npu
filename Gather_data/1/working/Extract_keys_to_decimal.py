f=open("cc.txt",'r')
ll=f.readlines()
test=[[g.split('=')[1] for g in l.split(' ') if g.split('=')[0] == 'key'] for l in ll]
test2=[t for t in test if t]
test3=[j[0][1:-1] for j in test2]
res=[int(t,16) for t in test3]


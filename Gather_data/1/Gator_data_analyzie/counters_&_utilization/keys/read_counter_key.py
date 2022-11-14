f = open("counter_key.txt", "r");
p=[];
for x in f:
	p.append(x.split(',')[-1]);

results=p[2::4];
value = list(map(int, results));
value.sort();
o= open("keys.txt", "a")
for v in value:
	o.write('{}\n'.format(v));
o.close();


  

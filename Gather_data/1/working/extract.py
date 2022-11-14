# extract counters from configuration.xml, captured.xml, or all_counters.xml using counter, type, or type keyword respectively
# and save them with A.xml to A.csv
import sys
fname=sys.argv[1]
key=''
if fname=='captured.xml':
    key='type'
if fname=='configuration.xml':
    key='counter'
if fname=="all_counters.xml":
    key='type'
f=open(fname,'r')
ll=f.readlines()
f.close()

def keys():
    test=[[g.split('=')[1] for g in l.split(' ') if g.split('=')[0] == 'key'] for l in ll]
    test2=[t for t in test if t]
    test3=[j[0][1:-1] for j in test2]
    res=[int(t,16) for t in test3]
    return res

def value(k):
    print(k)
    types=[[g.split('=')[1].split('"')[1] for g in l.split(' ') if g.split('=')[0] == k] for l in ll]
    print(len(types))
    f=open(k+'.csv','w')
    for t in types:
        if len(t)>0:
            f.write(t[0]+'\n')
    f.close()


# extract counters from configuration.xml, captured.xml, or all_counters.xml using counter, type, or type keyword respectively
def main():
    value(key)

# Compare two files and print lines of first file that are not existed in second file
def main2():
    if len(sys.argv)<3:
        exit
    with open(sys.argv[1]) as f:
        l1=f.readlines(f)
    with open(sys.argv[2]) as f:
        l2=f.readlines(f)
    for l in l1:
        see=0
        for x in l2:
            if l==x:
                see=1
        if see==0:
            print(l)



if __name__ == "__main__":
    main()
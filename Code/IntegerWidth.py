def width():
    type = ['short', 'int', 'long']
    fin = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\6A.c",encoding="utf-8")
    line = fin.readline()
    dic = {}
    list = []
    while line:
        if 'main' not in line:
            for i in type:
                if i in line:
                    pos = line.rfind(i)
                    terminator = line.rfind(';')
                    dic[line[(pos + len(i) + 1):terminator]] = type.index(i)
                    list.append(line[(pos + len(i) + 1):terminator])
        line = fin.readline()
    fin.close()

    # testdic = {'i': 1, 's': 0}
    # testlist = ['s', 'i']

    fin2 = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\6A.c")
    postion = []
    linenum = 1
    line2 = fin2.readline()
    while line2:
        if '=' in line2 and varexist(list, line2) and 'if' not in line2:
            equal = line2.rfind('=')
            termi = line2.rfind(';')
            left = line2[1:equal-1]
            right = line2[equal + 2:termi]
            leftvalue = dic[left]
            rightvalue = dic[right]
            if leftvalue < rightvalue:
                postion.append(linenum)
        linenum += 1
        line2 = fin2.readline()
    fin2.close()
    return postion


def varexist(list,line):
    for i in list:
        if i not in line:
            return False
    return True


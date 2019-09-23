def FormatString():
    list = 'printf'
    fin = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\5A.c",encoding="utf-8")
    dic = []
    line = fin.readline()
    linenum = 1
    while line:
        if list in line:
            symbol = line.count('%')
            coma = line.count(',')
            if coma < symbol:
                dic.append(linenum)
        linenum += 1
        line = fin.readline()
    fin.close()
    return dic

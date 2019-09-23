def nullpointer():
    fin = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\9A.c",encoding="utf-8")
    linenum = 1
    res = []
    line = fin.readline()
    while line:
        if 'null' in line or 'NULL' in line:
            res.append(linenum)
        linenum += 1
        line = fin.readline()
    return res
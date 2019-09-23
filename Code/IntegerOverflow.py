def IntegerOver():
    fin = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\7A.c",encoding="utf-8")
    line = fin.readline()
    res = []
    linenum = 1
    while line:
        if '+' in line or '*' in line:
            if '=' in line:
                res.append(linenum)
        linenum += 1
        line = fin.readline()
    return res
def buffer():
    list = ['strcpy', 'strncpy', 'memcpy', 'memncpy', 'strcat', 'strncat', 'sprintf', 'vsprintf', 'gets', 'getchar',
            'fgetc', 'getc', 'read', 'sscanf', 'fscanf', 'vfscanf', 'vscanf', 'vsscanf']
    fin = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\4A.c",encoding='utf_8')
    dic = {}
    line = fin.readline()
    linenum = 1
    while line:
        for i in list:
            if i in line:
                dic[linenum] = i
        linenum += 1
        line = fin.readline()
    fin.close()
    return dic


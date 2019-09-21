import ply.lex as lex


def homologyDetection():
    fin1 = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\1B.cpp", encoding='utf-8')
    pretreatefile1 = pretreate(fin1)
    lexfile1 = mylex(pretreatefile1)
    fin2 = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\1A.c", encoding='utf-8')
    pretreatefile2 = pretreate(fin2)
    lexfile2 = mylex(pretreatefile2)
    result = CalculateSimilarity(lexfile1, lexfile2)
    print("Similarity: %f%%" %(result))


# 1. Set characters that do not affect semantics to null
# 2. Restore source code redefinition type to original type
# for c/c++
def pretreate(file):
    dic = {}
    newTypelist = []
    line = file.readline()
    while line:
        if '#' in line or '/' in line:
            pass
        elif 'typedef' in line:
            oriType = line.split(' ')[1]
            newType = line.split(' ')[2]
            newType = newType.strip(';')
            dic[newType] = oriType
            newTypelist.append(newType)
        elif '{' in line:
            break
        line = file.readline()
    for key, value in dic.items():
        if dic.__contains__(value):
            dic[key] = dic[value]

    # 2. Restore source code redefinition type to original type
    tempfile = ""
    file.seek(0)
    line2 = file.readline()
    while line2:
        if '#' in line2 or '//' in line2 or 'typedef' in line2:
            pass
        else:
            place, res = TypeExist(newTypelist, line2)
            if res:
                line2 = line2.replace(place, dic[place])
            tempfile += line2
        line2 = file.readline()
    return tempfile


def TypeExist(list, line):
    for i in list:
        if i in line:
            return i, True
    return False, False


def mylex(data):
    reserved = {
        'if': '_IF',
        'char': '_CHAR',
        'short': '_SHORT',
        'int': '_INT',
        'long': '_LONG',
        'unsigned': '_UNSIGNED',
        'float': '_FLOAT',
        'double': '_DOUBLE',
        'while': '_WHILE',
        'for': '_FOR',
        'return': '_RETURN',
        'break': '_BREAK',
        'const': '_CONST',
        'continue': '_CONTINUE',
        'default': '_DEFAULT',
        'static': '_STATIC',
        'else': '_ELSE',
        'switch': '_SWITCH',
        'printf': '_PRINTF',
        'scanf': '_SCANF',
        'putchar': '_PUTCHAR',
        'getchar': '_GETCHAR',
        'gets': '_GETS',
        'puts': '_PUTS',
        'strlen': '_STRLEN',
        'strcpy': '_STRCPY',
        'strcmp': '_STRCMP',
        'malloc': '_MALLOC',
        'free': '_FREE',
    }

    tokens = [
                 'NUMBER',
                 'PLUS',
                 'MINUS',
                 'MULTI',
                 'DIVIDE',
                 'LARGER',
                 'LOWER',
                 'MOD',
                 'EQUAL',
                 'LSP',
                 'RSP',
                 'LP',
                 'RP',
                 'ID',
                 'CHARACTER',
                 'SEMI',
                 'COMA',
                 'COLON',
                 'EXCLA',
                 'BACKSLASH'
             ] + list(reserved.values())

    t_PLUS = r'\+'
    t_MINUS = r'-'
    t_MULTI = r'\*'
    t_DIVIDE = r'/'
    t_LARGER = r'>'
    t_LOWER = r'<'
    t_EQUAL = r'='
    t_MOD = r'\%'
    t_LSP = r'\{'
    t_RSP = r'\}'
    t_LP = r'\('
    t_RP = r'\)'
    t_SEMI = r';'
    t_COMA = r','
    t_COLON = r'\"'
    t_EXCLA = r'!'
    t_BACKSLASH = r'\\'

    def t_NUMBER(t):
        r'\d+'
        t.value = int(t.value)
        return t

    def t_newline(t):
        r'\n+'
        t.lexer.lineno += len(t.value)

    t_ignore = ' \t'

    def t_ID(t):
        r'[a-zA-Z_][a-zA-Z_0-9]*'
        t.type = reserved.get(t.value, 'ID')
        return t

    # Error handling rule
    def t_error(t):
        print("Illegal character '%s'" % t.value[0])
        t.lexer.skip(1)

    def t_CHARACTER(t):
        r"'.?'"
        return t
    # build lexer
    lexer = lex.lex()
    # input data
    lexer.input(data)
    # tokennize
    pre_line = 1
    result = ''
    while True:
        tok = lexer.token()
        if not tok:
            break
        if pre_line != tok.lineno:
            result += '\n'
            pre_line = tok.lineno
        result += tok.type 
    return result


def CalculateSimilarity(lexfile1,lexfile2):
    similarityLines = 0
    totalLines = 0
    first = []
    second = []
    for line in lexfile1.splitlines():
        first.append(line)
    for line in lexfile2.splitlines():
        second.append(line)
    for i, j in zip(first, second):
        if lcs(i, j) != 0:
            similarityLines += 1
    totalLines = max(len(first), len(second))
    similarity = similarityLines/totalLines
    similarity = similarity * 100
    return similarity


def lcs(x, y):
    m = len(x)
    n = len(y)
    LCS = [[0 for i in range(n+2)] for j in range(m+2)]
    for i in range(0, m+1):
        for j in range(0, n+1):
            if i == 0 or j == 0:
                LCS[i][j] = 0
            elif x[i - 1] == y[j - 1]:
                LCS[i][j] = LCS[i-1][j-1] + 1
            else:
                LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1])
    return LCS[m][n]


homologyDetection()
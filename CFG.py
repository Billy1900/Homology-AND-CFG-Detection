import ply.lex as lex
import networkx as nx

def CFG():
    fin1 = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\2-1A.c", encoding='utf-8')
    pretreatefile1 = pretreate(fin1)
    lexfile1 = mylex(pretreatefile1)
    graph1, node_list1 = initgraph(lexfile1)
    G1 = nx.DiGraph()
    G1.add_nodes_from(node_list1)
    G1.add_edges_from(graph1)
    G1_edges = G1.number_of_edges()

    fin2 = open("C:\\Users\\PC\\Desktop\\assignment\\Test\\2-1B.c", encoding='utf-8')
    pretreatefile2 = pretreate(fin2)
    lexfile2 = mylex(pretreatefile2)
    graph2, node_list2 = initgraph(lexfile2)
    G2 = nx.DiGraph()
    G2.add_nodes_from(node_list2)
    G1.add_edges_from(graph2)

    minv = 0.0
    for v in nx.optimize_graph_edit_distance(G1, G2):
        minv = v
    simi = (1 - ((minv - G1_edges) / G1_edges)) * 100
    print("similarity: %f%%" %(simi))


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
        result += tok.type + ' '
    return result


def keyExist(keylist, line):
    for i in keylist:
        if i in line:
            return i, True
    return False, False


def initgraph(lexfile):
    list = [[] for i in range(50)]
    node_list = []
    linenum_index = 0
    i = 0
    list[i].append(linenum_index) # it means 'start'
    startcycleindex = 0
    startcyclestatus = 0
    startcyclelistnum = 0
    lspnum = 0
    for line in lexfile.splitlines():

        if '_WHILE' in line:
            i += 1
            linenum_index += 1
            list[i - 1].append(linenum_index)
            list[i].append(linenum_index)
            startcycleindex = i
            startcyclestatus = True
            lspnum = 1
            startcyclelistnum = linenum_index
        elif '_IF' in line or 'ID LP' in line:
            i += 1
            linenum_index += 1
            if startcyclestatus == False:
                if startcycleindex != 0:
                    list[startcycleindex].append(linenum_index)
                    list[i].append(linenum_index)
                    startcycleindex = 0
                else:
                    list[i - 1].append(linenum_index)
                    list[i].append(linenum_index)
            elif startcyclestatus == True:
                list[i].append(linenum_index)
                list[i - 1].append(linenum_index)
                if 'LSP' in line:
                    lspnum += 1
        elif 'RSP' in line and startcyclestatus == True:
            lspnum -= 1
            if lspnum == 0:
                startcyclestatus = False
                list[i].append(startcyclelistnum)

    length = max(list)[0] + 1
    temp = [[] for i in range(50)]
    k = 0
    for i in range(len(list)):
        if len(list[i]) > 2:
            for j in range(1, len(list[i])):
                temp[k].append(list[i][0])
                temp[k].append(list[i][j])
                k += 1
        elif len(list[i]) < 2:
            pass
        else:
            temp[k].append(list[i][0])
            temp[k].append(list[i][1])
            k += 1
    for i in range(len(temp)):
        for j in range(len(temp[i])):
            temp[i][j] = str(temp[i][j])
    for i in range(len(temp)):
        if len(temp[i]) > 1:
          temp[i] = tuple(temp[i])
        elif len(temp[i]) == 0:
            temp = temp[0:i]
            break
    for i in range(0, length):
        node_list.append(str(i))
    return temp, node_list


if __name__ == '__main__':
    CFG()
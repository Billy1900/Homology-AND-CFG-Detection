bool ReadFile(phrase &clause, vector<VAR> &variable, string filename)
{

    vector<VAR> vartmp;
    int cnum, vnum;
    ifstream in(filename.c_str());
    if (!in.is_open())
    {
        cout << "Open wrong!" << endl;
        return false;
    }
    else
    {
        while (in.get() != 'p')
            ;
        string cnf;
        in >> cnf;
        in >> vnum >> cnum;
        variable.resize(vnum);
        clause.resize(cnum);

        for (int i = 0; i < vnum; i++)
        {
            variable[i].index = i + 1;
        }
        for (int i = 0; i < cnum; i++)
        {
            int var;
            do
            {
                in >> var;
                if (var != 0)
                {
                    clause[i].push_back(var);
                    variable[abs(var) - 1].num++;
                }
            } while (var != 0);
        }
        in.close();
        return true;
    }
}

string To_Cnf(VEC init[81], int n)
{
    ofstream in("sudoku.cnf");
    if (!in.is_open())
    {
        cout << "Open wrong!" << endl;
    }
    else
    {
        in << 'p' << ' ' << "cnf" << ' ' << 889 << ' ' << 8829 + n << ' ' << 0 << ' ';
        for (int i = 0; i < n; i++) //��ʼֵ�����Ӿ�
            in << init[i].x * 100 + init[i].y * 10 + init[i].value << ' ' << 0 << ' ';

        for (int x = 0; x < 9; x++) //ÿ����������һ��ֵ��1-9��
            for (int y = 0; y < 9; y++)
            {
                for (int z = 1; z <= 9; z++)
                    in << x * 100 + y * 10 + z << ' ';

                in << 0 << ' ';
            }

        for (int y = 0; y < 9; y++) //ÿ�����ֻ��һ��ֵΪz
            for (int z = 1; z <= 9; z++)
                for (int x = 0; x < 8; x++)
                    for (int i = x + 1; i < 9; i++)
                    {
                        in << 0 - (x * 100 + y * 10 + z) << ' ' << 0 - (i * 100 + y * 10 + z) << ' ' << 0 << ' ';
                    }

        for (int x = 0; x < 9; x++) //ÿ�����ֻ��һ��ֵΪz
            for (int z = 1; z <= 9; z++)
                for (int y = 0; y < 8; y++)
                    for (int i = y + 1; i < 9; i++)
                    {
                        in << 0 - (x * 100 + y * 10 + z) << ' ' << 0 - (x * 100 + i * 10 + z) << ' ' << 0 << ' ';
                    }

        for (int z = 1; z <= 9; z++) //3x3������û���ظ���ֵ
            for (int i = 0; i <= 2; i++)
                for (int j = 0; j <= 2; j++)
                    for (int x = 0; x < 3; x++)
                        for (int y = 0; y < 2; y++)
                            for (int k = y + 1; k < 3; k++)
                            {
                                in << 0 - ((3 * i + x) * 100 + (3 * j + y) * 10 + z) << ' ' << 0 - ((3 * i + x) * 100 + (3 * j + k) * 10 + z) << ' ' << 0 << ' ';
                            }
        for (int z = 1; z <= 9; z++)
            for (int i = 0; i <= 2; i++)
                for (int j = 0; j <= 2; j++)
                    for (int x = 0; x < 2; x++)
                        for (int y = 0; y < 3; y++)
                            for (int k = x + 1; k < 3; k++)
                                for (int l = 0; l < 3; l++)
                                {
                                    in << 0 - ((3 * i + x) * 100 + (3 * j + y) * 10 + z) << ' ' << 0 - ((3 * i + k) * 100 + (3 * j + l) * 10 + z) << ' ' << 0 << ' ';
                                }
    }
    in.close();
    return string("sudoku.cnf");
}
void Dig_Hole(int map[9][9], VEC (*init)[81]) //������ڶ�,��ʼֵ45����ÿ��ÿ��ʣ����½�4��
{
    int counts = 81; //ʣ���
    int rc[2][9];    //ÿ��ÿ��ʣ���
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 9; j++)
            rc[i][j] = 9;

    for (int i = 0; i < 9; i++)
    {

        for (int k = 0; k < 9; k += 2)
        {
            if (k == 0 && i % 2 == 1)
                k = 1;
            if (counts == 45)
            {
                To_Vec(map, counts, init);
                for (int m = 0; m < 9; m++)
                    for (int n = 0; n < 9; n++)
                    {
                        cout << map[m][n] << "  " << '|' << "  ";
                        if (n == 8)
                        {
                            cout << endl;
                            cout << "----------------------------------------------------" << endl;
                        }
                    }

                return;
            }
            else if (rc[0][i] <= 4 || rc[1][k] <= 4)
                ;
            else
            {
                int tmp = map[i][k];
                for (int z = 1; z <= 9; z++)
                {
                    if (z == tmp)
                        continue;
                    if (i == 0 && k == 0)
                    {
                        counts--;
                        rc[0][0]--;
                        rc[1][0]--;
                        map[0][0] = 0;
                        break;
                    }
                    else
                    {
                        map[i][k] = z;
                        int n;
                        VEC ini[81];
                        phrase clause;
                        vector<VAR> variable;
                        To_Vec(map, n, &ini);
                        string cnf = To_Cnf(ini, n);

                        if (!ReadFile(clause, variable, cnf.c_str()))
                            ;
                        else
                        {
                            dpllstart = clock();
                            if (DPLL(clause, variable))
                            {
                                map[i][k] = tmp;
                                dpllend = clock();
                                cout << "DPLL costs: " << (double)(dpllend - dpllstart) / CLOCKS_PER_SEC << " S" << endl;
                                ;
                                break;
                            }
                            else if (z == 9 || (z == 8 && tmp == 9))
                            {
                                map[i][k] = 0;
                                counts--;
                                rc[0][i]--;
                                rc[1][k]--;
                                cout << "hole num:" << counts << endl;
                            }
                            dpllend = clock();
                            cout << "DPLL costs: " << (double)(dpllend - dpllstart) / CLOCKS_PER_SEC << " S" << endl;
                            ;
                        }
                    }
                }
            }
        }
    }

    if (counts != 45)
        To_Vec(map, counts, init);
    return;
}

void To_Vec(int map[9][9], int &n, VEC (*init)[81])
{
    n = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (map[i][j] > 0 && map[i][j] <= 9)
            {
                (*init)[n].x = i;
                (*init)[n].y = j;
                (*init)[n].value = map[i][j];
                n++;
            }
        }
}
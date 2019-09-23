int main()
{

    phrase clause;        //�Ӿ伯
    vector<VAR> variable; //��Ԫ��
    VEC initvalue[81];    //������ʼֵ
    /*Sudoku_Create(&initvalue); //�����������


	string file = To_Cnf(initvalue, 45);
	if (!ReadFile(clause, variable, file.c_str()));
	else
	{

		if (DPLL(clause, variable))
		{
			Show_Solution(variable);
		}
		else
		{
			system("CLS");
			cout << "wrong!" << endl;
		}

	}*/
    if (!ReadFile(clause, variable, "7cnf20_90000_90000_7.shuffled-20.cnf"))
        ;
    else
    {
        dpllstart = clock();

        if (DPLL(clause, variable))
        {
            dpllend = clock();
            cout << "DPLL costs: " << (double)(dpllend - dpllstart) / CLOCKS_PER_SEC << " S" << endl;
            cout << "right" << endl;
        }
        else
        {
            system("CLS");
            dpllend = clock();
            cout << "DPLL costs: " << (double)(dpllend - dpllstart) / CLOCKS_PER_SEC << " S" << endl;
            cout << "wrong!" << endl;
        }
    }

    getchar();
    getchar();
    return 0;
}

bool DPLL(phrase S, vector<VAR> &variable)
{

    /*system("CLS");
	cout << "Waiting";
	for (int i = 0; i < times; i++)
	{
	cout << '.' << ' ';
	if (i == 2)
	times = -1;
	}
	times++;*/
    int i = 0;
    if (flag == 1)
        i = S.size() - 1;
    for (; i < S.size(); i++)
    {
        if (S[i].size() == 1)
        {
            S[i][0] > 0 ? variable[abs(S[i][0]) - 1].value = 1 : variable[abs(S[i][0]) - 1].value = 0;
            variable[abs(S[i][0]) - 1].num = 0;
            int val = S[i][0];
            i = -1;
            if (!ReConstruct(val, S))
                return false;
            else if (S.size() == 0)
                return true;
        }
    }

    vector<VAR> vartmp = variable;
    sort(vartmp.begin(), vartmp.end(), MySort);

    vector<int> tmp(1);
    tmp[0] = vartmp[0].index;
    S.push_back(tmp);
    flag = 1;
    if (DPLL(S, variable))
        return true;
    else
    {
        S.pop_back();
        tmp[0] = 0 - vartmp[0].index;
        S.push_back(tmp);
        return DPLL(S, variable);
    }
}
void Sudoku_Create(VEC (*init)[81])
{
    int terminalpattern[9][9];

    srand((int)time(NULL));
    int randseed = rand() % 4; //���ѡ��һ����������
    int mode = rand() % 4;     //���ѡ��һ�ֱ任ģʽ
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            terminalpattern[i][j] = seed[randseed][i][j];
}
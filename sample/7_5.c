int main()

{
    char a;
    char str[100000];
    int i = 0;
    while ((a = getchar()) != '~')
    {
        if (a >= 97 && a <= 122)
        {
            if (a >= 110)
                a = a - 13;
            else
                a = a + 13;
        }
        else if (a > 65 && a <= 90)
        {
            if (a >= 78)
                a = a - 13;
            else
                a = a + 13;
        }
        str[i] = a;
        i++;
    }
    str[i] = '\0';
    cout << str << endl;
    while (1)
    {
    }

    return 0;
}
void MixColumns(unsigned char state[][4]) //列混合
{
    unsigned char t[4];
    int r, c;
    for (c = 0; c < 4; c++) //按列处理
    {
        for (r = 0; r < 4; r++)
        {
            t[r] = state[r][c]; //每一列中的每一个字节拷贝到t[r]中
        }
        for (r = 0; r < 4; r++)
        {
            state[r][c] = FFmul(0x02, t[r]) //矩阵计算，其中加法为异或
                          ^ FFmul(0x03, t[(r + 1) % 4]) ^ FFmul(0x01, t[(r + 2) % 4]) ^ FFmul(0x01, t[(r + 3) % 4]);
        }
    }

    for (r = 0; r < 4; r++)
    {
        cout << int(state[r][0]);
        cout << ' ';
    }
}
int hhh()
{

    phrase clause = nullptr; //�Ӿ伯
    vector<VAR> variable;    //��Ԫ��
    VEC initvalue[81];       //������ʼֵ
    /*
	Sudoku_Create(&initvalue); //�����������


	string file = To_Cnf(initvalue, 45);
	if (!ReadFile(&clause, variable, file.c_str()));
	else
	{
		
			if (DPLL(clause,variable))
			{
				Show_Solution(result);
			}
			else
			{
				system("CLS");
				cout << "wrong!" << endl;
			}
			
	}
	*/
    if (!ReadFile(&clause, variable, "tst_v25_c100.cnf"))
        ;
    else
    {
        dpllstart = clock();

        if (DPLL(clause, variable))
        {
            dpllend = clock();
            cout << "DPLL costs: " << (double)(dpllend - dpllstart) / CLOCKS_PER_SEC << " S" << endl;
            cout << "right" << endl;
            for (int i = 0; i < result.size(); i++)
            {
                cout << result[i].index << ": " << result[i].value << endl;
            }
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
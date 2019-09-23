Status InitaList(SqList *L)
{
    L->elem = (ELemType *)malloc(LIST_INIT_SIZE * sizeof(ELemType));
    if (!L->elem)
    {
        exit(OVERFLOW);
    }
    L->length = 0;
    L->liststsize = LIST_INIT_SIZE;
    L->name = "";
    return OK;
}

//���ٱ�������������DestroyList(L)����ʼ���������Ա�L�Ѵ��ڣ�����������������Ա�L
Status DestroyList(SqList *L)
{
    if (L->elem)
    {
        free(L->elem);
        L->elem = NULL;
        return OK;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

//��ձ�������������ClearList(L)����ʼ���������Ա�L�Ѵ��ڣ���������ǽ�L����Ϊ�ձ�
Status ClearList(SqList *L)
{
    if (L->elem)
    {
        L->length = 0;
        return OK;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

//�ж��ձ�������������ListEmpty(L)����ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE
Status ListEmpty(SqList L)
{
    if (L.elem)
    {
        if (L.length == 0)
        {
            return TRUE;
        }
        else
            return FALSE;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

//�����������������ListLength(L)����ʼ���������Ա��Ѵ��ڣ���������Ƿ���L������Ԫ�صĸ���
int ListLength(SqList L)
{
    if (L.elem)
        return L.length;
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

//���Ԫ�أ�����������GetElem(L,i,e)����ʼ���������Ա��Ѵ��ڣ�1��i��ListLength(L)�������������e����L�е�i������Ԫ�ص�ֵ
Status GetElem(SqList L, int i, ELemType **e)
{
    if (L.elem)
    {
        if (i >= L.length || i <= 0)
        {
            return ERROR;
        }
        *e = L.elem + i - 1;
        return OK;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}
int LocateElem(SqList L, ELemType e)
{
    if (L.elem)
    {
        int k = 1;
        while (*L.elem != e)
        {
            L.elem++;
            k++;
        }
        if (k > L.length)
        {
            return FALSE;
        }
        return k;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

//���ǰ��������������PriorElem(L,cur_e,pre_e)����ʼ���������Ա�L�Ѵ��ڣ������������cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
Status PriorElem(SqList L, ELemType e, ELemType **pre_e)
{
    if (L.elem)
    {
        int i;
        if (L.elem[0] == e)
        { //��һ��Ԫ����ǰ��Ԫ��
            printf("��ǰ��Ԫ��\n");
            return ERROR;
        }
        for (i = 0; i <= L.length - 1; i++)
        { //����ѭ���ҵ���e��ͬ��Ԫ��
            if (e == L.elem[i])
            {
                *pre_e = &(L.elem[i - 1]); //����ֵΪe��Ԫ�ص�ǰһ��Ԫ��
                return OK;
            }
        }
        printf("δ�ҵ�Ԫ��\n");
        return ERROR;
    }
    else
        printf("���Ա�δ��ʼ����\n");
    return ERROR;
}

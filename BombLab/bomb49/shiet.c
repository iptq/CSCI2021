void __cdecl phase_6(char *input)
{
    __int64 v1;          // rdx@1
    __int64 v2;          // rcx@1
    int *element;        // r12@1
    signed int i;        // er13@1
    signed int j;        // ebx@5
    Node *current;       // rdx@10
    signed int jj;       // eax@10
    unsigned __int64 ii; // rsi@11
    int element_;        // ecx@14
    __int64 first;       // rbx@12
    __int64 *el;         // rax@12
    __int64 v12;         // rcx@12
    __int64 hello;       // rdx@16
    signed int iii;      // ebp@17
    __int64 arr[5];      // [sp+0h] [bp-78h]@11
    char v16;            // [sp+28h] [bp-50h]@16
    int numbers[18];     // [sp+30h] [bp-48h]@1

    read_six_numbers((__int64)input, (__int64)numbers);
    element = numbers;
    i = 0;
    while (1)
    {
        if ((unsigned int)(*element - 1) > 5)
            explode_bomb(input, numbers, v1, v2);
        if (++i == 6)
            break;
        j = i;
        do
        {
            if (*element == numbers[j])
                explode_bomb(input, numbers, v1, v2);
            ++j;
        } while (j <= 5);
        ++element;
    }
    ii = 0LL;
    do
    {
        element_ = numbers[ii / 4];
        jj = 1;
        current = &node1;
        if (element_ > 1)
        {
            do
            {
                current = *(Node **)&current->next;
                ++jj;
            } while (jj != element_);
        }
        arr[2 * ii / 8] = (__int64)current;
        ii += 4LL;
    } while (ii != 24);
    first = arr[0];
    el = arr;
    v12 = arr[0];
    do
    {
        hello = el[1];
        *(_QWORD *)(v12 + 8) = hello;
        ++el;
        v12 = hello;
    } while ((char *)el != &v16);
    *(_QWORD *)(hello + 8) = 0LL;
    iii = 5;
    do
    {
        if (*(_DWORD *)first < **(_DWORD **)(first + 8))
            explode_bomb(input, &v16, hello, hello);
        first = *(_QWORD *)(first + 8);
        --iii;
    } while (iii);
}
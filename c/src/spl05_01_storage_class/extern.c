int extern_function(void)
{
    extern int a;
    int b, c;
    a = b = c = 4;
    return a + b + c;
}
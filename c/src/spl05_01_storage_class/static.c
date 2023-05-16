void static_function()
{
    static int cnt = 0;
    ++cnt;
    printf("static int cnt is %d.\n", cnt);
}
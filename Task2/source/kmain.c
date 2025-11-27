
int sum_of_three(int arg1, int arg2, int arg3);
int multiply(int a, int b);
void print_message(const char* message);
int get_string_length(const char* str);

int sum_of_three(int arg1, int arg2, int arg3)
{
    return arg1 + arg2 + arg3;
}

int multiply(int a, int b)
{
    return a * b;
}

int get_string_length(const char* str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;

    return length;
}

int kmain()
{
    int result1 = sum_of_three(10, 20, 30); // 60

    int result2 = multiply(5, 7);   // 35

    const char* test_string = "Hello OS!";
    int result3 = get_string_length(test_string);   // 9


    return result1 + result2 + result3; // 60 + 35 + 9 = 104
}

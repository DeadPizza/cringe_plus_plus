#include <iostream>

static void *func_addrs[3];

void WhoCalls()
{
    void *ret_addr = nullptr;
    asm(
        "push %%rbp\n"
        "pop %0;"
        : "=r"(ret_addr)
    );
    ret_addr = *((void **)ret_addr + 1);

    if (func_addrs[0] < ret_addr && ret_addr < func_addrs[1])
        std::printf("cringe_func is calling (cringe)\n");
    else if (func_addrs[1] < ret_addr && ret_addr < func_addrs[2])
        std::printf("based_func is calling (based)\n");
    else
        std::printf("main is calling (idk)\n");

}

void cringe_func()
{
    WhoCalls();
}

void based_func()
{
    WhoCalls();
}

int main()
{
    func_addrs[0] = (void *)cringe_func;
    func_addrs[1] = (void *)based_func;
    func_addrs[2] = (void *)main;

    WhoCalls();
    cringe_func();
    cringe_func();
    based_func();
    WhoCalls();

    return 0;
}
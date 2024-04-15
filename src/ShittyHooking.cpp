#include <iostream>
#include <sys/mman.h>

#pragma pack(push, 1)
struct jump_instruction
{
    char opcode; //0xe9
    unsigned int offset;
};
#pragma pack(pop)

void do_magick(void *source, void *to_replace)
{
    u_int64_t source_page_start = (__uint64_t)source;
    source_page_start /= 4096;
    source_page_start *= 4096;
    if (mprotect((void *)source_page_start, 4096, PROT_READ | PROT_WRITE | PROT_EXEC) < 0)
    {
        return;
    }

    jump_instruction *jump_ptr = (jump_instruction *)(source);
    jump_ptr->opcode = 0xe9;
    jump_ptr->offset = (char *)(to_replace) - ((char *)source + sizeof(jump_instruction));

    if (mprotect((void *)source_page_start, 4096, PROT_READ | PROT_EXEC) < 0)
    {
        return;
    }
}

float original_function(float a, float b, float c)
{
    return a + b + c;
}

float my_function(float a, float b, float c)
{
    return a * b * c;
}

int main()
{
    do_magick((void*)original_function, (void*)my_function);

    float a = 2, b = 4, c = 6;
    float d = original_function(a, b, c);
    // ожидаем: 2 + 4 + 6 = 12
    // получаем: ???
    std::cout << d << std::endl;

    return 0;
}
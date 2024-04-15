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

struct MySuperClass
{
    virtual void do_job(int x)
    {
        my_x = x;
    }

    int my_x = 0;
};

void do_job_replacer(MySuperClass *thisp, int x)
{
    thisp->my_x = 228 + x;
}

int main()
{
    MySuperClass *obj = new MySuperClass();
    do_magick((*(void***)obj)[0], (void*)do_job_replacer);
    delete obj;


    // Чистый объект, ничем не засран
    obj = new MySuperClass();

    obj->do_job(2);
    
    std::cout << obj->my_x << std::endl;

    return 0;
}
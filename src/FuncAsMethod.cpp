#include <cmath>
#include <iostream>

struct TestClass
{
    float x1, x2;

    virtual void Solve(float a, float b, float c) {}
};

void TotallyNotAMethod_1(TestClass *obj, float a, float b, float c)
{
    float d = b * b - 4 * a * c;

    if (d < 0)
    {
        obj->x1 = obj->x2 = 0;
    }
    else
    {
        float d_sqrt = sqrt(d);

        obj->x1 = (b + d_sqrt) / (2 * a);
        obj->x2 = (-b + d_sqrt) / (2 * a);
    }
}

void TotallyNotAMethod_2(TestClass *obj, float a, float b, float c)
{
    obj->x1 = 228;
    obj->x2 = 1337;
}

int main()
{
    TestClass *test_obj = new TestClass();

    *(void ***)test_obj = (void **)malloc(sizeof(void *));
    **(void ***)test_obj = (void *)TotallyNotAMethod_1;

    test_obj->Solve(1, 5, 4);
    std::printf("x1=%f, x2=%f\n", test_obj->x1, test_obj->x2);

    **(void ***)test_obj = (void *)TotallyNotAMethod_2;

    test_obj->Solve(1, 5, 4);
    std::printf("x1=%f, x2=%f\n", test_obj->x1, test_obj->x2);
}

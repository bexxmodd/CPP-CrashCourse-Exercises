#include <cstdio>
#include <memory>

/* Unique Pointer with Deleter signature */
// std::unique_ptr<T, Deleter=std::default_delete<T>>
using FileGuard = std::unique_ptr<FILE, int(*)(FILE*)>;
using SharedGuard = std::shared_ptr<FILE>;

void write_hello(FileGuard file, const char *name)
{
    fprintf(file.get(), "HELLO %s", name);
}

int shared_hello(SharedGuard file, const char *name)
{
    return fprintf(file.get(), "ZD %s!\n", name);
}

std::shared_ptr<int> sh_ptr { 
    new int{ 10 },
    [](int *x) { delete x; },
    std::allocator<int>{}
};


int main()
{
    auto file = fopen("hal.txt", "a");
    if (!file)
        return errno;
    SharedGuard fileg { file, fclose };

    // File open
    auto r1 = shared_hello(fileg, "BekaM");
    printf("Number of chars written: %d\n", r1);
    // file closed
    printf("\tCount: %ld\n", fileg.use_count());

    SharedGuard another_g { fileg };
    r1 = shared_hello(another_g, "Nerseiiih");
    printf("Number of chars written: %d\n", r1);
    printf("\tCount: %ld\n", fileg.use_count());

    return 0;
}

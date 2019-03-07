#include <assert.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t timer;
    time(&timer);
    srand(timer);
    assert(1 < rand() % 4);
    return 0;
}

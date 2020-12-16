// cortex-m3-rtos template project
#include <kernel.hpp>

void task_routine(void * a_parameter)
{
    while(1);
}

int main()
{
    kernel::init();

    kernel::task::create(task_routine, kernel::task::Priority::Idle);

    kernel::start();

    for(;;);
}

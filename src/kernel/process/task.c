#include <stddef.h>
#include <task.h>

static task_table_t* CONTROL_TASK;

static task_table_t CONTROL_TASKS_MEMORY__section[0x400];

// Initialise control task memory section
static void init_mem_task()
{
    int i = 0;

    while (i < 0x400) {
        CONTROL_TASKS_MEMORY__section[i].pcb_t = (task_table_t)NULL;
        CONTROL_TASKS_MEMORY__section[i].next_entry = (task_table_t*)NULL;
    }

    CONTROL_TASK = CONTROL_TASKS_MEMORY__section;
}

void initialise_multitasking()
{
    // init memory , because the table use linked list data structure
    init_mem_task();

    intptr_t stack;

    process_control_block_t first_pcb = {

        stack,
        (virtaddr_t)initialise_multitasking,
        (task_t*)NULL,
        running,
        0,
        "initialise_multitasking"};

    CONTROL_TASK->pcb_t = first_pcb;
}
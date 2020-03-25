#pragma once 
enum enum_scheduling_algorithm {
    fifo,
    shortest_job,
    round_robin
};

enum enum_process_state
{
	ready,
	running,
	terminated
};
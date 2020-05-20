#pragma once 
enum enum_scheduling_algorithm {
	fifo,
	shortest_job,
	round_robin
};

enum enum_process_state {
	ready,
	running,
	terminated,
	aborted
};

enum enum_memory_allocation_algorithm {
	first_fit,
	best_fit,
	quick_fit
};
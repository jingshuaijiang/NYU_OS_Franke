#pragma once

typedef enum { TRANS_TO_READY, TRANS_TO_RUN, TRANS_TO_BLOCK, TRANS_TO_PREEMPT, TRANS_TO_DONE } event_transition;
class Event
{
public:
	event_transition transition
};


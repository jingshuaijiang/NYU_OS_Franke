#include "Scheduler.hpp"

void FIFO_Scheduler::add_request(IORequest* request)
{
	IOQueue.push_back(request);
}

IORequest* FIFO_Scheduler::get_next_request()
{
	if (IOQueue.empty())
	{
		return nullptr;
	}
	IORequest* request = IOQueue.front();
	IOQueue.pop_front();
	return request;
}

bool FIFO_Scheduler::NOpending()
{
	bool result = (IOQueue.empty()) ? true : false;
	return result;
}

void SSTF_Scheduler::add_request(IORequest* request)
{
	IOQueue.push_back(request);
}

IORequest* SSTF_Scheduler::get_next_request()
{
	if (IOQueue.empty())
	{
		return nullptr;
	}
	IORequest* request = IOQueue.front();
	int min = 0;
	for (int i = 0; i < IOQueue.size(); i++)
	{
		if (abs(current_track - IOQueue.at(i)->track) < abs(current_track - request->track))
		{
			request = IOQueue.at(i);
			min = i;
		}
	}
	std::deque<IORequest*>::iterator it = IOQueue.begin() + min;
	IOQueue.erase(it);
	return request;
}

bool SSTF_Scheduler::NOpending()
{
	bool result = (IOQueue.empty()) ? true : false;
	return result;
}


void LOOK_Scheduler::add_request(IORequest* request)
{
	IOQueue.push_back(request);
}

IORequest* LOOK_Scheduler::get_next_request()
{
	if (IOQueue.empty())
	{
		return nullptr;
	}
	IORequest* request = NULL;
	int min = -1;
	if (direction == 1)
	{
		for (int i = 0; i < IOQueue.size(); i++)
		{
			if (IOQueue.at(i)->track >=current_track)
			{
				if (request == NULL)
				{
					request = IOQueue.at(i);
					min = i;
				}
				else
				{
					if (IOQueue.at(i)->track < request->track)
					{
						request = IOQueue.at(i);
						min = i;
					}
				}
			}
		}
		if (request == NULL)
		{
			direction = -1;
			return get_next_request();
		}
		else
		{
			std::deque<IORequest*>::iterator it = IOQueue.begin() + min;
			IOQueue.erase(it);
			
		}
	}
	else
	{
		for (int i = 0; i < IOQueue.size(); i++)
		{
			if (IOQueue.at(i)->track <=current_track)
			{
				if (request == NULL)
				{
					request = IOQueue.at(i);
					min = i;
				}
				else
				{
					if (IOQueue.at(i)->track > request->track)
					{
						request = IOQueue.at(i);
						min = i;
					}
				}
			}
		}
		if (request == NULL)
		{
			direction = 1;
			return get_next_request();
		}
		else
		{
			std::deque<IORequest*>::iterator it = IOQueue.begin() + min;
			IOQueue.erase(it);
		}
	}
	return request;
}

bool LOOK_Scheduler::NOpending()
{
	bool result = (IOQueue.empty()) ? true : false;
	return result;
}

void CLOOK_Scheduler::add_request(IORequest* request)
{
	IOQueue.push_back(request);
}

IORequest* CLOOK_Scheduler::get_next_request()
{
	if (IOQueue.empty())
	{
		return nullptr;
	}
	IORequest* request = NULL;
	int min = -1;
	for (int i = 0; i < IOQueue.size(); i++)
	{
		if (IOQueue.at(i)->track >= current_track)
		{
			if (request == NULL)
			{
				request = IOQueue.at(i);
				min = i;
			}
			else
			{
				if (IOQueue.at(i)->track < request->track)
				{
					request = IOQueue.at(i);
					min = i;
				}
			}
		}
	}
	if (request != NULL)
	{
		std::deque<IORequest*>::iterator it = IOQueue.begin() + min;
		IOQueue.erase(it);
	}
	else
	{
		min = 0;
		request = IOQueue.front();
		for (int i = 0; i < IOQueue.size(); i++)
		{
			if (IOQueue.at(i)->track < request->track)
			{
				request = IOQueue.at(i);
				min = i;
			}
		}
		std::deque<IORequest*>::iterator it = IOQueue.begin() + min;
		IOQueue.erase(it);
	}	
	return request;
}

bool CLOOK_Scheduler::NOpending()
{
	bool result = (IOQueue.empty()) ? true : false;
	return result;
}
void FLOOK_Scheduler::add_request(IORequest* request)
{
	addqueue->push_back(request);
}

IORequest* FLOOK_Scheduler::get_next_request()
{
	if (activequeue->empty())
	{
		deque<IORequest*>* temp = addqueue;
		addqueue = activequeue;
		activequeue = temp;
	}
	IORequest* request = NULL;
	int min = -1;
	if (direction == 1)
	{
		for (int i = 0; i < activequeue->size(); i++)
		{
			if (activequeue->at(i)->track >= current_track)
			{
				if (request == NULL)
				{
					request = activequeue->at(i);
					min = i;
				}
				else
				{
					if (activequeue->at(i)->track < request->track)
					{
						request = activequeue->at(i);
						min = i;
					}
				}
			}
		}
		if (request == NULL)
		{
			direction = -1;
			return get_next_request();
		}
		else
		{
			std::deque<IORequest*>::iterator it = activequeue->begin() + min;
			activequeue->erase(it);

		}
	}
	else
	{
		for (int i = 0; i < activequeue->size(); i++)
		{
			if (activequeue->at(i)->track <= current_track)
			{
				if (request == NULL)
				{
					request = activequeue->at(i);
					min = i;
				}
				else
				{
					if (activequeue->at(i)->track > request->track)
					{
						request = activequeue->at(i);
						min = i;
					}
				}
			}
		}
		if (request == NULL)
		{
			direction = 1;
			return get_next_request();
		}
		else
		{
			std::deque<IORequest*>::iterator it = activequeue->begin() + min;
			activequeue->erase(it);
		}
	}
	return request;
}

bool FLOOK_Scheduler::NOpending()
{
	bool result = false;
	if (activequeue->empty() && addqueue->empty())
	{
		result = true;
	}
	return result;
}

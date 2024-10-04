#include "InputReceiver.hpp"

void InputReceiver::addEvent(Event event)
{
	_Events.push_back(event);
}

vector<Event>& InputReceiver::getEvents()
{
	return _Events;
}

void InputReceiver::clearEvents()
{
	_Events.clear();
}
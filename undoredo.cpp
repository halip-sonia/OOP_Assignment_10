#include "undoredo.h"

action UndoStack::get_last() 
{
	return actions.back();
}

void UndoStack::add_action(action a)
{
	actions.push_back(a);
}

void UndoStack::undo(EventRepo* r)
{
	auto current = get_last();
	if (current.performed == 2)
	{
		r->update_event(current.position, current.event);
	}
	if (current.performed == 1)
	{
		r->add_position(current.event, current.position);
	}
	if (current.performed == 0)
	{
		r->remove_event(current.position);
	}
	actions.pop_back();
}

action RedoStack::get_last()
{
	return actions.back();
}

void RedoStack::add_action(action a)
{
	actions.push_back(a);
}

void RedoStack::redo(EventRepo* r)
{
	auto current = get_last();
	if (current.performed == 2)
	{
		r->update_event(current.position, current.event);
	}
	if (current.performed == 0)
	{
		r->add_position(current.event, current.position);
	}
	if (current.performed == 1)
	{
		r->remove_event(current.position);
	}
	actions.pop_back();
}

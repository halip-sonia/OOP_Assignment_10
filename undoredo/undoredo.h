#pragma once
#include "repo/repo.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include <repo/repo.h>

class RedoStack;
class UndoStack;

struct action {
	Event event;
	int position;
	int performed;
};

class Stack {
protected:
	std::vector<action> actions;
public:
	virtual void add_action(action a)=0;
	bool isEmpty() { return actions.size() == 0; }

};

class UndoStack: public Stack
{
public:
	action get_last();
	void add_action(action a) override;
	void undo(EventRepo* r);
};

class RedoStack : public Stack
{
public:
	action get_last();
	void add_action(action a) override;
	void redo(EventRepo* r);
};



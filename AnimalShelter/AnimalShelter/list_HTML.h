#pragma once
#include "memory_repo.h"

class HTMLList :
	public MemRepo
{
public:
	HTMLList();
	~HTMLList();

	void save(); // override;
	void openInApp();// override;
};
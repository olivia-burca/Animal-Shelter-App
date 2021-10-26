#pragma once
#include "memory_repo.h"

class CSVList :
	public MemRepo
{
public:
	CSVList();
	~CSVList();

	void save(); // override;
	void openInApp();
};
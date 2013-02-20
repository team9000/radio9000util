#pragma once

class DynData
{
public:
	char* memory;
	size_t size;

	DynData()
	{
		memory = NULL;
		size = 0;
	}
	~DynData()
	{
		if(memory) free(memory);
	}

	void Realloc(size_t size);

	void Push(wxString string);
	void Push(const char* ptr, size_t length);

	wxString PopLine();
	void PopGarbage(size_t bytes);
};

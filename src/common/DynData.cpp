#include "prec.h"
#include "DynData.h"

void DynData::Realloc(size_t newsize)
{
	size = newsize;

	if(newsize == 0) {
		if(memory) {
			free(memory);
			memory = NULL;
		}
		return;
	}
	if(memory)
		memory = (char*)realloc(memory, newsize);
	else
		memory = (char*)malloc(newsize);
}

void DynData::Push(wxString string) {
	const char* ptr = string.ToUTF8();
	Push(ptr, strlen(ptr)+1);
}
void DynData::Push(const char* ptr, size_t length) {
	Realloc(size+length);
	memcpy(&memory[size-length], ptr, length);
}

wxString DynData::PopLine() {
	boolean foundNL = false;
	size_t strlen = 0;
	for(strlen = 0; strlen < size; strlen++) {
		if(memory[strlen] == '\n') {
			foundNL = true;
			break;
		}
	}
	if(!foundNL) return wxT("");

	wxString ret = wxString::FromUTF8(memory, strlen);

	if(strlen == this->size-1) {
		Realloc(0);
	} else {
		PopGarbage(strlen+1);
	}

	return ret;
}

void DynData::PopGarbage(size_t bytes) {
	size_t newsize = this->size-bytes;
	memcpy(memory, &memory[bytes], newsize);
	Realloc(newsize);
}

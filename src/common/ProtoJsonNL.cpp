#include "prec.h"
#include "ProtoJsonNL.h"

wxJSONValue ProtoJsonNL::ReadJson()
{
	wxString read = ReadLine();
	if(read.IsEmpty()) {
		return wxJSONValue(wxJSONTYPE_INVALID);
	}

	wxJSONValue root;
	wxJSONReader reader;
	int numErrors = reader.Parse(read, &root);
	wxArrayString errors = reader.GetErrors();
	if(numErrors > 0) {
		WLOG(wxT("PACKAGE DROPPED - JSON is not well-formed\n")+read+wxT("\n"));
		return wxJSONValue(wxJSONTYPE_INVALID);
	}

	return root;
}

void ProtoJsonNL::Send(wxJSONValue& message)
{
	wxJSONWriter writer;
	wxString output;
	writer.Write(message, output);
	SocketRaw::Send(output+"\n");
}

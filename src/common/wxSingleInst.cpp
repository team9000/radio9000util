#include "prec.h"
#include "wxSingleInst.h"
#include "wootalyzer.h"

bool sConnection::OnExecute(const wxString& topic, wxChar*data, int size, wxIPCFormat format)
{
	wxGetApp().OnSecondInstance();
	return true;
}

wxSingleInst::wxSingleInst()
{
	check = NULL;
	server = NULL;
	other = false;

	check = new wxSingleInstanceChecker(wxT(MUTEX_IDENT));
	if(check->IsAnotherRunning())
	{
		wxClient client;
		wxConnectionBase* connection = 
			client.MakeConnection(wxT("localhost"),
			wxT(MUTEX_IDENT), wxT(MUTEX_IDENT));

		if(connection) {
			connection->Execute(wxT(""));
			connection->Disconnect();
			delete connection;
			delete check;
			check = NULL;
			other = true;
			return;
		} else {
			// Maybe the other process crashed? Keep running
		}
	}

	// this server creation may fail, but if it does --- meh, oh well
	server = new sServer();
	server->Create(wxT(MUTEX_IDENT));
}

wxSingleInst::~wxSingleInst()
{
	if(check) delete check;
	if(server) delete server;
}

bool wxSingleInst::IsAnotherRunning()
{
	return other;
}

wxConnectionBase *sServer::OnAcceptConnection(const wxString& topic)
{
	if (topic.Lower() == wxString(wxT(MUTEX_IDENT)).Lower()) {
		// Check that there are no modal dialogs active
		wxWindowList::Node* node = wxTopLevelWindows.GetFirst();
		while (node)
		{
			wxDialog* dialog = wxDynamicCast(node->GetData(), wxDialog);
			if (dialog && dialog->IsModal())
			{
				return false;
			}

			node = node->GetNext();
		}
		return new sConnection();
	}
	else
		return NULL;
}

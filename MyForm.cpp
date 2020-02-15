#include "MyForm.h"

using namespace DiskMonitor;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	DiskMonitor::MyForm form;
	Application::Run(%form);

	return 0;
}



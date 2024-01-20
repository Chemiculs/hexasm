#include "MyForm.h"
using namespace System::Windows::Forms;
using namespace System;

[STAThreadAttribute]
System::Void main() {

	Application::EnableVisualStyles();

	Application::Run(gcnew hexasm::MyForm());

}

#include "winmain.h"


[STAThreadAttribute]
int __clrcall main() {


	System::Windows::Forms::Application::EnableVisualStyles();

	global::main_window = gcnew hexasm::winmain();

	System::Windows::Forms::Application::Run(global::main_window);

	return 0;

}
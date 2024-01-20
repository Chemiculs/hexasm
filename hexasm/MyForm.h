#pragma once

namespace hexasm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: wyDay::Controls::VistaMenu^ vista_m;
	protected:

	private: System::Windows::Forms::MainMenu^ mainMenu1;
	private: System::Windows::Forms::MenuItem^ file_m;
	private: System::Windows::Forms::MenuItem^ menuItem1;
	private: System::Windows::Forms::MenuItem^ menuItem2;
	private: System::Windows::Forms::MenuItem^ menuItem3;
	private: System::Windows::Forms::MenuItem^ menuItem4;
	private: System::Windows::Forms::MenuItem^ menuItem6;
	private: System::Windows::Forms::MenuItem^ menuItem5;
	private: System::Windows::Forms::MenuItem^ menuItem7;
	private: System::Windows::Forms::MenuItem^ menuItem8;
	private: System::Windows::Forms::MenuItem^ menuItem9;
	private: System::Windows::Forms::MenuItem^ menuItem10;
	private: System::Windows::Forms::MenuItem^ menuItem11;
	private: System::Windows::Forms::MenuItem^ menuItem12;
	private: System::Windows::Forms::MenuItem^ menuItem13;
	protected:

	protected:

	private: System::ComponentModel::IContainer^ components;

	protected:
















	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->vista_m = (gcnew wyDay::Controls::VistaMenu(this->components));
			this->mainMenu1 = (gcnew System::Windows::Forms::MainMenu(this->components));
			this->file_m = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem1 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem2 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem3 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem4 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem5 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem6 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem7 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem8 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem9 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem10 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem11 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem12 = (gcnew System::Windows::Forms::MenuItem());
			this->menuItem13 = (gcnew System::Windows::Forms::MenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vista_m))->BeginInit();
			this->SuspendLayout();
			// 
			// vista_m
			// 
			this->vista_m->ContainerControl = this;
			// 
			// mainMenu1
			// 
			this->mainMenu1->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
				this->file_m, this->menuItem10,
					this->menuItem12
			});
			// 
			// file_m
			// 
			this->file_m->Index = 0;
			this->file_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(9) {
				this->menuItem1, this->menuItem2,
					this->menuItem3, this->menuItem4, this->menuItem6, this->menuItem5, this->menuItem7, this->menuItem8, this->menuItem9
			});
			this->file_m->Text = L"&File";
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 0;
			this->menuItem1->Text = L"&New";
			// 
			// menuItem2
			// 
			this->menuItem2->Index = 1;
			this->menuItem2->Text = L"&Open..";
			// 
			// menuItem3
			// 
			this->menuItem3->Index = 2;
			this->menuItem3->Text = L"&Save";
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 3;
			this->menuItem4->Text = L"S&ave As...";
			// 
			// menuItem5
			// 
			this->menuItem5->Index = 5;
			this->menuItem5->Text = L"&Close";
			// 
			// menuItem6
			// 
			this->menuItem6->Index = 4;
			this->menuItem6->Text = L"-";
			// 
			// menuItem7
			// 
			this->menuItem7->Index = 6;
			this->menuItem7->Text = L"C&lose All";
			// 
			// menuItem8
			// 
			this->menuItem8->Index = 7;
			this->menuItem8->Text = L"-";
			// 
			// menuItem9
			// 
			this->menuItem9->Index = 8;
			this->menuItem9->Text = L"&Exit";
			// 
			// menuItem10
			// 
			this->menuItem10->Index = 1;
			this->menuItem10->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->menuItem11 });
			this->menuItem10->Text = L"&Options";
			// 
			// menuItem11
			// 
			this->menuItem11->Index = 0;
			this->menuItem11->Text = L"&Settings...";
			// 
			// menuItem12
			// 
			this->menuItem12->Index = 2;
			this->menuItem12->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->menuItem13 });
			this->menuItem12->Text = L"&Help";
			// 
			// menuItem13
			// 
			this->menuItem13->Index = 0;
			this->menuItem13->Text = L"&About...";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->DoubleBuffered = true;
			this->Menu = this->mainMenu1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vista_m))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
	}
	

	private: System::Void open_m_Click(System::Object^ sender, System::EventArgs^ e) {
		auto dialog_o = gcnew OpenFileDialog();

		if (dialog_o->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

		}

		delete dialog_o;
	}
};
}

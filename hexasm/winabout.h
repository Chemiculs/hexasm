#ifndef WINABOUT_H
#define WINABOUT_H

using namespace System;
using namespace System::Windows::Forms;

#include "util.hpp"
#include "resource/resource.hpp"

namespace hexasm {

	

	/// <summary>
	/// Summary for winabout
	/// </summary>
	public ref class winabout : public System::Windows::Forms::Form
	{
	public:
		winabout(void)
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
		~winabout()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pb_logo;
	protected:

	private: System::Windows::Forms::Label^ lbl_about;
	private: System::Windows::Forms::Button^ btn_ok;
	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winabout::typeid));
			this->pb_logo = (gcnew System::Windows::Forms::PictureBox());
			this->lbl_about = (gcnew System::Windows::Forms::Label());
			this->btn_ok = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_logo))->BeginInit();
			this->SuspendLayout();
			// 
			// pb_logo
			// 
			this->pb_logo->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_logo.InitialImage")));
			this->pb_logo->Location = System::Drawing::Point(12, 12);
			this->pb_logo->Name = L"pb_logo";
			this->pb_logo->Size = System::Drawing::Size(256, 256);
			this->pb_logo->TabIndex = 0;
			this->pb_logo->TabStop = false;
			// 
			// lbl_about
			// 
			this->lbl_about->AutoSize = true;
			this->lbl_about->Location = System::Drawing::Point(12, 271);
			this->lbl_about->Name = L"lbl_about";
			this->lbl_about->Size = System::Drawing::Size(244, 39);
			this->lbl_about->TabIndex = 1;
			this->lbl_about->Text = L"                              hexasm -\r\n\r\nA powerful binary data editor and manip"
				L"ulation tool\r\n";
			// 
			// btn_ok
			// 
			this->btn_ok->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_ok->Location = System::Drawing::Point(11, 320);
			this->btn_ok->Name = L"btn_ok";
			this->btn_ok->Size = System::Drawing::Size(256, 23);
			this->btn_ok->TabIndex = 2;
			this->btn_ok->Text = L"&Close";
			this->btn_ok->UseVisualStyleBackColor = true;
			this->btn_ok->Click += gcnew System::EventHandler(this, &winabout::btn_ok_Click);
			// 
			// winabout
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(280, 357);
			this->Controls->Add(this->btn_ok);
			this->Controls->Add(this->lbl_about);
			this->Controls->Add(this->pb_logo);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winabout";
			this->Text = L"About hexasm";
			this->Load += gcnew System::EventHandler(this, &winabout::winabout_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_logo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void btn_ok_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}
	private: System::Void winabout_Load(System::Object^ sender, System::EventArgs^ e) {

		auto screen = Screen::PrimaryScreen;

		this->Location = Point((screen->Bounds.Width / 2) - (this->Width / 2), (screen->Bounds.Height / 2) - (this->Height / 2));

		pb_logo->Image = util::image_from_native_array(&about_dialog_256x256, sizeof(about_dialog_256x256));
	}
};
}

#endif
#ifndef WINHEXSTR_H
#define WINHEXSTR_H

#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "interop.hpp"

namespace hexasm {


	/// <summary>
	/// Summary for winhexstr
	/// </summary>
	public ref class winhexstr : public System::Windows::Forms::Form
	{
	public:

		int is_copy_;

		winhexstr(int is_copy)
		{
			is_copy_ = is_copy;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~winhexstr()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn_cancel;
	protected:

	private: System::Windows::Forms::Button^ btn_ok;
	public: System::Windows::Forms::RadioButton^ rb_hex;
	public: System::Windows::Forms::RadioButton^ rb_string;
	private:

	public:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winhexstr::typeid));
			this->btn_cancel = (gcnew System::Windows::Forms::Button());
			this->btn_ok = (gcnew System::Windows::Forms::Button());
			this->rb_hex = (gcnew System::Windows::Forms::RadioButton());
			this->rb_string = (gcnew System::Windows::Forms::RadioButton());
			this->SuspendLayout();
			// 
			// btn_cancel
			// 
			this->btn_cancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel->Location = System::Drawing::Point(12, 36);
			this->btn_cancel->Name = L"btn_cancel";
			this->btn_cancel->Size = System::Drawing::Size(75, 23);
			this->btn_cancel->TabIndex = 0;
			this->btn_cancel->Text = L"&Cancel";
			this->btn_cancel->UseVisualStyleBackColor = true;
			this->btn_cancel->Click += gcnew System::EventHandler(this, &winhexstr::btn_cancel_Click);
			// 
			// btn_ok
			// 
			this->btn_ok->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_ok->Location = System::Drawing::Point(93, 36);
			this->btn_ok->Name = L"btn_ok";
			this->btn_ok->Size = System::Drawing::Size(75, 23);
			this->btn_ok->TabIndex = 1;
			this->btn_ok->UseVisualStyleBackColor = true;
			this->btn_ok->Click += gcnew System::EventHandler(this, &winhexstr::btn_ok_Click);
			// 
			// rb_hex
			// 
			this->rb_hex->AutoSize = true;
			this->rb_hex->Checked = true;
			this->rb_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_hex->Location = System::Drawing::Point(12, 12);
			this->rb_hex->Name = L"rb_hex";
			this->rb_hex->Size = System::Drawing::Size(50, 18);
			this->rb_hex->TabIndex = 2;
			this->rb_hex->TabStop = true;
			this->rb_hex->Text = L"&Hex";
			this->rb_hex->UseVisualStyleBackColor = true;
			// 
			// rb_string
			// 
			this->rb_string->AutoSize = true;
			this->rb_string->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_string->Location = System::Drawing::Point(110, 12);
			this->rb_string->Name = L"rb_string";
			this->rb_string->Size = System::Drawing::Size(58, 18);
			this->rb_string->TabIndex = 3;
			this->rb_string->Text = L"&String";
			this->rb_string->UseVisualStyleBackColor = true;
			// 
			// winhexstr
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(178, 70);
			this->Controls->Add(this->rb_string);
			this->Controls->Add(this->rb_hex);
			this->Controls->Add(this->btn_ok);
			this->Controls->Add(this->btn_cancel);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winhexstr";
			this->ShowInTaskbar = false;
			this->Load += gcnew System::EventHandler(this, &winhexstr::winhexstr_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &winhexstr::winhexstr_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btn_cancel_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}

	private: System::Void btn_ok_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void winhexstr_Load(System::Object^ sender, System::EventArgs^ e) {

		this->Location = Point((Screen::PrimaryScreen->Bounds.Width / 2) - (this->Width / 2), (Screen::PrimaryScreen->Bounds.Height / 2) - (this->Height / 2));

		if (!is_copy_) {
			this->Text = "Copy As...";
			btn_ok->Text = "C&opy";
		}
		else if(is_copy_ == 1){
			this->Text = "Paste As...";
			btn_ok->Text = "&Paste";
		}
		else {
			this->Text = "Cut As...";
			btn_ok->Text = "C&ut";
		}

		SetCursorPos(this->Bounds.Left + rb_string->Location.X, this->Bounds.Top + (rb_string->Location.Y) * 2);
	}

	private: System::Void winhexstr_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

		if (e->KeyCode != Keys::Enter)
			return;
	}

};
}

#endif
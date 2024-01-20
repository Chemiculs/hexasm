#ifndef WINJUMP_H
#define WINJUMP_H

#include "TextBoxBaseExtension.hpp"
using namespace hexasm::gui;

namespace hexasm {

	using namespace System;
	using namespace System::Windows::Forms;

	public ref class winjump : public System::Windows::Forms::Form
	{
	public: UInt64 original_offset = static_cast<UInt64>(0x0);

	public: UInt64 original_size = static_cast<UInt64>(0x0);

	public: UInt64 offset = static_cast<UInt64>(0x0);

	private:

		TextBoxBaseExtension<UInt64>^ filter_offset;

	public: inline __clrcall winjump(UInt64 selected_offset, UInt64 size_) : original_offset(selected_offset), original_size(size_)
	{
		InitializeComponent();
	}

	
	protected: inline __clrcall ~winjump()
	{
		if (components)
		{
			delete components;
		}
	}

	private: System::Windows::Forms::Button^ btn_cancel;

	private: System::Windows::Forms::Button^ btn_ok;
	private: System::Windows::Forms::GroupBox^ group_offset;

	private: System::Windows::Forms::RadioButton^ rb_dec;

	private: System::Windows::Forms::RadioButton^ rb_oct;
	private: System::Windows::Forms::RadioButton^ rb_hex;
	private: System::Windows::Forms::RadioButton^ rb_begin;
	private: System::Windows::Forms::RadioButton^ rb_end;


	private: System::Windows::Forms::RadioButton^ rb_current;
	private: System::Windows::Forms::TextBox^ txt_offset;


	private: System::Windows::Forms::GroupBox^ group_relate;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winjump::typeid));
			this->btn_cancel = (gcnew System::Windows::Forms::Button());
			this->btn_ok = (gcnew System::Windows::Forms::Button());
			this->group_offset = (gcnew System::Windows::Forms::GroupBox());
			this->txt_offset = (gcnew System::Windows::Forms::TextBox());
			this->rb_dec = (gcnew System::Windows::Forms::RadioButton());
			this->rb_oct = (gcnew System::Windows::Forms::RadioButton());
			this->rb_hex = (gcnew System::Windows::Forms::RadioButton());
			this->group_relate = (gcnew System::Windows::Forms::GroupBox());
			this->rb_end = (gcnew System::Windows::Forms::RadioButton());
			this->rb_begin = (gcnew System::Windows::Forms::RadioButton());
			this->rb_current = (gcnew System::Windows::Forms::RadioButton());
			this->group_offset->SuspendLayout();
			this->group_relate->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_cancel
			// 
			this->btn_cancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel->Location = System::Drawing::Point(6, 184);
			this->btn_cancel->Name = L"btn_cancel";
			this->btn_cancel->Size = System::Drawing::Size(122, 23);
			this->btn_cancel->TabIndex = 3;
			this->btn_cancel->Text = L"&Cancel";
			this->btn_cancel->UseVisualStyleBackColor = true;
			this->btn_cancel->Click += gcnew System::EventHandler(this, &winjump::btn_cancel_Click);
			// 
			// btn_ok
			// 
			this->btn_ok->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_ok->Location = System::Drawing::Point(149, 184);
			this->btn_ok->Name = L"btn_ok";
			this->btn_ok->Size = System::Drawing::Size(122, 23);
			this->btn_ok->TabIndex = 4;
			this->btn_ok->Text = L"&Jump";
			this->btn_ok->UseVisualStyleBackColor = true;
			this->btn_ok->Click += gcnew System::EventHandler(this, &winjump::btn_ok_Click);
			// 
			// group_offset
			// 
			this->group_offset->Controls->Add(this->txt_offset);
			this->group_offset->Controls->Add(this->rb_dec);
			this->group_offset->Controls->Add(this->rb_oct);
			this->group_offset->Controls->Add(this->rb_hex);
			this->group_offset->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->group_offset->ForeColor = System::Drawing::SystemColors::ButtonShadow;
			this->group_offset->Location = System::Drawing::Point(6, 13);
			this->group_offset->Name = L"group_offset";
			this->group_offset->Size = System::Drawing::Size(265, 74);
			this->group_offset->TabIndex = 5;
			this->group_offset->TabStop = false;
			this->group_offset->Text = L"Offset:";
			// 
			// txt_offset
			// 
			this->txt_offset->Location = System::Drawing::Point(6, 19);
			this->txt_offset->Name = L"txt_offset";
			this->txt_offset->Size = System::Drawing::Size(250, 20);
			this->txt_offset->TabIndex = 9;
			this->txt_offset->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &winjump::txt_offset_KeyDown);
			// 
			// rb_dec
			// 
			this->rb_dec->AutoSize = true;
			this->rb_dec->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_dec->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->rb_dec->Location = System::Drawing::Point(107, 47);
			this->rb_dec->Name = L"rb_dec";
			this->rb_dec->Size = System::Drawing::Size(51, 18);
			this->rb_dec->TabIndex = 6;
			this->rb_dec->Text = L"Dec";
			this->rb_dec->UseVisualStyleBackColor = true;
			this->rb_dec->CheckedChanged += gcnew System::EventHandler(this, &winjump::rb_dec_CheckedChanged);
			// 
			// rb_oct
			// 
			this->rb_oct->AutoSize = true;
			this->rb_oct->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_oct->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->rb_oct->Location = System::Drawing::Point(214, 47);
			this->rb_oct->Name = L"rb_oct";
			this->rb_oct->Size = System::Drawing::Size(48, 18);
			this->rb_oct->TabIndex = 7;
			this->rb_oct->Text = L"Oct";
			this->rb_oct->UseVisualStyleBackColor = true;
			this->rb_oct->CheckedChanged += gcnew System::EventHandler(this, &winjump::rb_oct_CheckedChanged);
			// 
			// rb_hex
			// 
			this->rb_hex->AutoSize = true;
			this->rb_hex->Checked = true;
			this->rb_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_hex->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->rb_hex->Location = System::Drawing::Point(6, 47);
			this->rb_hex->Name = L"rb_hex";
			this->rb_hex->Size = System::Drawing::Size(50, 18);
			this->rb_hex->TabIndex = 8;
			this->rb_hex->TabStop = true;
			this->rb_hex->Text = L"Hex";
			this->rb_hex->UseVisualStyleBackColor = true;
			this->rb_hex->CheckedChanged += gcnew System::EventHandler(this, &winjump::rb_hex_CheckedChanged);
			// 
			// group_relate
			// 
			this->group_relate->Controls->Add(this->rb_end);
			this->group_relate->Controls->Add(this->rb_begin);
			this->group_relate->Controls->Add(this->rb_current);
			this->group_relate->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->group_relate->Location = System::Drawing::Point(6, 93);
			this->group_relate->Name = L"group_relate";
			this->group_relate->Size = System::Drawing::Size(265, 85);
			this->group_relate->TabIndex = 6;
			this->group_relate->TabStop = false;
			this->group_relate->Text = L"Offset Relation:";
			// 
			// rb_end
			// 
			this->rb_end->AutoSize = true;
			this->rb_end->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_end->Location = System::Drawing::Point(6, 61);
			this->rb_end->Name = L"rb_end";
			this->rb_end->Size = System::Drawing::Size(94, 18);
			this->rb_end->TabIndex = 11;
			this->rb_end->Text = L"End (reverse)";
			this->rb_end->UseVisualStyleBackColor = true;
			// 
			// rb_begin
			// 
			this->rb_begin->AutoSize = true;
			this->rb_begin->Checked = true;
			this->rb_begin->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_begin->Location = System::Drawing::Point(6, 18);
			this->rb_begin->Name = L"rb_begin";
			this->rb_begin->Size = System::Drawing::Size(58, 18);
			this->rb_begin->TabIndex = 12;
			this->rb_begin->TabStop = true;
			this->rb_begin->Text = L"Begin";
			this->rb_begin->UseVisualStyleBackColor = true;
			// 
			// rb_current
			// 
			this->rb_current->AutoSize = true;
			this->rb_current->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_current->Location = System::Drawing::Point(6, 39);
			this->rb_current->Name = L"rb_current";
			this->rb_current->Size = System::Drawing::Size(96, 18);
			this->rb_current->TabIndex = 10;
			this->rb_current->TabStop = true;
			this->rb_current->Text = L"Current Offset";
			this->rb_current->UseVisualStyleBackColor = true;
			// 
			// winjump
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
				static_cast<System::Int32>(static_cast<System::Byte>(35)));
			this->ClientSize = System::Drawing::Size(277, 213);
			this->Controls->Add(this->group_relate);
			this->Controls->Add(this->group_offset);
			this->Controls->Add(this->btn_ok);
			this->Controls->Add(this->btn_cancel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winjump";
			this->Text = L"Jump to offset";
			this->Load += gcnew System::EventHandler(this, &winjump::winjump_Load);
			this->group_offset->ResumeLayout(false);
			this->group_offset->PerformLayout();
			this->group_relate->ResumeLayout(false);
			this->group_relate->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void winjump_Load(System::Object^ sender, System::EventArgs^ e) {

		this->Location = Point((Screen::PrimaryScreen->Bounds.Width / 2) - (this->Width / 2), (Screen::PrimaryScreen->Bounds.Height / 2) - (this->Height / 2));
		
		filter_offset = gcnew TextBoxBaseExtension<UInt64>(txt_offset, 16);

		txt_offset->Text = original_offset.ToString("X16");

		txt_offset->Select();

		txt_offset->Focus();
	}

	private: System::Void txt_offset_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

		if (e->KeyCode == Keys::Enter)
			btn_ok_Click(nullptr, nullptr);
	}

	private: System::Void btn_ok_Click(System::Object^ sender, System::EventArgs^ e) {
		UInt64 offset_ = static_cast<UInt64>(0x0);

		if(rb_dec->Checked){
			if (!UInt64::TryParse(txt_offset->Text, offset_)) {
				MessageBox::Show("Invalid decimal value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		else if (rb_hex->Checked) {
			try {

				if (txt_offset->Text->Length > 16) {
					MessageBox::Show("Invalid unsigned 64-bit integral value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				offset_ = Convert::ToUInt64(txt_offset->Text, 16);

			} catch (FormatException^) { MessageBox::Show("Invalid hexadecimal value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error); return; }
		}
		else if (rb_oct->Checked) {
			try {

				if (txt_offset->Text->Length > 23) {
					MessageBox::Show("Invalid unsigned 64-bit integral value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				offset_ = Convert::ToUInt64(txt_offset->Text, 8);

			} catch (FormatException^) { MessageBox::Show("Invalid octal value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error); return; }
		}

		if (rb_begin->Checked) {

			if (offset_ > original_size) {
				MessageBox::Show("Invalid offset relative to begin of data entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			offset = offset_;
		}
		else if (rb_current->Checked) {
			auto offset_new = offset_ + original_offset;

			if (offset_new >= original_size) {
				MessageBox::Show("Invalid offset relative to current position entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			offset = offset_new;
		}
		else if(rb_end->Checked){
			auto offset_new = original_size - offset_;

			if (offset_new >= original_size) {
				MessageBox::Show("Invalid offset relative to end of data entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			offset = offset_new;
		}

		DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void btn_cancel_Click(System::Object^ sender, System::EventArgs^ e) {
		DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}

	private: System::Void rb_hex_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		if (!filter_offset)
			return;

		filter_offset->swap_base(16);
	}

	private: System::Void rb_dec_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		if (!filter_offset)
			return;

		filter_offset->swap_base(10);
	}

	private: System::Void rb_oct_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		if (!filter_offset)
			return;

		filter_offset->swap_base(8);
	}

};
}


#endif
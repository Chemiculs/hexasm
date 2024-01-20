#ifndef WINBLOCKSEL_H
#define WINBLOCKSEL_H

#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "TextBoxBaseExtension.hpp"
using namespace hexasm::gui;

namespace hexasm {

	

	public ref class winblocksel : public System::Windows::Forms::Form
	{

	public:

		UInt64 start_address_;
		UInt64 end_address_;
		UInt64 original_size_;
		UInt64 original_offset_;

		TextBoxBaseExtension<UInt64>^ filter_start;
		TextBoxBaseExtension<UInt64>^ filter_end;
		TextBoxBaseExtension<UInt64>^ filter_length;

		winblocksel(UInt64 size, UInt64 offset) : original_size_(size), original_offset_(offset)
		{
			InitializeComponent();
		}

	protected:

		~winblocksel()
		{
			if (components)
			{
				delete components;
				delete filter_start;
				delete filter_end;
				delete filter_length;
			}
		}

	private: System::Windows::Forms::Label^ lbl_start;
	private: System::Windows::Forms::RadioButton^ rb_end;
	private: System::Windows::Forms::RadioButton^ rb_length;
	private: System::Windows::Forms::TextBox^ txt_start;

	private: System::Windows::Forms::TextBox^ txt_end;

	private: System::Windows::Forms::TextBox^ txt_length;

	private: System::Windows::Forms::GroupBox^ grp_type;
	private: System::Windows::Forms::RadioButton^ rb_oct;

	private: System::Windows::Forms::RadioButton^ rb_dec;
	private: System::Windows::Forms::RadioButton^ rb_hex;
	private: System::Windows::Forms::Button^ btn_cancel;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winblocksel::typeid));
			this->lbl_start = (gcnew System::Windows::Forms::Label());
			this->rb_end = (gcnew System::Windows::Forms::RadioButton());
			this->rb_length = (gcnew System::Windows::Forms::RadioButton());
			this->txt_start = (gcnew System::Windows::Forms::TextBox());
			this->txt_end = (gcnew System::Windows::Forms::TextBox());
			this->txt_length = (gcnew System::Windows::Forms::TextBox());
			this->grp_type = (gcnew System::Windows::Forms::GroupBox());
			this->rb_oct = (gcnew System::Windows::Forms::RadioButton());
			this->rb_dec = (gcnew System::Windows::Forms::RadioButton());
			this->rb_hex = (gcnew System::Windows::Forms::RadioButton());
			this->btn_cancel = (gcnew System::Windows::Forms::Button());
			this->btn_ok = (gcnew System::Windows::Forms::Button());
			this->grp_type->SuspendLayout();
			this->SuspendLayout();
			// 
			// lbl_start
			// 
			this->lbl_start->AutoSize = true;
			this->lbl_start->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_start->Location = System::Drawing::Point(12, 9);
			this->lbl_start->Name = L"lbl_start";
			this->lbl_start->Size = System::Drawing::Size(63, 13);
			this->lbl_start->TabIndex = 0;
			this->lbl_start->Text = L"Start Offset:";
			// 
			// rb_end
			// 
			this->rb_end->AutoSize = true;
			this->rb_end->Checked = true;
			this->rb_end->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_end->Location = System::Drawing::Point(12, 51);
			this->rb_end->Name = L"rb_end";
			this->rb_end->Size = System::Drawing::Size(84, 18);
			this->rb_end->TabIndex = 1;
			this->rb_end->TabStop = true;
			this->rb_end->Text = L"&End Offset:";
			this->rb_end->UseVisualStyleBackColor = true;
			this->rb_end->CheckedChanged += gcnew System::EventHandler(this, &winblocksel::rb_end_CheckedChanged);
			// 
			// rb_length
			// 
			this->rb_length->AutoSize = true;
			this->rb_length->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_length->Location = System::Drawing::Point(15, 101);
			this->rb_length->Name = L"rb_length";
			this->rb_length->Size = System::Drawing::Size(67, 18);
			this->rb_length->TabIndex = 2;
			this->rb_length->Text = L"&Length:";
			this->rb_length->UseVisualStyleBackColor = true;
			this->rb_length->CheckedChanged += gcnew System::EventHandler(this, &winblocksel::rb_length_CheckedChanged);
			// 
			// txt_start
			// 
			this->txt_start->Location = System::Drawing::Point(12, 25);
			this->txt_start->Name = L"txt_start";
			this->txt_start->Size = System::Drawing::Size(260, 20);
			this->txt_start->TabIndex = 3;
			// 
			// txt_end
			// 
			this->txt_end->Location = System::Drawing::Point(15, 75);
			this->txt_end->Name = L"txt_end";
			this->txt_end->Size = System::Drawing::Size(260, 20);
			this->txt_end->TabIndex = 4;
			// 
			// txt_length
			// 
			this->txt_length->Enabled = false;
			this->txt_length->Location = System::Drawing::Point(12, 125);
			this->txt_length->Name = L"txt_length";
			this->txt_length->Size = System::Drawing::Size(260, 20);
			this->txt_length->TabIndex = 5;
			// 
			// grp_type
			// 
			this->grp_type->Controls->Add(this->rb_oct);
			this->grp_type->Controls->Add(this->rb_dec);
			this->grp_type->Controls->Add(this->rb_hex);
			this->grp_type->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_type->Location = System::Drawing::Point(12, 151);
			this->grp_type->Name = L"grp_type";
			this->grp_type->Size = System::Drawing::Size(260, 37);
			this->grp_type->TabIndex = 6;
			this->grp_type->TabStop = false;
			// 
			// rb_oct
			// 
			this->rb_oct->AutoSize = true;
			this->rb_oct->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_oct->Location = System::Drawing::Point(208, 12);
			this->rb_oct->Name = L"rb_oct";
			this->rb_oct->Size = System::Drawing::Size(46, 18);
			this->rb_oct->TabIndex = 2;
			this->rb_oct->Text = L"&oct";
			this->rb_oct->UseVisualStyleBackColor = true;
			this->rb_oct->CheckedChanged += gcnew System::EventHandler(this, &winblocksel::rb_oct_CheckedChanged);
			// 
			// rb_dec
			// 
			this->rb_dec->AutoSize = true;
			this->rb_dec->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_dec->Location = System::Drawing::Point(109, 12);
			this->rb_dec->Name = L"rb_dec";
			this->rb_dec->Size = System::Drawing::Size(49, 18);
			this->rb_dec->TabIndex = 1;
			this->rb_dec->Text = L"dec";
			this->rb_dec->UseVisualStyleBackColor = true;
			this->rb_dec->CheckedChanged += gcnew System::EventHandler(this, &winblocksel::rb_dec_CheckedChanged);
			// 
			// rb_hex
			// 
			this->rb_hex->AutoSize = true;
			this->rb_hex->Checked = true;
			this->rb_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_hex->Location = System::Drawing::Point(6, 12);
			this->rb_hex->Name = L"rb_hex";
			this->rb_hex->Size = System::Drawing::Size(48, 18);
			this->rb_hex->TabIndex = 0;
			this->rb_hex->TabStop = true;
			this->rb_hex->Text = L"&hex";
			this->rb_hex->UseVisualStyleBackColor = true;
			this->rb_hex->CheckedChanged += gcnew System::EventHandler(this, &winblocksel::rb_hex_CheckedChanged);
			// 
			// btn_cancel
			// 
			this->btn_cancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel->Location = System::Drawing::Point(12, 194);
			this->btn_cancel->Name = L"btn_cancel";
			this->btn_cancel->Size = System::Drawing::Size(75, 23);
			this->btn_cancel->TabIndex = 7;
			this->btn_cancel->Text = L"&Cancel";
			this->btn_cancel->UseVisualStyleBackColor = true;
			this->btn_cancel->Click += gcnew System::EventHandler(this, &winblocksel::btn_cancel_Click);
			// 
			// btn_ok
			// 
			this->btn_ok->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_ok->Location = System::Drawing::Point(197, 194);
			this->btn_ok->Name = L"btn_ok";
			this->btn_ok->Size = System::Drawing::Size(75, 23);
			this->btn_ok->TabIndex = 8;
			this->btn_ok->Text = L"&Select";
			this->btn_ok->UseVisualStyleBackColor = true;
			this->btn_ok->Click += gcnew System::EventHandler(this, &winblocksel::btn_ok_Click);
			// 
			// winblocksel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 222);
			this->Controls->Add(this->btn_ok);
			this->Controls->Add(this->btn_cancel);
			this->Controls->Add(this->grp_type);
			this->Controls->Add(this->txt_length);
			this->Controls->Add(this->txt_end);
			this->Controls->Add(this->txt_start);
			this->Controls->Add(this->rb_length);
			this->Controls->Add(this->rb_end);
			this->Controls->Add(this->lbl_start);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winblocksel";
			this->Text = L"Select Block...";
			this->Load += gcnew System::EventHandler(this, &winblocksel::winblocksel_Load);
			this->grp_type->ResumeLayout(false);
			this->grp_type->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void btn_cancel_Click(System::Object^ sender, System::EventArgs^ e) {
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}

	private: System::Void rb_end_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		txt_end->Enabled = true;
		txt_length->Enabled = false;
	}

	private: System::Void rb_length_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		txt_length->Enabled = true;
		txt_end->Enabled = false;
	}

	private: System::Void btn_ok_Click(System::Object^ sender, System::EventArgs^ e) {
		
		UInt64 address = 0;
		UInt64 address_end;
		UInt64 size;

		short base;

		base = rb_hex->Checked ? 16 : (rb_dec->Checked ? 10 : 8);
		try {

			address = Convert::ToUInt64(txt_start->Text, base);

			if (rb_end->Checked) {
				address_end = Convert::ToUInt64(txt_end->Text, base);
			}
			else {
				size = Convert::ToUInt64(txt_length->Text, base);
				address_end = address + size;
			}
		}
		catch (FormatException^) { MessageBox::Show("Invalid base " + base.ToString() + " format entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error); return; }

		if (end_address_ >= original_size_) {
			MessageBox::Show("Invalid block region entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		start_address_ = address;
		end_address_ = address_end;

		this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void winblocksel_Load(System::Object^ sender, System::EventArgs^ e) {

		this->Location = Point( (Screen::PrimaryScreen->Bounds.Width / 2) - (this->Width / 2), (Screen::PrimaryScreen->Bounds.Height / 2) - (this->Height / 2) );

		txt_start->Text = original_offset_.ToString("X16");
		txt_end->Text = txt_start->Text;
		txt_length->Text = "01";

		filter_start = gcnew TextBoxBaseExtension<UInt64>(txt_start, 16);
		filter_end = gcnew TextBoxBaseExtension<UInt64>(txt_end, 16);
		filter_length = gcnew TextBoxBaseExtension<UInt64>(txt_length, 16);
	}

	private: System::Void rb_dec_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		filter_start->swap_base(10);
		filter_end->swap_base(10);
		filter_length->swap_base(10);
	}

	private: System::Void rb_hex_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		filter_start->swap_base(16);
		filter_end->swap_base(16);
		filter_length->swap_base(16);

	}

	private: System::Void rb_oct_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		filter_start->swap_base(8);
		filter_end->swap_base(8);
		filter_length->swap_base(8);
	}

};
}

#endif
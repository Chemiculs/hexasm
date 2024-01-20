#ifndef WINFIND_H
#define WINFIND_H

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;

#include "TextBoxBaseExtension.hpp"
#include "util.hpp"

namespace hexasm {

	enum find_type {
		string,
		hex,
		pattern,
		integer,
		float_
	};

	enum find_direction_type {
		forward,
		backward,
		all
	};

	public ref class winfind : public System::Windows::Forms::Form
	{
	public:

		array<Byte>^ search_data_;
		array<Byte>^ search_data_upper_;

		Encoding^ encoding_;
		bool is_ignore_case_;

		array<short>^ aob_search_data_;

		find_type find_option;
		find_direction_type find_direction;

		private: System::Windows::Forms::ImageList^ find_tab_img_list;
		private: System::Windows::Forms::TabPage^ tb_page_integer;
		private: System::Windows::Forms::TabPage^ tb_page_float;
		private: System::Windows::Forms::CheckBox^ cb_hex_i;
		private: System::Windows::Forms::Label^ label5;
		private: System::Windows::Forms::NumericUpDown^ nud_integer;

		private: System::Windows::Forms::Label^ label6;
		private: System::Windows::Forms::NumericUpDown^ nud_float;

		private: System::Windows::Forms::GroupBox^ grp_i_opt;
		private: System::Windows::Forms::Label^ lbl_endianness_i;

		private: System::Windows::Forms::ComboBox^ cb_endianness_i;
		private: System::Windows::Forms::ComboBox^ cb_bit_width_i;
		private: System::Windows::Forms::Label^ lbl_bit_width;
		private: System::Windows::Forms::GroupBox^ grp_direction_i;

		private: System::Windows::Forms::RadioButton^ rb_backward_i;
		private: System::Windows::Forms::RadioButton^ rb_forward_i;
		private: System::Windows::Forms::RadioButton^ rb_all_i;
		private: System::Windows::Forms::Button^ btn_cancel_i;
		private: System::Windows::Forms::Button^ btn_search_i;
		private: System::Windows::Forms::Button^ btn_cancel_f;

		private: System::Windows::Forms::Button^ btn_search_f;

		private: System::Windows::Forms::GroupBox^ grp_direction_f;
		private: System::Windows::Forms::RadioButton^ rb_backward_f;

		private: System::Windows::Forms::RadioButton^ rb_forward_f;

		private: System::Windows::Forms::RadioButton^ rb_all_f;

		private: System::Windows::Forms::GroupBox^ grp_option_f;
		private: System::Windows::Forms::Label^ lbl_endianess_f;

		private: System::Windows::Forms::ComboBox^ cb_endianess_f;

		private: System::Windows::Forms::ComboBox^ cb_bit_width_f;
		private: System::Windows::Forms::Label^ lbl_bit_width_f;

	public:

		TextBoxBaseExtension<UInt64>^ txt_hex_ext_;

		winfind(Encoding^ encoding) : encoding_(encoding)
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
		~winfind()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ tab_find;
	protected:

	private: System::Windows::Forms::TabPage^ tb_page_string;
	private: System::Windows::Forms::TabPage^ tb_page_hex;

	private: System::Windows::Forms::GroupBox^ grp_encoding;
	public: System::Windows::Forms::ComboBox^ cb_encoding;
	private:

	private:
	public: System::Windows::Forms::CheckBox^ cb_case;


	private: System::Windows::Forms::GroupBox^ grp_direction;
	public: System::Windows::Forms::TextBox^ txt_string;

	private: System::Windows::Forms::Label^ lbl_s_string;
	private: System::Windows::Forms::Label^ label1;
	public: System::Windows::Forms::RadioButton^ rb_backward;
	private:
	public: System::Windows::Forms::RadioButton^ rb_forward;
	public: System::Windows::Forms::RadioButton^ rb_all;

	private: System::Windows::Forms::Button^ btn_search;

	private: System::Windows::Forms::Button^ btn_cancel;
	private: System::Windows::Forms::Button^ btn_search_h;

	private: System::Windows::Forms::Button^ btn_cancel_h;
	private: System::Windows::Forms::TabPage^ tb_page_signature;




	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txt_hex_str;
	private: System::Windows::Forms::GroupBox^ grp_direction_hex;
	private: System::Windows::Forms::RadioButton^ rb_backward_hex;
	private: System::Windows::Forms::RadioButton^ rb_forward_hex;
	private: System::Windows::Forms::RadioButton^ rb_all_hex;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ rb_backward_s;
	private: System::Windows::Forms::RadioButton^ rb_forward_s;
	private: System::Windows::Forms::RadioButton^ rb_all_s;



	private: System::Windows::Forms::Button^ btn_search_s;


	private: System::Windows::Forms::Button^ btn_cancel_s;
	private: System::Windows::Forms::TextBox^ txt_aob;
	private: System::ComponentModel::IContainer^ components;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winfind::typeid));
			this->tab_find = (gcnew System::Windows::Forms::TabControl());
			this->tb_page_string = (gcnew System::Windows::Forms::TabPage());
			this->btn_search = (gcnew System::Windows::Forms::Button());
			this->btn_cancel = (gcnew System::Windows::Forms::Button());
			this->grp_direction = (gcnew System::Windows::Forms::GroupBox());
			this->rb_backward = (gcnew System::Windows::Forms::RadioButton());
			this->rb_forward = (gcnew System::Windows::Forms::RadioButton());
			this->rb_all = (gcnew System::Windows::Forms::RadioButton());
			this->txt_string = (gcnew System::Windows::Forms::TextBox());
			this->lbl_s_string = (gcnew System::Windows::Forms::Label());
			this->grp_encoding = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cb_encoding = (gcnew System::Windows::Forms::ComboBox());
			this->cb_case = (gcnew System::Windows::Forms::CheckBox());
			this->tb_page_hex = (gcnew System::Windows::Forms::TabPage());
			this->grp_direction_hex = (gcnew System::Windows::Forms::GroupBox());
			this->rb_backward_hex = (gcnew System::Windows::Forms::RadioButton());
			this->rb_forward_hex = (gcnew System::Windows::Forms::RadioButton());
			this->rb_all_hex = (gcnew System::Windows::Forms::RadioButton());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txt_hex_str = (gcnew System::Windows::Forms::TextBox());
			this->btn_search_h = (gcnew System::Windows::Forms::Button());
			this->btn_cancel_h = (gcnew System::Windows::Forms::Button());
			this->tb_page_signature = (gcnew System::Windows::Forms::TabPage());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rb_backward_s = (gcnew System::Windows::Forms::RadioButton());
			this->rb_forward_s = (gcnew System::Windows::Forms::RadioButton());
			this->rb_all_s = (gcnew System::Windows::Forms::RadioButton());
			this->btn_search_s = (gcnew System::Windows::Forms::Button());
			this->btn_cancel_s = (gcnew System::Windows::Forms::Button());
			this->txt_aob = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tb_page_integer = (gcnew System::Windows::Forms::TabPage());
			this->btn_cancel_i = (gcnew System::Windows::Forms::Button());
			this->btn_search_i = (gcnew System::Windows::Forms::Button());
			this->grp_direction_i = (gcnew System::Windows::Forms::GroupBox());
			this->rb_backward_i = (gcnew System::Windows::Forms::RadioButton());
			this->rb_forward_i = (gcnew System::Windows::Forms::RadioButton());
			this->rb_all_i = (gcnew System::Windows::Forms::RadioButton());
			this->grp_i_opt = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_endianness_i = (gcnew System::Windows::Forms::Label());
			this->cb_endianness_i = (gcnew System::Windows::Forms::ComboBox());
			this->cb_bit_width_i = (gcnew System::Windows::Forms::ComboBox());
			this->lbl_bit_width = (gcnew System::Windows::Forms::Label());
			this->cb_hex_i = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->nud_integer = (gcnew System::Windows::Forms::NumericUpDown());
			this->tb_page_float = (gcnew System::Windows::Forms::TabPage());
			this->btn_cancel_f = (gcnew System::Windows::Forms::Button());
			this->btn_search_f = (gcnew System::Windows::Forms::Button());
			this->grp_direction_f = (gcnew System::Windows::Forms::GroupBox());
			this->rb_backward_f = (gcnew System::Windows::Forms::RadioButton());
			this->rb_forward_f = (gcnew System::Windows::Forms::RadioButton());
			this->rb_all_f = (gcnew System::Windows::Forms::RadioButton());
			this->grp_option_f = (gcnew System::Windows::Forms::GroupBox());
			this->lbl_endianess_f = (gcnew System::Windows::Forms::Label());
			this->cb_endianess_f = (gcnew System::Windows::Forms::ComboBox());
			this->cb_bit_width_f = (gcnew System::Windows::Forms::ComboBox());
			this->lbl_bit_width_f = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->nud_float = (gcnew System::Windows::Forms::NumericUpDown());
			this->find_tab_img_list = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tab_find->SuspendLayout();
			this->tb_page_string->SuspendLayout();
			this->grp_direction->SuspendLayout();
			this->grp_encoding->SuspendLayout();
			this->tb_page_hex->SuspendLayout();
			this->grp_direction_hex->SuspendLayout();
			this->tb_page_signature->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tb_page_integer->SuspendLayout();
			this->grp_direction_i->SuspendLayout();
			this->grp_i_opt->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_integer))->BeginInit();
			this->tb_page_float->SuspendLayout();
			this->grp_direction_f->SuspendLayout();
			this->grp_option_f->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_float))->BeginInit();
			this->SuspendLayout();
			// 
			// tab_find
			// 
			this->tab_find->Controls->Add(this->tb_page_string);
			this->tab_find->Controls->Add(this->tb_page_hex);
			this->tab_find->Controls->Add(this->tb_page_signature);
			this->tab_find->Controls->Add(this->tb_page_integer);
			this->tab_find->Controls->Add(this->tb_page_float);
			this->tab_find->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tab_find->ImageList = this->find_tab_img_list;
			this->tab_find->Location = System::Drawing::Point(0, 0);
			this->tab_find->Name = L"tab_find";
			this->tab_find->SelectedIndex = 0;
			this->tab_find->Size = System::Drawing::Size(410, 296);
			this->tab_find->TabIndex = 0;
			// 
			// tb_page_string
			// 
			this->tb_page_string->Controls->Add(this->btn_search);
			this->tb_page_string->Controls->Add(this->btn_cancel);
			this->tb_page_string->Controls->Add(this->grp_direction);
			this->tb_page_string->Controls->Add(this->txt_string);
			this->tb_page_string->Controls->Add(this->lbl_s_string);
			this->tb_page_string->Controls->Add(this->grp_encoding);
			this->tb_page_string->Location = System::Drawing::Point(4, 23);
			this->tb_page_string->Name = L"tb_page_string";
			this->tb_page_string->Padding = System::Windows::Forms::Padding(3);
			this->tb_page_string->Size = System::Drawing::Size(402, 269);
			this->tb_page_string->TabIndex = 0;
			this->tb_page_string->Text = L"String";
			this->tb_page_string->UseVisualStyleBackColor = true;
			// 
			// btn_search
			// 
			this->btn_search->Enabled = false;
			this->btn_search->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_search->Location = System::Drawing::Point(321, 239);
			this->btn_search->Name = L"btn_search";
			this->btn_search->Size = System::Drawing::Size(75, 23);
			this->btn_search->TabIndex = 5;
			this->btn_search->Text = L"&Search";
			this->btn_search->UseVisualStyleBackColor = true;
			this->btn_search->Click += gcnew System::EventHandler(this, &winfind::btn_search_Click);
			// 
			// btn_cancel
			// 
			this->btn_cancel->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel->Location = System::Drawing::Point(8, 239);
			this->btn_cancel->Name = L"btn_cancel";
			this->btn_cancel->Size = System::Drawing::Size(75, 23);
			this->btn_cancel->TabIndex = 4;
			this->btn_cancel->Text = L"&Cancel";
			this->btn_cancel->UseVisualStyleBackColor = true;
			this->btn_cancel->Click += gcnew System::EventHandler(this, &winfind::btn_cancel_Click);
			// 
			// grp_direction
			// 
			this->grp_direction->Controls->Add(this->rb_backward);
			this->grp_direction->Controls->Add(this->rb_forward);
			this->grp_direction->Controls->Add(this->rb_all);
			this->grp_direction->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_direction->Location = System::Drawing::Point(241, 92);
			this->grp_direction->Name = L"grp_direction";
			this->grp_direction->Size = System::Drawing::Size(155, 100);
			this->grp_direction->TabIndex = 3;
			this->grp_direction->TabStop = false;
			this->grp_direction->Text = L"Search direction";
			// 
			// rb_backward
			// 
			this->rb_backward->AutoSize = true;
			this->rb_backward->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_backward->Location = System::Drawing::Point(11, 77);
			this->rb_backward->Name = L"rb_backward";
			this->rb_backward->Size = System::Drawing::Size(79, 18);
			this->rb_backward->TabIndex = 2;
			this->rb_backward->Text = L"&Backward";
			this->rb_backward->UseVisualStyleBackColor = true;
			// 
			// rb_forward
			// 
			this->rb_forward->AutoSize = true;
			this->rb_forward->Checked = true;
			this->rb_forward->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_forward->Location = System::Drawing::Point(11, 47);
			this->rb_forward->Name = L"rb_forward";
			this->rb_forward->Size = System::Drawing::Size(69, 18);
			this->rb_forward->TabIndex = 1;
			this->rb_forward->TabStop = true;
			this->rb_forward->Text = L"&Forward";
			this->rb_forward->UseVisualStyleBackColor = true;
			// 
			// rb_all
			// 
			this->rb_all->AutoSize = true;
			this->rb_all->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_all->Location = System::Drawing::Point(11, 19);
			this->rb_all->Name = L"rb_all";
			this->rb_all->Size = System::Drawing::Size(42, 18);
			this->rb_all->TabIndex = 0;
			this->rb_all->Text = L"&All";
			this->rb_all->UseVisualStyleBackColor = true;
			// 
			// txt_string
			// 
			this->txt_string->Location = System::Drawing::Point(79, 18);
			this->txt_string->Name = L"txt_string";
			this->txt_string->Size = System::Drawing::Size(315, 20);
			this->txt_string->TabIndex = 2;
			this->txt_string->TextChanged += gcnew System::EventHandler(this, &winfind::txt_string_TextChanged);
			// 
			// lbl_s_string
			// 
			this->lbl_s_string->AutoSize = true;
			this->lbl_s_string->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_s_string->Location = System::Drawing::Point(5, 21);
			this->lbl_s_string->Name = L"lbl_s_string";
			this->lbl_s_string->Size = System::Drawing::Size(62, 13);
			this->lbl_s_string->TabIndex = 1;
			this->lbl_s_string->Text = L"Search for: ";
			// 
			// grp_encoding
			// 
			this->grp_encoding->Controls->Add(this->label1);
			this->grp_encoding->Controls->Add(this->cb_encoding);
			this->grp_encoding->Controls->Add(this->cb_case);
			this->grp_encoding->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_encoding->Location = System::Drawing::Point(10, 92);
			this->grp_encoding->Name = L"grp_encoding";
			this->grp_encoding->Size = System::Drawing::Size(225, 100);
			this->grp_encoding->TabIndex = 0;
			this->grp_encoding->TabStop = false;
			this->grp_encoding->Text = L"Options";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label1->Location = System::Drawing::Point(6, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Encoding:";
			// 
			// cb_encoding
			// 
			this->cb_encoding->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cb_encoding->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_encoding->FormattingEnabled = true;
			this->cb_encoding->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"{ Editor Encoding }", L"Unicode (UTF-16 little endian)" });
			this->cb_encoding->Location = System::Drawing::Point(6, 46);
			this->cb_encoding->Name = L"cb_encoding";
			this->cb_encoding->Size = System::Drawing::Size(213, 21);
			this->cb_encoding->TabIndex = 1;
			// 
			// cb_case
			// 
			this->cb_case->AutoSize = true;
			this->cb_case->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_case->Location = System::Drawing::Point(6, 77);
			this->cb_case->Name = L"cb_case";
			this->cb_case->Size = System::Drawing::Size(104, 18);
			this->cb_case->TabIndex = 0;
			this->cb_case->Text = L"&Case sensetive";
			this->cb_case->UseVisualStyleBackColor = true;
			// 
			// tb_page_hex
			// 
			this->tb_page_hex->Controls->Add(this->grp_direction_hex);
			this->tb_page_hex->Controls->Add(this->label2);
			this->tb_page_hex->Controls->Add(this->txt_hex_str);
			this->tb_page_hex->Controls->Add(this->btn_search_h);
			this->tb_page_hex->Controls->Add(this->btn_cancel_h);
			this->tb_page_hex->Location = System::Drawing::Point(4, 23);
			this->tb_page_hex->Name = L"tb_page_hex";
			this->tb_page_hex->Padding = System::Windows::Forms::Padding(3);
			this->tb_page_hex->Size = System::Drawing::Size(402, 269);
			this->tb_page_hex->TabIndex = 1;
			this->tb_page_hex->Text = L"Hex";
			this->tb_page_hex->UseVisualStyleBackColor = true;
			// 
			// grp_direction_hex
			// 
			this->grp_direction_hex->Controls->Add(this->rb_backward_hex);
			this->grp_direction_hex->Controls->Add(this->rb_forward_hex);
			this->grp_direction_hex->Controls->Add(this->rb_all_hex);
			this->grp_direction_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_direction_hex->Location = System::Drawing::Point(241, 92);
			this->grp_direction_hex->Name = L"grp_direction_hex";
			this->grp_direction_hex->Size = System::Drawing::Size(155, 100);
			this->grp_direction_hex->TabIndex = 5;
			this->grp_direction_hex->TabStop = false;
			this->grp_direction_hex->Text = L"Search direction";
			// 
			// rb_backward_hex
			// 
			this->rb_backward_hex->AutoSize = true;
			this->rb_backward_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_backward_hex->Location = System::Drawing::Point(11, 77);
			this->rb_backward_hex->Name = L"rb_backward_hex";
			this->rb_backward_hex->Size = System::Drawing::Size(79, 18);
			this->rb_backward_hex->TabIndex = 2;
			this->rb_backward_hex->Text = L"&Backward";
			this->rb_backward_hex->UseVisualStyleBackColor = true;
			// 
			// rb_forward_hex
			// 
			this->rb_forward_hex->AutoSize = true;
			this->rb_forward_hex->Checked = true;
			this->rb_forward_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_forward_hex->Location = System::Drawing::Point(11, 47);
			this->rb_forward_hex->Name = L"rb_forward_hex";
			this->rb_forward_hex->Size = System::Drawing::Size(69, 18);
			this->rb_forward_hex->TabIndex = 1;
			this->rb_forward_hex->TabStop = true;
			this->rb_forward_hex->Text = L"&Forward";
			this->rb_forward_hex->UseVisualStyleBackColor = true;
			// 
			// rb_all_hex
			// 
			this->rb_all_hex->AutoSize = true;
			this->rb_all_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_all_hex->Location = System::Drawing::Point(11, 19);
			this->rb_all_hex->Name = L"rb_all_hex";
			this->rb_all_hex->Size = System::Drawing::Size(42, 18);
			this->rb_all_hex->TabIndex = 0;
			this->rb_all_hex->Text = L"&All";
			this->rb_all_hex->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label2->Location = System::Drawing::Point(5, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Search for: ";
			// 
			// txt_hex_str
			// 
			this->txt_hex_str->Location = System::Drawing::Point(79, 18);
			this->txt_hex_str->Name = L"txt_hex_str";
			this->txt_hex_str->Size = System::Drawing::Size(315, 20);
			this->txt_hex_str->TabIndex = 3;
			// 
			// btn_search_h
			// 
			this->btn_search_h->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_search_h->Location = System::Drawing::Point(321, 239);
			this->btn_search_h->Name = L"btn_search_h";
			this->btn_search_h->Size = System::Drawing::Size(75, 23);
			this->btn_search_h->TabIndex = 2;
			this->btn_search_h->Text = L"&Search";
			this->btn_search_h->UseVisualStyleBackColor = true;
			this->btn_search_h->Click += gcnew System::EventHandler(this, &winfind::btn_search_h_Click);
			// 
			// btn_cancel_h
			// 
			this->btn_cancel_h->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel_h->Location = System::Drawing::Point(8, 239);
			this->btn_cancel_h->Name = L"btn_cancel_h";
			this->btn_cancel_h->Size = System::Drawing::Size(75, 23);
			this->btn_cancel_h->TabIndex = 1;
			this->btn_cancel_h->Text = L"&Cancel";
			this->btn_cancel_h->UseVisualStyleBackColor = true;
			this->btn_cancel_h->Click += gcnew System::EventHandler(this, &winfind::btn_cancel_Click);
			// 
			// tb_page_signature
			// 
			this->tb_page_signature->Controls->Add(this->label4);
			this->tb_page_signature->Controls->Add(this->groupBox1);
			this->tb_page_signature->Controls->Add(this->btn_search_s);
			this->tb_page_signature->Controls->Add(this->btn_cancel_s);
			this->tb_page_signature->Controls->Add(this->txt_aob);
			this->tb_page_signature->Controls->Add(this->label3);
			this->tb_page_signature->Location = System::Drawing::Point(4, 23);
			this->tb_page_signature->Name = L"tb_page_signature";
			this->tb_page_signature->Padding = System::Windows::Forms::Padding(3);
			this->tb_page_signature->Size = System::Drawing::Size(402, 269);
			this->tb_page_signature->TabIndex = 2;
			this->tb_page_signature->Text = L"Signature";
			this->tb_page_signature->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label4->Location = System::Drawing::Point(81, 45);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(151, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Note: use \?\? for skipped bytes";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rb_backward_s);
			this->groupBox1->Controls->Add(this->rb_forward_s);
			this->groupBox1->Controls->Add(this->rb_all_s);
			this->groupBox1->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->groupBox1->Location = System::Drawing::Point(241, 92);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(155, 100);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Search direction";
			// 
			// rb_backward_s
			// 
			this->rb_backward_s->AutoSize = true;
			this->rb_backward_s->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_backward_s->Location = System::Drawing::Point(11, 77);
			this->rb_backward_s->Name = L"rb_backward_s";
			this->rb_backward_s->Size = System::Drawing::Size(79, 18);
			this->rb_backward_s->TabIndex = 2;
			this->rb_backward_s->Text = L"&Backward";
			this->rb_backward_s->UseVisualStyleBackColor = true;
			// 
			// rb_forward_s
			// 
			this->rb_forward_s->AutoSize = true;
			this->rb_forward_s->Checked = true;
			this->rb_forward_s->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_forward_s->Location = System::Drawing::Point(13, 47);
			this->rb_forward_s->Name = L"rb_forward_s";
			this->rb_forward_s->Size = System::Drawing::Size(69, 18);
			this->rb_forward_s->TabIndex = 1;
			this->rb_forward_s->TabStop = true;
			this->rb_forward_s->Text = L"&Forward";
			this->rb_forward_s->UseVisualStyleBackColor = true;
			// 
			// rb_all_s
			// 
			this->rb_all_s->AutoSize = true;
			this->rb_all_s->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_all_s->Location = System::Drawing::Point(11, 19);
			this->rb_all_s->Name = L"rb_all_s";
			this->rb_all_s->Size = System::Drawing::Size(42, 18);
			this->rb_all_s->TabIndex = 0;
			this->rb_all_s->Text = L"&All";
			this->rb_all_s->UseVisualStyleBackColor = true;
			// 
			// btn_search_s
			// 
			this->btn_search_s->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_search_s->Location = System::Drawing::Point(321, 240);
			this->btn_search_s->Name = L"btn_search_s";
			this->btn_search_s->Size = System::Drawing::Size(75, 23);
			this->btn_search_s->TabIndex = 3;
			this->btn_search_s->Text = L"&Search";
			this->btn_search_s->UseVisualStyleBackColor = true;
			this->btn_search_s->Click += gcnew System::EventHandler(this, &winfind::btn_search_s_Click);
			// 
			// btn_cancel_s
			// 
			this->btn_cancel_s->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel_s->Location = System::Drawing::Point(8, 240);
			this->btn_cancel_s->Name = L"btn_cancel_s";
			this->btn_cancel_s->Size = System::Drawing::Size(75, 23);
			this->btn_cancel_s->TabIndex = 2;
			this->btn_cancel_s->Text = L"&Cancel";
			this->btn_cancel_s->UseVisualStyleBackColor = true;
			this->btn_cancel_s->Click += gcnew System::EventHandler(this, &winfind::btn_cancel_Click);
			// 
			// txt_aob
			// 
			this->txt_aob->Location = System::Drawing::Point(79, 18);
			this->txt_aob->Name = L"txt_aob";
			this->txt_aob->Size = System::Drawing::Size(315, 20);
			this->txt_aob->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label3->Location = System::Drawing::Point(5, 21);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Search for: ";
			// 
			// tb_page_integer
			// 
			this->tb_page_integer->Controls->Add(this->btn_cancel_i);
			this->tb_page_integer->Controls->Add(this->btn_search_i);
			this->tb_page_integer->Controls->Add(this->grp_direction_i);
			this->tb_page_integer->Controls->Add(this->grp_i_opt);
			this->tb_page_integer->Controls->Add(this->cb_hex_i);
			this->tb_page_integer->Controls->Add(this->label5);
			this->tb_page_integer->Controls->Add(this->nud_integer);
			this->tb_page_integer->Location = System::Drawing::Point(4, 23);
			this->tb_page_integer->Name = L"tb_page_integer";
			this->tb_page_integer->Padding = System::Windows::Forms::Padding(3);
			this->tb_page_integer->Size = System::Drawing::Size(402, 269);
			this->tb_page_integer->TabIndex = 3;
			this->tb_page_integer->Text = L"Integer";
			this->tb_page_integer->UseVisualStyleBackColor = true;
			// 
			// btn_cancel_i
			// 
			this->btn_cancel_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel_i->Location = System::Drawing::Point(8, 240);
			this->btn_cancel_i->Name = L"btn_cancel_i";
			this->btn_cancel_i->Size = System::Drawing::Size(75, 23);
			this->btn_cancel_i->TabIndex = 3;
			this->btn_cancel_i->Text = L"&Cancel";
			this->btn_cancel_i->UseVisualStyleBackColor = true;
			this->btn_cancel_i->Click += gcnew System::EventHandler(this, &winfind::btn_cancel_Click);
			// 
			// btn_search_i
			// 
			this->btn_search_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_search_i->Location = System::Drawing::Point(321, 240);
			this->btn_search_i->Name = L"btn_search_i";
			this->btn_search_i->Size = System::Drawing::Size(75, 23);
			this->btn_search_i->TabIndex = 4;
			this->btn_search_i->Text = L"&Search";
			this->btn_search_i->UseVisualStyleBackColor = true;
			this->btn_search_i->Click += gcnew System::EventHandler(this, &winfind::btn_search_i_Click);
			// 
			// grp_direction_i
			// 
			this->grp_direction_i->Controls->Add(this->rb_backward_i);
			this->grp_direction_i->Controls->Add(this->rb_forward_i);
			this->grp_direction_i->Controls->Add(this->rb_all_i);
			this->grp_direction_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_direction_i->Location = System::Drawing::Point(241, 92);
			this->grp_direction_i->Name = L"grp_direction_i";
			this->grp_direction_i->Size = System::Drawing::Size(155, 100);
			this->grp_direction_i->TabIndex = 7;
			this->grp_direction_i->TabStop = false;
			this->grp_direction_i->Text = L"Search direction";
			// 
			// rb_backward_i
			// 
			this->rb_backward_i->AutoSize = true;
			this->rb_backward_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_backward_i->Location = System::Drawing::Point(11, 77);
			this->rb_backward_i->Name = L"rb_backward_i";
			this->rb_backward_i->Size = System::Drawing::Size(79, 18);
			this->rb_backward_i->TabIndex = 2;
			this->rb_backward_i->Text = L"&Backward";
			this->rb_backward_i->UseVisualStyleBackColor = true;
			// 
			// rb_forward_i
			// 
			this->rb_forward_i->AutoSize = true;
			this->rb_forward_i->Checked = true;
			this->rb_forward_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_forward_i->Location = System::Drawing::Point(11, 47);
			this->rb_forward_i->Name = L"rb_forward_i";
			this->rb_forward_i->Size = System::Drawing::Size(69, 18);
			this->rb_forward_i->TabIndex = 1;
			this->rb_forward_i->TabStop = true;
			this->rb_forward_i->Text = L"&Forward";
			this->rb_forward_i->UseVisualStyleBackColor = true;
			// 
			// rb_all_i
			// 
			this->rb_all_i->AutoSize = true;
			this->rb_all_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_all_i->Location = System::Drawing::Point(11, 19);
			this->rb_all_i->Name = L"rb_all_i";
			this->rb_all_i->Size = System::Drawing::Size(42, 18);
			this->rb_all_i->TabIndex = 0;
			this->rb_all_i->Text = L"&All";
			this->rb_all_i->UseVisualStyleBackColor = true;
			// 
			// grp_i_opt
			// 
			this->grp_i_opt->Controls->Add(this->lbl_endianness_i);
			this->grp_i_opt->Controls->Add(this->cb_endianness_i);
			this->grp_i_opt->Controls->Add(this->cb_bit_width_i);
			this->grp_i_opt->Controls->Add(this->lbl_bit_width);
			this->grp_i_opt->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_i_opt->Location = System::Drawing::Point(8, 92);
			this->grp_i_opt->Name = L"grp_i_opt";
			this->grp_i_opt->Size = System::Drawing::Size(225, 107);
			this->grp_i_opt->TabIndex = 3;
			this->grp_i_opt->TabStop = false;
			this->grp_i_opt->Text = L"Options";
			// 
			// lbl_endianness_i
			// 
			this->lbl_endianness_i->AutoSize = true;
			this->lbl_endianness_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_endianness_i->Location = System::Drawing::Point(6, 64);
			this->lbl_endianness_i->Name = L"lbl_endianness_i";
			this->lbl_endianness_i->Size = System::Drawing::Size(59, 13);
			this->lbl_endianness_i->TabIndex = 3;
			this->lbl_endianness_i->Text = L"Endianess:";
			// 
			// cb_endianness_i
			// 
			this->cb_endianness_i->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cb_endianness_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_endianness_i->FormattingEnabled = true;
			this->cb_endianness_i->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Little endian", L"Big endian" });
			this->cb_endianness_i->Location = System::Drawing::Point(6, 80);
			this->cb_endianness_i->Name = L"cb_endianness_i";
			this->cb_endianness_i->Size = System::Drawing::Size(213, 21);
			this->cb_endianness_i->TabIndex = 2;
			// 
			// cb_bit_width_i
			// 
			this->cb_bit_width_i->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cb_bit_width_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_bit_width_i->FormattingEnabled = true;
			this->cb_bit_width_i->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"{ Auto }", L"Unsigned 8 bit", L"Signed 8 bit",
					L"Unsigned 16 bit", L"Signed 16 bit", L"Unsigned 32 bit", L"Signed 32 bit", L"Unsigned 64 bit", L"Signed 64 bit"
			});
			this->cb_bit_width_i->Location = System::Drawing::Point(6, 37);
			this->cb_bit_width_i->Name = L"cb_bit_width_i";
			this->cb_bit_width_i->Size = System::Drawing::Size(213, 21);
			this->cb_bit_width_i->TabIndex = 1;
			this->cb_bit_width_i->SelectedIndexChanged += gcnew System::EventHandler(this, &winfind::cb_bit_width_i_SelectedIndexChanged);
			// 
			// lbl_bit_width
			// 
			this->lbl_bit_width->AutoSize = true;
			this->lbl_bit_width->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_bit_width->Location = System::Drawing::Point(6, 21);
			this->lbl_bit_width->Name = L"lbl_bit_width";
			this->lbl_bit_width->Size = System::Drawing::Size(50, 13);
			this->lbl_bit_width->TabIndex = 0;
			this->lbl_bit_width->Text = L"Bit width:";
			// 
			// cb_hex_i
			// 
			this->cb_hex_i->AutoSize = true;
			this->cb_hex_i->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_hex_i->Location = System::Drawing::Point(79, 44);
			this->cb_hex_i->Name = L"cb_hex_i";
			this->cb_hex_i->Size = System::Drawing::Size(51, 18);
			this->cb_hex_i->TabIndex = 2;
			this->cb_hex_i->Text = L"&Hex";
			this->cb_hex_i->UseVisualStyleBackColor = true;
			this->cb_hex_i->CheckedChanged += gcnew System::EventHandler(this, &winfind::cb_hex_i_CheckedChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label5->Location = System::Drawing::Point(6, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(62, 13);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Search for: ";
			// 
			// nud_integer
			// 
			this->nud_integer->Location = System::Drawing::Point(79, 18);
			this->nud_integer->Name = L"nud_integer";
			this->nud_integer->Size = System::Drawing::Size(317, 20);
			this->nud_integer->TabIndex = 0;
			this->nud_integer->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &winfind::nud_integer_KeyDown);
			// 
			// tb_page_float
			// 
			this->tb_page_float->Controls->Add(this->btn_cancel_f);
			this->tb_page_float->Controls->Add(this->btn_search_f);
			this->tb_page_float->Controls->Add(this->grp_direction_f);
			this->tb_page_float->Controls->Add(this->grp_option_f);
			this->tb_page_float->Controls->Add(this->label6);
			this->tb_page_float->Controls->Add(this->nud_float);
			this->tb_page_float->Location = System::Drawing::Point(4, 23);
			this->tb_page_float->Name = L"tb_page_float";
			this->tb_page_float->Padding = System::Windows::Forms::Padding(3);
			this->tb_page_float->Size = System::Drawing::Size(402, 269);
			this->tb_page_float->TabIndex = 4;
			this->tb_page_float->Text = L"Floating point";
			this->tb_page_float->UseVisualStyleBackColor = true;
			// 
			// btn_cancel_f
			// 
			this->btn_cancel_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_cancel_f->Location = System::Drawing::Point(8, 240);
			this->btn_cancel_f->Name = L"btn_cancel_f";
			this->btn_cancel_f->Size = System::Drawing::Size(75, 23);
			this->btn_cancel_f->TabIndex = 8;
			this->btn_cancel_f->Text = L"&Cancel";
			this->btn_cancel_f->UseVisualStyleBackColor = true;
			this->btn_cancel_f->Click += gcnew System::EventHandler(this, &winfind::btn_cancel_Click);
			// 
			// btn_search_f
			// 
			this->btn_search_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btn_search_f->Location = System::Drawing::Point(321, 240);
			this->btn_search_f->Name = L"btn_search_f";
			this->btn_search_f->Size = System::Drawing::Size(75, 23);
			this->btn_search_f->TabIndex = 10;
			this->btn_search_f->Text = L"&Search";
			this->btn_search_f->UseVisualStyleBackColor = true;
			this->btn_search_f->Click += gcnew System::EventHandler(this, &winfind::btn_search_f_Click);
			// 
			// grp_direction_f
			// 
			this->grp_direction_f->Controls->Add(this->rb_backward_f);
			this->grp_direction_f->Controls->Add(this->rb_forward_f);
			this->grp_direction_f->Controls->Add(this->rb_all_f);
			this->grp_direction_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_direction_f->Location = System::Drawing::Point(241, 92);
			this->grp_direction_f->Name = L"grp_direction_f";
			this->grp_direction_f->Size = System::Drawing::Size(155, 100);
			this->grp_direction_f->TabIndex = 11;
			this->grp_direction_f->TabStop = false;
			this->grp_direction_f->Text = L"Search direction";
			// 
			// rb_backward_f
			// 
			this->rb_backward_f->AutoSize = true;
			this->rb_backward_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_backward_f->Location = System::Drawing::Point(11, 77);
			this->rb_backward_f->Name = L"rb_backward_f";
			this->rb_backward_f->Size = System::Drawing::Size(79, 18);
			this->rb_backward_f->TabIndex = 2;
			this->rb_backward_f->Text = L"&Backward";
			this->rb_backward_f->UseVisualStyleBackColor = true;
			// 
			// rb_forward_f
			// 
			this->rb_forward_f->AutoSize = true;
			this->rb_forward_f->Checked = true;
			this->rb_forward_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_forward_f->Location = System::Drawing::Point(11, 47);
			this->rb_forward_f->Name = L"rb_forward_f";
			this->rb_forward_f->Size = System::Drawing::Size(69, 18);
			this->rb_forward_f->TabIndex = 1;
			this->rb_forward_f->TabStop = true;
			this->rb_forward_f->Text = L"&Forward";
			this->rb_forward_f->UseVisualStyleBackColor = true;
			// 
			// rb_all_f
			// 
			this->rb_all_f->AutoSize = true;
			this->rb_all_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->rb_all_f->Location = System::Drawing::Point(11, 19);
			this->rb_all_f->Name = L"rb_all_f";
			this->rb_all_f->Size = System::Drawing::Size(42, 18);
			this->rb_all_f->TabIndex = 0;
			this->rb_all_f->Text = L"&All";
			this->rb_all_f->UseVisualStyleBackColor = true;
			// 
			// grp_option_f
			// 
			this->grp_option_f->Controls->Add(this->lbl_endianess_f);
			this->grp_option_f->Controls->Add(this->cb_endianess_f);
			this->grp_option_f->Controls->Add(this->cb_bit_width_f);
			this->grp_option_f->Controls->Add(this->lbl_bit_width_f);
			this->grp_option_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grp_option_f->Location = System::Drawing::Point(8, 92);
			this->grp_option_f->Name = L"grp_option_f";
			this->grp_option_f->Size = System::Drawing::Size(225, 107);
			this->grp_option_f->TabIndex = 9;
			this->grp_option_f->TabStop = false;
			this->grp_option_f->Text = L"Options";
			// 
			// lbl_endianess_f
			// 
			this->lbl_endianess_f->AutoSize = true;
			this->lbl_endianess_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_endianess_f->Location = System::Drawing::Point(6, 64);
			this->lbl_endianess_f->Name = L"lbl_endianess_f";
			this->lbl_endianess_f->Size = System::Drawing::Size(59, 13);
			this->lbl_endianess_f->TabIndex = 3;
			this->lbl_endianess_f->Text = L"Endianess:";
			// 
			// cb_endianess_f
			// 
			this->cb_endianess_f->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cb_endianess_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_endianess_f->FormattingEnabled = true;
			this->cb_endianess_f->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Little endian", L"Big endian" });
			this->cb_endianess_f->Location = System::Drawing::Point(6, 80);
			this->cb_endianess_f->Name = L"cb_endianess_f";
			this->cb_endianess_f->Size = System::Drawing::Size(213, 21);
			this->cb_endianess_f->TabIndex = 2;
			// 
			// cb_bit_width_f
			// 
			this->cb_bit_width_f->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cb_bit_width_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cb_bit_width_f->FormattingEnabled = true;
			this->cb_bit_width_f->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Single (32-bit float)", L"Double (64-bit float)" });
			this->cb_bit_width_f->Location = System::Drawing::Point(6, 37);
			this->cb_bit_width_f->Name = L"cb_bit_width_f";
			this->cb_bit_width_f->Size = System::Drawing::Size(213, 21);
			this->cb_bit_width_f->TabIndex = 1;
			this->cb_bit_width_f->SelectedIndexChanged += gcnew System::EventHandler(this, &winfind::cb_bit_width_f_SelectedIndexChanged);
			// 
			// lbl_bit_width_f
			// 
			this->lbl_bit_width_f->AutoSize = true;
			this->lbl_bit_width_f->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_bit_width_f->Location = System::Drawing::Point(6, 21);
			this->lbl_bit_width_f->Name = L"lbl_bit_width_f";
			this->lbl_bit_width_f->Size = System::Drawing::Size(50, 13);
			this->lbl_bit_width_f->TabIndex = 0;
			this->lbl_bit_width_f->Text = L"Bit width:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->label6->Location = System::Drawing::Point(8, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(62, 13);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Search for: ";
			// 
			// nud_float
			// 
			this->nud_float->Location = System::Drawing::Point(81, 18);
			this->nud_float->Name = L"nud_float";
			this->nud_float->Size = System::Drawing::Size(315, 20);
			this->nud_float->TabIndex = 0;
			this->nud_float->ValueChanged += gcnew System::EventHandler(this, &winfind::nud_float_ValueChanged);
			// 
			// find_tab_img_list
			// 
			this->find_tab_img_list->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->find_tab_img_list->ImageSize = System::Drawing::Size(16, 16);
			this->find_tab_img_list->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// winfind
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(410, 296);
			this->Controls->Add(this->tab_find);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winfind";
			this->Text = L"Find...";
			this->Load += gcnew System::EventHandler(this, &winfind::winfind_Load);
			this->tab_find->ResumeLayout(false);
			this->tb_page_string->ResumeLayout(false);
			this->tb_page_string->PerformLayout();
			this->grp_direction->ResumeLayout(false);
			this->grp_direction->PerformLayout();
			this->grp_encoding->ResumeLayout(false);
			this->grp_encoding->PerformLayout();
			this->tb_page_hex->ResumeLayout(false);
			this->tb_page_hex->PerformLayout();
			this->grp_direction_hex->ResumeLayout(false);
			this->grp_direction_hex->PerformLayout();
			this->tb_page_signature->ResumeLayout(false);
			this->tb_page_signature->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tb_page_integer->ResumeLayout(false);
			this->tb_page_integer->PerformLayout();
			this->grp_direction_i->ResumeLayout(false);
			this->grp_direction_i->PerformLayout();
			this->grp_i_opt->ResumeLayout(false);
			this->grp_i_opt->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_integer))->EndInit();
			this->tb_page_float->ResumeLayout(false);
			this->tb_page_float->PerformLayout();
			this->grp_direction_f->ResumeLayout(false);
			this->grp_direction_f->PerformLayout();
			this->grp_option_f->ResumeLayout(false);
			this->grp_option_f->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nud_float))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void btn_cancel_Click(System::Object^ sender, System::EventArgs^ e) {
		DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}

	private: System::Void winfind_Load(System::Object^ sender, System::EventArgs^ e) {
		
		find_tab_img_list->Images->Add(global::img_string);
		find_tab_img_list->Images->Add(global::img_hex);
		find_tab_img_list->Images->Add(global::img_aob);
		find_tab_img_list->Images->Add(global::img_integer);
		find_tab_img_list->Images->Add(global::img_float);

		tb_page_string->ImageIndex = 0;
		tb_page_hex->ImageIndex = 1;
		tb_page_signature->ImageIndex = 2;
		tb_page_integer->ImageIndex = 3;
		tb_page_float->ImageIndex = 4;

		txt_hex_ext_ = gcnew TextBoxBaseExtension<UInt64>(txt_hex_str, 16); // template argument does not matter for our usage here

		this->Location = Point((Screen::PrimaryScreen->Bounds.Width / 2) - (this->Width / 2), (Screen::PrimaryScreen->Bounds.Height / 2) - (this->Height / 2));

		cb_encoding->SelectedIndex = 0;
		cb_bit_width_i->SelectedIndex = 0;
		cb_bit_width_f->SelectedIndex = 0;
		cb_endianness_i->SelectedIndex = 0;
		cb_endianess_f->SelectedIndex = 0;

		nud_float->Maximum = Decimal::MaxValue;
		nud_float->Minimum = Decimal::MinValue;
	}

	private: System::Void btn_search_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!txt_string->Text->Length) {
			MessageBox::Show("Must enter a string to be searched for!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		switch (cb_encoding->SelectedIndex) {

			case 0: {

				try {

					if (!cb_case->Checked) {

						search_data_ = encoding_->GetBytes(txt_string->Text->ToLower());
						search_data_upper_ = encoding_->GetBytes(txt_string->Text->ToUpper());
					}
					else {

						search_data_ = encoding_->GetBytes(txt_string->Text);
					}
				}
				catch (Exception^ except) {

					MessageBox::Show("Invalid characters per codepage entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				break;
			}
			case 1: {

				try {

					if (!cb_case->Checked) {

						search_data_ = Encoding::Unicode->GetBytes(txt_string->Text->ToLower());
						search_data_upper_ = Encoding::Unicode->GetBytes(txt_string->Text->ToUpper());
					}
					else {

						search_data_ = Encoding::Unicode->GetBytes(txt_string->Text);
					}
				}
				catch (FormatException^ except) {

					MessageBox::Show("Invalid Unicode characters entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				break;
			}
		}

		is_ignore_case_ = cb_case->Checked;

		find_option = find_type::string;

		if (rb_forward->Checked)
			find_direction = find_direction_type::forward;
		else if (rb_backward->Checked)
			find_direction = find_direction_type::backward;
		else
			find_direction = find_direction_type::all;

		DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void txt_string_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		btn_search->Enabled = txt_string->Text->Length ? true : false;
	}

	private: System::Void btn_search_h_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!txt_hex_str->Text->Length)
			goto do_err;

		auto hex_str = txt_hex_str->Text->Replace(" ", "");

		if (hex_str->Length % 2)
			goto do_err;

		auto buffer = gcnew array<unsigned char>(hex_str->Length / 2);

		if (!util::try_parse_hex_string(txt_hex_str->Text, buffer))
			goto do_err;

		search_data_ = buffer;

		if (rb_forward_hex->Checked)
			find_direction = find_direction_type::forward;
		else if (rb_backward_hex->Checked)
			find_direction = find_direction_type::backward;
		else
			find_direction = find_direction_type::all;

		DialogResult = System::Windows::Forms::DialogResult::OK;

		return;

	do_err:

		MessageBox::Show("Invalid hexadecimal string data entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);

	}

	inline aob_signature^ __clrcall aob_string_parse() {

		if (!txt_aob->Text->Length)
			goto do_err;

		auto aob_str = txt_aob->Text->Replace(" ", "");

		if (aob_str->Length % 2)
			goto do_err;

		auto signature_s = gcnew aob_signature();
		signature_s->scan_list = gcnew List<short>();

		for (Int64 i = 0; i < aob_str->Length; i += 2) {

			Byte buffer;

			if (util::try_parse_hex_string(aob_str->Substring(i, 2), buffer, false)) {

				signature_s->scan_list->Add(static_cast<short>(buffer));
			}
			else {

				if (aob_str[i] != L'?' || aob_str[i + 1] != L'?')
					goto do_err;

				signature_s->scan_list->Add(static_cast<short>(-1)); // -1 is flag for undefined char / byte, this is the easiest and most efficient way to map the data without excruciating arithmetic
			}
		}

		return signature_s;

	do_err:

		MessageBox::Show("Invalid AoB description entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);

		return nullptr;
	}

	private: System::Void __clrcall btn_search_s_Click(System::Object^ sender, System::EventArgs^ e) {

		auto aob_scan_object = aob_string_parse();

		if (!aob_scan_object)
			return;

		find_option = find_type::pattern;
		aob_search_data_ = aob_scan_object->scan_list->ToArray();

		delete aob_scan_object;

		if (rb_forward_s->Checked)
			find_direction = find_direction_type::forward;
		else if (rb_backward_s->Checked)
			find_direction = find_direction_type::backward;
		else
			find_direction = find_direction_type::all;

		DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void __clrcall cb_bit_width_f_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

		nud_float->DecimalPlaces = cb_bit_width_f->SelectedIndex ? 18 : 9;
	}

	private: System::Void __clrcall cb_bit_width_i_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

		switch (cb_bit_width_i->SelectedIndex) {
			case 0: {
				nud_integer->Maximum = UInt64::MaxValue;
				nud_integer->Minimum = Int64::MinValue;
				break;
			}
			case 1: {
				nud_integer->Maximum = Byte::MaxValue;
				nud_integer->Minimum = Byte::MinValue;
				break;
			}
			case 2: {
				nud_integer->Maximum = SByte::MaxValue;
				nud_integer->Minimum = SByte::MinValue;
				break;
			}
			case 3: {
				nud_integer->Maximum = UInt16::MaxValue;
				nud_integer->Minimum = UInt16::MinValue;
				break;
			}
			case 4: {
				nud_integer->Maximum = Int16::MaxValue;
				nud_integer->Minimum = Int16::MinValue;
				break;
			}
			case 5: {
				nud_integer->Maximum = UInt32::MaxValue;
				nud_integer->Minimum = UInt32::MinValue;
				break;
			}
			case 6:{
				nud_integer->Maximum = Int32::MaxValue;
				nud_integer->Minimum = Int32::MinValue;
				break;
			}
			case 7: {
				nud_integer->Maximum = UInt64::MaxValue;
				nud_integer->Minimum = UInt64::MinValue;
				break;
			}
			case 8: {
				nud_integer->Maximum = Int64::MaxValue;
				nud_integer->Minimum = Int64::MinValue;
				break;
			}
		}
	}

	private: System::Void __clrcall cb_hex_i_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		nud_integer->Hexadecimal = cb_hex_i->Checked;
	}

	private: System::Void __clrcall btn_search_i_Click(System::Object^ sender, System::EventArgs^ e) {

		if (nud_integer->Value > UInt64::MaxValue || nud_integer->Value < Int64::MinValue) { // we are only supporting 8-64 bit integers, likewise these are the bounds

			MessageBox::Show("Invalid integer value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}


		switch (cb_bit_width_i->SelectedIndex) {
			case 0: {
				
				auto value = nud_integer->Value;

				if (value >= 0) {

					if (value <= Byte::MaxValue) {

						goto parse_byte;
					}
					else if (value <= UInt16::MaxValue) {

						goto parse_ushort;
					}
					else if (value <= UInt32::MaxValue) {

						goto parse_uint;
					}
					else if (value <= UInt64::MaxValue) {

						goto parse_uint64;
					}

				}
				else {

					if (value >= SByte::MinValue) {

						goto parse_char;
					}
					else if (value <= Int16::MinValue) {

						goto parse_short;
					}
					else if (value <= Int32::MinValue) {

						goto parse_int;
					}
					else if (value <= Int64::MinValue) {

						goto parse_int64;
					}
				}

				break;
			}
			case 1: {

		parse_byte:

				Byte parsed = static_cast<Byte>(nud_integer->Value);

				search_data_ = gcnew array<Byte>(1) { parsed };

				break;
			}
			case 2: {

		parse_char:
				SByte parsed = static_cast<SByte>(nud_integer->Value);

				search_data_ = gcnew array<Byte>(1) { static_cast<Byte>(parsed) };

				break;
			}
			case 3: {

		parse_ushort:
				
				UInt16 parsed = static_cast<UInt16>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(2) { parsed_ptr[0], parsed_ptr[1] };

				break;
			}
			case 4: {

		parse_short:
				
				Int16 parsed = static_cast<Int16>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(2) { parsed_ptr[0], parsed_ptr[1] };

				break;
			}
			case 5: {

		parse_uint:
				
				UInt32 parsed = static_cast<UInt32>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(4) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3] };

				break;
			}
			case 6: {

		parse_int:
				
				Int32 parsed = static_cast<Int32>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(4) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3] };

				break;
			}
			case 7: {

		parse_uint64:
				
				UInt64 parsed = static_cast<UInt64>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(8) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3], parsed_ptr[4], parsed_ptr[5], parsed_ptr[6], parsed_ptr[7] };

				break;
			}
			case 8: {

		parse_int64:
				
				Int64 parsed = static_cast<Int64>(nud_integer->Value);

				auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

				search_data_ = gcnew array<Byte>(8) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3], parsed_ptr[4], parsed_ptr[5], parsed_ptr[6], parsed_ptr[7] };

				break;
			}
		}

		find_option = find_type::integer;

		if (cb_endianness_i->SelectedIndex)
			Array::Reverse(search_data_);

		if (rb_forward_i->Checked)
			find_direction = find_direction_type::forward;
		else if (rb_backward_i->Checked)
			find_direction = find_direction_type::backward;
		else
			find_direction = find_direction_type::all;

		DialogResult = System::Windows::Forms::DialogResult::OK;
	}

	private: System::Void nud_integer_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

		if (e->KeyCode == Keys::OemPeriod) {

			e->SuppressKeyPress = true;

			e->Handled = true;
		}
	}

	private: System::Void nud_float_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void btn_search_f_Click(System::Object^ sender, System::EventArgs^ e) {

		switch (cb_bit_width_f->SelectedIndex) {

			case 0: {

				float parsed;

				if (Single::TryParse(nud_float->Value.ToString(), parsed)) {

					auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

					search_data_ = gcnew array<Byte>(4) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3] };
				}

				break;
			}
			case 1: {

				double parsed;

				if (Double::TryParse(nud_float->Value.ToString(), parsed)) {

					auto* parsed_ptr = reinterpret_cast<Byte*>(&parsed);

					search_data_ = gcnew array<Byte>(8) { parsed_ptr[0], parsed_ptr[1], parsed_ptr[2], parsed_ptr[3], parsed_ptr[4], parsed_ptr[5], parsed_ptr[6], parsed_ptr[7] };
				}

				break;
			}
		}

		if (cb_endianess_f->SelectedIndex)
			Array::Reverse(search_data_);

		if (rb_forward_f->Checked)
			find_direction = find_direction_type::forward;
		else if (rb_backward_f->Checked)
			find_direction = find_direction_type::backward;
		else
			find_direction = find_direction_type::all;

		DialogResult = System::Windows::Forms::DialogResult::OK;

		return;

	do_err:

		MessageBox::Show("Invalid " + (cb_bit_width_f->SelectedIndex ? " float64 " : " float32 ") + "value entered!", "hexasm", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
};
}

#endif
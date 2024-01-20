#pragma once
#include "pe.hpp"
namespace hexasm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class wintest : public System::Windows::Forms::Form
	{
	public:

		native::pe_file* pe_file;

		wintest(native::pe_file* file) : pe_file(file)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~wintest()
		{
			if (components)
			{
				delete pe_file;
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	protected:
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ column1;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;

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
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->column1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->listView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->richTextBox1);
			this->splitContainer1->Size = System::Drawing::Size(621, 466);
			this->splitContainer1->SplitterDistance = 206;
			this->splitContainer1->TabIndex = 0;
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->column1 });
			this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView1->FullRowSelect = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(0, 0);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(206, 466);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &wintest::listView1_SelectedIndexChanged);
			// 
			// column1
			// 
			this->column1->Text = L"fn";
			this->column1->Width = 179;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(0, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(411, 466);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// wintest
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(621, 466);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"wintest";
			this->Text = L"wintest";
			this->Load += gcnew System::EventHandler(this, &wintest::wintest_Load);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void wintest_Load(System::Object^ sender, System::EventArgs^ e) {

		if (!pe_file)
			return;
		int nullsub_iter{}, sub_iter{};
		for (auto i = 0; i < pe_file->section_decompilations_->size(); ++i) {
			for (int x = 0; x < (*pe_file->section_decompilations_)[i].subroutines.size(); ++x) {

				auto& sub = (*pe_file->section_decompilations_)[i].subroutines[x];
				//use addressofentrypoint field in pe header - first fn is not alway entry
				ListViewItem^ lvi = gcnew ListViewItem(sub.is_entry_fn ? "main" : (sub.is_null_subroutine ? "nullsub " + sub.begin_offset.ToString("X16") : "sub " + sub.begin_offset.ToString("X16")));

				listView1->Items->Add(lvi);

				if (sub.is_null_subroutine)
					++nullsub_iter;
				else
					++sub_iter;
			}
		}

	}
	private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

		if (!listView1->SelectedItems->Count)
			return;

		auto% item = listView1->SelectedItems[0];

		auto& sub = (*pe_file->section_decompilations_)[0].subroutines[item->Index];

		richTextBox1->Clear();

		for (int i = 0; i < sub.instruction_count; ++i) {

			String^ insn = gcnew String(sub.instructions[i].mnemonic) + " " + gcnew String(sub.instructions[i].op_str) + gcnew String("\r\n");
			richTextBox1->AppendText(insn);

			delete insn;
		}
	}
};
}

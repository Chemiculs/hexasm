#pragma once

namespace hexasm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for winprogress
	/// </summary>
	public ref class winprogress : public System::Windows::Forms::Form
	{
	public:

		bool spinlock_ = false;

		winprogress(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~winprogress()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::ProgressBar^ main_progress;
	protected:
	public: System::Windows::Forms::Label^ lbl_task;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winprogress::typeid));
			this->main_progress = (gcnew System::Windows::Forms::ProgressBar());
			this->lbl_task = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// main_progress
			// 
			this->main_progress->Location = System::Drawing::Point(12, 25);
			this->main_progress->MarqueeAnimationSpeed = 12;
			this->main_progress->Name = L"main_progress";
			this->main_progress->Size = System::Drawing::Size(307, 24);
			this->main_progress->TabIndex = 0;
			// 
			// lbl_task
			// 
			this->lbl_task->AutoSize = true;
			this->lbl_task->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lbl_task->Location = System::Drawing::Point(12, 9);
			this->lbl_task->Name = L"lbl_task";
			this->lbl_task->Size = System::Drawing::Size(0, 13);
			this->lbl_task->TabIndex = 1;
			// 
			// winprogress
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(331, 63);
			this->Controls->Add(this->lbl_task);
			this->Controls->Add(this->main_progress);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"winprogress";
			this->Text = L"Loading...";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &winprogress::winprogress_Load);
			this->Shown += gcnew System::EventHandler(this, &winprogress::winprogress_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	public: System::Void __clrcall update_progress(String^ task, int value) {

		this->BringToFront();

		main_progress->Value = value > 100 ? 100 : value;

		if (task->Length)
			lbl_task->Text = task;

		Application::DoEvents();
	}

	private: System::Void winprogress_Load(System::Object^ sender, System::EventArgs^ e) {

		this->Focus();

		this->Location = Point((Screen::PrimaryScreen->Bounds.Width / 2) - (this->Width / 2), (Screen::PrimaryScreen->Bounds.Height / 2) - (this->Height / 2));
	}

	private: System::Void winprogress_Shown(System::Object^ sender, System::EventArgs^ e) {

	}

};
}

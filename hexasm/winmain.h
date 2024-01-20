#ifndef WINMAIN_H
#define WINMAIN_H

#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

#include "ListViewEx.hpp"
#include "winjump.h"
#include "winabout.h"
#include "winprogress.h"
#include "winhexstr.h"
#include "winblocksel.h"
#include "winfind.h"
#include "wintest.h"

#include "hash.hpp"
#include "pe.hpp"

using namespace ::hexasm::gui;

namespace hexasm {

#pragma region GUI Constants

#define TBTN_NEW  0x00FE
#define TBTN_OPEN 0x00FF
#define TBTN_SAVE 0x0100
#define TBTN_SAVEAS 0x0101
#define TBTN_JUMP 0x0102
#define TBTN_BLOCK 0x0103
#define TBTN_COPY_STRING 0x0104
#define TBTN_COPY_HEX 0x0105
#define TBTN_PASTE_STRING 0x0106
#define TBTN_PASTE_HEX 0x0107
#define TBTN_INSERT 0x0108

#pragma endregion

		
		static uint current_document_index = 0x0;

		public ref class winmain : public System::Windows::Forms::Form
		{

			private: winprogress^ progress_window_;
			private: winprogress^ hashing_progress_dlg_;
			private: System::Windows::Forms::TabControl^ tab_main_data;
			private: System::Windows::Forms::TabPage^ tb_page_graph;
			private: System::Windows::Forms::ContextMenu^ main_graph_ctx;
			private: System::Windows::Forms::MenuItem^ select_ctx;
			private: System::Windows::Forms::MenuItem^ beginning_ctx;
			private: System::Windows::Forms::MenuItem^ end_ctx;
			private: System::Windows::Forms::MenuItem^ entire_ctx;
			private: System::Windows::Forms::MenuItem^ tools_m;
			private: System::Windows::Forms::MenuItem^ find_m;
			private: System::Windows::Forms::MenuItem^ find_n_m;
			private: System::Windows::Forms::MenuItem^ find_p_m;
			private: System::Windows::Forms::MenuItem^ menuItem13;

		public:

#pragma region Ctor  / Dtor

			winmain(void)
			{

				progress_window_ = gcnew winprogress();

				progress_window_->Show();

				progress_window_->update_progress("initializing window...", 5);

				/* Load default theme settings */
				global::hex_editor_font = gcnew System::Drawing::Font("Consolas", 10);

				global::hex_text_foreground = global::DEFAULT_TEXT_FOREGROUND_COLOR;
				global::hex_offset_columns_color = global::DEFAULT_OFFSET_COLOR;
				global::hex_background_color = global::DEFAULT_BACKGROUND_COLOR;
				global::hex_headers_color = global::DEFAULT_HEX_HEADERS_COLOR;
				global::hex_background_selection_color = global::DEFAULT_HEX_SELECTION_BACKCOLOR;
				global::hex_foreground_selection_color = global::DEFAULT_HEX_SELECTION_FORECOLOR;

				InitializeComponent();
			}

		protected:
			~winmain()
			{
				if (components)
				{
					try {

						delete components;
						delete global::img_document;
						delete global::img_document_delete;
						delete global::img_document_edit;
						delete global::img_document_new;
						delete global::img_document_plus;
						delete global::img_document_minus;
						delete global::img_binary_document;
						delete global::img_document_export;
						delete global::img_document_hash;
						delete global::img_document_lines;
						delete global::hasher;
						delete global::img_write_hex;
						delete global::img_word;
						delete global::img_dword;
						delete global::img_qword;
						delete global::img_stack;
						delete global::img_type;
						delete global::img_python;
						delete global::img_perl;
						delete global::img_rust;
						delete global::img_java;
						delete global::img_pascal;
						delete global::img_c;
						delete global::img_cpp;
						delete global::img_csharp;
						delete global::img_block_del;
						delete global::img_block_end;
						delete global::img_block_ins;
						delete global::img_block_start;
						delete global::img_block_whole;
						delete global::img_select_block;
						delete global::img_edit_jmp;
						delete global::img_copy_string;
						delete global::img_copy_hex;
						delete global::img_paste_string;
						delete global::img_paste_hex;
						delete global::img_help_information;
						delete global::img_settings_cog;
						delete global::img_exit;
						delete global::hex_union_instances;
						delete global::hex_editor_font;
						delete global::disasm_handle;
						delete global::graph_union_instances;

					}
					catch (Exception^ except) {}
				}
			}

#pragma endregion

#pragma region Managed GUI Objects

		private: System::Windows::Forms::MainMenu^ main_menu;
		private: System::Windows::Forms::MenuItem^ file_m;
		private: System::Windows::Forms::MenuItem^ new_m;
		private: System::Windows::Forms::MenuItem^ open_m;
		private: System::Windows::Forms::MenuItem^ save_m;
		private: System::Windows::Forms::MenuItem^ saveas_m;
		private: System::Windows::Forms::MenuItem^ menuItem6;
		private: System::Windows::Forms::MenuItem^ close_m;
		private: System::Windows::Forms::MenuItem^ closeall_m;
		private: System::Windows::Forms::MenuItem^ menuItem8;
		private: System::Windows::Forms::MenuItem^ exit_m;
		private: System::Windows::Forms::MenuItem^ options_m;
		private: System::Windows::Forms::MenuItem^ settings_m;
		private: System::Windows::Forms::MenuItem^ help_m;
		private: System::Windows::Forms::MenuItem^ about_m;
		private: System::Windows::Forms::StatusStrip^ main_stat;
		private: wyDay::Controls::VistaMenu^ main_vist;
		private: System::Windows::Forms::SplitContainer^ sc_main;
		private: System::Windows::Forms::SplitContainer^ sc_tab_data;
		private: System::Windows::Forms::TabControl^ tab_main;
		private: System::Windows::Forms::SplitContainer^ sc_info_main;
		private: System::Windows::Forms::TabControl^ main_size_info_tab;
		private: System::Windows::Forms::TabPage^ main_type_view_tab;
		private: System::Windows::Forms::TabPage^ main_hash_view_tab;
		private: hexasm::gui::EditableListView^ main_type_lv;
		private: System::Windows::Forms::RadioButton^ main_little_endian_rb;
		private: System::Windows::Forms::RadioButton^ main_big_endian_rb;
		private: System::Windows::Forms::ToolBar^ main_tb;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_new;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_open;
		private: System::Windows::Forms::ImageList^ main_image_tb_list;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton1;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton2;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_save;
		private: System::Windows::Forms::GroupBox^ main_group_value;
		private: System::Windows::Forms::ToolStripStatusLabel^ tslbl_offset;
		private: System::Windows::Forms::ToolStripStatusLabel^ tslbl_textmode;
		private: System::Windows::Forms::ToolStripStatusLabel^ ts_seperator_1;
		private: System::Windows::Forms::ToolStripStatusLabel^ tslbl_block;
		private: System::Windows::Forms::ToolStripStatusLabel^ ts_seperator_2;
		private: System::Windows::Forms::ToolStripStatusLabel^ tslbl_length;
		private: System::Windows::Forms::ToolStripStatusLabel^ tslbl_modified;
		private: System::Windows::Forms::ContextMenu^ main_document_context_menu;
		private: System::Windows::Forms::MenuItem^ jmp_m_ctx;
		private: System::Windows::Forms::MenuItem^ edit_m;
		private: System::Windows::Forms::MenuItem^ jump_m;
		private: System::Windows::Forms::SplitContainer^ sc_main_doc_enc;
		private: System::Windows::Forms::ComboBox^ main_cb_encoding;
		private: System::Windows::Forms::MenuItem^ copy_string_ctx;
		private: System::Windows::Forms::MenuItem^ copy_hex_ctx;
		private: System::Windows::Forms::MenuItem^ copyas_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_cpp_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_csharp_m_ctx;
		private: System::Windows::Forms::MenuItem^ paste_string_ctx;
		private: System::Windows::Forms::MenuItem^ paste_hex_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_python_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_java_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_pascal_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_perl_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_rust_m_ctx;
		private: System::Windows::Forms::MenuItem^ cpy_vb_m_ctx;
		private: System::Windows::Forms::MenuItem^ copyas_m;
		private: System::Windows::Forms::MenuItem^ c_m;
		private: System::Windows::Forms::MenuItem^ csharp_m;
		private: System::Windows::Forms::MenuItem^ python_m;
		private: System::Windows::Forms::MenuItem^ java_m;
		private: System::Windows::Forms::MenuItem^ pascal_m;
		private: System::Windows::Forms::MenuItem^ perl_m;
		private: System::Windows::Forms::MenuItem^ rust_m;
		private: System::Windows::Forms::MenuItem^ vb_m;
		private: System::Windows::Forms::MenuItem^ copy_string_m;
		private: System::Windows::Forms::MenuItem^ copy_hex_m;
		private: System::Windows::Forms::MenuItem^ menuItem4;
		private: System::Windows::Forms::MenuItem^ menuItem5;
		private: System::Windows::Forms::MenuItem^ seperator_m;
		private: System::Windows::Forms::MenuItem^ paste_string_m;
		private: System::Windows::Forms::MenuItem^ paste_hex_m;
		private: System::Windows::Forms::MenuItem^ menuItem1;
		private: System::Windows::Forms::MenuItem^ menuItem2;
		private: System::Windows::Forms::MenuItem^ save_all_m;
		private: System::Windows::Forms::CheckBox^ main_cb_hex;
		private: System::Windows::Forms::MenuItem^ jmp_selection_ctx;
		private: System::Windows::Forms::MenuItem^ jmp_selection_m;
		private: System::Windows::Forms::MenuItem^ word_m;
		private: System::Windows::Forms::MenuItem^ dword_m;
		private: System::Windows::Forms::MenuItem^ qword_m;
		private: System::Windows::Forms::MenuItem^ word_ctx;
		private: System::Windows::Forms::MenuItem^ dword_ctx;
		private: System::Windows::Forms::MenuItem^ qword_ctx;
		private: System::Windows::Forms::ContextMenu^ main_edit_context_menu;
		private: System::Windows::Forms::MenuItem^ edit_ctx;
		private: System::Windows::Forms::MenuItem^ menuItem10;
		private: System::Windows::Forms::MenuItem^ copy_ctx;
		private: System::Windows::Forms::MenuItem^ menuItem11;
		private: System::Windows::Forms::MenuItem^ paste_ctx;
		private: System::Windows::Forms::MenuItem^ menuItem9;
		private: System::Windows::Forms::MenuItem^ cut_hex_m;
		private: System::Windows::Forms::MenuItem^ cut_string_m;
		private: System::Windows::Forms::MenuItem^ menuItem12;
		private: System::Windows::Forms::MenuItem^ cut_hex_ctx;
		private: System::Windows::Forms::MenuItem^ cut_string_ctx;
		private: System::Windows::Forms::MenuItem^ menuItem3;
		private: System::Windows::Forms::MenuItem^ menuItem7;
		private: System::Windows::Forms::MenuItem^ select_all_ctx;
		private: System::Windows::Forms::MenuItem^ select_all_m;
		private: System::Windows::Forms::MenuItem^ select_block_m;
		private: System::Windows::Forms::MenuItem^ copy_offset_m;
		private: System::Windows::Forms::MenuItem^ select_block_ctx;
		private: System::Windows::Forms::MenuItem^ copy_offset_ctx;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton3;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_jump;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_select_block;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton6;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_copy_string;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_copy_hex;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_paste_string;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_paste_hex;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_saveas;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton4;
		private: System::Windows::Forms::ToolBarButton^ toolBarButton5;
		private: System::Windows::Forms::ToolBarButton^ tb_btn_insert;
		private: System::Windows::Forms::SplitContainer^ sc_disasm_main;
		private: System::Windows::Forms::SplitContainer^ sc_disasm_stack_main;
		private: System::Windows::Forms::SplitContainer^ sc_disasm_stack_change;
		private: System::Windows::Forms::Label^ lbl_disasm_stack_undo;
		private: System::Windows::Forms::SplitContainer^ sc_disasm_stack_undone;
		private: System::Windows::Forms::Label^ lbl_disasm_stack_redo;
		private: System::Windows::Forms::ListView^ lv_main_undo;
		private: System::Windows::Forms::ColumnHeader^ columnHeader1;
		private: System::Windows::Forms::ListView^ lv_main_redo;
		private: System::Windows::Forms::ColumnHeader^ columnHeader2;
		private: System::Windows::Forms::ColumnHeader^ columnHeader3;
		private: System::Windows::Forms::ColumnHeader^ columnHeader4;
		private: System::Windows::Forms::ColumnHeader^ columnHeader5;
		private: System::Windows::Forms::ColumnHeader^ columnHeader6;
		private: System::Windows::Forms::TabControl^ tab_main_stack;
		private: System::Windows::Forms::TabPage^ tb_page_stack;
		private: System::Windows::Forms::TabPage^ tb_page_log;
		private: System::Windows::Forms::RichTextBox^ rtb_log;
		private: System::Windows::Forms::ListView^ lv_main_hash;
		private: System::Windows::Forms::ColumnHeader^ columnHeader7;
		private: System::Windows::Forms::ColumnHeader^ columnHeader8;
		private: System::Windows::Forms::SplitContainer^ sc_main_hash;
		private: System::Windows::Forms::SplitContainer^ sc_buttons_hash;
		private: System::Windows::Forms::Button^ btn_compute_all;
		private: System::Windows::Forms::Button^ btn_compute;
		private: System::Windows::Forms::SplitContainer^ sc_list_rb_hash;
		private: System::Windows::Forms::GroupBox^ grp_main_hash;
		private: System::Windows::Forms::RadioButton^ rb_whole_hash;
		private: System::Windows::Forms::RadioButton^ rb_current_hash;
		private: System::ComponentModel::IContainer^ components;
		
#pragma endregion

#pragma region Windows Form Designer generated code

			void InitializeComponent(void)
			{
				this->components = (gcnew System::ComponentModel::Container());
				System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"MD5",
						L"null"
				}, -1));
				System::Windows::Forms::ListViewItem^ listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"SHA1",
						L"null"
				}, -1));
				System::Windows::Forms::ListViewItem^ listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"SHA256",
						L"null"
				}, -1));
				System::Windows::Forms::ListViewItem^ listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"SHA384",
						L"null"
				}, -1));
				System::Windows::Forms::ListViewItem^ listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"SHA512",
						L"null"
				}, -1));
				System::Windows::Forms::ListViewItem^ listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
					L"RIPEMD160",
						L"null"
				}, -1));
				System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(winmain::typeid));
				this->main_menu = (gcnew System::Windows::Forms::MainMenu(this->components));
				this->file_m = (gcnew System::Windows::Forms::MenuItem());
				this->new_m = (gcnew System::Windows::Forms::MenuItem());
				this->open_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem4 = (gcnew System::Windows::Forms::MenuItem());
				this->save_m = (gcnew System::Windows::Forms::MenuItem());
				this->saveas_m = (gcnew System::Windows::Forms::MenuItem());
				this->save_all_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem6 = (gcnew System::Windows::Forms::MenuItem());
				this->close_m = (gcnew System::Windows::Forms::MenuItem());
				this->closeall_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem8 = (gcnew System::Windows::Forms::MenuItem());
				this->exit_m = (gcnew System::Windows::Forms::MenuItem());
				this->edit_m = (gcnew System::Windows::Forms::MenuItem());
				this->jump_m = (gcnew System::Windows::Forms::MenuItem());
				this->jmp_selection_m = (gcnew System::Windows::Forms::MenuItem());
				this->word_m = (gcnew System::Windows::Forms::MenuItem());
				this->dword_m = (gcnew System::Windows::Forms::MenuItem());
				this->qword_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem3 = (gcnew System::Windows::Forms::MenuItem());
				this->select_all_m = (gcnew System::Windows::Forms::MenuItem());
				this->select_block_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem5 = (gcnew System::Windows::Forms::MenuItem());
				this->copy_string_m = (gcnew System::Windows::Forms::MenuItem());
				this->copy_hex_m = (gcnew System::Windows::Forms::MenuItem());
				this->copy_offset_m = (gcnew System::Windows::Forms::MenuItem());
				this->copyas_m = (gcnew System::Windows::Forms::MenuItem());
				this->c_m = (gcnew System::Windows::Forms::MenuItem());
				this->csharp_m = (gcnew System::Windows::Forms::MenuItem());
				this->python_m = (gcnew System::Windows::Forms::MenuItem());
				this->java_m = (gcnew System::Windows::Forms::MenuItem());
				this->pascal_m = (gcnew System::Windows::Forms::MenuItem());
				this->perl_m = (gcnew System::Windows::Forms::MenuItem());
				this->rust_m = (gcnew System::Windows::Forms::MenuItem());
				this->vb_m = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem9 = (gcnew System::Windows::Forms::MenuItem());
				this->cut_hex_m = (gcnew System::Windows::Forms::MenuItem());
				this->cut_string_m = (gcnew System::Windows::Forms::MenuItem());
				this->seperator_m = (gcnew System::Windows::Forms::MenuItem());
				this->paste_string_m = (gcnew System::Windows::Forms::MenuItem());
				this->paste_hex_m = (gcnew System::Windows::Forms::MenuItem());
				this->tools_m = (gcnew System::Windows::Forms::MenuItem());
				this->find_m = (gcnew System::Windows::Forms::MenuItem());
				this->find_n_m = (gcnew System::Windows::Forms::MenuItem());
				this->find_p_m = (gcnew System::Windows::Forms::MenuItem());
				this->options_m = (gcnew System::Windows::Forms::MenuItem());
				this->settings_m = (gcnew System::Windows::Forms::MenuItem());
				this->help_m = (gcnew System::Windows::Forms::MenuItem());
				this->about_m = (gcnew System::Windows::Forms::MenuItem());
				this->main_stat = (gcnew System::Windows::Forms::StatusStrip());
				this->tslbl_offset = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->ts_seperator_1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->tslbl_block = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->ts_seperator_2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->tslbl_length = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->tslbl_modified = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->tslbl_textmode = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->main_vist = (gcnew wyDay::Controls::VistaMenu(this->components));
				this->tab_main = (gcnew System::Windows::Forms::TabControl());
				this->main_image_tb_list = (gcnew System::Windows::Forms::ImageList(this->components));
				this->sc_tab_data = (gcnew System::Windows::Forms::SplitContainer());
				this->sc_main_doc_enc = (gcnew System::Windows::Forms::SplitContainer());
				this->main_cb_encoding = (gcnew System::Windows::Forms::ComboBox());
				this->sc_info_main = (gcnew System::Windows::Forms::SplitContainer());
				this->main_size_info_tab = (gcnew System::Windows::Forms::TabControl());
				this->main_type_view_tab = (gcnew System::Windows::Forms::TabPage());
				this->main_hash_view_tab = (gcnew System::Windows::Forms::TabPage());
				this->sc_main_hash = (gcnew System::Windows::Forms::SplitContainer());
				this->sc_list_rb_hash = (gcnew System::Windows::Forms::SplitContainer());
				this->lv_main_hash = (gcnew System::Windows::Forms::ListView());
				this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
				this->grp_main_hash = (gcnew System::Windows::Forms::GroupBox());
				this->rb_whole_hash = (gcnew System::Windows::Forms::RadioButton());
				this->rb_current_hash = (gcnew System::Windows::Forms::RadioButton());
				this->sc_buttons_hash = (gcnew System::Windows::Forms::SplitContainer());
				this->btn_compute_all = (gcnew System::Windows::Forms::Button());
				this->btn_compute = (gcnew System::Windows::Forms::Button());
				this->main_group_value = (gcnew System::Windows::Forms::GroupBox());
				this->main_cb_hex = (gcnew System::Windows::Forms::CheckBox());
				this->main_big_endian_rb = (gcnew System::Windows::Forms::RadioButton());
				this->main_little_endian_rb = (gcnew System::Windows::Forms::RadioButton());
				this->sc_main = (gcnew System::Windows::Forms::SplitContainer());
				this->sc_disasm_main = (gcnew System::Windows::Forms::SplitContainer());
				this->tab_main_data = (gcnew System::Windows::Forms::TabControl());
				this->tb_page_graph = (gcnew System::Windows::Forms::TabPage());
				this->tab_main_stack = (gcnew System::Windows::Forms::TabControl());
				this->tb_page_stack = (gcnew System::Windows::Forms::TabPage());
				this->sc_disasm_stack_main = (gcnew System::Windows::Forms::SplitContainer());
				this->sc_disasm_stack_change = (gcnew System::Windows::Forms::SplitContainer());
				this->lbl_disasm_stack_undo = (gcnew System::Windows::Forms::Label());
				this->lv_main_undo = (gcnew System::Windows::Forms::ListView());
				this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
				this->sc_disasm_stack_undone = (gcnew System::Windows::Forms::SplitContainer());
				this->lbl_disasm_stack_redo = (gcnew System::Windows::Forms::Label());
				this->lv_main_redo = (gcnew System::Windows::Forms::ListView());
				this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
				this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
				this->tb_page_log = (gcnew System::Windows::Forms::TabPage());
				this->rtb_log = (gcnew System::Windows::Forms::RichTextBox());
				this->main_tb = (gcnew System::Windows::Forms::ToolBar());
				this->tb_btn_new = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton1 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_open = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton2 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_save = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_saveas = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton3 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_jump = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_select_block = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton6 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_copy_string = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_copy_hex = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton4 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_paste_string = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_paste_hex = (gcnew System::Windows::Forms::ToolBarButton());
				this->toolBarButton5 = (gcnew System::Windows::Forms::ToolBarButton());
				this->tb_btn_insert = (gcnew System::Windows::Forms::ToolBarButton());
				this->main_document_context_menu = (gcnew System::Windows::Forms::ContextMenu());
				this->jmp_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->jmp_selection_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->word_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->dword_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->qword_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem7 = (gcnew System::Windows::Forms::MenuItem());
				this->select_all_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->select_block_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem1 = (gcnew System::Windows::Forms::MenuItem());
				this->copy_string_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->copy_hex_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->copy_offset_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->copyas_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_cpp_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_csharp_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_python_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_java_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_pascal_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_perl_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_rust_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cpy_vb_m_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem12 = (gcnew System::Windows::Forms::MenuItem());
				this->cut_hex_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->cut_string_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem2 = (gcnew System::Windows::Forms::MenuItem());
				this->paste_string_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->paste_hex_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->main_edit_context_menu = (gcnew System::Windows::Forms::ContextMenu());
				this->edit_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem10 = (gcnew System::Windows::Forms::MenuItem());
				this->copy_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem11 = (gcnew System::Windows::Forms::MenuItem());
				this->paste_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->main_graph_ctx = (gcnew System::Windows::Forms::ContextMenu());
				this->select_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->beginning_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->end_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->menuItem13 = (gcnew System::Windows::Forms::MenuItem());
				this->entire_ctx = (gcnew System::Windows::Forms::MenuItem());
				this->main_stat->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->main_vist))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_tab_data))->BeginInit();
				this->sc_tab_data->Panel1->SuspendLayout();
				this->sc_tab_data->Panel2->SuspendLayout();
				this->sc_tab_data->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main_doc_enc))->BeginInit();
				this->sc_main_doc_enc->Panel1->SuspendLayout();
				this->sc_main_doc_enc->Panel2->SuspendLayout();
				this->sc_main_doc_enc->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_info_main))->BeginInit();
				this->sc_info_main->Panel1->SuspendLayout();
				this->sc_info_main->Panel2->SuspendLayout();
				this->sc_info_main->SuspendLayout();
				this->main_size_info_tab->SuspendLayout();
				this->main_hash_view_tab->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main_hash))->BeginInit();
				this->sc_main_hash->Panel1->SuspendLayout();
				this->sc_main_hash->Panel2->SuspendLayout();
				this->sc_main_hash->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_list_rb_hash))->BeginInit();
				this->sc_list_rb_hash->Panel1->SuspendLayout();
				this->sc_list_rb_hash->Panel2->SuspendLayout();
				this->sc_list_rb_hash->SuspendLayout();
				this->grp_main_hash->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_buttons_hash))->BeginInit();
				this->sc_buttons_hash->Panel1->SuspendLayout();
				this->sc_buttons_hash->Panel2->SuspendLayout();
				this->sc_buttons_hash->SuspendLayout();
				this->main_group_value->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main))->BeginInit();
				this->sc_main->Panel1->SuspendLayout();
				this->sc_main->Panel2->SuspendLayout();
				this->sc_main->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_main))->BeginInit();
				this->sc_disasm_main->Panel1->SuspendLayout();
				this->sc_disasm_main->Panel2->SuspendLayout();
				this->sc_disasm_main->SuspendLayout();
				this->tab_main_data->SuspendLayout();
				this->tab_main_stack->SuspendLayout();
				this->tb_page_stack->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_main))->BeginInit();
				this->sc_disasm_stack_main->Panel1->SuspendLayout();
				this->sc_disasm_stack_main->Panel2->SuspendLayout();
				this->sc_disasm_stack_main->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_change))->BeginInit();
				this->sc_disasm_stack_change->Panel1->SuspendLayout();
				this->sc_disasm_stack_change->Panel2->SuspendLayout();
				this->sc_disasm_stack_change->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_undone))->BeginInit();
				this->sc_disasm_stack_undone->Panel1->SuspendLayout();
				this->sc_disasm_stack_undone->Panel2->SuspendLayout();
				this->sc_disasm_stack_undone->SuspendLayout();
				this->tb_page_log->SuspendLayout();
				this->SuspendLayout();
				// 
				// main_menu
				// 
				this->main_menu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(5) {
					this->file_m, this->edit_m,
						this->tools_m, this->options_m, this->help_m
				});
				// 
				// file_m
				// 
				this->file_m->Index = 0;
				this->file_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(11) {
					this->new_m, this->open_m, this->menuItem4,
						this->save_m, this->saveas_m, this->save_all_m, this->menuItem6, this->close_m, this->closeall_m, this->menuItem8, this->exit_m
				});
				this->file_m->Text = L"&File";
				this->file_m->Select += gcnew System::EventHandler(this, &winmain::file_m_Select);
				// 
				// new_m
				// 
				this->new_m->Index = 0;
				this->new_m->Text = L"&New...";
				this->new_m->Click += gcnew System::EventHandler(this, &winmain::new_m_Click);
				// 
				// open_m
				// 
				this->open_m->Index = 1;
				this->open_m->Text = L"&Open..";
				this->open_m->Click += gcnew System::EventHandler(this, &winmain::open_m_Click);
				// 
				// menuItem4
				// 
				this->menuItem4->Index = 2;
				this->menuItem4->Text = L"-";
				// 
				// save_m
				// 
				this->save_m->Index = 3;
				this->save_m->Text = L"&Save";
				this->save_m->Click += gcnew System::EventHandler(this, &winmain::save_m_Click);
				// 
				// saveas_m
				// 
				this->saveas_m->Index = 4;
				this->saveas_m->Text = L"S&ave As...";
				this->saveas_m->Click += gcnew System::EventHandler(this, &winmain::saveas_m_Click);
				// 
				// save_all_m
				// 
				this->save_all_m->Index = 5;
				this->save_all_m->Text = L"Save &All";
				this->save_all_m->Click += gcnew System::EventHandler(this, &winmain::save_all_m_Click);
				// 
				// menuItem6
				// 
				this->menuItem6->Index = 6;
				this->menuItem6->Text = L"-";
				// 
				// close_m
				// 
				this->close_m->Index = 7;
				this->close_m->Text = L"&Close";
				this->close_m->Click += gcnew System::EventHandler(this, &winmain::close_m_Click);
				// 
				// closeall_m
				// 
				this->closeall_m->Index = 8;
				this->closeall_m->Text = L"C&lose All";
				this->closeall_m->Click += gcnew System::EventHandler(this, &winmain::closeall_m_Click);
				// 
				// menuItem8
				// 
				this->menuItem8->Index = 9;
				this->menuItem8->Text = L"-";
				// 
				// exit_m
				// 
				this->exit_m->Index = 10;
				this->exit_m->Text = L"&Exit";
				this->exit_m->Click += gcnew System::EventHandler(this, &winmain::exit_m_Click);
				// 
				// edit_m
				// 
				this->edit_m->Index = 1;
				this->edit_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(16) {
					this->jump_m, this->jmp_selection_m,
						this->menuItem3, this->select_all_m, this->select_block_m, this->menuItem5, this->copy_string_m, this->copy_hex_m, this->copy_offset_m,
						this->copyas_m, this->menuItem9, this->cut_hex_m, this->cut_string_m, this->seperator_m, this->paste_string_m, this->paste_hex_m
				});
				this->edit_m->Text = L"&Edit";
				this->edit_m->Popup += gcnew System::EventHandler(this, &winmain::edit_m_Click);
				// 
				// jump_m
				// 
				this->jump_m->Index = 0;
				this->jump_m->Text = L"&Jump To Address...";
				this->jump_m->Click += gcnew System::EventHandler(this, &winmain::tslbl_offset_DoubleClick);
				// 
				// jmp_selection_m
				// 
				this->jmp_selection_m->Index = 1;
				this->jmp_selection_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
					this->word_m, this->dword_m,
						this->qword_m
				});
				this->jmp_selection_m->Text = L"Jump To Selec&tion...";
				this->jmp_selection_m->Popup += gcnew System::EventHandler(this, &winmain::jmp_selection_ctx_Popup);
				// 
				// word_m
				// 
				this->word_m->Index = 0;
				this->word_m->Text = L"&WORD Value";
				this->word_m->Click += gcnew System::EventHandler(this, &winmain::word_m_Click);
				// 
				// dword_m
				// 
				this->dword_m->Index = 1;
				this->dword_m->Text = L"&DWORD Value";
				this->dword_m->Click += gcnew System::EventHandler(this, &winmain::dword_m_Click);
				// 
				// qword_m
				// 
				this->qword_m->Index = 2;
				this->qword_m->Text = L"&QWORD Value";
				this->qword_m->Click += gcnew System::EventHandler(this, &winmain::qword_m_Click);
				// 
				// menuItem3
				// 
				this->menuItem3->Index = 2;
				this->menuItem3->Text = L"-";
				// 
				// select_all_m
				// 
				this->select_all_m->Index = 3;
				this->select_all_m->Text = L"Select Al&l";
				this->select_all_m->Click += gcnew System::EventHandler(this, &winmain::select_all_m_Click);
				// 
				// select_block_m
				// 
				this->select_block_m->Index = 4;
				this->select_block_m->Text = L"Select &Block...";
				this->select_block_m->Click += gcnew System::EventHandler(this, &winmain::select_block_m_Click);
				// 
				// menuItem5
				// 
				this->menuItem5->Index = 5;
				this->menuItem5->Text = L"-";
				// 
				// copy_string_m
				// 
				this->copy_string_m->Index = 6;
				this->copy_string_m->Text = L"&Copy String Selection";
				this->copy_string_m->Click += gcnew System::EventHandler(this, &winmain::copy_string_m_Click);
				// 
				// copy_hex_m
				// 
				this->copy_hex_m->Index = 7;
				this->copy_hex_m->Text = L"Copy &Hex Selection";
				this->copy_hex_m->Click += gcnew System::EventHandler(this, &winmain::copy_hex_m_Click);
				// 
				// copy_offset_m
				// 
				this->copy_offset_m->Index = 8;
				this->copy_offset_m->Text = L"Copy &Offset";
				this->copy_offset_m->Click += gcnew System::EventHandler(this, &winmain::copy_offset_m_Click);
				// 
				// copyas_m
				// 
				this->copyas_m->Index = 9;
				this->copyas_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(8) {
					this->c_m, this->csharp_m,
						this->python_m, this->java_m, this->pascal_m, this->perl_m, this->rust_m, this->vb_m
				});
				this->copyas_m->Text = L"Copy &As...";
				// 
				// c_m
				// 
				this->c_m->Index = 0;
				this->c_m->Text = L"C / C++";
				this->c_m->Click += gcnew System::EventHandler(this, &winmain::cpy_cpp_m_ctx_Click);
				// 
				// csharp_m
				// 
				this->csharp_m->Index = 1;
				this->csharp_m->Text = L"&C#";
				this->csharp_m->Click += gcnew System::EventHandler(this, &winmain::cpy_csharp_m_ctx_Click);
				// 
				// python_m
				// 
				this->python_m->Index = 2;
				this->python_m->Text = L"P&ython";
				this->python_m->Click += gcnew System::EventHandler(this, &winmain::cpy_python_m_ctx_Click);
				// 
				// java_m
				// 
				this->java_m->Index = 3;
				this->java_m->Text = L"&Java";
				this->java_m->Click += gcnew System::EventHandler(this, &winmain::cpy_java_m_ctx_Click);
				// 
				// pascal_m
				// 
				this->pascal_m->Index = 4;
				this->pascal_m->Text = L"Pa&scal";
				this->pascal_m->Click += gcnew System::EventHandler(this, &winmain::cpy_pascal_m_ctx_Click);
				// 
				// perl_m
				// 
				this->perl_m->Index = 5;
				this->perl_m->Text = L"&Perl";
				this->perl_m->Click += gcnew System::EventHandler(this, &winmain::cpy_perl_m_ctx_Click);
				// 
				// rust_m
				// 
				this->rust_m->Index = 6;
				this->rust_m->Text = L"&Rust";
				this->rust_m->Click += gcnew System::EventHandler(this, &winmain::cpy_rust_m_ctx_Click);
				// 
				// vb_m
				// 
				this->vb_m->Index = 7;
				this->vb_m->Text = L"&Visual Basic";
				this->vb_m->Click += gcnew System::EventHandler(this, &winmain::cpy_vb_m_ctx_Click);
				// 
				// menuItem9
				// 
				this->menuItem9->Index = 10;
				this->menuItem9->Text = L"-";
				// 
				// cut_hex_m
				// 
				this->cut_hex_m->Index = 11;
				this->cut_hex_m->Text = L"C&ut Hex Selection";
				this->cut_hex_m->Click += gcnew System::EventHandler(this, &winmain::cut_hex_m_Click);
				// 
				// cut_string_m
				// 
				this->cut_string_m->Index = 12;
				this->cut_string_m->Text = L"Cut String Sel&ection";
				this->cut_string_m->Click += gcnew System::EventHandler(this, &winmain::cut_string_m_Click);
				// 
				// seperator_m
				// 
				this->seperator_m->Index = 13;
				this->seperator_m->Text = L"-";
				// 
				// paste_string_m
				// 
				this->paste_string_m->Index = 14;
				this->paste_string_m->Text = L"&Paste String";
				this->paste_string_m->Click += gcnew System::EventHandler(this, &winmain::paste_string_m_Click);
				// 
				// paste_hex_m
				// 
				this->paste_hex_m->Index = 15;
				this->paste_hex_m->Text = L"Paste He&x";
				this->paste_hex_m->Click += gcnew System::EventHandler(this, &winmain::paste_hex_m_Click);
				// 
				// tools_m
				// 
				this->tools_m->Index = 2;
				this->tools_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
					this->find_m, this->find_n_m,
						this->find_p_m
				});
				this->tools_m->Text = L"&Tools";
				// 
				// find_m
				// 
				this->find_m->Index = 0;
				this->find_m->Text = L"&Find...";
				this->find_m->Click += gcnew System::EventHandler(this, &winmain::find_m_Click);
				// 
				// find_n_m
				// 
				this->find_n_m->Enabled = false;
				this->find_n_m->Index = 1;
				this->find_n_m->Text = L"Find &Next";
				// 
				// find_p_m
				// 
				this->find_p_m->Enabled = false;
				this->find_p_m->Index = 2;
				this->find_p_m->Text = L"Find &Previous";
				// 
				// options_m
				// 
				this->options_m->Index = 3;
				this->options_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->settings_m });
				this->options_m->Text = L"&Options";
				// 
				// settings_m
				// 
				this->settings_m->Index = 0;
				this->settings_m->Text = L"&Settings...";
				// 
				// help_m
				// 
				this->help_m->Index = 4;
				this->help_m->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) { this->about_m });
				this->help_m->Text = L"&Help";
				// 
				// about_m
				// 
				this->about_m->Index = 0;
				this->about_m->Text = L"&About...";
				this->about_m->Click += gcnew System::EventHandler(this, &winmain::about_m_Click);
				// 
				// main_stat
				// 
				this->main_stat->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->main_stat->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
					this->tslbl_offset, this->ts_seperator_1,
						this->tslbl_block, this->ts_seperator_2, this->tslbl_length, this->tslbl_modified, this->tslbl_textmode
				});
				this->main_stat->Location = System::Drawing::Point(0, 686);
				this->main_stat->Name = L"main_stat";
				this->main_stat->Size = System::Drawing::Size(1350, 22);
				this->main_stat->TabIndex = 0;
				// 
				// tslbl_offset
				// 
				this->tslbl_offset->AutoToolTip = true;
				this->tslbl_offset->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
					static_cast<System::Int32>(static_cast<System::Byte>(36)));
				this->tslbl_offset->BorderStyle = System::Windows::Forms::Border3DStyle::Etched;
				this->tslbl_offset->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->tslbl_offset->DoubleClickEnabled = true;
				this->tslbl_offset->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->tslbl_offset->Name = L"tslbl_offset";
				this->tslbl_offset->Size = System::Drawing::Size(99, 17);
				this->tslbl_offset->Text = L"offset (h) : Invalid";
				this->tslbl_offset->ToolTipText = L"The offset in hexadecimal, from the beginning of the file";
				this->tslbl_offset->DoubleClick += gcnew System::EventHandler(this, &winmain::tslbl_offset_DoubleClick);
				// 
				// ts_seperator_1
				// 
				this->ts_seperator_1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->ts_seperator_1->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->ts_seperator_1->Name = L"ts_seperator_1";
				this->ts_seperator_1->Size = System::Drawing::Size(46, 17);
				this->ts_seperator_1->Text = L"      |      ";
				// 
				// tslbl_block
				// 
				this->tslbl_block->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->tslbl_block->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->tslbl_block->Name = L"tslbl_block";
				this->tslbl_block->Size = System::Drawing::Size(63, 17);
				this->tslbl_block->Text = L"Block (h) : ";
				this->tslbl_block->ToolTipText = L"The beginning address of the selected block - ending address";
				// 
				// ts_seperator_2
				// 
				this->ts_seperator_2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->ts_seperator_2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->ts_seperator_2->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->ts_seperator_2->Name = L"ts_seperator_2";
				this->ts_seperator_2->Size = System::Drawing::Size(46, 17);
				this->ts_seperator_2->Text = L"      |      ";
				// 
				// tslbl_length
				// 
				this->tslbl_length->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->tslbl_length->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->tslbl_length->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->tslbl_length->Name = L"tslbl_length";
				this->tslbl_length->Size = System::Drawing::Size(71, 17);
				this->tslbl_length->Text = L"Length (h) : ";
				this->tslbl_length->ToolTipText = L"The length of the selected block in bytes, represented in hexadecimal";
				// 
				// tslbl_modified
				// 
				this->tslbl_modified->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->tslbl_modified->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->tslbl_modified->Name = L"tslbl_modified";
				this->tslbl_modified->Size = System::Drawing::Size(489, 17);
				this->tslbl_modified->Spring = true;
				this->tslbl_modified->Text = L"* Modified *";
				this->tslbl_modified->ToolTipText = L"Modified document";
				// 
				// tslbl_textmode
				// 
				this->tslbl_textmode->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->tslbl_textmode->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->tslbl_textmode->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->tslbl_textmode->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
				this->tslbl_textmode->Name = L"tslbl_textmode";
				this->tslbl_textmode->Size = System::Drawing::Size(489, 17);
				this->tslbl_textmode->Spring = true;
				this->tslbl_textmode->Text = L"Overwrite";
				this->tslbl_textmode->ToolTipText = L"Text mode for the current document";
				// 
				// main_vist
				// 
				this->main_vist->ContainerControl = this;
				// 
				// tab_main
				// 
				this->tab_main->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tab_main->ImageList = this->main_image_tb_list;
				this->tab_main->Location = System::Drawing::Point(0, 0);
				this->tab_main->Name = L"tab_main";
				this->tab_main->SelectedIndex = 0;
				this->tab_main->ShowToolTips = true;
				this->tab_main->Size = System::Drawing::Size(920, 457);
				this->tab_main->TabIndex = 1;
				this->tab_main->SelectedIndexChanged += gcnew System::EventHandler(this, &winmain::tab_main_SelectedIndexChanged);
				// 
				// main_image_tb_list
				// 
				this->main_image_tb_list->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
				this->main_image_tb_list->ImageSize = System::Drawing::Size(16, 16);
				this->main_image_tb_list->TransparentColor = System::Drawing::Color::Transparent;
				// 
				// sc_tab_data
				// 
				this->sc_tab_data->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_tab_data->IsSplitterFixed = true;
				this->sc_tab_data->Location = System::Drawing::Point(0, 0);
				this->sc_tab_data->Name = L"sc_tab_data";
				// 
				// sc_tab_data.Panel1
				// 
				this->sc_tab_data->Panel1->Controls->Add(this->sc_main_doc_enc);
				// 
				// sc_tab_data.Panel2
				// 
				this->sc_tab_data->Panel2->Controls->Add(this->sc_info_main);
				this->sc_tab_data->Size = System::Drawing::Size(1350, 483);
				this->sc_tab_data->SplitterDistance = 920;
				this->sc_tab_data->SplitterWidth = 1;
				this->sc_tab_data->TabIndex = 2;
				// 
				// sc_main_doc_enc
				// 
				this->sc_main_doc_enc->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_main_doc_enc->IsSplitterFixed = true;
				this->sc_main_doc_enc->Location = System::Drawing::Point(0, 0);
				this->sc_main_doc_enc->Name = L"sc_main_doc_enc";
				this->sc_main_doc_enc->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_main_doc_enc.Panel1
				// 
				this->sc_main_doc_enc->Panel1->Controls->Add(this->main_cb_encoding);
				// 
				// sc_main_doc_enc.Panel2
				// 
				this->sc_main_doc_enc->Panel2->Controls->Add(this->tab_main);
				this->sc_main_doc_enc->Size = System::Drawing::Size(920, 483);
				this->sc_main_doc_enc->SplitterDistance = 25;
				this->sc_main_doc_enc->SplitterWidth = 1;
				this->sc_main_doc_enc->TabIndex = 2;
				// 
				// main_cb_encoding
				// 
				this->main_cb_encoding->Dock = System::Windows::Forms::DockStyle::Fill;
				this->main_cb_encoding->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				this->main_cb_encoding->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->main_cb_encoding->FormattingEnabled = true;
				this->main_cb_encoding->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
					L"ANSI ( Codepage 1252 )", L"ASCII ( Codepage 437 )",
						L"EBCDIC ( Codepage 500 )"
				});
				this->main_cb_encoding->Location = System::Drawing::Point(0, 0);
				this->main_cb_encoding->Name = L"main_cb_encoding";
				this->main_cb_encoding->Size = System::Drawing::Size(920, 21);
				this->main_cb_encoding->TabIndex = 0;
				this->main_cb_encoding->SelectedIndexChanged += gcnew System::EventHandler(this, &winmain::main_cb_encoding_SelectedIndexChanged);
				// 
				// sc_info_main
				// 
				this->sc_info_main->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_info_main->IsSplitterFixed = true;
				this->sc_info_main->Location = System::Drawing::Point(0, 0);
				this->sc_info_main->Name = L"sc_info_main";
				this->sc_info_main->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_info_main.Panel1
				// 
				this->sc_info_main->Panel1->Controls->Add(this->main_size_info_tab);
				// 
				// sc_info_main.Panel2
				// 
				this->sc_info_main->Panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->sc_info_main->Panel2->Controls->Add(this->main_group_value);
				this->sc_info_main->Size = System::Drawing::Size(429, 483);
				this->sc_info_main->SplitterDistance = 440;
				this->sc_info_main->SplitterWidth = 1;
				this->sc_info_main->TabIndex = 0;
				// 
				// main_size_info_tab
				// 
				this->main_size_info_tab->Controls->Add(this->main_type_view_tab);
				this->main_size_info_tab->Controls->Add(this->main_hash_view_tab);
				this->main_size_info_tab->Dock = System::Windows::Forms::DockStyle::Fill;
				this->main_size_info_tab->ImageList = this->main_image_tb_list;
				this->main_size_info_tab->Location = System::Drawing::Point(0, 0);
				this->main_size_info_tab->Name = L"main_size_info_tab";
				this->main_size_info_tab->SelectedIndex = 0;
				this->main_size_info_tab->Size = System::Drawing::Size(429, 440);
				this->main_size_info_tab->TabIndex = 0;
				// 
				// main_type_view_tab
				// 
				this->main_type_view_tab->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->main_type_view_tab->Location = System::Drawing::Point(4, 23);
				this->main_type_view_tab->Name = L"main_type_view_tab";
				this->main_type_view_tab->Padding = System::Windows::Forms::Padding(3);
				this->main_type_view_tab->Size = System::Drawing::Size(421, 413);
				this->main_type_view_tab->TabIndex = 0;
				this->main_type_view_tab->Text = L"Type View";
				// 
				// main_hash_view_tab
				// 
				this->main_hash_view_tab->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->main_hash_view_tab->Controls->Add(this->sc_main_hash);
				this->main_hash_view_tab->Location = System::Drawing::Point(4, 23);
				this->main_hash_view_tab->Name = L"main_hash_view_tab";
				this->main_hash_view_tab->Padding = System::Windows::Forms::Padding(3);
				this->main_hash_view_tab->Size = System::Drawing::Size(421, 413);
				this->main_hash_view_tab->TabIndex = 1;
				this->main_hash_view_tab->Text = L"Hash View";
				// 
				// sc_main_hash
				// 
				this->sc_main_hash->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_main_hash->IsSplitterFixed = true;
				this->sc_main_hash->Location = System::Drawing::Point(3, 3);
				this->sc_main_hash->Name = L"sc_main_hash";
				this->sc_main_hash->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_main_hash.Panel1
				// 
				this->sc_main_hash->Panel1->Controls->Add(this->sc_list_rb_hash);
				// 
				// sc_main_hash.Panel2
				// 
				this->sc_main_hash->Panel2->Controls->Add(this->sc_buttons_hash);
				this->sc_main_hash->Size = System::Drawing::Size(415, 407);
				this->sc_main_hash->SplitterDistance = 376;
				this->sc_main_hash->SplitterWidth = 1;
				this->sc_main_hash->TabIndex = 1;
				// 
				// sc_list_rb_hash
				// 
				this->sc_list_rb_hash->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_list_rb_hash->IsSplitterFixed = true;
				this->sc_list_rb_hash->Location = System::Drawing::Point(0, 0);
				this->sc_list_rb_hash->Name = L"sc_list_rb_hash";
				this->sc_list_rb_hash->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_list_rb_hash.Panel1
				// 
				this->sc_list_rb_hash->Panel1->Controls->Add(this->lv_main_hash);
				// 
				// sc_list_rb_hash.Panel2
				// 
				this->sc_list_rb_hash->Panel2->Controls->Add(this->grp_main_hash);
				this->sc_list_rb_hash->Size = System::Drawing::Size(415, 376);
				this->sc_list_rb_hash->SplitterDistance = 344;
				this->sc_list_rb_hash->TabIndex = 1;
				// 
				// lv_main_hash
				// 
				this->lv_main_hash->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
					this->columnHeader7,
						this->columnHeader8
				});
				this->lv_main_hash->Dock = System::Windows::Forms::DockStyle::Fill;
				this->lv_main_hash->FullRowSelect = true;
				this->lv_main_hash->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
				this->lv_main_hash->HideSelection = false;
				this->lv_main_hash->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(6) {
					listViewItem1, listViewItem2,
						listViewItem3, listViewItem4, listViewItem5, listViewItem6
				});
				this->lv_main_hash->Location = System::Drawing::Point(0, 0);
				this->lv_main_hash->MultiSelect = false;
				this->lv_main_hash->Name = L"lv_main_hash";
				this->lv_main_hash->Size = System::Drawing::Size(415, 344);
				this->lv_main_hash->TabIndex = 0;
				this->lv_main_hash->UseCompatibleStateImageBehavior = false;
				this->lv_main_hash->View = System::Windows::Forms::View::Details;
				this->lv_main_hash->SelectedIndexChanged += gcnew System::EventHandler(this, &winmain::lv_main_hash_SelectedIndexChanged);
				// 
				// columnHeader7
				// 
				this->columnHeader7->Text = L"Type";
				this->columnHeader7->Width = 127;
				// 
				// columnHeader8
				// 
				this->columnHeader8->Text = L"Value";
				this->columnHeader8->Width = 283;
				// 
				// grp_main_hash
				// 
				this->grp_main_hash->BackColor = System::Drawing::SystemColors::Control;
				this->grp_main_hash->Controls->Add(this->rb_whole_hash);
				this->grp_main_hash->Controls->Add(this->rb_current_hash);
				this->grp_main_hash->Dock = System::Windows::Forms::DockStyle::Fill;
				this->grp_main_hash->Location = System::Drawing::Point(0, 0);
				this->grp_main_hash->Name = L"grp_main_hash";
				this->grp_main_hash->Size = System::Drawing::Size(415, 28);
				this->grp_main_hash->TabIndex = 0;
				this->grp_main_hash->TabStop = false;
				this->grp_main_hash->Text = L"Compute For:";
				// 
				// rb_whole_hash
				// 
				this->rb_whole_hash->AutoSize = true;
				this->rb_whole_hash->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->rb_whole_hash->Location = System::Drawing::Point(229, 7);
				this->rb_whole_hash->Name = L"rb_whole_hash";
				this->rb_whole_hash->Size = System::Drawing::Size(77, 18);
				this->rb_whole_hash->TabIndex = 2;
				this->rb_whole_hash->Text = L"E&ntire File";
				this->rb_whole_hash->UseVisualStyleBackColor = true;
				this->rb_whole_hash->CheckedChanged += gcnew System::EventHandler(this, &winmain::rb_whole_hash_CheckedChanged);
				// 
				// rb_current_hash
				// 
				this->rb_current_hash->AutoSize = true;
				this->rb_current_hash->Checked = true;
				this->rb_current_hash->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->rb_current_hash->Location = System::Drawing::Point(78, 7);
				this->rb_current_hash->Name = L"rb_current_hash";
				this->rb_current_hash->Size = System::Drawing::Size(112, 18);
				this->rb_current_hash->TabIndex = 1;
				this->rb_current_hash->TabStop = true;
				this->rb_current_hash->Text = L"Cur&rent Selection";
				this->rb_current_hash->UseVisualStyleBackColor = true;
				this->rb_current_hash->CheckedChanged += gcnew System::EventHandler(this, &winmain::rb_current_hash_CheckedChanged);
				// 
				// sc_buttons_hash
				// 
				this->sc_buttons_hash->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_buttons_hash->Location = System::Drawing::Point(0, 0);
				this->sc_buttons_hash->Name = L"sc_buttons_hash";
				// 
				// sc_buttons_hash.Panel1
				// 
				this->sc_buttons_hash->Panel1->Controls->Add(this->btn_compute_all);
				this->sc_buttons_hash->Panel1MinSize = 16;
				// 
				// sc_buttons_hash.Panel2
				// 
				this->sc_buttons_hash->Panel2->Controls->Add(this->btn_compute);
				this->sc_buttons_hash->Panel2MinSize = 16;
				this->sc_buttons_hash->Size = System::Drawing::Size(415, 30);
				this->sc_buttons_hash->SplitterDistance = 199;
				this->sc_buttons_hash->SplitterWidth = 1;
				this->sc_buttons_hash->TabIndex = 0;
				// 
				// btn_compute_all
				// 
				this->btn_compute_all->Dock = System::Windows::Forms::DockStyle::Fill;
				this->btn_compute_all->Enabled = false;
				this->btn_compute_all->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->btn_compute_all->Location = System::Drawing::Point(0, 0);
				this->btn_compute_all->Name = L"btn_compute_all";
				this->btn_compute_all->Size = System::Drawing::Size(199, 30);
				this->btn_compute_all->TabIndex = 0;
				this->btn_compute_all->Text = L"Compute &All";
				this->btn_compute_all->UseVisualStyleBackColor = true;
				this->btn_compute_all->Click += gcnew System::EventHandler(this, &winmain::btn_compute_all_Click);
				// 
				// btn_compute
				// 
				this->btn_compute->Dock = System::Windows::Forms::DockStyle::Fill;
				this->btn_compute->Enabled = false;
				this->btn_compute->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->btn_compute->Location = System::Drawing::Point(0, 0);
				this->btn_compute->Name = L"btn_compute";
				this->btn_compute->Size = System::Drawing::Size(215, 30);
				this->btn_compute->TabIndex = 1;
				this->btn_compute->Text = L"&Compute";
				this->btn_compute->UseVisualStyleBackColor = true;
				this->btn_compute->Click += gcnew System::EventHandler(this, &winmain::btn_compute_Click);
				// 
				// main_group_value
				// 
				this->main_group_value->BackColor = System::Drawing::SystemColors::Control;
				this->main_group_value->Controls->Add(this->main_cb_hex);
				this->main_group_value->Controls->Add(this->main_big_endian_rb);
				this->main_group_value->Controls->Add(this->main_little_endian_rb);
				this->main_group_value->Dock = System::Windows::Forms::DockStyle::Fill;
				this->main_group_value->ForeColor = System::Drawing::SystemColors::ControlLightLight;
				this->main_group_value->Location = System::Drawing::Point(0, 0);
				this->main_group_value->Name = L"main_group_value";
				this->main_group_value->Size = System::Drawing::Size(429, 42);
				this->main_group_value->TabIndex = 3;
				this->main_group_value->TabStop = false;
				this->main_group_value->Text = L"Endianness";
				// 
				// main_cb_hex
				// 
				this->main_cb_hex->AutoSize = true;
				this->main_cb_hex->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->main_cb_hex->Location = System::Drawing::Point(372, 8);
				this->main_cb_hex->Name = L"main_cb_hex";
				this->main_cb_hex->Size = System::Drawing::Size(51, 18);
				this->main_cb_hex->TabIndex = 3;
				this->main_cb_hex->Text = L"Hex";
				this->main_cb_hex->UseVisualStyleBackColor = true;
				this->main_cb_hex->CheckedChanged += gcnew System::EventHandler(this, &winmain::main_cb_hex_CheckedChanged);
				// 
				// main_big_endian_rb
				// 
				this->main_big_endian_rb->AutoSize = true;
				this->main_big_endian_rb->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->main_big_endian_rb->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
					static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
				this->main_big_endian_rb->Location = System::Drawing::Point(266, 8);
				this->main_big_endian_rb->Name = L"main_big_endian_rb";
				this->main_big_endian_rb->Size = System::Drawing::Size(82, 18);
				this->main_big_endian_rb->TabIndex = 2;
				this->main_big_endian_rb->TabStop = true;
				this->main_big_endian_rb->Text = L"Big Endian";
				this->main_big_endian_rb->UseVisualStyleBackColor = true;
				this->main_big_endian_rb->CheckedChanged += gcnew System::EventHandler(this, &winmain::main_big_endian_rb_CheckedChanged);
				// 
				// main_little_endian_rb
				// 
				this->main_little_endian_rb->AutoSize = true;
				this->main_little_endian_rb->Checked = true;
				this->main_little_endian_rb->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->main_little_endian_rb->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
					static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
				this->main_little_endian_rb->Location = System::Drawing::Point(108, 8);
				this->main_little_endian_rb->Name = L"main_little_endian_rb";
				this->main_little_endian_rb->Size = System::Drawing::Size(89, 18);
				this->main_little_endian_rb->TabIndex = 0;
				this->main_little_endian_rb->TabStop = true;
				this->main_little_endian_rb->Text = L"Little Endian";
				this->main_little_endian_rb->UseVisualStyleBackColor = true;
				this->main_little_endian_rb->CheckedChanged += gcnew System::EventHandler(this, &winmain::main_little_endian_rb_CheckedChanged);
				// 
				// sc_main
				// 
				this->sc_main->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->sc_main->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_main->IsSplitterFixed = true;
				this->sc_main->Location = System::Drawing::Point(0, 28);
				this->sc_main->Name = L"sc_main";
				this->sc_main->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_main.Panel1
				// 
				this->sc_main->Panel1->Controls->Add(this->sc_tab_data);
				// 
				// sc_main.Panel2
				// 
				this->sc_main->Panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->sc_main->Panel2->Controls->Add(this->sc_disasm_main);
				this->sc_main->Size = System::Drawing::Size(1350, 658);
				this->sc_main->SplitterDistance = 483;
				this->sc_main->SplitterWidth = 1;
				this->sc_main->TabIndex = 3;
				// 
				// sc_disasm_main
				// 
				this->sc_disasm_main->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_disasm_main->IsSplitterFixed = true;
				this->sc_disasm_main->Location = System::Drawing::Point(0, 0);
				this->sc_disasm_main->Name = L"sc_disasm_main";
				// 
				// sc_disasm_main.Panel1
				// 
				this->sc_disasm_main->Panel1->Controls->Add(this->tab_main_data);
				// 
				// sc_disasm_main.Panel2
				// 
				this->sc_disasm_main->Panel2->Controls->Add(this->tab_main_stack);
				this->sc_disasm_main->Size = System::Drawing::Size(1350, 174);
				this->sc_disasm_main->SplitterDistance = 919;
				this->sc_disasm_main->SplitterWidth = 1;
				this->sc_disasm_main->TabIndex = 0;
				// 
				// tab_main_data
				// 
				this->tab_main_data->Controls->Add(this->tb_page_graph);
				this->tab_main_data->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tab_main_data->ImageList = this->main_image_tb_list;
				this->tab_main_data->Location = System::Drawing::Point(0, 0);
				this->tab_main_data->Name = L"tab_main_data";
				this->tab_main_data->SelectedIndex = 0;
				this->tab_main_data->Size = System::Drawing::Size(919, 174);
				this->tab_main_data->TabIndex = 0;
				// 
				// tb_page_graph
				// 
				this->tb_page_graph->Location = System::Drawing::Point(4, 23);
				this->tb_page_graph->Name = L"tb_page_graph";
				this->tb_page_graph->Padding = System::Windows::Forms::Padding(3);
				this->tb_page_graph->Size = System::Drawing::Size(911, 147);
				this->tb_page_graph->TabIndex = 0;
				this->tb_page_graph->Text = L"Data Graph";
				this->tb_page_graph->UseVisualStyleBackColor = true;
				// 
				// tab_main_stack
				// 
				this->tab_main_stack->Controls->Add(this->tb_page_stack);
				this->tab_main_stack->Controls->Add(this->tb_page_log);
				this->tab_main_stack->Dock = System::Windows::Forms::DockStyle::Fill;
				this->tab_main_stack->ImageList = this->main_image_tb_list;
				this->tab_main_stack->Location = System::Drawing::Point(0, 0);
				this->tab_main_stack->Name = L"tab_main_stack";
				this->tab_main_stack->SelectedIndex = 0;
				this->tab_main_stack->Size = System::Drawing::Size(430, 174);
				this->tab_main_stack->TabIndex = 0;
				// 
				// tb_page_stack
				// 
				this->tb_page_stack->Controls->Add(this->sc_disasm_stack_main);
				this->tb_page_stack->Location = System::Drawing::Point(4, 23);
				this->tb_page_stack->Name = L"tb_page_stack";
				this->tb_page_stack->Padding = System::Windows::Forms::Padding(3);
				this->tb_page_stack->Size = System::Drawing::Size(422, 147);
				this->tb_page_stack->TabIndex = 0;
				this->tb_page_stack->Text = L"Stack";
				this->tb_page_stack->UseVisualStyleBackColor = true;
				// 
				// sc_disasm_stack_main
				// 
				this->sc_disasm_stack_main->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_disasm_stack_main->IsSplitterFixed = true;
				this->sc_disasm_stack_main->Location = System::Drawing::Point(3, 3);
				this->sc_disasm_stack_main->Name = L"sc_disasm_stack_main";
				// 
				// sc_disasm_stack_main.Panel1
				// 
				this->sc_disasm_stack_main->Panel1->Controls->Add(this->sc_disasm_stack_change);
				// 
				// sc_disasm_stack_main.Panel2
				// 
				this->sc_disasm_stack_main->Panel2->Controls->Add(this->sc_disasm_stack_undone);
				this->sc_disasm_stack_main->Size = System::Drawing::Size(416, 141);
				this->sc_disasm_stack_main->SplitterDistance = 200;
				this->sc_disasm_stack_main->TabIndex = 0;
				// 
				// sc_disasm_stack_change
				// 
				this->sc_disasm_stack_change->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_disasm_stack_change->IsSplitterFixed = true;
				this->sc_disasm_stack_change->Location = System::Drawing::Point(0, 0);
				this->sc_disasm_stack_change->Name = L"sc_disasm_stack_change";
				this->sc_disasm_stack_change->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_disasm_stack_change.Panel1
				// 
				this->sc_disasm_stack_change->Panel1->Controls->Add(this->lbl_disasm_stack_undo);
				this->sc_disasm_stack_change->Panel1MinSize = 16;
				// 
				// sc_disasm_stack_change.Panel2
				// 
				this->sc_disasm_stack_change->Panel2->Controls->Add(this->lv_main_undo);
				this->sc_disasm_stack_change->Size = System::Drawing::Size(200, 141);
				this->sc_disasm_stack_change->SplitterDistance = 25;
				this->sc_disasm_stack_change->SplitterWidth = 1;
				this->sc_disasm_stack_change->TabIndex = 0;
				// 
				// lbl_disasm_stack_undo
				// 
				this->lbl_disasm_stack_undo->AutoSize = true;
				this->lbl_disasm_stack_undo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->lbl_disasm_stack_undo->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->lbl_disasm_stack_undo->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->lbl_disasm_stack_undo->Location = System::Drawing::Point(46, 6);
				this->lbl_disasm_stack_undo->Name = L"lbl_disasm_stack_undo";
				this->lbl_disasm_stack_undo->Size = System::Drawing::Size(98, 13);
				this->lbl_disasm_stack_undo->TabIndex = 1;
				this->lbl_disasm_stack_undo->Text = L"Write (Undo) Stack";
				// 
				// lv_main_undo
				// 
				this->lv_main_undo->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
					this->columnHeader1,
						this->columnHeader2, this->columnHeader3
				});
				this->lv_main_undo->Dock = System::Windows::Forms::DockStyle::Fill;
				this->lv_main_undo->FullRowSelect = true;
				this->lv_main_undo->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
				this->lv_main_undo->HideSelection = false;
				this->lv_main_undo->Location = System::Drawing::Point(0, 0);
				this->lv_main_undo->MultiSelect = false;
				this->lv_main_undo->Name = L"lv_main_undo";
				this->lv_main_undo->Size = System::Drawing::Size(200, 115);
				this->lv_main_undo->SmallImageList = this->main_image_tb_list;
				this->lv_main_undo->TabIndex = 0;
				this->lv_main_undo->UseCompatibleStateImageBehavior = false;
				this->lv_main_undo->View = System::Windows::Forms::View::Details;
				// 
				// columnHeader1
				// 
				this->columnHeader1->Text = L"Type";
				this->columnHeader1->Width = 72;
				// 
				// columnHeader2
				// 
				this->columnHeader2->Text = L"Offset";
				this->columnHeader2->Width = 62;
				// 
				// columnHeader3
				// 
				this->columnHeader3->Text = L"Size";
				this->columnHeader3->Width = 69;
				// 
				// sc_disasm_stack_undone
				// 
				this->sc_disasm_stack_undone->Dock = System::Windows::Forms::DockStyle::Fill;
				this->sc_disasm_stack_undone->IsSplitterFixed = true;
				this->sc_disasm_stack_undone->Location = System::Drawing::Point(0, 0);
				this->sc_disasm_stack_undone->Name = L"sc_disasm_stack_undone";
				this->sc_disasm_stack_undone->Orientation = System::Windows::Forms::Orientation::Horizontal;
				// 
				// sc_disasm_stack_undone.Panel1
				// 
				this->sc_disasm_stack_undone->Panel1->Controls->Add(this->lbl_disasm_stack_redo);
				this->sc_disasm_stack_undone->Panel1MinSize = 16;
				// 
				// sc_disasm_stack_undone.Panel2
				// 
				this->sc_disasm_stack_undone->Panel2->Controls->Add(this->lv_main_redo);
				this->sc_disasm_stack_undone->Size = System::Drawing::Size(212, 141);
				this->sc_disasm_stack_undone->SplitterDistance = 25;
				this->sc_disasm_stack_undone->SplitterWidth = 1;
				this->sc_disasm_stack_undone->TabIndex = 0;
				// 
				// lbl_disasm_stack_redo
				// 
				this->lbl_disasm_stack_redo->AutoSize = true;
				this->lbl_disasm_stack_redo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->lbl_disasm_stack_redo->FlatStyle = System::Windows::Forms::FlatStyle::System;
				this->lbl_disasm_stack_redo->ForeColor = System::Drawing::Color::WhiteSmoke;
				this->lbl_disasm_stack_redo->Location = System::Drawing::Point(53, 6);
				this->lbl_disasm_stack_redo->Name = L"lbl_disasm_stack_redo";
				this->lbl_disasm_stack_redo->Size = System::Drawing::Size(109, 13);
				this->lbl_disasm_stack_redo->TabIndex = 0;
				this->lbl_disasm_stack_redo->Text = L"Unwrite (Redo) Stack";
				// 
				// lv_main_redo
				// 
				this->lv_main_redo->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
					this->columnHeader4,
						this->columnHeader5, this->columnHeader6
				});
				this->lv_main_redo->Dock = System::Windows::Forms::DockStyle::Fill;
				this->lv_main_redo->FullRowSelect = true;
				this->lv_main_redo->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
				this->lv_main_redo->HideSelection = false;
				this->lv_main_redo->Location = System::Drawing::Point(0, 0);
				this->lv_main_redo->MultiSelect = false;
				this->lv_main_redo->Name = L"lv_main_redo";
				this->lv_main_redo->Size = System::Drawing::Size(212, 115);
				this->lv_main_redo->SmallImageList = this->main_image_tb_list;
				this->lv_main_redo->TabIndex = 1;
				this->lv_main_redo->UseCompatibleStateImageBehavior = false;
				this->lv_main_redo->View = System::Windows::Forms::View::Details;
				// 
				// columnHeader4
				// 
				this->columnHeader4->Text = L"Type";
				this->columnHeader4->Width = 73;
				// 
				// columnHeader5
				// 
				this->columnHeader5->Text = L"Offset";
				this->columnHeader5->Width = 71;
				// 
				// columnHeader6
				// 
				this->columnHeader6->Text = L"Size";
				this->columnHeader6->Width = 69;
				// 
				// tb_page_log
				// 
				this->tb_page_log->Controls->Add(this->rtb_log);
				this->tb_page_log->Location = System::Drawing::Point(4, 23);
				this->tb_page_log->Name = L"tb_page_log";
				this->tb_page_log->Padding = System::Windows::Forms::Padding(3);
				this->tb_page_log->Size = System::Drawing::Size(422, 147);
				this->tb_page_log->TabIndex = 1;
				this->tb_page_log->Text = L"Log";
				this->tb_page_log->UseVisualStyleBackColor = true;
				// 
				// rtb_log
				// 
				this->rtb_log->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->rtb_log->Dock = System::Windows::Forms::DockStyle::Fill;
				this->rtb_log->Font = (gcnew System::Drawing::Font(L"Courier New", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				this->rtb_log->ForeColor = System::Drawing::SystemColors::InfoText;
				this->rtb_log->Location = System::Drawing::Point(3, 3);
				this->rtb_log->Name = L"rtb_log";
				this->rtb_log->ReadOnly = true;
				this->rtb_log->Size = System::Drawing::Size(416, 141);
				this->rtb_log->TabIndex = 0;
				this->rtb_log->Text = L"";
				// 
				// main_tb
				// 
				this->main_tb->Buttons->AddRange(gcnew cli::array< System::Windows::Forms::ToolBarButton^  >(17) {
					this->tb_btn_new, this->toolBarButton1,
						this->tb_btn_open, this->toolBarButton2, this->tb_btn_save, this->tb_btn_saveas, this->toolBarButton3, this->tb_btn_jump, this->tb_btn_select_block,
						this->toolBarButton6, this->tb_btn_copy_string, this->tb_btn_copy_hex, this->toolBarButton4, this->tb_btn_paste_string, this->tb_btn_paste_hex,
						this->toolBarButton5, this->tb_btn_insert
				});
				this->main_tb->ButtonSize = System::Drawing::Size(32, 32);
				this->main_tb->DropDownArrows = true;
				this->main_tb->ImageList = this->main_image_tb_list;
				this->main_tb->Location = System::Drawing::Point(0, 0);
				this->main_tb->Name = L"main_tb";
				this->main_tb->ShowToolTips = true;
				this->main_tb->Size = System::Drawing::Size(1350, 28);
				this->main_tb->TabIndex = 4;
				this->main_tb->ButtonClick += gcnew System::Windows::Forms::ToolBarButtonClickEventHandler(this, &winmain::main_tb_ButtonClick);
				// 
				// tb_btn_new
				// 
				this->tb_btn_new->Name = L"tb_btn_new";
				this->tb_btn_new->ToolTipText = L"Creates a blank document";
				// 
				// toolBarButton1
				// 
				this->toolBarButton1->Name = L"toolBarButton1";
				this->toolBarButton1->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_open
				// 
				this->tb_btn_open->Name = L"tb_btn_open";
				this->tb_btn_open->ToolTipText = L"Open a new file from disk";
				// 
				// toolBarButton2
				// 
				this->toolBarButton2->Name = L"toolBarButton2";
				this->toolBarButton2->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_save
				// 
				this->tb_btn_save->Enabled = false;
				this->tb_btn_save->Name = L"tb_btn_save";
				this->tb_btn_save->ToolTipText = L"Save the currently opened document to disk";
				// 
				// tb_btn_saveas
				// 
				this->tb_btn_saveas->Name = L"tb_btn_saveas";
				this->tb_btn_saveas->ToolTipText = L"Save the document to a seperate file ";
				// 
				// toolBarButton3
				// 
				this->toolBarButton3->Name = L"toolBarButton3";
				this->toolBarButton3->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_jump
				// 
				this->tb_btn_jump->Name = L"tb_btn_jump";
				this->tb_btn_jump->ToolTipText = L"Goto an address within the document";
				// 
				// tb_btn_select_block
				// 
				this->tb_btn_select_block->Name = L"tb_btn_select_block";
				this->tb_btn_select_block->ToolTipText = L"Select a block of data within the document";
				// 
				// toolBarButton6
				// 
				this->toolBarButton6->Name = L"toolBarButton6";
				this->toolBarButton6->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_copy_string
				// 
				this->tb_btn_copy_string->Name = L"tb_btn_copy_string";
				this->tb_btn_copy_string->ToolTipText = L"Copy the selection as a string encoded in the selected format";
				// 
				// tb_btn_copy_hex
				// 
				this->tb_btn_copy_hex->Name = L"tb_btn_copy_hex";
				this->tb_btn_copy_hex->ToolTipText = L"Copy the current selection\'s hex representation";
				// 
				// toolBarButton4
				// 
				this->toolBarButton4->Name = L"toolBarButton4";
				this->toolBarButton4->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_paste_string
				// 
				this->tb_btn_paste_string->Name = L"tb_btn_paste_string";
				this->tb_btn_paste_string->ToolTipText = L"Paste clipboard contents as a string encoded in selected format";
				// 
				// tb_btn_paste_hex
				// 
				this->tb_btn_paste_hex->Name = L"tb_btn_paste_hex";
				this->tb_btn_paste_hex->ToolTipText = L"Paste contents of the clipboard as hex data";
				// 
				// toolBarButton5
				// 
				this->toolBarButton5->Name = L"toolBarButton5";
				this->toolBarButton5->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
				// 
				// tb_btn_insert
				// 
				this->tb_btn_insert->Name = L"tb_btn_insert";
				this->tb_btn_insert->Style = System::Windows::Forms::ToolBarButtonStyle::ToggleButton;
				this->tb_btn_insert->ToolTipText = L"Toggle the insert mode of the active document";
				// 
				// main_document_context_menu
				// 
				this->main_document_context_menu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(16) {
					this->jmp_m_ctx,
						this->jmp_selection_ctx, this->menuItem7, this->select_all_ctx, this->select_block_ctx, this->menuItem1, this->copy_string_ctx,
						this->copy_hex_ctx, this->copy_offset_ctx, this->copyas_ctx, this->menuItem12, this->cut_hex_ctx, this->cut_string_ctx, this->menuItem2,
						this->paste_string_ctx, this->paste_hex_ctx
				});
				this->main_document_context_menu->Popup += gcnew System::EventHandler(this, &winmain::main_document_context_menu_Popup);
				// 
				// jmp_m_ctx
				// 
				this->jmp_m_ctx->Index = 0;
				this->jmp_m_ctx->Text = L"&Jump To Address...";
				this->jmp_m_ctx->Click += gcnew System::EventHandler(this, &winmain::tslbl_offset_DoubleClick);
				// 
				// jmp_selection_ctx
				// 
				this->jmp_selection_ctx->Index = 1;
				this->jmp_selection_ctx->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
					this->word_ctx, this->dword_ctx,
						this->qword_ctx
				});
				this->jmp_selection_ctx->Text = L"Jump To Selec&tion...";
				this->jmp_selection_ctx->Popup += gcnew System::EventHandler(this, &winmain::jmp_selection_ctx_Popup);
				// 
				// word_ctx
				// 
				this->word_ctx->Index = 0;
				this->word_ctx->Text = L"&WORD Value";
				this->word_ctx->Click += gcnew System::EventHandler(this, &winmain::word_m_Click);
				// 
				// dword_ctx
				// 
				this->dword_ctx->Index = 1;
				this->dword_ctx->Text = L"&DWORD Value";
				this->dword_ctx->Click += gcnew System::EventHandler(this, &winmain::dword_m_Click);
				// 
				// qword_ctx
				// 
				this->qword_ctx->Index = 2;
				this->qword_ctx->Text = L"&QWORD Value";
				this->qword_ctx->Click += gcnew System::EventHandler(this, &winmain::qword_m_Click);
				// 
				// menuItem7
				// 
				this->menuItem7->Index = 2;
				this->menuItem7->Text = L"-";
				// 
				// select_all_ctx
				// 
				this->select_all_ctx->Index = 3;
				this->select_all_ctx->Text = L"Select Al&l";
				this->select_all_ctx->Click += gcnew System::EventHandler(this, &winmain::select_all_m_Click);
				// 
				// select_block_ctx
				// 
				this->select_block_ctx->Index = 4;
				this->select_block_ctx->Text = L"Select &Block...";
				this->select_block_ctx->Click += gcnew System::EventHandler(this, &winmain::select_block_m_Click);
				// 
				// menuItem1
				// 
				this->menuItem1->Index = 5;
				this->menuItem1->Text = L"-";
				// 
				// copy_string_ctx
				// 
				this->copy_string_ctx->Index = 6;
				this->copy_string_ctx->Text = L"Copy &String Selection";
				this->copy_string_ctx->Click += gcnew System::EventHandler(this, &winmain::copy_string_m_Click);
				// 
				// copy_hex_ctx
				// 
				this->copy_hex_ctx->Index = 7;
				this->copy_hex_ctx->Text = L"Copy H&ex Selection";
				this->copy_hex_ctx->Click += gcnew System::EventHandler(this, &winmain::copy_hex_m_Click);
				// 
				// copy_offset_ctx
				// 
				this->copy_offset_ctx->Index = 8;
				this->copy_offset_ctx->Text = L"Copy &Offset";
				this->copy_offset_ctx->Click += gcnew System::EventHandler(this, &winmain::copy_offset_m_Click);
				// 
				// copyas_ctx
				// 
				this->copyas_ctx->Index = 9;
				this->copyas_ctx->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(8) {
					this->cpy_cpp_m_ctx, this->cpy_csharp_m_ctx,
						this->cpy_python_m_ctx, this->cpy_java_m_ctx, this->cpy_pascal_m_ctx, this->cpy_perl_m_ctx, this->cpy_rust_m_ctx, this->cpy_vb_m_ctx
				});
				this->copyas_ctx->Text = L"Copy &As...";
				// 
				// cpy_cpp_m_ctx
				// 
				this->cpy_cpp_m_ctx->Index = 0;
				this->cpy_cpp_m_ctx->Text = L"C / C++";
				this->cpy_cpp_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_cpp_m_ctx_Click);
				// 
				// cpy_csharp_m_ctx
				// 
				this->cpy_csharp_m_ctx->Index = 1;
				this->cpy_csharp_m_ctx->Text = L"&C#";
				this->cpy_csharp_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_csharp_m_ctx_Click);
				// 
				// cpy_python_m_ctx
				// 
				this->cpy_python_m_ctx->Index = 2;
				this->cpy_python_m_ctx->Text = L"P&ython";
				this->cpy_python_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_python_m_ctx_Click);
				// 
				// cpy_java_m_ctx
				// 
				this->cpy_java_m_ctx->Index = 3;
				this->cpy_java_m_ctx->Text = L"&Java";
				this->cpy_java_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_java_m_ctx_Click);
				// 
				// cpy_pascal_m_ctx
				// 
				this->cpy_pascal_m_ctx->Index = 4;
				this->cpy_pascal_m_ctx->Text = L"Pa&scal";
				this->cpy_pascal_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_pascal_m_ctx_Click);
				// 
				// cpy_perl_m_ctx
				// 
				this->cpy_perl_m_ctx->Index = 5;
				this->cpy_perl_m_ctx->Text = L"&Perl";
				this->cpy_perl_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_perl_m_ctx_Click);
				// 
				// cpy_rust_m_ctx
				// 
				this->cpy_rust_m_ctx->Index = 6;
				this->cpy_rust_m_ctx->Text = L"&Rust";
				this->cpy_rust_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_rust_m_ctx_Click);
				// 
				// cpy_vb_m_ctx
				// 
				this->cpy_vb_m_ctx->Index = 7;
				this->cpy_vb_m_ctx->Text = L"&Visual Basic";
				this->cpy_vb_m_ctx->Click += gcnew System::EventHandler(this, &winmain::cpy_vb_m_ctx_Click);
				// 
				// menuItem12
				// 
				this->menuItem12->Index = 10;
				this->menuItem12->Text = L"-";
				// 
				// cut_hex_ctx
				// 
				this->cut_hex_ctx->Index = 11;
				this->cut_hex_ctx->Text = L"&Cut Hex Selection";
				this->cut_hex_ctx->Click += gcnew System::EventHandler(this, &winmain::cut_hex_m_Click);
				// 
				// cut_string_ctx
				// 
				this->cut_string_ctx->Index = 12;
				this->cut_string_ctx->Text = L"Cut String Sel&ection";
				this->cut_string_ctx->Click += gcnew System::EventHandler(this, &winmain::cut_string_m_Click);
				// 
				// menuItem2
				// 
				this->menuItem2->Index = 13;
				this->menuItem2->Text = L"-";
				// 
				// paste_string_ctx
				// 
				this->paste_string_ctx->Index = 14;
				this->paste_string_ctx->Text = L"&Paste String";
				this->paste_string_ctx->Click += gcnew System::EventHandler(this, &winmain::paste_string_m_Click);
				// 
				// paste_hex_ctx
				// 
				this->paste_hex_ctx->Index = 15;
				this->paste_hex_ctx->Text = L"Paste &Hex";
				this->paste_hex_ctx->Click += gcnew System::EventHandler(this, &winmain::paste_hex_m_Click);
				// 
				// main_edit_context_menu
				// 
				this->main_edit_context_menu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(5) {
					this->edit_ctx,
						this->menuItem10, this->copy_ctx, this->menuItem11, this->paste_ctx
				});
				this->main_edit_context_menu->Popup += gcnew System::EventHandler(this, &winmain::main_edit_context_menu_Popup);
				// 
				// edit_ctx
				// 
				this->edit_ctx->Index = 0;
				this->edit_ctx->Text = L"&Edit";
				this->edit_ctx->Click += gcnew System::EventHandler(this, &winmain::edit_ctx_Click);
				// 
				// menuItem10
				// 
				this->menuItem10->Index = 1;
				this->menuItem10->Text = L"-";
				// 
				// copy_ctx
				// 
				this->copy_ctx->Index = 2;
				this->copy_ctx->Text = L"&Copy Value";
				this->copy_ctx->Click += gcnew System::EventHandler(this, &winmain::copy_ctx_Click);
				// 
				// menuItem11
				// 
				this->menuItem11->Index = 3;
				this->menuItem11->Text = L"-";
				// 
				// paste_ctx
				// 
				this->paste_ctx->Index = 4;
				this->paste_ctx->Text = L"&Paste Value";
				this->paste_ctx->Click += gcnew System::EventHandler(this, &winmain::paste_ctx_Click);
				// 
				// main_graph_ctx
				// 
				this->main_graph_ctx->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {
					this->select_ctx, this->menuItem13,
						this->entire_ctx
				});
				this->main_graph_ctx->Popup += gcnew System::EventHandler(this, &winmain::main_graph_ctx_Popup);
				this->main_graph_ctx->Collapse += gcnew System::EventHandler(this, &winmain::main_graph_ctx_Collapse);
				// 
				// select_ctx
				// 
				this->select_ctx->Index = 0;
				this->select_ctx->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) { this->beginning_ctx, this->end_ctx });
				this->select_ctx->Text = L"&Jump to...";
				// 
				// beginning_ctx
				// 
				this->beginning_ctx->Index = 0;
				this->beginning_ctx->Text = L"&Beginning of block";
				this->beginning_ctx->Click += gcnew System::EventHandler(this, &winmain::beginning_ctx_Click);
				// 
				// end_ctx
				// 
				this->end_ctx->Index = 1;
				this->end_ctx->Text = L"&End of block";
				this->end_ctx->Click += gcnew System::EventHandler(this, &winmain::end_ctx_Click);
				// 
				// menuItem13
				// 
				this->menuItem13->Index = 1;
				this->menuItem13->Text = L"-";
				// 
				// entire_ctx
				// 
				this->entire_ctx->Index = 2;
				this->entire_ctx->Text = L"&Select block";
				this->entire_ctx->Click += gcnew System::EventHandler(this, &winmain::entire_ctx_Click);
				// 
				// winmain
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(35)), static_cast<System::Int32>(static_cast<System::Byte>(35)),
					static_cast<System::Int32>(static_cast<System::Byte>(35)));
				this->ClientSize = System::Drawing::Size(1350, 708);
				this->Controls->Add(this->sc_main);
				this->Controls->Add(this->main_stat);
				this->Controls->Add(this->main_tb);
				this->DoubleBuffered = true;
				this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				this->Menu = this->main_menu;
				this->MinimumSize = System::Drawing::Size(800, 600);
				this->Name = L"winmain";
				this->Text = L"hexasm";
				this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
				this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &winmain::winmain_FormClosing);
				this->Load += gcnew System::EventHandler(this, &winmain::winmain_Load);
				this->SizeChanged += gcnew System::EventHandler(this, &winmain::winmain_SizeChanged);
				this->main_stat->ResumeLayout(false);
				this->main_stat->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->main_vist))->EndInit();
				this->sc_tab_data->Panel1->ResumeLayout(false);
				this->sc_tab_data->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_tab_data))->EndInit();
				this->sc_tab_data->ResumeLayout(false);
				this->sc_main_doc_enc->Panel1->ResumeLayout(false);
				this->sc_main_doc_enc->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main_doc_enc))->EndInit();
				this->sc_main_doc_enc->ResumeLayout(false);
				this->sc_info_main->Panel1->ResumeLayout(false);
				this->sc_info_main->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_info_main))->EndInit();
				this->sc_info_main->ResumeLayout(false);
				this->main_size_info_tab->ResumeLayout(false);
				this->main_hash_view_tab->ResumeLayout(false);
				this->sc_main_hash->Panel1->ResumeLayout(false);
				this->sc_main_hash->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main_hash))->EndInit();
				this->sc_main_hash->ResumeLayout(false);
				this->sc_list_rb_hash->Panel1->ResumeLayout(false);
				this->sc_list_rb_hash->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_list_rb_hash))->EndInit();
				this->sc_list_rb_hash->ResumeLayout(false);
				this->grp_main_hash->ResumeLayout(false);
				this->grp_main_hash->PerformLayout();
				this->sc_buttons_hash->Panel1->ResumeLayout(false);
				this->sc_buttons_hash->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_buttons_hash))->EndInit();
				this->sc_buttons_hash->ResumeLayout(false);
				this->main_group_value->ResumeLayout(false);
				this->main_group_value->PerformLayout();
				this->sc_main->Panel1->ResumeLayout(false);
				this->sc_main->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_main))->EndInit();
				this->sc_main->ResumeLayout(false);
				this->sc_disasm_main->Panel1->ResumeLayout(false);
				this->sc_disasm_main->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_main))->EndInit();
				this->sc_disasm_main->ResumeLayout(false);
				this->tab_main_data->ResumeLayout(false);
				this->tab_main_stack->ResumeLayout(false);
				this->tb_page_stack->ResumeLayout(false);
				this->sc_disasm_stack_main->Panel1->ResumeLayout(false);
				this->sc_disasm_stack_main->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_main))->EndInit();
				this->sc_disasm_stack_main->ResumeLayout(false);
				this->sc_disasm_stack_change->Panel1->ResumeLayout(false);
				this->sc_disasm_stack_change->Panel1->PerformLayout();
				this->sc_disasm_stack_change->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_change))->EndInit();
				this->sc_disasm_stack_change->ResumeLayout(false);
				this->sc_disasm_stack_undone->Panel1->ResumeLayout(false);
				this->sc_disasm_stack_undone->Panel1->PerformLayout();
				this->sc_disasm_stack_undone->Panel2->ResumeLayout(false);
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sc_disasm_stack_undone))->EndInit();
				this->sc_disasm_stack_undone->ResumeLayout(false);
				this->tb_page_log->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion

#pragma region Data Interpreter

		static String^ invalid_ = "Invalid";

		private: inline void __clrcall interpret_editor_index(uint index) {

			if (!global::hex_union_instances->Count || index < 0)
				return;

			auto% control_h = global::hex_union_instances[index];

			String^ bit_s = invalid_;
			String^ byte_s = invalid_;
			String^ chari_s = invalid_;
			String^ ushort_s = invalid_;
			String^ short_s = invalid_;
			String^ uint_s = invalid_;
			String^ int_s = invalid_;
			String^ uint64_s = invalid_;
			String^ int64_s = invalid_;
			String^ float_s = invalid_;
			String^ double_s = invalid_;
			String^ char_s = invalid_;
			String^ wchar_s = invalid_;
			String^ guid_s = invalid_;
			String^ dasm16_s = invalid_;
			String^ dasm32_s = invalid_;
			String^ dasm64_s = invalid_;
			String^ dasmA32_s = invalid_;
			String^ dasmA64_s = invalid_;
			String^ dasm_ppc_be = invalid_;
			String^ dasm_ppc_le = invalid_;
			String^ dasm_m32_s = invalid_;
			String^ dasm_m64_s = invalid_;

			if (!control_h->ByteProvider->Length)
				goto assign_strings;

			if (control_h->ByteProvider->Length <= control_h->SelectionStart)
				goto assign_strings;

			try {
				auto bytes_to_read = control_h->ByteProvider->Length - control_h->SelectionStart;
				
				if (!bytes_to_read)
					goto assign_strings;

				auto disasm_extract_byte_count = bytes_to_read >= global::disasm_t_block_size ? global::disasm_t_block_size : bytes_to_read;

				auto buffer_disasm = util::read_bytes_from_provider(control_h->ByteProvider, control_h->SelectionStart, disasm_extract_byte_count);
				pin_ptr<Byte> buffer_disasm_ = &buffer_disasm[0];

				Byte* pointer_dasm = buffer_disasm_;

				auto instruction_16 = global::disasm_handle->disasm_16_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_16.success)
					goto disasm_instruction_32;

				dasm16_s = gcnew System::String(instruction_16.instruction.mnemonic) + " " + gcnew System::String(instruction_16.instruction.op_str);

			disasm_instruction_32:

				auto instruction_32 = global::disasm_handle->disasm_32_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_32.success)
					goto disasm_instruction_64;
				
				dasm32_s = gcnew System::String(instruction_32.instruction.mnemonic) + " " + gcnew System::String(instruction_32.instruction.op_str);

			disasm_instruction_64:

				auto instruction_64 = global::disasm_handle->disasm_64_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_64.success)
					goto disasm_instruction_a32;

				dasm64_s = gcnew System::String(instruction_64.instruction.mnemonic) + " " + gcnew System::String(instruction_64.instruction.op_str);

			disasm_instruction_a32:

				auto instruction_a32 = global::disasm_handle->disasm_a32_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_a32.success)
					goto disasm_instruction_a64;

				dasmA32_s = gcnew System::String(instruction_a32.instruction.mnemonic) + " " + gcnew System::String(instruction_a32.instruction.op_str);

			disasm_instruction_a64:

				auto instruction_a64 = global::disasm_handle->disasm_a64_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_a64.success)
					goto disasm_instruction_ppc_be;

				dasmA64_s = gcnew System::String(instruction_a64.instruction.mnemonic) + " " + gcnew System::String(instruction_a64.instruction.op_str);


			disasm_instruction_ppc_be:

				auto instruction_ppc_be = global::disasm_handle->disasm_ppc_be_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_ppc_be.success)
					goto disasm_instruction_ppc_le;

				dasm_ppc_be = gcnew System::String(instruction_ppc_be.instruction.mnemonic) + " " + gcnew System::String(instruction_ppc_be.instruction.op_str);

			disasm_instruction_ppc_le:

				auto instruction_ppc_le = global::disasm_handle->disasm_ppc_le_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_ppc_le.success)
					goto disasm_instruction_m32;

				dasm_ppc_le = gcnew System::String(instruction_ppc_le.instruction.mnemonic) + " " + gcnew System::String(instruction_ppc_le.instruction.op_str);

			disasm_instruction_m32:

				auto instruction_m32 = global::disasm_handle->disasm_m32_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_m32.success)
					goto disasm_instruction_m64;

				dasm_m32_s = gcnew System::String(instruction_m32.instruction.mnemonic) + " " + gcnew System::String(instruction_m32.instruction.op_str);

			disasm_instruction_m64:

				auto instruction_m64 = global::disasm_handle->disasm_m64_single(pointer_dasm, disasm_extract_byte_count, control_h->SelectionStart);

				if (!instruction_m64.success)
					goto interpret_type_data;

				dasm_m64_s = gcnew System::String(instruction_m64.instruction.mnemonic) + " " + gcnew System::String(instruction_m64.instruction.op_str);

				pointer_dasm = nullptr;
				buffer_disasm_ = nullptr;
				delete buffer_disasm;
			}
			catch (std::exception& except) { throw except; }

		interpret_type_data:

			auto buffer = control_h->ByteProvider->ReadByte(control_h->SelectionStart);

			bit_s = gcnew String( ::native::t_to_bits(buffer).c_str() );

			byte_s = global::is_type_view_hexadecimal ? buffer.ToString("X2") : buffer.ToString();
			chari_s = global::is_type_view_hexadecimal ? static_cast<signed char>(buffer).ToString("X2") : static_cast<signed char>(buffer).ToString();

			char_s = gcnew String(static_cast<char>(buffer), 1);

			if (control_h->ByteProvider->Length < control_h->SelectionStart + sizeof(UInt16))
				goto assign_strings;

			auto buffer_word = util::read_bytes_from_provider(control_h->ByteProvider, control_h->SelectionStart, sizeof(UInt16));

			if (global::type_endian_mode == endian_mode::big)
				Array::Reverse(buffer_word);

			pin_ptr<Byte> buffer_word_ = &buffer_word[0];

			Byte* pointer_w = buffer_word_;

			ushort_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<unsigned short*>(pointer_w)).ToString("X4") : (*reinterpret_cast<unsigned short*>(pointer_w)).ToString();
			short_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<signed short*>(pointer_w)).ToString("X4") : (*reinterpret_cast<signed short*>(pointer_w)).ToString();

			wchar_s = gcnew String(*reinterpret_cast<wchar_t*>(pointer_w), 1);

			pointer_w = nullptr;
			buffer_word_ = nullptr;
			delete buffer_word;

			if (control_h->ByteProvider->Length < control_h->SelectionStart + sizeof(UInt32))
				goto assign_strings;

			auto buffer_dword = util::read_bytes_from_provider(control_h->ByteProvider, control_h->SelectionStart, sizeof(UInt32));

			if (global::type_endian_mode == endian_mode::big)
				Array::Reverse(buffer_dword);

			pin_ptr<Byte> buffer_dword_ = &buffer_dword[0];

			Byte* pointer_dw = buffer_dword_;

			uint_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<unsigned int*>(pointer_dw)).ToString("X8") : (*reinterpret_cast<unsigned int*>(pointer_dw)).ToString();
			int_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<signed int*>(pointer_dw)).ToString("X8") : (*reinterpret_cast<signed int*>(pointer_dw)).ToString();
			float_s = (*reinterpret_cast<float*>(pointer_dw)).ToString();

			pointer_dw = nullptr;
			buffer_dword_ = nullptr;
			delete buffer_dword;

			if (control_h->ByteProvider->Length < control_h->SelectionStart + sizeof(UInt64))
				goto assign_strings;

			auto buffer_qword = util::read_bytes_from_provider(control_h->ByteProvider, control_h->SelectionStart, sizeof(UInt64));

			if (global::type_endian_mode == endian_mode::big)
				Array::Reverse(buffer_qword);

			pin_ptr<Byte> buffer_qword_ = &buffer_qword[0];

			Byte* pointer_qw = buffer_qword_;

			uint64_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<UInt64*>(pointer_qw)).ToString("X16") : (*reinterpret_cast<UInt64*>(pointer_qw)).ToString();
			int64_s = global::is_type_view_hexadecimal ? (*reinterpret_cast<Int64*>(pointer_qw)).ToString("X16") : (*reinterpret_cast<Int64*>(pointer_qw)).ToString();
			double_s = (*reinterpret_cast<double*>(pointer_qw)).ToString();

			pointer_qw = nullptr;
			buffer_qword_ = nullptr;
			delete buffer_qword;

		assign_strings:

			if (main_type_lv->Items->Count) {

				main_type_lv->Items[0]->SubItems[1]->Text = bit_s;
				main_type_lv->Items[1]->SubItems[1]->Text = byte_s;
				main_type_lv->Items[2]->SubItems[1]->Text = chari_s;
				main_type_lv->Items[3]->SubItems[1]->Text = ushort_s;
				main_type_lv->Items[4]->SubItems[1]->Text = short_s;
				main_type_lv->Items[5]->SubItems[1]->Text = uint_s;
				main_type_lv->Items[6]->SubItems[1]->Text = int_s;
				main_type_lv->Items[7]->SubItems[1]->Text = uint64_s;
				main_type_lv->Items[8]->SubItems[1]->Text = int64_s;
				main_type_lv->Items[9]->SubItems[1]->Text = float_s;
				main_type_lv->Items[10]->SubItems[1]->Text = double_s;
				main_type_lv->Items[11]->SubItems[1]->Text = char_s;
				main_type_lv->Items[12]->SubItems[1]->Text = wchar_s;
				main_type_lv->Items[13]->SubItems[1]->Text = dasm16_s;
				main_type_lv->Items[14]->SubItems[1]->Text = dasm32_s;
				main_type_lv->Items[15]->SubItems[1]->Text = dasm64_s;
				main_type_lv->Items[16]->SubItems[1]->Text = dasmA32_s;
				main_type_lv->Items[17]->SubItems[1]->Text = dasmA64_s;
				main_type_lv->Items[18]->SubItems[1]->Text = dasm_ppc_be;
				main_type_lv->Items[19]->SubItems[1]->Text = dasm_ppc_le;
				main_type_lv->Items[20]->SubItems[1]->Text = dasm_m32_s;
				main_type_lv->Items[21]->SubItems[1]->Text = dasm_m64_s;

				delete bit_s;
				delete byte_s;
				delete chari_s;
				delete ushort_s;
				delete short_s;
				delete uint_s;
				delete int_s;
				delete uint64_s;
				delete int64_s;
				delete float_s;
				delete double_s;
				delete char_s;
				delete wchar_s;
				delete dasm16_s;
				delete dasm32_s;
				delete dasm64_s;
				delete dasmA32_s;
				delete dasmA64_s;
				delete dasm_ppc_be;
				delete dasm_ppc_le;
				delete dasm_m32_s;
				delete dasm_m64_s;

			}

			auto selection_start = control_h->SelectionStart;

			auto block_size = control_h->SelectionLength;

			auto block_end_offset = selection_start + block_size;

			tslbl_offset->Text = "Offset (h) : " + selection_start.ToString("X16");

			tslbl_block->Text = "Block (h) : " + selection_start.ToString("X16") + " - " + block_end_offset.ToString("X16");

			tslbl_length->Text = "Length (h) : " + block_size.ToString("X16");

			tslbl_modified->Visible = control_h->ByteProvider->HasChanges();

			bool selection = (block_size > 1 && block_end_offset != selection_start);

			tslbl_block->Visible = selection;
			tslbl_length->Visible = selection;
			ts_seperator_1->Visible = selection;
			ts_seperator_2->Visible = selection;
			
			tslbl_textmode->Text = control_h->InsertActive ? "Insert" : "Overwrite";

			tslbl_textmode->Visible = true;
			
		}

#pragma endregion

#pragma region Helper Methods

		private: __forceinline HexBox^ __clrcall generate_hex_editor(bool is_blank) {
			HexBox^ hex_box_o = gcnew HexBox();

			hex_box_o->Font = global::hex_editor_font;

			hex_box_o->BackColor = global::hex_background_color;
			hex_box_o->offset_fore_color = global::hex_offset_columns_color;
			hex_box_o->ForeColor = global::hex_text_foreground;
			hex_box_o->header_title_color = global::hex_headers_color;
			hex_box_o->SelectionForeColor = global::hex_foreground_selection_color;
			hex_box_o->SelectionBackColor = global::hex_background_selection_color;
			hex_box_o->GroupSize = 2;

			hex_box_o->LineInfoVisible = true;
			hex_box_o->ColumnInfoVisible = true;
			hex_box_o->StringViewVisible = true;

			if(is_blank)
				hex_box_o->ByteProvider = gcnew DynamicByteProvider(gcnew List<Byte>());

			hex_box_o->Dock = DockStyle::Fill;
			hex_box_o->VScrollBarVisible = true;
			hex_box_o->UseFixedBytesPerLine = true;

			hex_box_o->ContextMenu = main_document_context_menu;
			
			hex_box_o->KeyDown += gcnew KeyEventHandler(this, &winmain::hex_OnKeyDown);

			return hex_box_o;
		}

		private: inline System::Void __clrcall instantiate_globals() {

			progress_window_->update_progress("Setting window properties...", 35);

			tslbl_block->Visible = false;
			tslbl_length->Visible = false;
			tslbl_modified->Visible = false;
			tslbl_textmode->Visible = false;

			ts_seperator_1->Visible = false;
			ts_seperator_2->Visible = false;

			main_cb_encoding->SelectedIndex = 0;
			main_cb_encoding->Enabled = tab_main->TabPages->Count ? true : false;

			progress_window_->update_progress("Initializing disassembler...", 55);
			log_append("Initializing disassembler...", true);

			global::disasm_handle = new native::disasm_t();
			global::disasm_t_block_size = static_cast<unsigned int>(0x10); // maximum data to read for disassembly view

			global::type_endian_mode = endian_mode::little;
			global::is_type_view_hexadecimal = false;

			global::hasher = gcnew hash_g(gcnew hash_g::HashProgressCallback(this, &winmain::cumbersome_hash_callback));

			progress_window_->update_progress("Parsing UI icons...", 80);
			log_append("Parsing UI icons...", true);

			//global::is_theme_dark = util::is_color_dark(System::Drawing::SystemColors::Menu);

			global::is_theme_dark = util::is_theme_dark(this->Handle);

			// could minimize this with ternary operator
			if (global::is_theme_dark) {
				global::img_binary_document = util::image_from_native_array(&document_binary_16x16_white, sizeof(document_binary_16x16_white));
				global::img_document = util::image_from_native_array(&document_16x16_white, sizeof(document_16x16_white));
				global::img_document_delete = util::image_from_native_array(&document_delete_16x16_white, sizeof(document_delete_16x16_white));
				global::img_document_edit = util::image_from_native_array(&document_edit_16x16_white, sizeof(document_edit_16x16_white));
				global::img_document_new = util::image_from_native_array(&document_new_16x16_white, sizeof(document_new_16x16_white));
				global::img_document_plus = util::image_from_native_array(&folder_open_16x16_white, sizeof(folder_open_16x16_white));
				global::img_document_minus = util::image_from_native_array(&document_minus_16x16_white, sizeof(document_minus_16x16_white));
				global::img_document_export = util::image_from_native_array(&document_export_16x16_white, sizeof(document_export_16x16_white));
				global::img_document_hash = util::image_from_native_array(&document_hash_16x16_white, sizeof(document_hash_16x16_white));
				global::img_document_lines = util::image_from_native_array(&document_lines_16x16_white, sizeof(document_lines_16x16_white));
				global::img_search = util::image_from_native_array(&search_16x16_white, sizeof(search_16x16_white));
				global::img_search_next = util::image_from_native_array(&search_next_16x16_white, sizeof(search_next_16x16_white));
				global::img_search_back = util::image_from_native_array(&search_back_16x16_white, sizeof(search_back_16x16_white));
				global::img_aob = util::image_from_native_array(&aob_16x16_white, sizeof(aob_16x16_white));
				global::img_hex = util::image_from_native_array(&hex_16x16_white, sizeof(hex_16x16_white));
				global::img_string = util::image_from_native_array(&string_16x16_white, sizeof(string_16x16_white));
				global::img_float = util::image_from_native_array(&float_16x16_white, sizeof(float_16x16_white));
				global::img_integer = util::image_from_native_array(&integer_16x16_white, sizeof(integer_16x16_white));
				global::img_stack = util::image_from_native_array(&stack_16x16_white, sizeof(stack_16x16_white));
				global::img_type = util::image_from_native_array(&type_16x16_white, sizeof(type_16x16_white));
				global::bar_chart = util::image_from_native_array(&bar_chart_16x16_white, sizeof(bar_chart_16x16_white));
				global::img_insert = util::image_from_native_array(&insert_16x16_white, sizeof(insert_16x16_white));
				global::img_edit = util::image_from_native_array(&edit_16x16_white, sizeof(edit_16x16_white));
				global::img_write_hex = util::image_from_native_array(&write_hex_single_16x16_white, sizeof(write_hex_single_16x16_white));
				global::img_block_start = util::image_from_native_array(&block_start_16x16_white, sizeof(block_start_16x16_white));
				global::img_block_end = util::image_from_native_array(&block_end_16x16_white, sizeof(block_end_16x16_white));
				global::img_block_whole = util::image_from_native_array(&block_whole_16x16_white, sizeof(block_whole_16x16_white));
				global::img_block_ins = util::image_from_native_array(&block_insert_16x16_white, sizeof(block_insert_16x16_white));
				global::img_block_del = util::image_from_native_array(&block_delete_16x16_white, sizeof(block_delete_16x16_white));
				global::img_undo = util::image_from_native_array(&redo_16x16_white, sizeof(redo_16x16_white));
				global::img_redo = util::image_from_native_array(&undo_16x16_white, sizeof(undo_16x16_white));
				global::img_copy_offset = util::image_from_native_array(&copy_offset_16x16_white, sizeof(copy_offset_16x16_white));
				global::copy_plain = util::image_from_native_array(&copy_plain_16x16_white, sizeof(copy_plain_16x16_white));
				global::paste_plain = util::image_from_native_array(&paste_plain_16x16_white, sizeof(paste_plain_16x16_white));
				global::cut_hex = util::image_from_native_array(&cut_hex_16x16_white, sizeof(cut_hex_16x16_white));
				global::cut_string = util::image_from_native_array(&cut_string_16x16_white, sizeof(cut_string_16x16_white));
				global::img_copy_hex = util::image_from_native_array(&copy_hex_16x16_white, sizeof(copy_hex_16x16_white));
				global::img_copy_string = util::image_from_native_array(&copy_string_16x16_white, sizeof(copy_string_16x16_white));
				global::img_paste_string = util::image_from_native_array(&paste_string_16x16_white, sizeof(paste_string_16x16_white));
				global::img_paste_hex = util::image_from_native_array(&paste_hex_16x16_white, sizeof(paste_hex_16x16_white));
				global::img_select_block = util::image_from_native_array(&select_block_16x16_white, sizeof(select_block_16x16_white));
				global::img_edit_jmp = util::image_from_native_array(&edit_jump_16x16_white, sizeof(edit_jump_16x16_white));
				global::img_select_all = util::image_from_native_array(&select_all_16x16_white, sizeof(select_all_16x16_white));
				global::img_word = util::image_from_native_array(&word_16x16_white, sizeof(word_16x16_white));
				global::img_dword = util::image_from_native_array(&dword_16x16_white, sizeof(dword_16x16_white));
				global::img_qword = util::image_from_native_array(&qword_16x16_white, sizeof(qword_16x16_white));
				global::img_settings_cog = util::image_from_native_array(&settings_cog_16x16_white, sizeof(settings_cog_16x16_white));
				global::img_help_information = util::image_from_native_array(&help_information_16x16_white, sizeof(help_information_16x16_white));
				global::img_exit = util::image_from_native_array(&exit_16x16_white, sizeof(exit_16x16_white));
				global::img_save = util::image_from_native_array(&save_16x16_white, sizeof(save_16x16_white));
				global::img_save_as = util::image_from_native_array(&save_as_16x16_white, sizeof(save_as_16x16_white));
				global::img_save_all = util::image_from_native_array(&save_all_16x16_white, sizeof(save_all_16x16_white));
				global::img_c = util::image_from_native_array(&c_16x16_white, sizeof(c_16x16_white));
				global::img_cpp = util::image_from_native_array(&cpp_16x16_white, sizeof(cpp_16x16_white));
				global::img_java = util::image_from_native_array(&java_16x16_white, sizeof(java_16x16_white));
				global::img_python = util::image_from_native_array(&python_16x16_white, sizeof(python_16x16_white));
				global::img_csharp = util::image_from_native_array(&csharp_16x16_white, sizeof(csharp_16x16_white));
				global::img_perl = util::image_from_native_array(&perl_16x16_white, sizeof(perl_16x16_white));
				global::img_rust = util::image_from_native_array(&rust_16x16_white, sizeof(rust_16x16_white));
				global::img_vb = util::image_from_native_array(&vb_16x16_white, sizeof(vb_16x16_white));
				global::img_pascal = util::image_from_native_array(&pascal_16x16_white, sizeof(pascal_16x16_white));

				progress_window_->update_progress("", 85);
			}
			else {
				global::img_binary_document = util::image_from_native_array(&document_binary_16x16_black, sizeof(document_binary_16x16_black));
				global::img_document = util::image_from_native_array(&document_16x16_black, sizeof(document_16x16_black));
				global::img_document_delete = util::image_from_native_array(&document_delete_16x16_black, sizeof(document_delete_16x16_black));
				global::img_document_edit = util::image_from_native_array(&document_edit_16x16_black, sizeof(document_edit_16x16_black));
				global::img_document_new = util::image_from_native_array(&document_new_16x16_black, sizeof(document_new_16x16_black));
				global::img_document_plus = util::image_from_native_array(&folder_open_16x16_black, sizeof(folder_open_16x16_black));
				global::img_document_minus = util::image_from_native_array(&document_minus_16x16_black, sizeof(document_minus_16x16_black));
				global::img_document_export = util::image_from_native_array(&document_export_16x16_black, sizeof(document_export_16x16_black));
				global::img_document_hash = util::image_from_native_array(&document_hash_16x16_black, sizeof(document_hash_16x16_black));
				global::img_document_lines = util::image_from_native_array(&document_lines_16x16_black, sizeof(document_lines_16x16_black));
				global::img_search = util::image_from_native_array(&search_16x16_black, sizeof(search_16x16_black));
				global::img_search_next = util::image_from_native_array(&search_next_16x16_black, sizeof(search_next_16x16_black));
				global::img_search_back = util::image_from_native_array(&search_back_16x16_black, sizeof(search_back_16x16_black));
				global::img_aob = util::image_from_native_array(&aob_16x16_black, sizeof(aob_16x16_black));
				global::img_hex = util::image_from_native_array(&hex_16x16_black, sizeof(hex_16x16_black));
				global::img_string = util::image_from_native_array(&string_16x16_black, sizeof(string_16x16_black));
				global::img_float = util::image_from_native_array(&float_16x16_black, sizeof(float_16x16_black));
				global::img_integer = util::image_from_native_array(&integer_16x16_black, sizeof(integer_16x16_black));
				global::img_stack = util::image_from_native_array(&stack_16x16_black, sizeof(stack_16x16_black));
				global::img_type = util::image_from_native_array(&type_16x16_black, sizeof(type_16x16_black));
				global::bar_chart = util::image_from_native_array(&bar_chart_16x16_black, sizeof(bar_chart_16x16_black));
				global::img_insert = util::image_from_native_array(&insert_16x16_black, sizeof(insert_16x16_black));
				global::img_edit = util::image_from_native_array(&edit_16x16_black, sizeof(edit_16x16_black));
				global::img_write_hex = util::image_from_native_array(&write_hex_single_16x16_black, sizeof(write_hex_single_16x16_black));
				global::img_block_start = util::image_from_native_array(&block_start_16x16_black, sizeof(block_start_16x16_black));
				global::img_block_end = util::image_from_native_array(&block_end_16x16_black, sizeof(block_end_16x16_black));
				global::img_block_whole = util::image_from_native_array(&block_whole_16x16_black, sizeof(block_whole_16x16_black));
				global::img_block_ins = util::image_from_native_array(&block_insert_16x16_black, sizeof(block_insert_16x16_black));
				global::img_block_del = util::image_from_native_array(&block_delete_16x16_black, sizeof(block_delete_16x16_black));
				global::img_undo = util::image_from_native_array(&redo_16x16_black, sizeof(redo_16x16_black));
				global::img_redo = util::image_from_native_array(&undo_16x16_black, sizeof(undo_16x16_black));
				global::copy_plain = util::image_from_native_array(&copy_plain_16x16_black, sizeof(copy_plain_16x16_black));
				global::paste_plain = util::image_from_native_array(&paste_plain_16x16_black, sizeof(paste_plain_16x16_black));
				global::cut_hex = util::image_from_native_array(&cut_hex_16x16_black, sizeof(cut_hex_16x16_black));
				global::cut_string = util::image_from_native_array(&cut_string_16x16_black, sizeof(cut_string_16x16_black));
				global::img_copy_offset = util::image_from_native_array(&copy_offset_16x16_black, sizeof(copy_offset_16x16_black));
				global::img_copy_hex = util::image_from_native_array(&copy_hex_16x16_black, sizeof(copy_hex_16x16_black));
				global::img_copy_string = util::image_from_native_array(&copy_string_16x16_black, sizeof(copy_string_16x16_black));
				global::img_paste_string = util::image_from_native_array(&paste_string_16x16_black, sizeof(paste_string_16x16_black));
				global::img_paste_hex = util::image_from_native_array(&paste_hex_16x16_black, sizeof(paste_hex_16x16_black));
				global::img_edit_jmp = util::image_from_native_array(&edit_jump_16x16_black, sizeof(edit_jump_16x16_black));
				global::img_select_block = util::image_from_native_array(&select_block_16x16_black, sizeof(select_block_16x16_black));
				global::img_select_all = util::image_from_native_array(&select_all_16x16_black, sizeof(select_all_16x16_black));
				global::img_word = util::image_from_native_array(&word_16x16_black, sizeof(word_16x16_black));
				global::img_dword = util::image_from_native_array(&dword_16x16_black, sizeof(dword_16x16_black));
				global::img_qword = util::image_from_native_array(&qword_16x16_black, sizeof(qword_16x16_black));
				global::img_edit_jmp = util::image_from_native_array(&edit_jump_16x16_black, sizeof(edit_jump_16x16_black));
				global::img_settings_cog = util::image_from_native_array(&settings_cog_16x16_black, sizeof(settings_cog_16x16_black));
				global::img_help_information = util::image_from_native_array(&help_information_16x16_black, sizeof(help_information_16x16_black));
				global::img_exit = util::image_from_native_array(&exit_16x16_black, sizeof(exit_16x16_black));
				global::img_save = util::image_from_native_array(&save_16x16_black, sizeof(save_16x16_black));
				global::img_save_as = util::image_from_native_array(&save_as_16x16_black, sizeof(save_as_16x16_black));
				global::img_save_all = util::image_from_native_array(&save_all_16x16_black, sizeof(save_all_16x16_black));
				global::img_c = util::image_from_native_array(&c_16x16_black, sizeof(c_16x16_black));
				global::img_cpp = util::image_from_native_array(&cpp_16x16_black, sizeof(cpp_16x16_black));
				global::img_java = util::image_from_native_array(&java_16x16_black, sizeof(java_16x16_black));
				global::img_python = util::image_from_native_array(&python_16x16_black, sizeof(python_16x16_black));
				global::img_csharp = util::image_from_native_array(&csharp_16x16_black, sizeof(csharp_16x16_black));
				global::img_perl = util::image_from_native_array(&perl_16x16_black, sizeof(perl_16x16_black));
				global::img_rust = util::image_from_native_array(&rust_16x16_black, sizeof(rust_16x16_black));
				global::img_vb = util::image_from_native_array(&vb_16x16_black, sizeof(vb_16x16_black));
				global::img_pascal = util::image_from_native_array(&pascal_16x16_black, sizeof(pascal_16x16_black));

				progress_window_->update_progress("", 85);
			}


			main_image_tb_list->Images->Add(global::img_document_new);
			main_image_tb_list->Images->Add(global::img_document_plus);
			main_image_tb_list->Images->Add(global::img_save);
			main_image_tb_list->Images->Add(global::img_save_as);
			main_image_tb_list->Images->Add(global::img_edit_jmp);
			main_image_tb_list->Images->Add(global::img_select_block);
			main_image_tb_list->Images->Add(global::img_copy_string);
			main_image_tb_list->Images->Add(global::img_copy_hex);
			main_image_tb_list->Images->Add(global::img_paste_string);
			main_image_tb_list->Images->Add(global::img_paste_hex);
			main_image_tb_list->Images->Add(global::img_insert);
			// extra image below to avoid instancing new imagelist for single image for tabpages
			main_image_tb_list->Images->Add(global::img_binary_document);
			//extra images for undo / redo stack view
			main_image_tb_list->Images->Add(global::img_write_hex);
			main_image_tb_list->Images->Add(global::img_block_ins);
			main_image_tb_list->Images->Add(global::img_block_del);

			main_image_tb_list->Images->Add(global::img_document_hash);
			main_image_tb_list->Images->Add(global::img_document_lines);
			main_image_tb_list->Images->Add(global::img_stack); //17
			main_image_tb_list->Images->Add(global::img_type);
			main_image_tb_list->Images->Add(global::bar_chart);

			main_vist->SetImage(new_m, global::img_document_new);
			main_vist->SetImage(open_m, global::img_document_plus);
			main_vist->SetImage(save_m, global::img_save);
			main_vist->SetImage(save_all_m, global::img_save_all);
			main_vist->SetImage(saveas_m, global::img_save_as);
			main_vist->SetImage(close_m, global::img_document_minus);
			main_vist->SetImage(closeall_m, global::img_document_delete);
			main_vist->SetImage(exit_m, global::img_exit);
			main_vist->SetImage(settings_m, global::img_settings_cog);
			main_vist->SetImage(about_m, global::img_help_information);
			main_vist->SetImage(find_m, global::img_search);
			main_vist->SetImage(find_n_m, global::img_search_next);
			main_vist->SetImage(find_p_m, global::img_search_back);

			progress_window_->update_progress("", 90);

			/* EDIT menus */
			main_vist->SetImage(jmp_m_ctx, global::img_edit_jmp);
			main_vist->SetImage(jump_m, global::img_edit_jmp);
			main_vist->SetImage(word_ctx, global::img_word);
			main_vist->SetImage(word_m, global::img_word);
			main_vist->SetImage(dword_ctx, global::img_dword);
			main_vist->SetImage(dword_m, global::img_dword);
			main_vist->SetImage(qword_ctx, global::img_qword);
			main_vist->SetImage(qword_m, global::img_qword);
			main_vist->SetImage(copy_offset_ctx, global::img_copy_offset);
			main_vist->SetImage(copy_offset_m, global::img_copy_offset);
			main_vist->SetImage(cut_hex_ctx, global::cut_hex);
			main_vist->SetImage(cut_hex_m, global::cut_hex);
			main_vist->SetImage(cut_string_ctx, global::cut_string);
			main_vist->SetImage(cut_string_m, global::cut_string);
			main_vist->SetImage(copy_string_ctx, global::img_copy_string);
			main_vist->SetImage(copy_string_m, global::img_copy_string);
			main_vist->SetImage(copy_hex_ctx, global::img_copy_hex);
			main_vist->SetImage(copy_hex_m, global::img_copy_hex);
			main_vist->SetImage(paste_string_ctx, global::img_paste_string);
			main_vist->SetImage(paste_string_m, global::img_paste_string);
			main_vist->SetImage(paste_hex_ctx, global::img_paste_hex);
			main_vist->SetImage(paste_hex_m, global::img_paste_hex);
			main_vist->SetImage(select_all_ctx, global::img_select_all);
			main_vist->SetImage(select_all_m, global::img_select_all);
			main_vist->SetImage(select_block_ctx, global::img_select_block);
			main_vist->SetImage(select_block_m, global::img_select_block);

			main_vist->SetImage(cpy_cpp_m_ctx, global::img_cpp);
			main_vist->SetImage(c_m, global::img_cpp);
			main_vist->SetImage(cpy_java_m_ctx, global::img_java);
			main_vist->SetImage(java_m, global::img_java);
			main_vist->SetImage(cpy_python_m_ctx, global::img_python);
			main_vist->SetImage(python_m, global::img_python);
			main_vist->SetImage(cpy_csharp_m_ctx, global::img_csharp);
			main_vist->SetImage(csharp_m, global::img_csharp);
			main_vist->SetImage(cpy_perl_m_ctx, global::img_perl);
			main_vist->SetImage(perl_m, global::img_perl);
			main_vist->SetImage(cpy_rust_m_ctx, global::img_rust);
			main_vist->SetImage(rust_m, global::img_rust);
			main_vist->SetImage(cpy_vb_m_ctx, global::img_vb);
			main_vist->SetImage(vb_m, global::img_vb);
			main_vist->SetImage(cpy_pascal_m_ctx, global::img_pascal);
			main_vist->SetImage(pascal_m, global::img_pascal);

			main_vist->SetImage(edit_ctx, global::img_edit);
			main_vist->SetImage(copy_ctx, global::copy_plain);
			main_vist->SetImage(paste_ctx, global::paste_plain);

			main_vist->SetImage(beginning_ctx, global::img_block_start);
			main_vist->SetImage(end_ctx, global::img_block_end);
			main_vist->SetImage(entire_ctx, global::img_block_whole);

			tb_btn_new->ImageIndex = 0;
			tb_btn_new->Tag = static_cast<unsigned short>(TBTN_NEW);

			tb_btn_open->ImageIndex = 1;
			tb_btn_open->Tag = static_cast<unsigned short>(TBTN_OPEN);

			tb_btn_save->ImageIndex = 2;
			tb_btn_save->Tag = static_cast<unsigned short>(TBTN_SAVE);

			tb_btn_saveas->ImageIndex = 3;
			tb_btn_saveas->Tag = static_cast<unsigned short>(TBTN_SAVEAS);

			tb_btn_jump->ImageIndex = 4;
			tb_btn_jump->Tag = static_cast<unsigned short>(TBTN_JUMP);

			tb_btn_select_block->ImageIndex = 5;
			tb_btn_select_block->Tag = static_cast<unsigned short>(TBTN_BLOCK);

			tb_btn_copy_string->ImageIndex = 6;
			tb_btn_copy_string->Tag = static_cast<unsigned short>(TBTN_COPY_STRING);

			tb_btn_copy_hex->ImageIndex = 7;
			tb_btn_copy_hex->Tag = static_cast<unsigned short>(TBTN_COPY_HEX);

			tb_btn_paste_string->ImageIndex = 8;
			tb_btn_paste_string->Tag = static_cast<unsigned short>(TBTN_PASTE_STRING);

			tb_btn_paste_hex->ImageIndex = 9;
			tb_btn_paste_hex->Tag = static_cast<unsigned short>(TBTN_PASTE_HEX);

			tb_btn_insert->ImageIndex = 10;
			tb_btn_insert->Tag = static_cast<unsigned short>(TBTN_INSERT);

#pragma region Extended GUI Initialization

			progress_window_->update_progress("Building type view...", 95);
			log_append("Building type view...", true);

			main_type_lv = gcnew EditableListView();

			main_type_lv->Columns->Add("Type");
			main_type_lv->Columns->Add("Value");

			main_type_lv->Dock = DockStyle::Fill;
			main_type_lv->BackColor = global::hex_background_color;
			main_type_lv->ForeColor = global::hex_text_foreground;
			main_type_lv->HeaderStyle = ColumnHeaderStyle::Nonclickable;
		
			ListViewItem^ lvi_bin = gcnew ListViewItem("Binary");
			lvi_bin->SubItems->Add(invalid_);

			ListViewItem^ lvi_uint8 = gcnew ListViewItem("uint8_t");
			lvi_uint8->SubItems->Add(invalid_);

			ListViewItem^ lvi_int8 = gcnew ListViewItem("int8_t");
			lvi_int8->SubItems->Add(invalid_);

			ListViewItem^ lvi_uint16 = gcnew ListViewItem("uint16_t");
			lvi_uint16->SubItems->Add(invalid_);

			ListViewItem^ lvi_int16 = gcnew ListViewItem("int16_t");
			lvi_int16->SubItems->Add(invalid_);

			ListViewItem^ lvi_uint32 = gcnew ListViewItem("uint32_t");
			lvi_uint32->SubItems->Add(invalid_);

			ListViewItem^ lvi_int32 = gcnew ListViewItem("int32_t");
			lvi_int32->SubItems->Add(invalid_);

			ListViewItem^ lvi_uint64 = gcnew ListViewItem("uint64_t");
			lvi_uint64->SubItems->Add(invalid_);

			ListViewItem^ lvi_int64 = gcnew ListViewItem("int64_t");
			lvi_int64->SubItems->Add(invalid_);

			ListViewItem^ lvi_achar = gcnew ListViewItem("char8_t");
			lvi_achar->SubItems->Add(invalid_);

			ListViewItem^ lvi_wchar = gcnew ListViewItem("char16_t");
			lvi_wchar->SubItems->Add(invalid_);

			ListViewItem^ lvi_float = gcnew ListViewItem("float32 (Single)");
			lvi_float->SubItems->Add(invalid_);

			ListViewItem^ lvi_double = gcnew ListViewItem("float64 (Double)");
			lvi_double->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm16= gcnew ListViewItem("Disassembly (x86-16)");
			lvi_dasm16->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm32 = gcnew ListViewItem("Disassembly (x86-32)");
			lvi_dasm32->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm64 = gcnew ListViewItem("Disassembly (x86-64)");
			lvi_dasm64->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasmA32 = gcnew ListViewItem("Disassembly (ARM32)");
			lvi_dasmA32->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasmA64 = gcnew ListViewItem("Disassembly (ARM64)");
			lvi_dasmA64->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm_ppc_be = gcnew ListViewItem("Disassembly (PowerPC Big Endian)");
			lvi_dasm_ppc_be->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm_ppc_le = gcnew ListViewItem("Disassembly (PowerPC Little Endian)");
			lvi_dasm_ppc_le->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm_m32 = gcnew ListViewItem("Disassembly (MIPS32)");
			lvi_dasm_m32->SubItems->Add(invalid_);

			ListViewItem^ lvi_dasm_m64 = gcnew ListViewItem("Disassembly (MIPS64)");
			lvi_dasm_m64->SubItems->Add(invalid_);

			main_type_lv->Items->Add(lvi_bin);
			main_type_lv->Items->Add(lvi_uint8);
			main_type_lv->Items->Add(lvi_int8);
			main_type_lv->Items->Add(lvi_uint16);
			main_type_lv->Items->Add(lvi_int16);
			main_type_lv->Items->Add(lvi_uint32);
			main_type_lv->Items->Add(lvi_int32);
			main_type_lv->Items->Add(lvi_uint64);
			main_type_lv->Items->Add(lvi_int64);
			main_type_lv->Items->Add(lvi_float);
			main_type_lv->Items->Add(lvi_double);
			main_type_lv->Items->Add(lvi_achar);
			main_type_lv->Items->Add(lvi_wchar);
			main_type_lv->Items->Add(lvi_dasm16);
			main_type_lv->Items->Add(lvi_dasm32);
			main_type_lv->Items->Add(lvi_dasm64);
			main_type_lv->Items->Add(lvi_dasmA32);
			main_type_lv->Items->Add(lvi_dasmA64);
			main_type_lv->Items->Add(lvi_dasm_ppc_be);
			main_type_lv->Items->Add(lvi_dasm_ppc_le);
			main_type_lv->Items->Add(lvi_dasm_m32);
			main_type_lv->Items->Add(lvi_dasm_m64);

			progress_window_->update_progress("Finalizing UI setup...", 97);
			log_append("Finalizing UI setup...", true);

			main_hash_view_tab->ImageIndex = 15;
			main_type_view_tab->ImageIndex = 18;
			tb_page_stack->ImageIndex = 17;
			tb_page_log->ImageIndex = 16;
			tb_page_graph->ImageIndex = 19;

			main_type_lv->ContextMenu = main_edit_context_menu;

			main_type_lv->ProxySaveRequested += gcnew ProxySaveRequestedHandler(this, &winmain::type_update_requested);

			main_type_view_tab->Controls->Add(main_type_lv);

			gui::EditableListView::SetStyleListView(lv_main_undo);
			gui::EditableListView::SetStyleListView(lv_main_redo);
			gui::EditableListView::SetStyleListView(lv_main_hash);

			lv_main_hash->BackColor = global::hex_background_color;
			lv_main_hash->ForeColor = global::hex_text_foreground;

			lv_main_hash->ColumnWidthChanging += gcnew ColumnWidthChangingEventHandler(this, &winmain::on_listview_column_drag);

			progress_window_->update_progress("Done.", 99);
			log_append("Done.", true);

			rtb_log->Font = global::hex_editor_font;

			delete progress_window_;

			this->Show();

			this->OnEndResize(nullptr, nullptr);

			do_jump_menu_update();

			do_toolbar_update();

#pragma endregion
		
		}

		inline void __clrcall log_append(String^ _log_data, bool _success) {

			rtb_log->SelectionStart = rtb_log->Text->Length;
			if (_success) {
				rtb_log->AppendText("\r\n[+]");
			}
			else {
				rtb_log->AppendText("\r\n[-]");
			}
			rtb_log->SelectionColor = global::hex_text_foreground;
			rtb_log->SelectionLength = 0;
			rtb_log->AppendText(_log_data);
			rtb_log->ScrollToCaret();
		}

		inline ListViewItem^ get_action_list_view_item(HexAction^% action) {

			auto lvi_action = gcnew ListViewItem();

			String^ type_a = gcnew String("");
			String^ offset_a = gcnew String("");
			String^ size_a = gcnew String("");
			int index_a = 0;

			switch (action->type_) {

				case HexActionType::Write: {
					type_a = "WRT";
					offset_a = action->position_.ToString("X16");
					size_a = "0000000000000001";
					index_a = 12;
					break;
				}
				case HexActionType::WriteMany: {
					type_a = "WBLK";
					offset_a = action->position_.ToString("X16");
					size_a = action->length_.ToString("X16");
					index_a = 13;
					break;
				}
				case HexActionType::Insert: {
					type_a = "INS";
					offset_a = action->position_.ToString("X16");
					size_a = action->length_.ToString("X16");
					index_a = 10;
					break;
				}
				case HexActionType::Delete: {
					type_a = "DEL";
					offset_a = action->position_.ToString("X16");
					size_a = action->length_.ToString("X16");
					index_a = 14;
					break;
				}
			}

			lvi_action->Text = type_a;
			lvi_action->SubItems->Add(offset_a);
			lvi_action->SubItems->Add(size_a);
			lvi_action->ImageIndex = index_a;
			lvi_action->Tag = action;

			delete type_a;
			delete offset_a;
			delete size_a;

			return lvi_action;
		}

#pragma region Hashing

		inline void __clrcall do_graph_view_update() {

			if (!global::graph_union_instances)
				return;

			if (!global::graph_union_instances->Count)
				return;

			for (auto i = (tb_page_graph->Controls->Count - 1); i > -1; --i)
				tb_page_graph->Controls->RemoveAt(i);

			auto% control_g = global::graph_union_instances[current_document_index];

			tb_page_graph->Controls->Add(control_g);
		}

		inline void __clrcall do_hash_view_update() {

			String^ hash_set = gcnew String("null");

			for each (auto % item in lv_main_hash->Items)
				reinterpret_cast<ListViewItem^>(item)->SubItems[1]->Text = hash_set;

			btn_compute->Enabled = false;
			btn_compute_all->Enabled = false;

			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (rb_current_hash->Checked) {
				btn_compute->Enabled = control_h->SelectionLength ? true : false;
				btn_compute_all->Enabled = control_h->SelectionLength ? true : false;
			}
			else {
				btn_compute->Enabled = control_h->ByteProvider->Length ? true : false;
				btn_compute_all->Enabled = control_h->ByteProvider->Length ? true : false;
			}
		}

		inline void __clrcall cumbersome_hash_callback(int iteration, int total) {

			if (!total)
				return;

			if (!hashing_progress_dlg_) {
				// instance window, delete after hash complete etc.
				hashing_progress_dlg_ = gcnew winprogress();
				hashing_progress_dlg_->TopMost = true;

				hashing_progress_dlg_->Show();
			}

			auto progress = (iteration * 100) / total;

			hashing_progress_dlg_->update_progress("", progress);

			if (iteration >= (total)) {
				delete hashing_progress_dlg_;
				hashing_progress_dlg_ = nullptr;
			}
		}

		inline void __clrcall do_cumbersome_hash(ListViewItem^% hash_i) {

			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			String^ hash_str = gcnew String("");

			if (control_h->ByteProvider->Type == ProviderType::File) {
				switch (hash_i->Index) {

					case 0: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_md5_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
					case 1: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha1_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
					case 2: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha256_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
					case 3: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha384_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
					case 4: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha512_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
					case 5: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_ripemd160_buffered(reinterpret_cast<DynamicFileByteProvider^>(control_h->ByteProvider)->stream));
						break;
					}
				}
			}
			else {
				switch (hash_i->Index) {

					case 0: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_md5(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
					case 1: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha1(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
					case 2: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha256(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
					case 3: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha384(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
					case 4: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_sha512(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
					case 5: {
						hash_str = util::byte_array_to_hex_string(global::hasher->digest_ripemd160(reinterpret_cast<DynamicByteProvider^>(control_h->ByteProvider)->Bytes->ToArray()));
						break;
					}
				}
			}

			hash_i->SubItems[1]->Text = hash_str;

		}

		inline void __clrcall do_find_dialog() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			auto dialog_f = gcnew winfind(control_h->ByteCharConverter->GetEncoding);

			if (dialog_f->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

				auto% option_o = global::current_find_option[current_document_index];
				
				switch (dialog_f->find_option) {
					case find_type::hex: {
						goto do_raw_search;
						break;
					}
					case find_type::integer: {
						goto do_raw_search;
						break;
					}
					case find_type::string:{
						goto do_raw_search;
						break;
					}
					case find_type::float_: {
						goto do_raw_search;
					}
					case find_type::pattern: {
						goto do_pattern_scan;
						break;
					}
				}

			do_raw_search:

				auto option = gcnew FindOptions();

				option->Type = FindType::Hex;

				option->FindBuffer = dialog_f->search_data_;
				option->FindBufferUpper = dialog_f->search_data_upper_;

				FindDirection direction;

				switch (dialog_f->find_direction) {

					case find_direction_type::forward: {

						direction = FindDirection::Forward;

						break;
					}
					case find_direction_type::backward: {

						direction = FindDirection::Backward;

						break;
					}
				}

				option->Direction = direction;

				option->StartPosition = control_h->SelectionStart + control_h->SelectionLength;

				if (dialog_f->find_direction != find_direction_type::all) {
					control_h->Find(option, true);
				}
				else {

					bool cancel = false;

					auto entries = util::find_all(control_h, option, &cancel);

					int x = 0;
				}

				return;

			do_pattern_scan:

				auto option_aob = gcnew FindOptions();

				option_aob->Type = FindType::AoB;

				option_aob->AoB = dialog_f->aob_search_data_;
				
				FindDirection direction_aob;

				switch (dialog_f->find_direction) {

					case find_direction_type::forward: {

						direction_aob = FindDirection::Forward;

						break;
					}
					case find_direction_type::backward: {

						direction_aob = FindDirection::Backward;

						break;
					}
				}

				option_aob->Direction = direction_aob;

				

				if (dialog_f->find_direction != find_direction_type::all) {

					option_aob->StartPosition = control_h->SelectionStart + control_h->SelectionLength;
					control_h->Find(option_aob, true);
				}
				else {
					bool cancel = false;

					option_aob->StartPosition = 0;

					auto entries = util::find_all(control_h, option_aob, &cancel);

					if (entries) {

						int x = entries->Length;

						MessageBox::Show(x.ToString());
					}
				}

				
				return;
			}
		}

#pragma endregion

		public: inline void __clrcall do_update_stack() {

			lv_main_undo->Items->Clear();
			lv_main_redo->Items->Clear();

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (!control_h->CanUndo())
				return;

			for (int i = (control_h->ByteProvider->undo_actions_->Count - 1); i > -1; --i) {

				auto% action = control_h->ByteProvider->undo_actions_[i];

				auto lvi_action = get_action_list_view_item(action);

				lv_main_undo->Items->Add(lvi_action);
			}

			if (!control_h->CanRedo())
				return;

			for (int i = (control_h->ByteProvider->redo_actions_->Count - 1); i > -1; --i) {

				auto% action = control_h->ByteProvider->redo_actions_[i];

				auto lvi_action = get_action_list_view_item(action);

				lv_main_redo->Items->Add(lvi_action);
			}
		}

		public: inline System::Void __clrcall do_insert_toggle() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->InsertActive = control_h->InsertActive ? false : true; // permutate state

			do_toolbar_update();
		}

		public: inline void __clrcall do_copy_string() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->Copy();

			log_append("Selection copied to clipboard as String, size: " + control_h->SelectionLength.ToString(), true);
		}

		public: inline void __clrcall do_copy_hex() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->CopyHex();

			log_append("Selection copied to clipboard as Hex, size: " + control_h->SelectionLength.ToString(), true);
		}

		public: inline void __clrcall do_paste_string() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->PasteString();

			log_append("Selection pasted from clipboard as String", true);
		}

		public: inline void __clrcall do_paste_hex() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->PasteHex();

			log_append("Selection pasted from clipboard as Hex", true);
		}

		public: inline void __clrcall do_block_dialog() {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (!control_h->ByteProvider->Length)
				return;

			auto dialog_b = gcnew winblocksel(control_h->ByteProvider->Length, control_h->SelectionStart);

			if (dialog_b->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

				control_h->ScrollByteIntoView(dialog_b->start_address_);
				control_h->Select(dialog_b->start_address_, dialog_b->end_address_ - dialog_b->start_address_);
				log_append("Data block: " + dialog_b->start_address_.ToString("X16") + " - " + dialog_b->end_address_.ToString("X16") + " selected", true);
			}

			delete dialog_b;
		}

		public: inline void __clrcall do_jump_menu_update() {

			bool is_document_open = (current_document_index != 0xFFFFFFFF && tab_main->TabPages->Count > 0 );

			jmp_selection_ctx->Enabled = is_document_open;
			jmp_selection_m->Enabled = is_document_open;

			if (!is_document_open)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			bool selection_length_word	= (control_h->ByteProvider->Length >= control_h->SelectionStart + sizeof(UInt16) );
			bool selection_length_dword = (control_h->ByteProvider->Length >= control_h->SelectionStart + sizeof(UInt32) );
			bool selection_length_qword = (control_h->ByteProvider->Length >= control_h->SelectionStart + sizeof(UInt64) );

			word_ctx->Enabled = selection_length_word;
			word_m->Enabled = selection_length_word;
			dword_ctx->Enabled = selection_length_dword;
			dword_m->Enabled = selection_length_dword;
			qword_ctx->Enabled = selection_length_qword;
			qword_m->Enabled = selection_length_qword;

			if (!selection_length_word)
				return;

			auto buffer_w_ = control_h->ByteProvider->ReadBytes(control_h->SelectionStart, sizeof(UInt16));

			if (global::type_endian_mode == big)
				Array::Reverse(buffer_w_);

			pin_ptr<Byte> buffer_c_w = &buffer_w_[0];
			Byte* buffer_w = buffer_c_w;

			UInt16 address_w = *reinterpret_cast<UInt16*>(buffer_w);

			String^ string_w = gcnew String("&WORD Value: ( " + ( address_w < control_h->ByteProvider->Length ? "0x" + address_w.ToString("X4" ) : "Invalid Address") + " )");

			word_ctx->Text = string_w;
			word_ctx->Tag = address_w;
			word_ctx->Enabled = (address_w < control_h->ByteProvider->Length);
			word_m->Text = string_w;
			word_m->Tag = address_w;
			word_m->Enabled = (address_w < control_h->ByteProvider->Length);

			buffer_w = nullptr;
			buffer_c_w = nullptr;
			delete buffer_w_;
			delete string_w;

			if (!selection_length_dword)
				return;

			auto buffer_dw_ = control_h->ByteProvider->ReadBytes(control_h->SelectionStart, sizeof(UInt32));

			if (global::type_endian_mode == big)
				Array::Reverse(buffer_dw_);

			pin_ptr<Byte> buffer_c_dw = &buffer_dw_[0];
			Byte* buffer_dw = buffer_c_dw;

			UInt32 address_dw = *reinterpret_cast<UInt32*>(buffer_dw);

			String^ string_dw = gcnew String("&DWORD Value: ( " + (address_dw < control_h->ByteProvider->Length ? "0x" + address_dw.ToString("X8") : "Invalid Address") + " )");

			dword_ctx->Text = string_dw;
			dword_ctx->Tag = address_dw;
			dword_ctx->Enabled = (address_dw < control_h->ByteProvider->Length);
			dword_m->Text = string_dw;
			dword_m->Tag = address_dw;
			dword_m->Enabled = (address_dw < control_h->ByteProvider->Length);

			buffer_dw = nullptr;
			buffer_c_dw = nullptr;
			delete buffer_dw_;
			delete string_dw;

			if (!selection_length_qword)
				return;

			auto buffer_qw_ = control_h->ByteProvider->ReadBytes(control_h->SelectionStart, sizeof(UInt64));

			if (global::type_endian_mode == big)
				Array::Reverse(buffer_qw_);

			pin_ptr<Byte> buffer_c_qw = &buffer_qw_[0];
			Byte* buffer_qw = buffer_c_qw;

			UInt64 address_qw = *reinterpret_cast<UInt64*>(buffer_qw);

			String^ string_qw = gcnew String("&QWORD Value: ( " + ( address_qw < control_h->ByteProvider->Length ? "0x" + address_qw.ToString("X16") : "Invalid Address") + " )");

			qword_ctx->Text = string_qw;
			qword_ctx->Tag = address_qw;
			qword_ctx->Enabled = (address_qw < control_h->ByteProvider->Length);
			qword_m->Text = string_qw;
			qword_m->Tag = address_qw;
			qword_m->Enabled = (address_qw < control_h->ByteProvider->Length);

			buffer_qw = nullptr;
			buffer_c_qw = nullptr;
			delete buffer_qw_;
			delete string_qw;

		}

		public: inline void __clrcall insert_active_changed(Object^ sender, EventArgs^ e) {
			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			tslbl_textmode->Text = control_h->InsertActive ? "Insert" : "Overwrite";
			tb_btn_insert->Pushed = control_h->InsertActive;

			log_append("Insert toggled " + (control_h->InsertActive ? "on" : "off"), true);
		}

		public: inline void __clrcall do_toolbar_update() {

			if (!tab_main->TabPages->Count) {
				tb_btn_saveas->Enabled = false;
				tb_btn_save->Enabled = false;
				tb_btn_copy_string->Enabled = false;
				tb_btn_copy_hex->Enabled = false;
				tb_btn_paste_hex->Enabled = false;
				tb_btn_paste_string->Enabled = false;
				tb_btn_jump->Enabled = false;
				tb_btn_select_block->Enabled = false;
				tb_btn_insert->Enabled = false;
				return;
			}

			auto% control_h = global::hex_union_instances[current_document_index];

			bool is_length = control_h->ByteProvider->Length ? true : false;

			bool is_length_and_change = ( is_length && control_h->ByteProvider->HasChanges() );

			bool is_document_selection_length = ( control_h->SelectionLength ? true : false );

			tb_btn_save->Enabled = is_length_and_change;
			tb_btn_jump->Enabled = is_length;
			tb_btn_select_block->Enabled = is_length;
			tb_btn_copy_string->Enabled = is_document_selection_length;
			tb_btn_copy_hex->Enabled = is_document_selection_length;
			tb_btn_paste_string->Enabled = tab_main->TabPages->Count ? true : false;
			tb_btn_paste_hex->Enabled = tb_btn_paste_string->Enabled;
			tb_btn_saveas->Enabled = true;
			tb_btn_insert->Enabled = true;

			tb_btn_insert->Pushed = control_h->InsertActive;
			tslbl_textmode->Text = control_h->InsertActive ? "Insert" : "Overwrite";

			tslbl_modified->Visible = tb_btn_save->Enabled;
		}

		public: inline void __clrcall do_close_all_documents() {

			if (!tab_main->TabPages->Count)
				return;

			for (int i = ( tab_main->TabPages->Count - 1 ) ; i > -1 ; --i)
				do_close_document(i);
		}

		public: inline void __clrcall do_close_document(int index) {

			if (!tab_main->TabPages->Count)
				return;

			if ((tab_main->TabPages->Count - 1) < index)
				return;

			auto% control_h = global::hex_union_instances[index];

			if (control_h->ByteProvider->HasChanges())
				if (MB_QUE("File " + tab_main->TabPages[index]->Text + " has unsaved changes, Save before closing ?", "") == System::Windows::Forms::DialogResult::Yes)
					do_save_document(index);

			for (auto i = index; i < global::hex_union_instances->Count; ++i) // relocate indexing for subsequent hex boxes
				--global::hex_union_instances[i]->document_index_;

			log_append("Document " + tab_main->TabPages[index]->ToolTipText + " closed", true);

			global::hex_union_instances->RemoveAt(index);

			if(index == current_document_index)
				tb_page_graph->Controls->Clear();

			global::graph_union_instances->RemoveAt(index);

			global::current_find_option->RemoveAt(index);

			tab_main->TabPages->RemoveAt(index);

			if (tab_main->TabPages->Count - 1) {
				if ((index - 1) > -1) {
					tab_main->SelectedIndex = index - 1;
					current_document_index = index - 1;
				}
				else {
					tab_main->SelectedIndex = index + 1;
					current_document_index = index + 1;
				}
			}

			this->tab_main_SelectedIndexChanged(nullptr, nullptr); // trigger the event because .Net controls are wierd

			main_cb_encoding->Enabled = tab_main->TabPages->Count ? true : false;

			if (!main_cb_encoding->Enabled)
				main_cb_encoding->SelectedIndex = 0;
		}

		public: inline void __clrcall do_save_document(int index) {

			if (!tab_main->TabPages->Count)
				return;

			if ((tab_main->TabPages->Count - 1) < index)
				return;

			auto% control_h = global::hex_union_instances[index];

			if (control_h->ByteProvider->Type == ProviderType::File) {
				control_h->ByteProvider->ApplyChanges();
				log_append(tab_main->TabPages[index]->ToolTipText + " saved, " + control_h->ByteProvider->Length.ToString() + " bytes written to disk", true);
			}
			else if (control_h->ByteProvider->Type == ProviderType::Memory) {
				do_save_as_document(index);
			}

			do_toolbar_update();
		}

		public: inline void __clrcall do_save_as_document(int index) {

			if (!tab_main->TabPages->Count)
				return;

			if ((tab_main->TabPages->Count - 1) < index)
				return;

			auto% control_h = global::hex_union_instances[index];

			auto dialog_s = gcnew SaveFileDialog();

			dialog_s->FileName = tab_main->TabPages[index]->Text;

			if (dialog_s->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

				try {
					auto stream_f = gcnew FileStream(dialog_s->FileName, FileMode::Create);

					control_h->ByteProvider->SaveToStream(stream_f);

					stream_f->Close();

					delete stream_f;

					if (control_h->ByteProvider->Type == ProviderType::Memory) { // swap provider to saved file

						control_h->ByteProvider = gcnew DynamicFileByteProvider(dialog_s->FileName, false);

						tab_main->TabPages[index]->Text = Path::GetFileName(dialog_s->FileName);

						tab_main->TabPages[index]->ToolTipText = dialog_s->FileName;
					}
				}
				catch (UnauthorizedAccessException^) { MB_ERR("Unauthorized access to specified file / directory! ", ""); log_append("File access denied", true);
				}
				finally {

					log_append(dialog_s->FileName + " saved as new document, " + control_h->ByteProvider->Length.ToString() + " bytes written to disk", true);
				}
			}

#pragma region Workaround for MainMenu Draw Glitch

			// mainmenu glitches after openfiledialog is shown and fails to redraw surface UNLESS we show another form
			auto draw_glitch_fix = gcnew winjump(0, 0);
			draw_glitch_fix->Show();
			delete draw_glitch_fix;

#pragma endregion

			do_toolbar_update();

			delete dialog_s;
			
		}

		public: inline void __clrcall do_copy_as_lang(programming_language_type type_) {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (control_h->SelectionLength)
				control_h->CopyAsLang(type_);
		}

		public: inline System::Void __clrcall do_jmp_address_dialog() {

			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			auto dialog_j = gcnew winjump(control_h->SelectionStart, control_h->ByteProvider->Length);

			if (dialog_j->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				control_h->ScrollByteIntoView(dialog_j->offset);
				control_h->Select(dialog_j->offset, 1);
			}

			delete dialog_j;
		}

		public: inline System::Void __clrcall do_add_document(TabPage^% page, HexBox^% doc) {

			doc->SelectionStartChanged += gcnew EventHandler(this, &winmain::document_selected_byte_changed);
			doc->SelectionLengthChanged += gcnew EventHandler(this, &winmain::document_selection_length_change);
			doc->InsertActiveChanged += gcnew EventHandler(this, &winmain::insert_active_changed);
			doc->ByteProvider->UndoActionQueued += gcnew UndoActionQueued(this, &winmain::OnUndoActionQueued);
			doc->ByteProvider->RedoActionQueued += gcnew RedoActionQueued(this, &winmain::OnRedoActionQueued);
			doc->ByteProvider->UndoActionPerformed += gcnew UndoActionQueued(this, &winmain::OnUndoPerformed);
			doc->ByteProvider->RedoActionPerformed += gcnew RedoActionQueued(this, &winmain::OnRedoPerformed);

			tab_main->TabPages->Add(page);

			page->ImageIndex = 11;

			page->Tag = static_cast<unsigned char>(0x01);
			main_cb_encoding->Enabled = tab_main->TabPages->Count ? true : false;


			global::current_find_option->Add(nullptr); // placeholder for the tab

			// add option to load graph on demand or not laod at all later

#pragma region Graph Control Parsing

			log_append("Generating data graph...", true);

			auto graph_o = gcnew data_graph(doc);
			graph_o->Dock = DockStyle::Fill;
			graph_o->ContextMenu = main_graph_ctx;

			for (int i = tb_page_graph->Controls->Count - 1; i > -1; --i)
				tb_page_graph->Controls->RemoveAt(i);

			global::graph_union_instances->Add(graph_o);

			tb_page_graph->Controls->Add(graph_o);

#pragma endregion

			tab_main->SelectTab( tab_main->TabPages->Count - 1 );

			current_document_index = tab_main->SelectedIndex;

			page->Select();
			doc->Select();

			interpret_editor_index(tab_main->SelectedIndex);

			do_toolbar_update();

			if (!global::hex_union_instances->Count)
				return;

			if (rb_whole_hash->Checked) {
				btn_compute->Enabled = true;
				btn_compute_all->Enabled = true;
			}
			else {
				btn_compute->Enabled = lv_main_hash->SelectedItems->Count && doc->SelectionLength;
				btn_compute_all->Enabled = doc->SelectionLength ? true : false;
			}

			log_append("Document opened: " + page->ToolTipText, true);
		}

		public: inline System::Void __clrcall new_blank_instance() {

			HexBox^ hex_box_o = generate_hex_editor(true);

			hex_box_o->document_index_ = global::hex_union_instances->Count;
			hex_box_o->InsertActive = true;

			global::hex_union_instances->Add(hex_box_o);

			size_t name_indexer = static_cast<size_t>(0x0);

			for each (auto page in tab_main->TabPages)
				if (reinterpret_cast<TabPage^>(page)->Text->Contains("Untitled"))
					++name_indexer;

			TabPage^ tab_page_new = gcnew TabPage("Untitled" + (name_indexer ? (" " + name_indexer.ToString()) : ""));
			tab_page_new->Controls->Add(hex_box_o);

			tab_page_new->ToolTipText = tab_page_new->Text;

			do_add_document(tab_page_new, hex_box_o);
		}

		public: inline bool __clrcall open_new_file() {

			auto dialog_o = gcnew OpenFileDialog();

			if (dialog_o->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

				try {

					auto hex_box_o = generate_hex_editor(false);

					hex_box_o->document_index_ = global::hex_union_instances->Count;

					global::hex_union_instances->Add(hex_box_o);

					DynamicFileByteProvider^ provider_f = gcnew DynamicFileByteProvider(dialog_o->FileName, false);

					hex_box_o->ByteProvider = provider_f;

					auto tab_page_open = gcnew TabPage(Path::GetFileName(dialog_o->FileName));
					tab_page_open->Controls->Add(hex_box_o);

					tab_page_open->ToolTipText = dialog_o->FileName;

					do_add_document(tab_page_open, hex_box_o);
				}
				catch (UnauthorizedAccessException^) { MB_ERR("Unauthorized access to selected file! ", ""); return false; }

				delete dialog_o;

#pragma region Workaround for MainMenu Draw Glitch

				// mainmenu glitches after openfiledialog is shown and fails to redraw surface UNLESS we show another form
				auto draw_glitch_fix = gcnew winjump(0, 0);
				draw_glitch_fix->Show();
				delete draw_glitch_fix;

#pragma endregion

				return true;
			}

#pragma region Workaround for MainMenu Draw Glitch

			// mainmenu glitches after openfiledialog is shown and fails to redraw surface UNLESS we show another form
			auto draw_glitch_fix = gcnew winjump(0, 0);
			draw_glitch_fix->Show();
			delete draw_glitch_fix;

#pragma endregion

			delete dialog_o;
			return false;
		}

#pragma endregion

#pragma region GUI Callbacks

		private: __declspec(noinline) System::Void __clrcall document_selection_length_change(Object^ sender, EventArgs^ event_l) {

			auto% control_h = global::hex_union_instances[current_document_index];

			auto selection_start = control_h->SelectionStart;

			auto block_size = control_h->SelectionLength;

			auto block_end_offset = selection_start + block_size;

			tslbl_block->Text = "Block (h) : " + selection_start.ToString("X16") + " - " + block_end_offset.ToString("X16");

			tslbl_length->Text = "Length (h) : " + block_size.ToString("X16");

			tslbl_modified->Visible = control_h->ByteProvider->HasChanges();

			bool selection = (block_size > 0 && block_end_offset != selection_start);

			tslbl_block->Visible = selection;
			tslbl_length->Visible = selection;
			ts_seperator_1->Visible = selection;
			ts_seperator_2->Visible = selection;

			bool is_compute_selection = rb_current_hash->Checked && block_size;

			btn_compute->Enabled = rb_whole_hash->Checked ? true : is_compute_selection;
			btn_compute_all->Enabled = rb_whole_hash->Checked ? true : is_compute_selection;

			do_toolbar_update();
		}

		private: __declspec(noinline) System::Void __clrcall new_m_Click(System::Object^ sender, System::EventArgs^ e) {

			new_blank_instance();
		}

		private: __declspec(noinline) System::Void __clrcall winmain_Load(System::Object^ sender, System::EventArgs^ e) {

			this->ResizeBegin += gcnew EventHandler(this, &winmain::OnBeginResize);
			this->ResizeEnd += gcnew EventHandler(this, &winmain::OnEndResize);

			this->Hide();
			this->DoubleBuffered = true;
			this->CheckForIllegalCrossThreadCalls = false;

			progress_window_->update_progress("loading global variables...", 25);

			instantiate_globals();

		}

		private: __declspec(noinline) System::Void __clrcall OnBeginResize(Object^ sender, EventArgs^ e) {
			this->SuspendLayout();
		}

		private: __declspec(noinline) System::Void __clrcall OnEndResize(Object^ sender, EventArgs^ e) {

			if (this->WindowState == FormWindowState::Minimized)
				return;

			auto sc_dist_w = (this->Width / 3) * 2;

			auto sc_dist_h = (this->Height / 3) * 2;

			this->sc_main_hash->SplitterDistance = sc_main_hash->Height - sc_main_hash->Panel2MinSize;

			this->sc_list_rb_hash->SplitterDistance = this->sc_list_rb_hash->Height - 33;

			this->sc_buttons_hash->SplitterDistance = sc_buttons_hash->Width / 2;

			rb_current_hash->Location = Point(sc_buttons_hash->Width / 3,  ( (grp_main_hash->Height / 2) - (rb_current_hash->Height / 2) ) + (rb_current_hash->Height / 4) );
			rb_whole_hash->Location = Point( (sc_buttons_hash->Width / 3) * 2 , (grp_main_hash->Height / 2) - (rb_current_hash->Height / 2) + (rb_current_hash->Height / 4) );

			this->sc_info_main->SplitterDistance = this->sc_info_main->Size.Height - 33;

			this->sc_tab_data->SplitterDistance = sc_dist_w;

			this->sc_main->SplitterDistance = sc_dist_h - main_stat->Height;

			this->sc_main_doc_enc->SplitterDistance = 0;

			this->sc_main->SplitterDistance = sc_dist_h;

			this->sc_disasm_main->SplitterDistance = sc_dist_w;

			sc_disasm_stack_main->SplitterDistance = sc_dist_w / 4;

			sc_disasm_stack_change->SplitterDistance = 16;

			sc_disasm_stack_undone->SplitterDistance = 16;

			auto lv_col_dist_stack = (((sc_dist_w / 4) / 3) + 4) > -1 ? (((sc_dist_w / 4) / 3) + 4) : 1;
			auto lv_col_type_stack = (lv_col_dist_stack / 3) * 2;

			lv_col_dist_stack = Math::Round(1.5f * lv_col_dist_stack);

			lv_main_undo->Columns[0]->Width = lv_col_type_stack;
			lv_main_undo->Columns[1]->Width = lv_col_dist_stack;
			lv_main_undo->Columns[2]->Width = lv_col_dist_stack;

			lv_main_redo->Columns[0]->Width = lv_col_type_stack;
			lv_main_redo->Columns[1]->Width = lv_col_dist_stack - 4;
			lv_main_redo->Columns[2]->Width = lv_col_dist_stack - 4;

			auto loc_label = Drawing::Point((lv_main_undo->Width / 2) - (lbl_disasm_stack_redo->Width / 2), (sc_disasm_stack_undone->Panel1->Height / 2) - (lbl_disasm_stack_undo->Height / 2));

			lbl_disasm_stack_redo->Location = loc_label;
			lbl_disasm_stack_undo->Location = loc_label;

			lv_main_hash->Columns[0]->Width = (lv_main_hash->Width / 4);
			lv_main_hash->Columns[1]->Width = (lv_main_hash->Width / 4) * 3;

			if (main_type_lv) {

				main_type_lv->Columns[0]->Width = (main_type_view_tab->Width / 2) - 5;
				main_type_lv->Columns[1]->Width = (main_type_view_tab->Width / 2) - 5;

				main_little_endian_rb->Location = Point(main_group_value->Width / 4, main_little_endian_rb->Location.Y);
				main_big_endian_rb->Location = Point((main_group_value->Width / 4) * 2, main_little_endian_rb->Location.Y);
				main_cb_hex->Location = Point((main_group_value->Width / 4) * 3, main_little_endian_rb->Location.Y);
			}

			this->ResumeLayout();
		}

		private: __declspec(noinline) System::Void about_m_Click(System::Object^ sender, System::EventArgs^ e) {

			winabout^ dialog_a = gcnew winabout();

			dialog_a->ShowDialog();

			delete dialog_a;
		}

		private: __declspec(noinline) System::Void winmain_SizeChanged(System::Object^ sender, System::EventArgs^ e) {

			if (this->WindowState == FormWindowState::Maximized)
			{

				auto sc_dist_w = (this->Width / 3) * 2;

				auto sc_dist_h = (this->Height / 3) * 2;

				this->sc_main_hash->SplitterDistance = sc_main_hash->Height - sc_main_hash->Panel2MinSize;

				this->sc_list_rb_hash->SplitterDistance = this->sc_list_rb_hash->Height - 33;

				this->sc_buttons_hash->SplitterDistance = sc_buttons_hash->Width / 2;

				rb_current_hash->Location = Point(sc_buttons_hash->Width / 3, ((grp_main_hash->Height / 2) - (rb_current_hash->Height / 2)) + (rb_current_hash->Height / 4));
				rb_whole_hash->Location = Point((sc_buttons_hash->Width / 3) * 2, (grp_main_hash->Height / 2) - (rb_current_hash->Height / 2) + (rb_current_hash->Height / 4));

				this->sc_info_main->SplitterDistance = this->sc_info_main->Size.Height - 33;

				this->sc_tab_data->SplitterDistance = sc_dist_w;

				this->sc_main->SplitterDistance = sc_dist_h - main_stat->Height;

				this->sc_main_doc_enc->SplitterDistance = 0;

				this->sc_main->SplitterDistance = sc_dist_h;

				this->sc_disasm_main->SplitterDistance = sc_dist_w;

				sc_disasm_stack_main->SplitterDistance = sc_dist_w / 4;

				sc_disasm_stack_change->SplitterDistance = 16;

				sc_disasm_stack_undone->SplitterDistance = 16;

				auto lv_col_dist_stack = (((sc_dist_w / 4) / 3) + 4) > -1 ? (((sc_dist_w / 4) / 3) + 4) : 1;
				auto lv_col_type_stack = (lv_col_dist_stack / 3) * 2;

				lv_col_dist_stack = Math::Round(1.5f * lv_col_dist_stack);

				lv_main_undo->Columns[0]->Width = lv_col_type_stack;
				lv_main_undo->Columns[1]->Width = lv_col_dist_stack;
				lv_main_undo->Columns[2]->Width = lv_col_dist_stack;

				lv_main_redo->Columns[0]->Width = lv_col_type_stack;
				lv_main_redo->Columns[1]->Width = lv_col_dist_stack - 4;
				lv_main_redo->Columns[2]->Width = lv_col_dist_stack - 4;

				auto loc_label = Drawing::Point((lv_main_undo->Width / 2) - (lbl_disasm_stack_redo->Width / 2), (sc_disasm_stack_undone->Panel1->Height / 2) - (lbl_disasm_stack_undo->Height / 2));

				lbl_disasm_stack_redo->Location = loc_label;
				lbl_disasm_stack_undo->Location = loc_label;

				lv_main_hash->Columns[0]->Width = (lv_main_hash->Width / 4);
				lv_main_hash->Columns[1]->Width = (lv_main_hash->Width / 4) * 3;

				if (main_type_lv) {

					main_type_lv->Columns[0]->Width = (main_type_view_tab->Width / 2) - 5;
					main_type_lv->Columns[1]->Width = (main_type_view_tab->Width / 2) - 5;

					main_little_endian_rb->Location = Point(main_group_value->Width / 4, main_little_endian_rb->Location.Y);
					main_big_endian_rb->Location = Point((main_group_value->Width / 4) * 2, main_little_endian_rb->Location.Y);
					main_cb_hex->Location = Point((main_group_value->Width / 4) * 3, main_little_endian_rb->Location.Y);
				}
			}
		}

		private: __declspec(noinline) System::Void __clrcall on_listview_column_drag(Object^ sender, ColumnWidthChangingEventArgs^ event_c) {

			event_c->NewWidth = lv_main_hash->Columns[event_c->ColumnIndex]->Width;
			event_c->Cancel = true;
		}

		private: __declspec(noinline) System::Void tab_main_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			current_document_index = tab_main->SelectedIndex;

			do_toolbar_update();

			if (!global::hex_union_instances->Count)
				return;

			if (global::hex_union_instances[tab_main->SelectedIndex]) {

				main_cb_encoding->SelectedIndex = static_cast<unsigned char>(tab_main->SelectedTab->Tag) - 1;

				interpret_editor_index(tab_main->SelectedIndex);

				do_hash_view_update();

				do_update_stack();

				do_graph_view_update();
			}

		}

		private: __declspec(noinline) System::Void document_selected_byte_changed(Object^ sender, EventArgs^ event_a) {

			auto control_h = reinterpret_cast<HexBox^>(sender);

			do_toolbar_update();

			interpret_editor_index(control_h->document_index_);
		}

		private: System::Void main_little_endian_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			if (!tab_main->TabPages->Count)
				return;

			if (global::type_endian_mode == endian_mode::big) {

				global::type_endian_mode = endian_mode::little;

				auto control_h = reinterpret_cast<HexBox^>(global::hex_union_instances[tab_main->SelectedIndex]);

				interpret_editor_index(control_h->document_index_);

				log_append("Type view encoding changed to little endian", true);
			}
		}

		private: System::Void __clrcall main_big_endian_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

			if (!tab_main->TabPages->Count)
				return;

			if (global::type_endian_mode == endian_mode::little) {

				global::type_endian_mode = endian_mode::big;

				auto control_h = reinterpret_cast<HexBox^>(global::hex_union_instances[tab_main->SelectedIndex]);

				interpret_editor_index(control_h->document_index_);

				log_append("Type view encoding changed to big endian", true);
			}
		}

		template<typename T>
		inline void __clrcall perform_type_update(uintptr_t position, T value) {

			//TODO CHECK ENDIAN TYPE BEFORE WRITE

			auto size = sizeof(value);
			auto address = reinterpret_cast<Byte*>(&value);

			auto buffer = gcnew array<unsigned char>(size);

			for (auto i = 0; i < size; ++i)
				buffer[i] = address[i];

			if (global::type_endian_mode == big)
				Array::Reverse(buffer);

			auto% current_document = global::hex_union_instances[current_document_index];

			current_document->ByteProvider->WriteBytes(current_document->SelectionStart, buffer, size);

			current_document->Refresh();
			interpret_editor_index(current_document_index);
		}

		private: System::Void __clrcall type_update_requested(Object^ editor, Object^ sender, Object^ value) {

			auto item = reinterpret_cast<ListViewItem^>(sender);
			auto% current_document = global::hex_union_instances[current_document_index];

			switch (item->Index) {
				case 0: {
					perform_type_update(current_document->SelectionStart, static_cast<Byte>(value)); // binary is returned as a byte
					break;
				}
				case 1: {
					perform_type_update(current_document->SelectionStart, static_cast<Byte>(value));
					break;
				}
				case 2: {
					perform_type_update(current_document->SelectionStart, static_cast<SByte>(value));
					break;
				}
				case 3: {
					perform_type_update(current_document->SelectionStart, static_cast<UInt16>(value));
					break;
				}
				case 4: {
					perform_type_update(current_document->SelectionStart, static_cast<Int16>(value));
					break;
				}
				case 5: {
					perform_type_update(current_document->SelectionStart, static_cast<UInt32>(value));
					break;
				}
				case 6: {
					perform_type_update(current_document->SelectionStart, static_cast<Int32>(value));
					break;
				}
				case 7: {
					perform_type_update(current_document->SelectionStart, static_cast<UInt64>(value));
					break;
				}
				case 8: {
					perform_type_update(current_document->SelectionStart, static_cast<Int64>(value));
					break;
				}
				case 9: {
					perform_type_update(current_document->SelectionStart, static_cast<Single>(value));
					break;
				}
				case 10: {
					perform_type_update(current_document->SelectionStart, static_cast<Double>(value));
					break;
				}
				case 11: {
					perform_type_update(current_document->SelectionStart, static_cast<char>(value));
					break;
				}
				case 12: {
					perform_type_update(current_document->SelectionStart, static_cast<wchar_t>(value));
					break;
				}
				default: {
					return;
					break;
				}
			}

			if(editor)
				delete editor;
		}

		private: System::Void __clrcall open_m_Click(System::Object^ sender, System::EventArgs^ e) {
			open_new_file();
		}

		private: System::Void __clrcall tslbl_offset_DoubleClick(System::Object^ sender, System::EventArgs^ e) {

			do_jmp_address_dialog();
		}

		private: System::Void __clrcall main_tb_ButtonClick(System::Object^ sender, System::Windows::Forms::ToolBarButtonClickEventArgs^ e) {

			switch (static_cast<System::UInt16>(e->Button->Tag)) {

				case TBTN_NEW: {
					new_blank_instance();
					break;
				}
				case TBTN_OPEN: {
					open_new_file();
					break;
				}
				case TBTN_SAVE: {
					do_save_document(current_document_index);
					break;
				}
				case TBTN_SAVEAS: {
					do_save_as_document(current_document_index);
					break;
				}
				case TBTN_JUMP: {
					do_jmp_address_dialog();
					break;
				}
				case TBTN_BLOCK: {
					do_block_dialog();
					break;
				}
				case TBTN_COPY_STRING: {
					do_copy_string();
					break;
				}
				case TBTN_COPY_HEX: {
					do_copy_hex();
					break;
				}
				case TBTN_PASTE_STRING: {
					do_paste_string();
					break;
				}
				case TBTN_PASTE_HEX: {
					do_paste_hex();
					break;
				}
				case TBTN_INSERT: {
					do_insert_toggle();
					break;
				}
				default: {
					break;
				}
			}
		}

		private: System::Void __clrcall main_cb_encoding_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			switch (main_cb_encoding->SelectedIndex) {
				case 0: {
					tab_main->SelectedTab->Tag = static_cast<unsigned char>(0x01);
					control_h->ByteCharConverter = gcnew DefaultByteCharConverter();
					break;
				}
				case 1: {
					tab_main->SelectedTab->Tag = static_cast<unsigned char>(0x02);
					control_h->ByteCharConverter = gcnew ASCIIByteCharConverter();
					break;
				}
				case 2: {
					tab_main->SelectedTab->Tag = static_cast<unsigned char>(0x03);
					control_h->ByteCharConverter = gcnew EbcdicByteCharProvider();
					break;
				}
			}
			control_h->Refresh();

		}
		private: System::Void __clrcall cpy_cpp_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::CPP);
		}

		private: System::Void __clrcall cpy_csharp_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::CSHARP);
		}

		private: System::Void __clrcall cpy_python_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::Python);
		}

		private: System::Void __clrcall cpy_java_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::JAVA);
		}

		private: System::Void __clrcall cpy_pascal_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::Pascal);
		}

		private: System::Void __clrcall cpy_perl_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::Perl);
		}

		private: System::Void __clrcall cpy_rust_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::RUST);
		}

		private: System::Void __clrcall cpy_vb_m_ctx_Click(System::Object^ sender, System::EventArgs^ e) {
			do_copy_as_lang(programming_language_type::VB);
		}

		private: System::Void __clrcall edit_m_Click(System::Object^ sender, System::EventArgs^ e) {

			bool is_document_active = tab_main->TabPages->Count > 0 ? true : false;

			jump_m->Enabled = is_document_active;

			copy_string_m->Enabled = is_document_active;
			copy_hex_m->Enabled = is_document_active;
			copyas_m->Enabled = is_document_active;
			paste_string_m->Enabled = is_document_active;
			paste_hex_m->Enabled = is_document_active;
			select_all_m->Enabled = is_document_active;
			cut_hex_m->Enabled = is_document_active;
			cut_string_m->Enabled = is_document_active;
			select_block_m->Enabled = is_document_active;
			copy_offset_m->Enabled = is_document_active;

			if (!is_document_active)
				return;

			//further analysis and re-assign enabled values if we reach this point
			auto% control_h = global::hex_union_instances[current_document_index];

			bool is_document_selection = (is_document_active && control_h->SelectionStart > -1 && control_h->ByteProvider->Length && control_h->SelectionLength);

			copy_string_m->Enabled = is_document_selection;
			copy_hex_m->Enabled = is_document_selection;
			copyas_m->Enabled = is_document_selection;

			cut_hex_m->Enabled = (is_document_selection && control_h->InsertActive);
			cut_string_m->Enabled = (is_document_selection && control_h->InsertActive);

			if (control_h->SelectionStart > -1) {
				paste_string_m->Enabled = true;
				paste_hex_m->Enabled = true;
			}

			do_jump_menu_update();

		}

		private: System::Void __clrcall main_document_context_menu_Popup(System::Object^ sender, System::EventArgs^ e) {

			auto% control_h = global::hex_union_instances[current_document_index];

			bool is_document_selection = (control_h->SelectionStart > -1 && control_h->ByteProvider->Length && control_h->SelectionLength);

			copy_string_ctx->Enabled = is_document_selection;
			copy_hex_ctx->Enabled = is_document_selection;
			copyas_ctx->Enabled = is_document_selection;

			if (control_h->SelectionStart > -1) {
				paste_string_ctx->Enabled = true;
				paste_hex_ctx->Enabled = true;
				select_all_ctx->Enabled = control_h->ByteProvider->Length ? true : false;
			}

			cut_hex_ctx->Enabled = (control_h->InsertActive && is_document_selection);
			cut_string_ctx->Enabled = (control_h->InsertActive && is_document_selection);

			do_jump_menu_update();
		}

		private: System::Void __clrcall copy_string_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_copy_string();

		}
		private: System::Void __clrcall copy_hex_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_copy_hex();

		}
		private: System::Void __clrcall paste_string_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_paste_string();

		}
		private: System::Void __clrcall paste_hex_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_paste_hex();
		}

		private: System::Void __clrcall save_m_Click(System::Object^ sender, System::EventArgs^ e) {
			do_save_document(current_document_index);
		}

		private: System::Void __clrcall saveas_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_save_as_document(current_document_index);
		}

		private: System::Void __clrcall close_m_Click(System::Object^ sender, System::EventArgs^ e) {
			do_close_document(current_document_index);
		}

		private: System::Void __clrcall file_m_Select(System::Object^ sender, System::EventArgs^ e) {
			bool enable_m = tab_main->TabPages->Count ? true : false;

			save_m->Enabled = enable_m;
			saveas_m->Enabled = enable_m;
			save_all_m->Enabled = enable_m;

			close_m->Enabled = enable_m;
			closeall_m->Enabled = enable_m;

			if (!enable_m)
				return;

			bool is_document_modified = global::hex_union_instances[current_document_index]->ByteProvider->HasChanges();

			save_m->Enabled = is_document_modified;
		}
		
		private: System::Void __clrcall exit_m_Click(System::Object^ sender, System::EventArgs^ e) {
			Application::Exit();
		}

		private: System::Void __clrcall closeall_m_Click(System::Object^ sender, System::EventArgs^ e) {
			do_close_all_documents();
		}
		
		private: System::Void __clrcall main_cb_hex_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			
			global::is_type_view_hexadecimal = main_cb_hex->Checked;

			if (current_document_index < 0)
				return;

			interpret_editor_index(current_document_index);
		}

		private: System::Void __clrcall jmp_selection_ctx_Popup(System::Object^ sender, System::EventArgs^ e) {
			do_jump_menu_update();
		}

		public: System::Void __clrcall hex_OnKeyDown(Object^ sender, KeyEventArgs^ e) {

			if (!e->Control)
				return;

			winhexstr^ dialog_h;

			auto% control_h = global::hex_union_instances[current_document_index];

			switch (e->KeyCode) {
				case Keys::C: {

					if (!control_h->SelectionLength || !control_h->ByteProvider->Length)
						return;

					dialog_h = gcnew winhexstr(0);

					if (dialog_h->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

						if (dialog_h->rb_hex->Checked)
							control_h->CopyHex();
						else
							control_h->Copy();
					}

					break;
				}
				case Keys::X:{

					if (!control_h->SelectionLength || !control_h->ByteProvider->Length || !control_h->InsertActive)
						return;

					dialog_h = gcnew winhexstr(2);

					if (dialog_h->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

						if (dialog_h->rb_hex->Checked)
							control_h->CutHex();
						else
							control_h->CutString();
					}

					break;
				}
				case Keys::V: {

					if (!control_h->ByteProvider->Length && !control_h->InsertActive)
						return;

					dialog_h = gcnew winhexstr(1);

					if (dialog_h->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

						if (dialog_h->rb_hex->Checked)
							control_h->PasteHex();
						else
							control_h->PasteString();
					}

					break;
				}
				case Keys::Z: {

					if (control_h->CanUndo())
						control_h->Undo();

					break;
				}
				case Keys::Y: {

					if (control_h->CanRedo())
						control_h->Redo();

					break;
				}

				case Keys::A: {

					if (control_h->ByteProvider->Length)
						control_h->SelectAll();

					break;
				}

				default: {
					return;
				}
			}
			delete dialog_h;
		}

		private: System::Void word_m_Click(System::Object^ sender, System::EventArgs^ e) {

			if (word_m->Text->Contains("Invalid") || !tab_main->TabPages->Count)
				return;

			auto address = static_cast<UInt16>(word_m->Tag);

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->ScrollByteIntoView(address);
			control_h->Select(address, 1);

		}

		private: System::Void dword_m_Click(System::Object^ sender, System::EventArgs^ e) {

			if (word_m->Text->Contains("Invalid") || !tab_main->TabPages->Count)
				return;

			auto address = static_cast<UInt32>(dword_m->Tag);

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->ScrollByteIntoView(address);
			control_h->Select(address, 1);
		}

		private: System::Void qword_m_Click(System::Object^ sender, System::EventArgs^ e) {

			if (word_m->Text->Contains("Invalid") || !tab_main->TabPages->Count)
				return;

			auto address = static_cast<UInt64>(qword_m->Tag);

			auto% control_h = global::hex_union_instances[current_document_index];

			control_h->ScrollByteIntoView(address);
			control_h->Select(address, 1);
		}

		private: System::Void cut_hex_m_Click(System::Object^ sender, System::EventArgs^ e) {

			global::hex_union_instances[current_document_index]->CutHex();
		}

		private: System::Void cut_string_m_Click(System::Object^ sender, System::EventArgs^ e) {

			global::hex_union_instances[current_document_index]->CutString();
		}
		
		private: System::Void main_edit_context_menu_Popup(System::Object^ sender, System::EventArgs^ e) {

			bool item_count = ( main_type_lv->SelectedItems->Count && tab_main->TabPages->Count  && !main_type_lv->SelectedItems[0]->SubItems[1]->Text->Contains("Invalid"));

			edit_ctx->Enabled = item_count;
			copy_ctx->Enabled = item_count;
			paste_ctx->Enabled = item_count;

			if (!item_count)
				return;

			bool item_is_write_range = main_type_lv->SelectedItems[0]->Index > 12 ? false : true;

			edit_ctx->Enabled = item_is_write_range;
			paste_ctx->Enabled = item_is_write_range;

		}

		private: System::Void edit_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			main_type_lv->do_show_edit_box();
		}

		private: System::Void copy_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			DataObject^ object_d = gcnew DataObject();

			object_d->SetData(String::typeid, main_type_lv->SelectedItems[0]->SubItems[1]->Text);

			Clipboard::SetDataObject(object_d, true);
		}

		private: System::Void paste_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			auto object_d = Clipboard::GetDataObject();

			auto clipboard_s = reinterpret_cast<String^>(object_d->GetData(String::typeid));

			bool is_valid_input = true;

			Object^ data;

			switch (main_type_lv->SelectedIndices[0]) {
				case 0: {
					if (this->Text->Length != 8) {
						is_valid_input = false;
						break;
					}
					for each (auto % character in clipboard_s)
						is_valid_input = (character == L'0' || character == L'1');
					break;
				}
				case 1: {
					Byte result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : Byte::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 2: {
					SByte result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : SByte::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 3: {
					UInt16 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : UInt16::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 4: {
					Int16 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : Int16::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 5: {
					UInt32 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : UInt32::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 6: {
					Int32 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : Int32::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 7: {
					UInt64 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : UInt64::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 8: {
					Int64 result{};
					is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(clipboard_s, result, (global::type_endian_mode == little ? true : false)) : Int64::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 9: {
					Single result{};
					is_valid_input = Single::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 10: {
					Double result{};
					is_valid_input = Double::TryParse(clipboard_s, result);
					data = result;
					break;
				}
				case 11: {

					if (!clipboard_s->Length)
						is_valid_input = false;

					if (clipboard_s->Length > 1)
						is_valid_input = false;

					data = static_cast<char>(clipboard_s[0]);
					break;
				}
				case 12: {
					System::Char result{};
					is_valid_input = System::Char::TryParse(clipboard_s, result);
					data = result;
					break;
				}
			}

			if (!is_valid_input)
				return;

			type_update_requested(nullptr, main_type_lv->SelectedItems[0], data);
		}

		private: System::Void select_all_m_Click(System::Object^ sender, System::EventArgs^ e) {

			global::hex_union_instances[current_document_index]->SelectAll();
		}

		private: System::Void select_block_m_Click(System::Object^ sender, System::EventArgs^ e) {

			do_block_dialog();
		}

		private: System::Void copy_offset_m_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!tab_main->TabPages->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (control_h->SelectionStart < 0)
				return;

			DataObject^ data_c = gcnew DataObject();

			data_c->SetData(String::typeid, control_h->SelectionStart.ToString("X16"));

			Clipboard::SetDataObject(data_c, true);
		}

		private: System::Void save_all_m_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!tab_main->TabPages->Count)
				return;

			for (auto i = (tab_main->TabPages->Count - 1); i > -1; --i)
				do_save_document(i);
		}

		private: System::Void winmain_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
			try {

				do_close_all_documents();

			}
			catch (Exception^ except) { return; }
		}

		private: System::Void __clrcall OnUndoActionQueued(Object^ sender, HexAction^ event_u) {
			// null argument #2 indicates stack clear
			if (!event_u) {
				lv_main_redo->Items->Clear();
				lv_main_undo->Items->Clear();
				return;
			}

			auto lvi_action = get_action_list_view_item(event_u);

			lv_main_undo->Items->Insert(0, lvi_action);
			lvi_action->Selected = true;
		}

		private: System::Void __clrcall OnRedoActionQueued(Object^ sender, HexAction^ event_r) {
			// trash event
			return;
		}

		private: System::Void __clrcall OnUndoPerformed(Object^ sender, HexAction^ event_p) {

			if (!lv_main_undo->Items->Count)
				return;

			auto lvi_action = lv_main_undo->Items[0];

			lv_main_undo->Items->RemoveAt(0);

			lv_main_redo->Items->Insert(0, lvi_action);
		}

		private: System::Void __clrcall OnRedoPerformed(Object^ sender, HexAction^ event_p) {

			if (!lv_main_redo->Items->Count)
				return;

			auto lvi_action = lv_main_redo->Items[0];

			lv_main_redo->Items->RemoveAt(0);

			lv_main_undo->Items->Insert(0, lvi_action);
		}

		private: System::Void rb_whole_hash_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (!global::hex_union_instances->Count)
				return;

			if (rb_whole_hash->Checked) {
				btn_compute->Enabled = true;
				btn_compute_all->Enabled = true;
			}
		}

		private: System::Void rb_current_hash_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (!global::hex_union_instances->Count)
				return;

			if (rb_current_hash->Checked) {

				bool is_selection = (global::hex_union_instances[current_document_index]->SelectionLength <= 0) ? false : true;

				btn_compute->Enabled = is_selection;
				btn_compute_all->Enabled = is_selection;
			}
		}

		private: System::Void btn_compute_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!lv_main_hash->SelectedItems->Count)
				return;

			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];

			if (!rb_current_hash->Checked) {
				do_cumbersome_hash(lv_main_hash->SelectedItems[0]);
			}
			else {

				switch (lv_main_hash->SelectedItems[0]->Index) {

					case 0: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_md5(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 1: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha1(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 2: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha256(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 3: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha384(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 4: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha512(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 5: {
						lv_main_hash->SelectedItems[0]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_ripemd160(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}

				}

			}

		}

		private: System::Void lv_main_hash_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

			if (!rb_current_hash->Checked)
				return;

			if (!global::hex_union_instances->Count)
				return;
			
			auto% control_h = global::hex_union_instances[current_document_index];

			btn_compute->Enabled = lv_main_hash->SelectedItems->Count && control_h->SelectionLength;
			btn_compute_all->Enabled = control_h->SelectionLength ? true : false;
		}

		private: System::Void btn_compute_all_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!global::hex_union_instances->Count)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];
			for (auto i = 0; i < lv_main_hash->Items->Count; ++i) {

				if (!rb_current_hash->Checked) {
					do_cumbersome_hash(lv_main_hash->Items[i]);
				}
				else {

					switch (lv_main_hash->Items[i]->Index) {

					case 0: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_md5(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 1: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha1(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 2: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha256(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 3: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha384(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 4: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_sha512(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}
					case 5: {
						lv_main_hash->Items[i]->SubItems[1]->Text = util::byte_array_to_hex_string(global::hasher->digest_ripemd160(control_h->ByteProvider->ReadBytes(control_h->SelectionStart, control_h->SelectionLength)));
						break;
					}

					}

				}
			}
		}

		private: System::Void beginning_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!global::graph_union_instances || !global::hex_union_instances)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];
			auto% control_g = global::graph_union_instances[current_document_index];

			if ( !control_g->current_data_block || control_g->current_data_block->start_address >= control_h->ByteProvider->Length)
				return;

			control_h->Select(control_g->current_data_block->start_address, 1);
		}

		private: System::Void end_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!global::graph_union_instances || !global::hex_union_instances)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];
			auto% control_g = global::graph_union_instances[current_document_index];

			if (!control_g->current_data_block || control_g->current_data_block->start_address >= control_h->ByteProvider->Length)
				return;

			control_h->Select(control_g->current_data_block->end_address ? (control_g->current_data_block->end_address - 1) : 0 , 1);
		}

		private: System::Void entire_ctx_Click(System::Object^ sender, System::EventArgs^ e) {

			if (!global::graph_union_instances || !global::hex_union_instances)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];
			auto% control_g = global::graph_union_instances[current_document_index];

			if (!control_g->current_data_block || control_g->current_data_block->start_address >= control_h->ByteProvider->Length)
				return;

			control_h->Select(control_g->current_data_block->start_address, control_g->current_data_block->end_address - control_g->current_data_block->start_address);
		}

		private: System::Void main_graph_ctx_Popup(System::Object^ sender, System::EventArgs^ e) {

			if (!global::graph_union_instances || !global::hex_union_instances)
				return;

			auto% control_g = global::graph_union_instances[current_document_index];

			if (!control_g->current_data_block)
				return;

			control_g->context_lock = true;
		}

		private: System::Void main_graph_ctx_Collapse(System::Object^ sender, System::EventArgs^ e) {

			if (!global::graph_union_instances || !global::hex_union_instances)
				return;

			auto% control_h = global::hex_union_instances[current_document_index];
			auto% control_g = global::graph_union_instances[current_document_index];

			control_g->context_lock = false;
		}

		private: System::Void find_m_Click(System::Object^ sender, System::EventArgs^ e) {
			
			do_find_dialog();
		}
#pragma endregion


	};
}

#endif

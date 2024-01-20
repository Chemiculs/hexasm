#ifndef LISTVIEWEX_H
#define LISTVIEWEX_H

using namespace System;
using namespace System::Windows::Forms;

#include "global.hpp"
#include "interop.hpp"
#include "native.hpp"

namespace hexasm {

	namespace gui {

#pragma region Constants

		const int LVM_FIRST = 0x1000;

		const int LVM_SETEXTENDEDLISTVIEWSTYLE = LVM_FIRST + 54;
		const int LVS_EX_FULLROWSELECT = 0x00000020;

		const int LVS_EX_DOUBLEBUFFER = 0x00010000;

#pragma endregion

#pragma region Type Definitions

		enum gui_data_t {

			BYTE = 0,
			SBYTE = 1,
			SHORT = 2,
			USHORT = 3,
			INT = 4,
			UINT = 5,
			LONGLONG = 6,
			ULONGLONG = 7,
			FLOAT32 = 8,
			FLOAT64 = 9,
			STRING = 10,
			WIDESTRING = 11,
			CHAR = 12,
			WIDECHAR =13,
			CTIME = 14,
			BINARY = 15,
			INT24 = 16,
			UINT24 = 17

		};

		delegate void ProxySaveAttemptHandler(Object^, Object^, Object^);
		delegate void ProxySaveRequestedHandler(Object^, Object^, Object^);

#pragma endregion

		ref class TextBoxProxy : public TextBox {

		private:
			
			String^ original_data;
			ListViewItem^ item_data_bound = nullptr;
			uintptr_t item_sub_index = 1;

		public:

			ProxySaveAttemptHandler^ ProxySaveAttempt = gcnew ProxySaveAttemptHandler(this, &TextBoxProxy::OnProxySaveAttempt);

			gui_data_t data_type_ = gui_data_t::BINARY;

			inline void __clrcall Show() {
				this->Font = item_data_bound->Font;
				this->Size = item_data_bound->SubItems[item_sub_index]->Bounds.Size;

				this->Text = reinterpret_cast<String^>(item_data_bound->SubItems[item_sub_index]->Text);
				this->Visible = true;
				this->BringToFront();
				this->Focus();
			}

			inline void __clrcall Hide(int save) {
				if (save == 0)
					goto end_fn;

				if (save == 1) {

					bool is_valid_input = true;

					switch (data_type_) {
						case BINARY: {
							if (this->Text->Length != 8) {
								is_valid_input = false;
								break;
							}
							for each (auto% character in this->Text)
								is_valid_input = (character == L'0' || character == L'1');
							break;
						}
						case BYTE: {
							Byte result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, ( global::type_endian_mode == little ? true : false)) : Byte::TryParse(this->Text, result);
							break;
						}
						case SBYTE: {
							SByte result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : SByte::TryParse(this->Text, result);
							break;
						}
						case USHORT: {
							UInt16 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : UInt16::TryParse(this->Text, result);
							break;
						}
						case SHORT: {
							Int16 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : Int16::TryParse(this->Text, result);
							break;
						}
						case UINT: {
							UInt32 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : UInt32::TryParse(this->Text, result);
							break;
						}
						case INT: {
							Int32 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : Int32::TryParse(this->Text, result);
							break;
						}
						case ULONGLONG: {
							UInt64 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : UInt64::TryParse(this->Text, result);
							break;
						}
						case LONGLONG: {
							Int64 result{};
							is_valid_input = global::is_type_view_hexadecimal ? util::try_parse_hex_string(this->Text, result, (global::type_endian_mode == little ? true : false)) : Int64::TryParse(this->Text, result);
							break;
						}
						case FLOAT32: {
							Single result{};
							is_valid_input = Single::TryParse(this->Text, result);
							break;
						}
						case FLOAT64: {
							Double result{};
							is_valid_input = Double::TryParse(this->Text, result);
							break;
						}
						case CHAR: {

							if (!this->Text->Length)
								is_valid_input = false;

							if (this->Text->Length > 1)
								is_valid_input = false;

							break;
						}
						case WIDECHAR: {
							System::Char result{};
							is_valid_input = System::Char::TryParse(this->Text, result);
							break;
						}
					}

					if (is_valid_input) {
						ProxySaveAttempt(this, nullptr, this->Text);
					}
					else {
						ProxySaveAttempt(this, nullptr, nullptr);
						goto end_fn;
					}

				}

			end_fn:

				//this->Text = original_data;

				this->Visible = false;
				this->SendToBack();

				if (this->Parent)
					this->Parent->Focus();

				return;
			}

#pragma region Events

			inline virtual void __clrcall OnProxySaveAttempt(Object^ _this, Object^ sender, Object^ data) {
				return;
			}

			inline void __clrcall OnKeyDown_(Object^ sender, KeyEventArgs^ event_k) {
				if (event_k->KeyCode == Keys::Enter)
					Hide(1);
				else if (event_k->KeyCode == Keys::Escape)
					Hide(0);
			}

			inline void __clrcall OnFocusLost(Object^ sender, EventArgs^ event_e) {
				Hide(false);
			}

#pragma endregion

#pragma region Ctor

			inline __clrcall TextBoxProxy(ListViewItem^% data, gui_data_t _type) : TextBox() {
				this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);

				this->original_data = data->SubItems[1]->Text;
				this->item_data_bound = data;
				this->data_type_ = _type;

				this->Visible = false;

				this->LostFocus += gcnew EventHandler(this, &TextBoxProxy::OnFocusLost);
				this->KeyDown += gcnew KeyEventHandler(this, &TextBoxProxy::OnKeyDown_);
				
			}

#pragma endregion

		};

		ref class EditableListView : public ListView {

		private:

			//nothing

		public:

			ProxySaveRequestedHandler^ ProxySaveRequested = gcnew ProxySaveRequestedHandler(this, &EditableListView::OnProxySaveRequested);

			static inline void __clrcall SetStyleListView(ListView^% lv_) {

				lv_->BackColor = global::hex_background_color;
				lv_->ForeColor = global::hex_text_foreground;
				SetWindowTheme(lv_->Handle, "explorer", nullptr);
				SendMessage(lv_->Handle, LVM_SETEXTENDEDLISTVIEWSTYLE, static_cast<IntPtr>(LVS_EX_DOUBLEBUFFER), static_cast<IntPtr>(LVS_EX_DOUBLEBUFFER));
			}

			inline __clrcall EditableListView() : ListView() {
				this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
				this->View = Windows::Forms::View::Details;
				this->FullRowSelect = true;
				this->MultiSelect = false;

				this->BackColor = global::hex_background_color;
				this->ForeColor = global::hex_text_foreground;

				SetWindowTheme(this->Handle, "explorer", nullptr);
				SendMessage(this->Handle, LVM_SETEXTENDEDLISTVIEWSTYLE, static_cast<IntPtr>(LVS_EX_DOUBLEBUFFER), static_cast<IntPtr>(LVS_EX_DOUBLEBUFFER));

				this->DoubleClick += gcnew EventHandler(this, &EditableListView::OnDoubleClick);
				this->ColumnWidthChanging += gcnew ColumnWidthChangingEventHandler(this, &EditableListView::OnColumnWidthChanging);
			}

			inline void __clrcall do_show_edit_box() {

				if (this->SelectedItems->Count) {

					auto% item = this->SelectedItems[0];

					if (item->SubItems->Count) {

						if (item->SubItems[1]->Text->Length) {

							if (item->SubItems[1]->Text == "Invalid")
								return;

							bool is_valid_index = true;
							gui_data_t _type = gui_data_t::BINARY;

							switch (item->Index) {
							case 0: {
								break;
							}
							case 1: {
								_type = gui_data_t::BYTE;
								break;
							}
							case 2: {
								_type = gui_data_t::SBYTE;
								break;
							}
							case 3: {
								_type = gui_data_t::USHORT;
								break;
							}
							case 4: {
								_type = gui_data_t::SHORT;
								break;
							}
							case 5: {
								_type = gui_data_t::UINT;
								break;
							}
							case 6: {
								_type = gui_data_t::INT;
								break;
							}
							case 7: {
								_type = gui_data_t::ULONGLONG;
								break;
							case 8: {
								_type = gui_data_t::LONGLONG;
								break;
							}
							case 9: {
								_type = gui_data_t::FLOAT32;
								break;
							}
							case 10: {
								_type = gui_data_t::FLOAT64;
								break;
							}
							case 11: {
								_type = gui_data_t::CHAR;
								break;
							}
							case 12: {
								_type = gui_data_t::WIDECHAR;
								break;
							}
							default: {
								is_valid_index = false;
								break;
							}
							}
							}

							if (!is_valid_index)
								return;

							TextBoxProxy^ proxy_editor = gcnew TextBoxProxy(item, _type);

							proxy_editor->Location = item->SubItems[1]->Bounds.Location;
							this->Parent->Controls->Add(proxy_editor);

							proxy_editor->ProxySaveAttempt += gcnew ProxySaveAttemptHandler(this, &EditableListView::OnProxySaveAttempt);

							proxy_editor->Show();

						}
					}

				}
			}

			inline void __clrcall OnDoubleClick(Object^ sender, EventArgs^ event_d) {

				do_show_edit_box();
			}

			inline void __clrcall OnProxySaveAttempt(Object^ editor, Object^ sender, Object^ data) {
				
				if (!editor)
					goto do_parse_data;

				if (!data || !this->SelectedItems->Count) { // invalid data entered
					reinterpret_cast<TextBoxProxy^>(editor)->Hide(false);
					delete editor;
					MB_ERR("Invalid Value Entered!", "");
					return;
				}

			do_parse_data:

				Object^ event_data;

				switch (this->SelectedItems[0]->Index) {
					case 0: {
						char* buffer = new char[8];

						string_to_char_array(reinterpret_cast<String^>(data), buffer, 8);

						auto to_byte = ::native::bits_to_t(buffer);

						event_data = to_byte;

						break;
					}
					case 1: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<Byte>(reinterpret_cast<String^>(data), ( global::type_endian_mode == little ? true : false)) : Byte::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 2: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<SByte>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : SByte::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 3: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<UInt16>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : UInt16::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 4: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<Int16>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : Int16::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 5: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<UInt32>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : UInt32::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 6: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<Int32>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : Int32::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 7: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<UInt64>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : UInt64::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 8: {
						event_data = global::is_type_view_hexadecimal ? util::parse_hex_string<Int64>(reinterpret_cast<String^>(data), (global::type_endian_mode == little ? true : false)) : Int64::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 9: {
						event_data = Single::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 10: {
						event_data = Double::Parse(reinterpret_cast<String^>(data));
						break;
					}
					case 11: {
						event_data = static_cast<char>(reinterpret_cast<String^>(data)[0]);
						break;
					}
					case 12: {
						event_data = Char::Parse(reinterpret_cast<String^>(data));
						break;
					}
					default: {
						event_data = nullptr;
						break;
					}
				}

				if (!event_data)
					return;

				this->ProxySaveRequested(editor, this->SelectedItems[0], event_data);

			}

			inline void __clrcall OnProxySaveRequested(Object^ editor, Object^ sender, Object^ data) {
				return;
			}

			inline void __clrcall OnColumnWidthChanging(Object^ sender, ColumnWidthChangingEventArgs^ event_c) {

				event_c->NewWidth = this->Columns[event_c->ColumnIndex]->Width;
				event_c->Cancel = true;

			}

		};

	}

}

#endif
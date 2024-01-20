#ifndef TEXTBASE_H
#define TEXTBASE_H

#pragma once
using namespace System;
using namespace System::Windows::Forms;

namespace hexasm {

	namespace gui {

		static constexpr wchar_t base_character_array_upper[16] {

			L'0', L'1', L'2', L'3', L'4',
			L'5', L'6', L'7', L'8', L'9',
			L'A', L'B', L'C', L'D', L'E',
			L'F'
		
		};

		static constexpr wchar_t base_character_array_lower[16] {

			L'0', L'1', L'2', L'3', L'4',
			L'5', L'6', L'7', L'8', L'9',
			L'a', L'b', L'c', L'd', L'e',
			L'f'

		};

		template<typename T>
		ref class TextBoxBaseExtension {

		private:

			short base_;

			TextBox^ text_box_;

			void __clrcall OnKeyDownFilter(Object^ sender, KeyPressEventArgs^ event_k) {

				if (!text_box_)
					return;

				bool is_valid_key = false;

				for (short i = 0; i < base_; ++i) {
					if (base_character_array_upper[i] == event_k->KeyChar) {
						is_valid_key = true;
						break;
					}
				}

				if (is_valid_key)
					goto do_key_press;

				for (short i = 0; i < base_; ++i) {
					if (base_character_array_lower[i] == event_k->KeyChar) {
						is_valid_key = true;
						break;
					}
				}

			do_key_press:

				//event_k->Handled = true;

				if (!is_valid_key) {
					if( event_k->KeyChar != static_cast<wchar_t>(Keys::Back) && event_k->KeyChar != static_cast<wchar_t>(Keys::Shift))
						event_k->Handled = true;
					return;
				}

				auto control_c = reinterpret_cast<TextBox^>(sender);

				auto% start_o = control_c->SelectionStart;

				event_k->KeyChar = Char::ToUpper(event_k->KeyChar);

				//control_c->Text = control_c->Text->Insert( control_c->SelectionStart, Char::ToString( Char::ToUpper( event_k->KeyChar ) ) );

				//control_c->Select(start_o + 1, 0);
			}

		public:

			inline __clrcall TextBoxBaseExtension(TextBox^% control_t, short base) : text_box_(control_t), base_(base) {

				AddKeyFilter(text_box_);
			}

			inline void AddKeyFilter(TextBox^% control_t) {
				control_t->KeyPress += gcnew KeyPressEventHandler(this, &TextBoxBaseExtension::OnKeyDownFilter);
			}

			inline void __clrcall swap_base(short base_new) {

				auto% text = text_box_->Text;

				try {

					switch (sizeof(T)) {

						case 1: {

							if (!text->Length)
								break;

							Byte cast_o = Convert::ToByte(text, base_);

							String^ base_o = Convert::ToString(cast_o, base_new);

							this->text_box_->Text = base_o;

							break;
						}
						case 2: { // parse WORD

							if (!text->Length)
								break;

							UInt16 cast_o = Convert::ToUInt16(text, base_);

							String^ base_o = Convert::ToString(static_cast<Int16>(cast_o), base_new)->ToUpper();

							this->text_box_->Text = base_o;

							break;
						}
						case 4: {

							if (!text->Length)
								break;

							UInt32 cast_o = Convert::ToUInt32(text, base_);

							String^ base_o = Convert::ToString(static_cast<Int32>(cast_o), base_new)->ToUpper();

							this->text_box_->Text = base_o;

							break;
						}
						case 8: {

							if (!text->Length)
								break;

							UInt64 cast_o = Convert::ToUInt64(text, base_);

							auto base_o = Convert::ToString(static_cast<Int64>(cast_o), base_new)->ToUpper();

							this->text_box_->Text = base_o;

							break;
						}
					}

				}
				catch (FormatException^) { text_box_->Text = ""; base_ = base_new; return; }

				base_ = base_new;
			}

		};		

	}

}


#endif

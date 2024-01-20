#ifndef DATAGRAPH_H
#define DATAGRAPH_H

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Collections::Generic;

using namespace Be::Windows::Forms;

#include "winprogress.h"

namespace hexasm {

	namespace gui {

#pragma region Type Definitions

		enum graph_view_type {

			block,
			distribution
		};

		typedef struct data_section {

			bool is_position_assigned;

			float graph_width_, graph_height_;
			float bar_height_, bar_width_;
			float bar_begin_, bar_end_;
			float begin_x, end_x;
			float begin_y, end_y;

			Int64 start_address;
			Int64 end_address;

			Byte average;
			Byte high;
			Byte low;
		};

#pragma endregion

		// make this graph view have all modes within it and create a switch inside paint method to determine which is displayed

		ref class data_graph : Control {

		private: static constexpr Int64 stream_buffer_size = 19200000; // 16mb

		private:

#pragma region Globals

			bool context_data_lock_ = false;

#pragma region Block View Globals

			data_section* context_data_section_;
			Point context_click_point_;

			Point mouse_client_pos_;
			array<PointF>^ mouse_line_pos_;
			array<PointF>^ mouse_line_pos_x_;

			data_section* file_line_section_;
			array<PointF>^ file_line_pos_;
			Pen^ file_line_color_;

			data_section* mouse_selected_section_;
			UInt32 mouse_selected_section_index_;

			List<UInt64>^ graph_list_;

#pragma endregion

#pragma region Other

			HexBox^ parent_;

			Pen^ outline_color_;

			Pen^ selection_line_color_;
			SolidBrush^ selection_text_color_;

			Pen^ bar_outline_;
			Pen^ bar_outline_active_;
			SolidBrush^ bar_inline_;

			Drawing::Font^ font_ = gcnew System::Drawing::Font("Courier New", 8);
			SizeF font_size ;

#pragma endregion

#pragma region Distribution View Globals

			array<UInt64>^ graph_distribution_list_;

			UInt64 max_byte_dist_ct;

			graph_view_type view_mode = graph_view_type::block;

#pragma endregion

#pragma endregion

#pragma region Helper Methods

			inline void __clrcall fetch_graph_data(Object^ obj) {

				bool show_dialog = static_cast<bool>(obj);

				winprogress^ dialog_p = gcnew winprogress();

				if (show_dialog) {
					dialog_p->Show();

					dialog_p->update_progress("Generating data graph...", 5);

					dialog_p->update_progress("Clearing cache...", 10);
				}

				if (graph_list_->Count)
					for (auto i = 0; i < graph_list_->Count; ++i)
						delete reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

				if (mouse_line_pos_)
					delete mouse_line_pos_;

				mouse_line_pos_ = nullptr;

				graph_list_->Clear();
				
				for (auto i = 0; i < 256; ++i)
					graph_distribution_list_[i] = static_cast<UInt64>(0x0);

				Stream^ stream;

				if (parent_->ByteProvider->Type == ProviderType::File)
					stream = reinterpret_cast<DynamicFileByteProvider^>(parent_->ByteProvider)->stream;
				else
					stream = gcnew MemoryStream(reinterpret_cast<DynamicByteProvider^>(parent_->ByteProvider)->Bytes->ToArray());

				auto position = stream->Position;
				stream->Position = 0;

				Int64 bytes_read = 0;

				Int64 buffer_size = (stream->Length / 200) ? (stream->Length / 200) : stream->Length;

				array<Byte>^ buffer = gcnew array<Byte>(stream_buffer_size);

				Int64 begin_address = 0;

				if(show_dialog)
					dialog_p->update_progress("Interpreting stream... ", 50);

				while ((bytes_read = stream->Read(buffer, 0, buffer->Length)) > 0) {

					Int64 end_address = stream->Position;

#pragma region Alignment Fixes

					auto section_count = bytes_read / buffer_size;

					array<Byte>^ scoped_buffer;

					if (!section_count) { // complete new block , we are dealing with a large file 

						auto buffer_t = gcnew array<Byte>(buffer_size - bytes_read);

						auto scoped_bytes_read = 0;

						scoped_bytes_read = stream->Read(buffer_t, 0, buffer_t->Length);

						scoped_buffer = gcnew array<Byte>(bytes_read + scoped_bytes_read);

						Array::Copy(buffer, scoped_buffer, bytes_read);
						Array::Copy(buffer_t, 0, scoped_buffer, static_cast<UInt32>(bytes_read), scoped_bytes_read);

						end_address += scoped_bytes_read;

						delete buffer_t;

						goto parse_data;
					}

					if (bytes_read % buffer_size) { // fill incomplete block, we are dealing with a smaller file

						auto buffer_t = gcnew array<Byte>(buffer_size - (bytes_read % buffer_size)); // fill remainder of block

						Int64 scoped_bytes_read = 0;

						scoped_bytes_read = stream->Read(buffer_t, 0, buffer_t->Length);

						scoped_buffer = gcnew array<Byte>(bytes_read + scoped_bytes_read);

						Array::Copy(buffer, 0, scoped_buffer, 0, static_cast<UInt32> (bytes_read));
						Array::Copy(buffer_t, 0, scoped_buffer, static_cast<UInt32>(bytes_read), static_cast<UInt32>(scoped_bytes_read));

						end_address += scoped_bytes_read;

						delete buffer_t;

					}
					else { // very small file, under 100 bytes

						scoped_buffer = gcnew array<Byte>(bytes_read);

						Array::Copy(buffer, scoped_buffer, bytes_read);
					}

#pragma endregion

				parse_data:
					
					if (!scoped_buffer)
						continue;

					auto stream_m = gcnew MemoryStream(scoped_buffer);

					Int64 bytes_read_m = 0;

					Int32 iterator = 0;

					array<Byte>^ buffer_m = gcnew array<Byte>((buffer_size == stream->Length ? 1 : buffer_size));

					while ((bytes_read_m = stream_m->Read(buffer_m, 0, buffer_m->Length)) > 0) {

						auto* section_d = new data_section();

						Byte high = 0;
						Byte low = 255;
						UInt64 average_inc = 0;

						for (auto i = 0; i < bytes_read_m; ++i) {
							high = (buffer_m[i] > high ? buffer_m[i] : high);
							low = (buffer_m[i] < low ? buffer_m[i] : low);

							average_inc += static_cast<int>(buffer_m[i]);

							++graph_distribution_list_[buffer_m[i]]; // byte distribution increment
						}

						section_d->high = high;
						section_d->low = low;
						section_d->average = static_cast<Byte>(Math::Round(average_inc / bytes_read_m));
						section_d->start_address = begin_address + (iterator * (buffer_size == stream->Length ? 1 : buffer_size));
						section_d->end_address = section_d->start_address + bytes_read_m;
						section_d->is_position_assigned = false;

						graph_list_->Add(reinterpret_cast<UInt64>(reinterpret_cast<void*>(section_d)));

						++iterator;
					}

					stream_m->Close();
					delete stream_m;

					begin_address = stream->Position;
				}

				if(show_dialog)
					dialog_p->update_progress("Freeing resources... ", 95);

				delete buffer;

				if (parent_->ByteProvider->Type == ProviderType::Memory)
					delete stream;

				if(show_dialog)
					dialog_p->update_progress("Done", 100);

				delete dialog_p;

				this->Invalidate();
			}

#pragma endregion

		public:

#pragma region Accessors

			property data_section* current_data_block {

				data_section* get() {
					return context_data_section_;
				}

			}

			property bool context_lock {

				bool get() {
					return context_data_lock_;
				}

				void set(bool in) {
					context_data_lock_ = in;
				}

			}

#pragma endregion

#pragma region Ctor / Dtor

			inline __clrcall data_graph(HexBox^% _parent) : parent_(_parent), Control() {

				this->ResizeRedraw = true;

				this->BackColor = Color::FromArgb(35, 35, 35);

				this->SetStyle(Windows::Forms::ControlStyles::OptimizedDoubleBuffer, true);

				this->SizeChanged += gcnew EventHandler(this, &data_graph::OnSizeChanged);
				this->MouseMove += gcnew MouseEventHandler(this, &data_graph::OnMouseMove);
				this->MouseLeave += gcnew EventHandler(this, &data_graph::OnMouseLeave);
				this->Click += gcnew EventHandler(this, &data_graph::OnClick);
				this->DoubleClick += gcnew EventHandler(this, &data_graph::OnDoubleClick);

				parent_->ByteProvider->Changed += gcnew EventHandler(this, &data_graph::OnByteChanged);
				parent_->ByteProvider->ChangesApplied += gcnew EventHandler(this, &data_graph::OnChangesAppied);
				parent_->SelectionStartChanged += gcnew EventHandler(this, &data_graph::OnSelectionStartChanged);
				parent_->ByteProviderChanged += gcnew EventHandler(this, &data_graph::OnProviderChanged);

				this->outline_color_ = Pens::WhiteSmoke;
				this->file_line_color_ = Pens::Lime;
				this->bar_outline_ = Pens::WhiteSmoke;
				this->bar_outline_active_ = Pens::Red;
				this->selection_line_color_ = Pens::WhiteSmoke;

				this->selection_text_color_ = gcnew SolidBrush(Color::Red);
				this->bar_inline_ = gcnew SolidBrush(Color::SteelBlue);

				graph_list_ = gcnew List<UInt64>();
				graph_distribution_list_ = gcnew array<UInt64>(256);

				auto graphics_t = this->CreateGraphics();
				font_size = graphics_t->MeasureString("FF", font_);

				fetch_graph_data(true);

				this->Paint += gcnew PaintEventHandler(this, &data_graph::OnPaint);

				this->OnSelectionStartChanged(nullptr, nullptr); // invoke this event because it contains data that must be initialized
			}


			inline __clrcall ~data_graph() {
				for (auto i = 0; i < graph_list_->Count; ++i)
					delete reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));
			}

#pragma endregion

#pragma region Event Callbacks

			inline void __clrcall OnSelectionStartChanged(Object^ sender, EventArgs^ e) {

				if (!graph_list_->Count)
					return;

				auto offset = parent_->SelectionStart;

				data_section* data_o;

				for (auto i = 0; i < graph_list_->Count; ++i) {

					data_o = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

					if (data_o->start_address <= offset)
						if (data_o->end_address > offset)
							break;

					data_o = nullptr;
				}

				if (!data_o)
					return;

				file_line_section_ = data_o;

				if (!file_line_pos_) // first iter
					return;

				delete file_line_pos_;

				file_line_pos_ = gcnew array<PointF>(2) { PointF(data_o->begin_x + 1.f, 3.f), PointF(data_o->begin_x + 1.f, data_o->begin_y) };

				this->Invalidate();
			}

			inline void __clrcall OnProviderChanged(Object^ sender, EventArgs^ event_p) {

				if (!parent_->ByteProvider)
					return;

				parent_->ByteProvider->ChangesApplied += gcnew EventHandler(this, &data_graph::OnChangesAppied);
				parent_->ByteProvider->Changed += gcnew EventHandler(this, &data_graph::OnByteChanged);

				fetch_graph_data(true); // this only occurs when saving a memory document to disk
			}

			inline void __clrcall OnChangesAppied(Object^ sender, EventArgs^ event_a) {

				if (!parent_->ByteProvider)
					return;

				fetch_graph_data(true); // this only occurs when saving a memory document to disk
			}

			inline void __clrcall OnByteChanged(Object^ sender, EventArgs^ event_b) {

				if (!parent_->ByteProvider)
					return;

				if (parent_->ByteProvider->Type != ProviderType::Memory)
					return;

				fetch_graph_data(false); // it is reasonable to refresh the graph whenever a change occurs from a memory document, but it is unreasonable and would kill performance to do this with a file
			}

			inline void __clrcall OnMouseLeave(Object^ sender, EventArgs^ event_l){
				
				if (!mouse_line_pos_)
					return;

				delete mouse_line_pos_;
				delete mouse_line_pos_x_;
				mouse_line_pos_ = nullptr;
				mouse_line_pos_x_ = nullptr;

				Invalidate();
			}

			inline void __clrcall OnMouseMove(Object^ sender, MouseEventArgs^ event_h) {

				if (!graph_list_->Count) {
					if (mouse_line_pos_) {
						delete mouse_line_pos_;
						delete mouse_line_pos_x_;
						mouse_line_pos_ = nullptr;
						mouse_line_pos_x_ = nullptr;
					}
					return;
				}

				auto* first_ = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[0]));

				if (!first_->is_position_assigned) // if for whatever reason the scaling has not been calculated, return
					return;

				auto coordinate_m = event_h->Location;

				if (coordinate_m.X < first_->begin_x || coordinate_m.X >((first_->begin_x - 1) + first_->graph_width_)) { // make sure mouse position is within graph area
					delete mouse_line_pos_;
					delete mouse_line_pos_x_;
					mouse_line_pos_ = nullptr;
					mouse_line_pos_x_ = nullptr;
					return;
				}

				data_section* selected_section;
				UInt32 section_index;

				for (auto i = 0; i < graph_list_->Count; ++i) {
					
					auto* data_o = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

					if (data_o->begin_x <= coordinate_m.X && data_o->end_x >= coordinate_m.X) {
						selected_section = data_o;
						section_index = i;
						break;
					}
				}
				
				if (!selected_section)
					return;

				if (!context_lock) {
					context_click_point_ = coordinate_m;
					context_data_section_ = selected_section;
				}
				else {
					return;
				}

				mouse_client_pos_ = coordinate_m;
				mouse_selected_section_ = selected_section;
				mouse_selected_section_index_ = section_index;

				mouse_line_pos_ = gcnew array<PointF>(2) { PointF(coordinate_m.X, 2.f), PointF(coordinate_m.X, selected_section->begin_y) };
				mouse_line_pos_x_ = gcnew array<PointF>(2) { PointF(selected_section->bar_begin_, coordinate_m.Y), PointF(selected_section->bar_end_, coordinate_m.Y) };

				Invalidate();
			}

			inline void __clrcall OnSizeChanged(Object^ sender, EventArgs^ event_d) {

				for (int i = 0; i < graph_list_->Count; ++i)
					reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]))->is_position_assigned = false;
			}

			inline void __clrcall OnClick(Object^ sender, EventArgs^ event_c) {

				if (!parent_->ByteProvider)
					return;

				if (!graph_list_->Count)
					return;

				auto event_cast = reinterpret_cast<MouseEventArgs^>(event_c);

				auto coordinate_m = PointToClient(this->MousePosition);

				data_section* data_o;

				for (auto i = 0; i < graph_list_->Count; ++i) {

					data_o = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

					if (data_o->begin_x <= coordinate_m.X)
						if (data_o->end_x > coordinate_m.X)
							break;

					data_o = nullptr;
				}

				if (!data_o)
					return;

				if (parent_->ByteProvider->Length < data_o->start_address)
					return;
				
				parent_->ScrollByteIntoView(data_o->start_address);
				parent_->Select(data_o->start_address, 1);
			}

			inline void __clrcall OnDoubleClick(Object^ sender, EventArgs^ event_d) {

				if (!parent_->ByteProvider)
					return;

				if (!graph_list_->Count)
					return;

				auto event_cast = reinterpret_cast<MouseEventArgs^>(event_d);

				if (event_cast->Button != Windows::Forms::MouseButtons::Left)
					return;

				auto coordinate_m = PointToClient(this->MousePosition);

				data_section* data_o;

				for (auto i = 0; i < graph_list_->Count; ++i) {

					data_o = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

					if (data_o->begin_x <= coordinate_m.X)
						if (data_o->end_x >= coordinate_m.X)
							break;

					data_o = nullptr;
				}

				if (!data_o)
					return;

				if (parent_->ByteProvider->Length < data_o->start_address)
					return;

				parent_->ScrollByteIntoView(data_o->start_address);
				parent_->Select(data_o->start_address, data_o->end_address <= parent_->ByteProvider->Length ? data_o->end_address - data_o->start_address : 1);
			}

#pragma region Drawing

			inline void __clrcall OnPaint(Object^ sender, PaintEventArgs^ event_p) {

				auto% graphics = event_p->Graphics;

				graphics->Clear(this->BackColor);
				
				auto graph_working_area = RectangleF( font_size.Width + 2.f, 2.f, (static_cast<float>(this->Width) - font_size.Width) - 3.f, this->Height - 3.f);

				auto ft_size_div = font_size.Height / 2.f;

				auto pt_lbl_mid_y = (static_cast<float>(this->Height / 2.f)) - ft_size_div;

				switch (view_mode) {

					case distribution: {

						auto mid_byte_ct = max_byte_dist_ct > 1 ? (max_byte_dist_ct / 2) : max_byte_dist_ct; // if max_byte_dist_ct then print ?

						break;
					}

					case block: {

						graphics->DrawString("00", font_, Brushes::WhiteSmoke, RectangleF(PointF(1, (this->Height - font_size.Height) - 1.f), font_size));

						graphics->DrawString("7F", font_, Brushes::WhiteSmoke, RectangleF(PointF(1, pt_lbl_mid_y), font_size));

						graphics->DrawString("FF", font_, Brushes::WhiteSmoke, RectangleF(PointF(1, 1), font_size));

						graphics->DrawRectangle(outline_color_, graph_working_area.X, graph_working_area.Y, graph_working_area.Width, graph_working_area.Height); // system::Drawing glitch, use relative height

						if (!graph_list_->Count) {

							String^ str_err = gcnew String("No data loaded!");

							auto err_sz = graphics->MeasureString(str_err, font_);

							graphics->DrawString("No data loaded!", font_, Brushes::Red, RectangleF(PointF((this->Width / 2) - (err_sz.Width / 2), (this->Height / 2) - (err_sz.Height / 2)), err_sz));

							delete str_err;

							return;
						}

						graphics->DrawLine(outline_color_, PointF(graph_working_area.X, pt_lbl_mid_y + ft_size_div), PointF(graph_working_area.Right, pt_lbl_mid_y + ft_size_div));

						float bar_width = (graph_working_area.Width / static_cast<float>(graph_list_->Count)); // graph_list_->Count is 1px pad between each, -2 before mult is outline, -2 last is outline per bar

						float scale_h = graph_working_area.Height / 255.f;

						data_section* first_;

						for (long i = 0; i < graph_list_->Count; ++i) {

							auto data_o = reinterpret_cast<data_section*>(reinterpret_cast<void*>(graph_list_[i]));

							if (!i)
								first_ = data_o;

							if (!data_o->is_position_assigned) {
								float rect_start = graph_working_area.X + ((bar_width * i) + 2);
								auto rect_end = rect_start + bar_width;

								float rect_y = (graph_working_area.Height + graph_working_area.Y) - (data_o->average * scale_h);

								float rect_height = data_o->average * scale_h;

								data_o->begin_x = rect_start;
								data_o->begin_y = rect_y;
								data_o->end_x = rect_end;
								data_o->end_y = rect_y + rect_height;
								data_o->is_position_assigned = true;
								data_o->graph_width_ = graph_working_area.Width;
								data_o->graph_height_ = graph_working_area.Height;
								data_o->bar_width_ = bar_width;
								data_o->bar_height_ = rect_height;
								data_o->bar_begin_ = graph_working_area.X;
								data_o->bar_end_ = graph_working_area.X + graph_working_area.Width;

								graphics->FillRectangle(bar_inline_, rect_start, rect_y, bar_width, rect_height);
							}
							else {
								graphics->FillRectangle(bar_inline_, data_o->begin_x, data_o->begin_y, data_o->end_x - data_o->begin_x, data_o->end_y - data_o->begin_y);
							}
						}

						if (!file_line_pos_)
							file_line_pos_ = gcnew array<PointF>(2) { PointF(first_->begin_x + 1.f, 2.f), PointF(first_->begin_x + 1.f, first_->begin_y) };

						graphics->DrawLine(file_line_color_, file_line_pos_[0], file_line_pos_[1]); // this is not updating position on resize, maybe the AfterResize() event would be proper to execute OnSelectionStartChanged event manually?

						if (file_line_section_)
							graphics->DrawRectangle(file_line_color_, file_line_section_->begin_x, file_line_section_->begin_y, file_line_section_->end_x - file_line_section_->begin_x, file_line_section_->end_y - file_line_section_->begin_y);

						if (mouse_line_pos_) {

							if (mouse_selected_section_)
								graphics->DrawRectangle(bar_outline_active_, mouse_selected_section_->begin_x, mouse_selected_section_->begin_y, mouse_selected_section_->end_x - mouse_selected_section_->begin_x, mouse_selected_section_->end_y - mouse_selected_section_->begin_y);

							graphics->DrawLine(selection_line_color_, mouse_line_pos_[0], mouse_line_pos_[1]);

							graphics->DrawLine(selection_line_color_, mouse_line_pos_x_[0], mouse_line_pos_x_[1]);

							String^ block_desc = gcnew String("Block (" + mouse_selected_section_->start_address.ToString("X16") + " - " + mouse_selected_section_->end_address.ToString("X16"));

							String^ block_min = gcnew String("Min: " + mouse_selected_section_->low.ToString("X2"));

							String^ block_max = gcnew String("Max: " + mouse_selected_section_->high.ToString("X2"));

							String^ block_avg = gcnew String("Avg: " + mouse_selected_section_->average.ToString("X2"));

							float scale_h = graph_working_area.Height / 255.f;

							Byte byte_val_column = static_cast<Byte>((mouse_selected_section_->graph_height_ - (mouse_client_pos_.Y - 2)) / scale_h);

							String^ column_val = gcnew String(byte_val_column.ToString("X2"));

							auto block_sz = graphics->MeasureString(block_desc, font_);
							auto block_inf_sz = graphics->MeasureString(block_min, font_);

							if (mouse_client_pos_.X + block_sz.Width + 2 > this->Width) {
								graphics->DrawString(column_val, font_, selection_text_color_, RectangleF((mouse_client_pos_.X - 2) - font_size.Width, (mouse_client_pos_.Y - font_size.Height) - 2, font_size.Width, font_size.Height));
								graphics->DrawString(block_desc, font_, selection_text_color_, RectangleF((mouse_client_pos_.X - 2) - block_sz.Width, mouse_client_pos_.Y + 20, block_sz.Width, block_sz.Height));
								graphics->DrawString(block_min, font_, selection_text_color_, RectangleF((mouse_client_pos_.X - 2) - (block_inf_sz.Width), static_cast<float>(mouse_client_pos_.Y + 21 + block_sz.Height), block_inf_sz.Width, block_inf_sz.Height));
								graphics->DrawString(block_max, font_, selection_text_color_, RectangleF((mouse_client_pos_.X - 2) - (block_inf_sz.Width), static_cast<float>(mouse_client_pos_.Y + 22 + (block_sz.Height * 2)), block_inf_sz.Width, block_inf_sz.Height));
								graphics->DrawString(block_avg, font_, selection_text_color_, RectangleF((mouse_client_pos_.X - 2) - (block_inf_sz.Width), static_cast<float>(mouse_client_pos_.Y + 23 + (block_sz.Height * 3)), block_inf_sz.Width, block_inf_sz.Height));
							}
							else {
								graphics->DrawString(column_val, font_, selection_text_color_, RectangleF((mouse_client_pos_.X + 2), (mouse_client_pos_.Y - font_size.Height) - 2, font_size.Width, font_size.Height));
								graphics->DrawString(block_desc, font_, selection_text_color_, RectangleF(mouse_client_pos_.X + 2, mouse_client_pos_.Y + 20, block_sz.Width, block_sz.Height));
								graphics->DrawString(block_min, font_, selection_text_color_, RectangleF(mouse_client_pos_.X + 2, mouse_client_pos_.Y + 21 + block_sz.Height, block_sz.Width, block_sz.Height));
								graphics->DrawString(block_max, font_, selection_text_color_, RectangleF(mouse_client_pos_.X + 2, mouse_client_pos_.Y + 22 + (block_sz.Height * 2), block_sz.Width, block_sz.Height));
								graphics->DrawString(block_avg, font_, selection_text_color_, RectangleF(mouse_client_pos_.X + 2, mouse_client_pos_.Y + 23 + (block_sz.Height * 3), block_sz.Width, block_sz.Height));
							}

							delete block_desc;
							delete block_min;
							delete block_max;
							delete block_avg;
							delete column_val;

							break;
						}
					}
				}
				graphics->DrawLine(outline_color_, PointF(graph_working_area.Right, graph_working_area.Y), PointF(graph_working_area.Right, graph_working_area.Height - graph_working_area.Y));
			}

#pragma endregion

#pragma endregion

		};

	}

}

#endif
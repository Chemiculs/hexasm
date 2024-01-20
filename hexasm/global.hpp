#ifndef GLOBAL_H
#define GLOBAL_H

#pragma once
using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Collections::Generic;

using namespace Be::Windows::Forms;

#include "resource/resource.hpp"
#include "disasm.hpp"
#include "native.hpp"
#include "util.hpp"
#include "def.hpp"
#include "hash.hpp"
#include "DataGraph.hpp"

static ref class global {

private:

	static Form^ main_window_;

	static bool is_type_view_hexadecimal_;

	static Image^ img_binary_document_;
	static Image^ img_document_;
	static Image^ img_document_delete_;
	static Image^ img_document_edit_;
	static Image^ img_document_new_;
	static Image^ img_document_plus_;
	static Image^ img_document_minus_;
	static Image^ img_document_export_;
	static Image^ img_document_hash_;
	static Image^ img_document_lines_;
	static Image^ img_aob_;
	static Image^ img_search_;
	static Image^ img_search_next_;
	static Image^ img_search_back_;
	static Image^ img_hex_;
	static Image^ img_string_;
	static Image^ img_float_;
	static Image^ img_integer_;
	static Image^ img_stack_;
	static Image^ img_type_;
	static Image^ bar_chart_;
	static Image^ img_insert_;
	static Image^ img_edit_;
	static Image^ img_write_hex_;
	static Image^ img_block_start_;
	static Image^ img_block_end_;
	static Image^ img_block_whole_;
	static Image^ img_block_ins_;
	static Image^ img_block_del_;
	static Image^ img_undo_;
	static Image^ img_redo_;
	static Image^ img_copy_plain_;
	static Image^ img_paste_plain_;
	static Image^ img_cut_hex_;
	static Image^ img_cut_string_;
	static Image^ img_copy_hex_;
	static Image^ img_copy_string_;
	static Image^ img_copy_offset_;
	static Image^ img_paste_hex_;
	static Image^ img_paste_string_;
	static Image^ img_edit_jmp_;
	static Image^ img_select_block_;
	static Image^ img_select_all_;
	static Image^ img_word_;
	static Image^ img_dword_;
	static Image^ img_qword_;
	static Image^ img_settings_cog_;
	static Image^ img_help_information_;
	static Image^ img_save_;
	static Image^ img_save_as_;
	static Image^ img_save_all_;
	static Image^ img_exit_;
	static Image^ img_c_;
	static Image^ img_cpp_;
	static Image^ img_java_;
	static Image^ img_python_;
	static Image^ img_csharp_;
	static Image^ img_perl_;
	static Image^ img_rust_;
	static Image^ img_vb_;
	static Image^ img_pascal_;

	static bool is_theme_dark_;

	static Font^ hex_editor_font_;

	static Color hex_headers_color_;
	static Color hex_background_color_;
	static Color hex_offset_columns_color_;
	static Color hex_foreground_selection_color_;
	static Color hex_background_selection_color_;
	static Color hex_text_foreground_;

	static List<HexBox^>^ hex_union_instances_;
	static List<hexasm::gui::data_graph^>^ graph_union_instances_;

	static List<FindOptions^>^ current_find_options_;

	static unsigned int disasm_t_block_size_;
	static hexasm::native::disasm_t* disasm_handle_;

	static hexasm::hash_g^ hasher_;

	static endian_mode type_endian_mode_;
	
public:

	static const Color DEFAULT_HEX_SELECTION_FORECOLOR = Color::WhiteSmoke;
	static const Color DEFAULT_HEX_SELECTION_BACKCOLOR = Color::FromArgb(0, 128, 255);
	static const Color DEFAULT_HEX_HEADERS_COLOR = Color::FromArgb(0, 128, 255);
	static const Color DEFAULT_TEXT_FOREGROUND_COLOR = Color::WhiteSmoke;
	static const Color DEFAULT_BACKGROUND_COLOR = Color::FromArgb(35, 35, 35);
	static const Color DEFAULT_OFFSET_COLOR = Color::Red;

	static property Form^ main_window {

		Form^ get() {
			return main_window_;
		}

		void set(Form^ in) {
			main_window_ = in;
		}

	}

	static property bool is_type_view_hexadecimal {

		bool get() {
			return is_type_view_hexadecimal_;
		}

		void set(bool in) {
			is_type_view_hexadecimal_ = in;
		}

	}

	static property Image^ img_binary_document {

		Image^ get() {
			return img_binary_document_;
		}

		void set(Image^ in) {
			img_binary_document_ = in;
		}

	}

	static property Image^ img_document {

		Image^ get() {
			return img_document_;
		}

		void set(Image^ in) {
			img_document_ = in;
		}

	}

	static property Image^ img_document_delete {

		Image^ get() {
			return img_document_delete_;
		}

		void set(Image^ in) {
			img_document_delete_ = in;
		}

	}

	static property Image^ img_document_edit {

		Image^ get() {
			return img_document_edit_;
		}

		void set(Image^ in) {
			img_document_edit_ = in;
		}

	}

	static property Image^ img_document_new {

		Image^ get() {
			return img_document_new_;
		}

		void set(Image^ in) {
			img_document_new_ = in;
		}

	}

	static property Image^ img_document_plus {

		Image^ get() {
			return img_document_plus_;
		}

		void set(Image^ in) {
			img_document_plus_ = in;
		}

	}

	static property Image^ img_document_minus{

		Image^ get() {
			return img_document_minus_;
		}

		void set(Image^ in) {
			img_document_minus_ = in;
		}

	}

	static property Image^ img_document_export {

		Image^ get() {
			return img_document_export_;
		}

		void set(Image^ in) {
			img_document_export_ = in;
		}

	}

	static property Image^ img_document_hash {

		Image^ get() {
			return img_document_hash_;
		}

		void set(Image^ in) {
			img_document_hash_ = in;
		}

	}

	static property Image^ img_document_lines {

		Image^ get() {
			return img_document_lines_;
		}

		void set(Image^ in) {
			img_document_lines_ = in;
		}

	}

	static property Image^ img_search {

		Image^ get() {
			return img_search_;
		}

		void set(Image^ in) {
			img_search_ = in;
		}

	}

	static property Image^ img_search_next {

		Image^ get() {
			return img_search_next_;
		}

		void set(Image^ in) {
			img_search_next_ = in;
		}

	}

	static property Image^ img_search_back {

		Image^ get() {
			return img_search_back_;
		}

		void set(Image^ in) {
			img_search_back_ = in;
		}

	}

	static property Image^ img_aob {

		Image^ get() {
			return img_aob_;
		}

		void set(Image^ in) {
			img_aob_ = in;
		}

	}

	static property Image^ img_hex {

		Image^ get() {
			return img_hex_;
		}

		void set(Image^ in) {
			img_hex_ = in;
		}

	}

	static property Image^ img_string {

		Image^ get() {
			return img_string_;
		}

		void set(Image^ in) {
			img_string_ = in;
		}

	}

	static property Image^ img_float {

		Image^ get() {
			return img_float_;
		}

		void set(Image^ in) {
			img_float_ = in;
		}

	}

	static property Image^ img_integer {

		Image^ get() {
			return img_integer_;
		}

		void set(Image^ in) {
			img_integer_ = in;
		}

	}

	static property Image^ img_stack {

		Image^ get() {
			return img_stack_;
		}

		void set(Image^ in) {
			img_stack_ = in;
		}

	}

	static property Image^ img_type {

		Image^ get() {
			return img_type_;
		}

		void set(Image^ in) {
			img_type_ = in;
		}

	}

	static property Image^ bar_chart {

		Image^ get() {
			return bar_chart_;
		}

		void set(Image^ in) {
			bar_chart_ = in;
		}

	}

	static property Image^ img_insert {

		Image^ get() {
			return img_insert_;
		}

		void set(Image^ in) {
			img_insert_ = in;
		}

	}

	static property Image^ img_edit {

		Image^ get() {
			return img_edit_;
		}

		void set(Image^ in) {
			img_edit_ = in;
		}

	}

	static property Image^ img_write_hex {

		Image^ get() {
			return img_write_hex_;
		}

		void set(Image^ in) {
			img_write_hex_ = in;
		}

	}

	static property Image^ img_block_start {

		Image^ get() {
			return img_block_start_;
		}

		void set(Image^ in) {
			img_block_start_ = in;
		}

	}

	static property Image^ img_block_end {

		Image^ get() {
			return img_block_end_;
		}

		void set(Image^ in) {
			img_block_end_ = in;
		}

	}

	static property Image^ img_block_whole {

		Image^ get() {
			return img_block_whole_;
		}

		void set(Image^ in) {
			img_block_whole_ = in;
		}

	}

	static property Image^ img_block_ins {

		Image^ get() {
			return img_block_ins_;
		}

		void set(Image^ in) {
			img_block_ins_ = in;
		}

	}

	static property Image^ img_block_del {

		Image^ get() {
			return img_block_del_;
		}

		void set(Image^ in) {
			img_block_del_ = in;
		}

	}

	static property Image^ img_undo {

		Image^ get() {
			return img_undo_;
		}

		void set(Image^ in) {
			img_undo_ = in;
		}

	}

	static property Image^ img_redo {

		Image^ get() {
			return img_redo_;
		}

		void set(Image^ in) {
			img_redo_ = in;
		}

	}

	static property Image^ copy_plain {

		Image^ get() {
			return img_copy_plain_;
		}

		void set(Image^ in) {
			img_copy_plain_ = in;
		}

	}

	static property Image^ img_copy_offset {

		Image^ get() {
			return img_copy_offset_;
		}

		void set(Image^ in) {
			img_copy_offset_ = in;
		}

	}

	static property Image^ paste_plain {

		Image^ get() {
			return img_paste_plain_;
		}

		void set(Image^ in) {
			img_paste_plain_ = in;
		}

	}

	static property Image^ cut_hex {

		Image^ get() {
			return img_cut_hex_;
		}

		void set(Image^ in) {
			img_cut_hex_ = in;
		}

	}

	static property Image^ cut_string {

		Image^ get() {
			return img_cut_string_;
		}

		void set(Image^ in) {
			img_cut_string_ = in;
		}

	}

	static property Image^ img_copy_hex {

		Image^ get() {
			return img_copy_hex_;
		}

		void set(Image^ in) {
			img_copy_hex_ = in;
		}

	}

	static property Image^ img_copy_string {

		Image^ get() {
			return img_copy_string_;
		}

		void set(Image^ in) {
			img_copy_string_ = in;
		}

	}

	static property Image^ img_paste_hex {

		Image^ get() {
			return img_paste_hex_;
		}

		void set(Image^ in) {
			img_paste_hex_ = in;
		}

	}

	static property Image^ img_paste_string {

		Image^ get() {
			return img_paste_string_;
		}

		void set(Image^ in) {
			img_paste_string_ = in;
		}

	}

	static property Image^ img_select_block {

		Image^ get() {
			return img_select_block_;
		}

		void set(Image^ in) {
			img_select_block_ = in;
		}

	}

	static property Image^ img_select_all{

		Image^ get() {
			return img_select_all_;
		}

		void set(Image^ in) {
			img_select_all_ = in;
		}

	}

	static property Image^ img_edit_jmp {

		Image^ get() {
			return img_edit_jmp_;
		}

		void set(Image^ in) {
			img_edit_jmp_ = in;
		}

	}

	static property Image^ img_word {

		Image^ get() {
			return img_word_;
		}

		void set(Image^ in) {
			img_word_ = in;
		}

	}

	static property Image^ img_dword {

		Image^ get() {
			return img_dword_;
		}

		void set(Image^ in) {
			img_dword_ = in;
		}

	}

	static property Image^ img_qword {

		Image^ get() {
			return img_qword_;
		}

		void set(Image^ in) {
			img_qword_ = in;
		}

	}

	static property Image^ img_settings_cog {

		Image^ get() {
			return img_settings_cog_;
		}

		void set(Image^ in) {
			img_settings_cog_ = in;
		}

	}

	static property Image^ img_help_information {

		Image^ get() {
			return img_help_information_;
		}

		void set(Image^ in) {
			img_help_information_ = in;
		}
		
	}

	static property Image^ img_save {

		Image^ get() {
			return img_save_;
		}

		void set(Image^ in) {
			img_save_ = in;
		}

	}

	static property Image^ img_save_as {

		Image^ get() {
			return img_save_as_;
		}

		void set(Image^ in) {
			img_save_as_ = in;
		}

	}

	static property Image^ img_save_all {

		Image^ get() {
			return img_save_all_;
		}

		void set(Image^ in) {
			img_save_all_ = in;
		}

	}

	static property Image^ img_exit {
		Image^ get() {
			return img_exit_;
		}

		void set(Image^ in) {
			img_exit_ = in;
		}

	}

	static property Color hex_background_color {

		Color get() {
			return hex_background_color_;
		}

		void set(Color in) {
			hex_background_color_ = in;
		}

	}

	static property Color hex_headers_color {
		Color get() {
			return hex_headers_color_;
		}

		void set(Color in) {
			hex_headers_color_ = in;
		}
	}

	static property Color hex_offset_columns_color {

		Color get() {
			return hex_offset_columns_color_;
		}

		void set(Color in) {
			hex_offset_columns_color_ = in;
		}

	}
	
	static property Color hex_foreground_selection_color {

		Color get() {
			return hex_foreground_selection_color_;
		}

		void set(Color in) {
			hex_foreground_selection_color_ = in;
		}

	}

	static property Color hex_background_selection_color {

		Color get() {
			return hex_background_selection_color_;
		}

		void set(Color in) {
			hex_background_selection_color_ = in;
		}

	}

	static property Color hex_text_foreground {

		Color get() {
			return hex_text_foreground_;
		}

		void set(Color in) {
			hex_text_foreground_ = in;
		}

	}

	static property bool is_theme_dark {

		bool get() {
			return is_theme_dark_;
		}

		void set(bool in) {
			is_theme_dark_ = in;
		}

	}

	static property Font^ hex_editor_font {

		Font^ get() {
			return hex_editor_font_;
		}

		void set(Font^ in) {
			hex_editor_font_ = in;
		}

	}

	static property List<HexBox^>^ hex_union_instances {

		List<HexBox^>^ get() {
			if (!hex_union_instances_)
				hex_union_instances_ = gcnew List<HexBox^>();

			return hex_union_instances_;
		}

		void set(List<HexBox^>^ in) {
			hex_union_instances_ = in;
		}

	}

	static property List<hexasm::gui::data_graph^>^ graph_union_instances {

		List<hexasm::gui::data_graph^>^ get() {
			if (!graph_union_instances_)
				graph_union_instances_ = gcnew List<hexasm::gui::data_graph^>();

			return graph_union_instances_;
		}

		void set(List<hexasm::gui::data_graph^>^ in) {
			graph_union_instances_ = in;
		}

	}

	static property List<FindOptions^>^ current_find_option {
		
		List<FindOptions^>^ get() {

			if (!current_find_options_)
				current_find_options_ = gcnew List<FindOptions^>();

			return current_find_options_;
		}

		void set(List<FindOptions^>^ in) {
			current_find_options_ = in;
		}
	}

	static property unsigned int disasm_t_block_size {

		unsigned int get() {
			return disasm_t_block_size_;
		}

		void set(unsigned int in) {
			disasm_t_block_size_ = in;
		}

	}

	static property hexasm::native::disasm_t* disasm_handle {

		hexasm::native::disasm_t* get() {
			return disasm_handle_;
		}

		void set(hexasm::native::disasm_t* in) {
			disasm_handle_ = in;
		}

	}

	static property hexasm::hash_g^ hasher {

		hexasm::hash_g^ get() {
			return hasher_;
		}

		void set(hexasm::hash_g^ in) {
			hasher_ = in;
		}

	}

	static property endian_mode type_endian_mode {

		endian_mode get() {
			return type_endian_mode_;
		}

		void set(endian_mode in) {
			type_endian_mode_ = in;
		}

	}

	static property Image^ img_c {

		Image^ get() {
			return img_c_;
		}

		void set(Image^ in) {
			img_c_ = in;
		}

	}

	static property Image^ img_cpp {

		Image^ get() {
			return img_cpp_;
		}

		void set(Image^ in) {
			img_cpp_ = in;
		}

	}

	static property Image^ img_java {

		Image^ get() {
			return img_java_;
		}

		void set(Image^ in) {
			img_java_ = in;
		}

	}

	static property Image^ img_python {

		Image^ get() {
			return img_python_;
		}

		void set(Image^ in) {
			img_python_ = in;
		}

	}

	static property Image^ img_csharp {

		Image^ get() {
			return img_csharp_;
		}

		void set(Image^ in) {
			img_csharp_ = in;
		}

	}

	static property Image^ img_perl {

		Image^ get() {
			return img_perl_;
		}

		void set(Image^ in) {
			img_perl_ = in;
		}

	}

	static property Image^ img_rust {

		Image^ get() {
			return img_rust_;
		}

		void set(Image^ in) {
			img_rust_ = in;
		}

	}

	static property Image^ img_vb {

		Image^ get() {
			return img_vb_;
		}

		void set(Image^ in) {
			img_vb_ = in;
		}

	}

	static property Image^ img_pascal {

		Image^ get() {
			return img_pascal_;
		}

		void set(Image^ in) {
			img_pascal_ = in;
		}

	}

};

#endif
#ifndef HASH_H
#define HASH_H

namespace hexasm {


	using namespace System;
	using namespace System::Security::Cryptography;

	ref class hash_g {

	public: delegate void HashProgressCallback(int iteration, int total);

	private:

		MD5^ md5_o_;

		SHA1^ sha1_o_;
		SHA256^ sha256_o_;
		SHA384^ sha384_o_;
		SHA512^ sha512_o_;

		RIPEMD160^ ripemd160_o_;

		HashProgressCallback^ callback_;

	public:

		inline __clrcall hash_g(HashProgressCallback^ callback) : callback_(callback) {

			md5_o_ = MD5::Create();

			sha1_o_ = SHA1::Create();
			sha256_o_ = SHA256::Create();
			sha384_o_ = SHA384::Create();
			sha512_o_ = SHA512::Create();

			ripemd160_o_ = RIPEMD160::Create();
		}

		inline __clrcall ~hash_g() {

			delete md5_o_;

			delete sha1_o_;
			delete sha256_o_;
			delete sha384_o_;
			delete sha512_o_;

			delete ripemd160_o_;
		}

		array<Byte>^ digest_md5(array<Byte>^ buffer) {

			auto buffer_r = md5_o_->ComputeHash(buffer);

			md5_o_->Clear();

			md5_o_ = MD5::Create();

			return buffer_r;
		}

		array<Byte>^ digest_sha1(array<Byte>^ buffer) {

			auto buffer_r = sha1_o_->ComputeHash(buffer);

			sha1_o_->Clear();

			sha1_o_ = SHA1::Create();

			return buffer_r;
		}

		array<Byte>^ digest_sha256(array<Byte>^ buffer) {

			auto buffer_r = sha256_o_->ComputeHash(buffer);

			sha256_o_->Clear();

			sha256_o_ = SHA256::Create();

			return buffer_r;

		}

		array<Byte>^ digest_sha384(array<Byte>^ buffer) {

			auto buffer_r = sha384_o_->ComputeHash(buffer);

			sha384_o_->Clear();

			sha384_o_ = SHA384::Create();

			return buffer_r;
		}

		array<Byte>^ digest_sha512(array<Byte>^ buffer) {

			auto buffer_r = sha512_o_->ComputeHash(buffer);

			sha512_o_->Clear();

			sha512_o_ = SHA512::Create();

			return buffer_r;
		}

		array<Byte>^ digest_ripemd160(array<Byte>^ buffer) {
			auto buffer_r = ripemd160_o_->ComputeHash(buffer);

			ripemd160_o_->Clear();

			ripemd160_o_ = RIPEMD160::Create();

			return buffer_r;
		}

		static constexpr unsigned int buffer_size = 19200000; // 16mb buffer cache

		// add a callback argument in Ctor to trigger progress reports for a progress window
		array<Byte>^ digest_md5_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {
				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					md5_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				md5_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = md5_o_->Hash;

				md5_o_->Clear();

				md5_o_ = MD5::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}

		array<Byte>^ digest_sha1_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {
				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					sha1_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				sha1_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = sha1_o_->Hash;

				sha1_o_->Clear();

				sha1_o_ = SHA1::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}

		array<Byte>^ digest_sha256_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {

				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					sha256_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				sha256_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = sha256_o_->Hash;

				sha256_o_->Clear();

				sha256_o_ = SHA256::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}

		array<Byte>^ digest_sha384_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {

				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					sha384_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				sha384_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = sha384_o_->Hash;

				sha384_o_->Clear();

				sha384_o_ = SHA384::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}

		array<Byte>^ digest_sha512_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {

				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					sha512_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				sha512_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = sha512_o_->Hash;

				sha512_o_->Clear();

				sha512_o_ = SHA512::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}

		array<Byte>^ digest_ripemd160_buffered(Stream^ stream) {

			auto iteration_div = stream->Length / buffer_size;

			if (stream->Length % buffer_size) // if extra data exists after last block append an iteration
				++iteration_div;

			array<Byte>^ buffer_r;

			array<Byte>^ buffer = gcnew array<Byte>(buffer_size);
			unsigned int bytes_read = 0;

			auto position_old = stream->Position;
			stream->Position = 0;

			try {

				auto current_iteration = 0;

				while ((bytes_read = stream->Read(buffer, 0, buffer_size)) > 0) {

					ripemd160_o_->TransformBlock(buffer, 0, bytes_read, nullptr, 0);

					callback_->Invoke(current_iteration, iteration_div - 1);

					++current_iteration;
				}
			}
			finally {
				ripemd160_o_->TransformFinalBlock(gcnew array<Byte>(0), 0, 0);

				buffer_r = ripemd160_o_->Hash;

				ripemd160_o_->Clear();

				ripemd160_o_ = RIPEMD160::Create();
			}

			stream->Position = position_old;

			return buffer_r;
		}
	};
}

#endif
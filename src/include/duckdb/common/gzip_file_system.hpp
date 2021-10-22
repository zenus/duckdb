//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/common/gzip_file_system.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/file_system.hpp"

namespace duckdb {

class GZipFileSystem : public FileSystem {
public:
	static unique_ptr<FileHandle> OpenCompressedFile(unique_ptr<FileHandle> handle);

	int64_t Read(FileHandle &handle, void *buffer, int64_t nr_bytes) override;

	void Reset(FileHandle &handle) override;

	int64_t GetFileSize(FileHandle &handle) override;

	bool OnDiskFile(FileHandle &handle) override;
	bool CanSeek() override {
		return false;
	}

	std::string GetName() const override {
		return "GZipFileSystem";
	}
};

static constexpr const uint8_t GZIP_COMPRESSION_DEFLATE = 0x08;

static constexpr const uint8_t GZIP_FLAG_ASCII = 0x1;
static constexpr const uint8_t GZIP_FLAG_MULTIPART = 0x2;
static constexpr const uint8_t GZIP_FLAG_EXTRA = 0x4;
static constexpr const uint8_t GZIP_FLAG_NAME = 0x8;
static constexpr const uint8_t GZIP_FLAG_COMMENT = 0x10;
static constexpr const uint8_t GZIP_FLAG_ENCRYPT = 0x20;

static constexpr const uint8_t GZIP_HEADER_MINSIZE = 10;

static constexpr const unsigned char GZIP_FLAG_UNSUPPORTED =
    GZIP_FLAG_ASCII | GZIP_FLAG_MULTIPART | GZIP_FLAG_EXTRA | GZIP_FLAG_COMMENT | GZIP_FLAG_ENCRYPT;

} // namespace duckdb

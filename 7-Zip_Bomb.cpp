#include <fstream>
#include <iostream>
#include <string>
#include "miniz.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Please specify a .zip file as an argument." << std::endl;
    return 1;
  }

  // Open the .zip file
  mz_zip_archive zip_archive;
  memset(&zip_archive, 0, sizeof(zip_archive));
  if (!mz_zip_reader_init_file(&zip_archive, argv[1], 0)) {
    std::cerr << "Failed to open the .zip file." << std::endl;
    return 1;
  }

  // Iterate over the files inside the .zip file
  int file_count = mz_zip_reader_get_num_files(&zip_archive);
  for (int i = 0; i < file_count; i++) {
    mz_zip_archive_file_stat file_stat;
    if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
      std::cerr << "Failed to retrieve file stat for file " << i << "." << std::endl;
      continue;
    }

    // Open the file inside the .zip archive
    size_t uncompressed_size;
    void* uncompressed_data = mz_zip_reader_extract_to_heap(&zip_archive, file_stat.m_filename, &uncompressed_size, 0);
    if (!uncompressed_data) {
      std::cerr << "Failed to extract file " << i << "." << std::endl;
      continue;
    }

    // Perform some manipulation on the file
    // ...

    // Clean up
    mz_free(uncompressed_data);
  }

  // Close the .zip file
  mz_zip_reader_end(&zip_archive);

  return 0;
}

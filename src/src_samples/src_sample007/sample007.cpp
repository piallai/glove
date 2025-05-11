/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 - 2025 Pierre Allain.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*! Example of how to open file streams using the Glove file system framework.
* Here is detailed how works the relative path as compared to the absolute path.*/

#ifndef OPTION_COMPILE_SAMPLES_WITH_SINGLE_HEADER
#include "filestream/SlvFileMgr.h"
#else
#include "glove.h"
#endif

int main(int argc, char *argv[]) {

    SlvStatus status; 

    SlvFile file("test-file0.xyz");
    std::cout << file.get_file_name().extension << std::endl;
    std::ofstream file_stream;
    // No absolute path provided => opens ./test-file0.xyz
    status = SlvFileMgr::open_file(file_stream, file);
    if (status) {
        file_stream.close();
    }

    SlvFileMgr::master_relative_path() = "../";
    file.set_name("test-file1.xyz");
    // No absolute path provided => opens ../test-file0.xyz
    status = SlvFileMgr::open_file(file_stream, file);
    if (status) {
        file_stream.close();
    }

#ifdef OS_WIN
    file.set_directory("C:/foo/foo/");// => replace with you own absolute path for example (Windows)
#elif defined(OS_LINUX)
    file.set_directory("/foo/foo/");// => replace with you own absolute path for example (Linux)
#endif
    file.set_name("test-file2.xyz");
    // Absolute path, therefore SlvFileMgr::master_relative_path() is ignored.
    // Opens: C:/foo/foo/test-file2.xyz
    // C:/foo/foo must already exist => no automatic folder creation
    status = SlvFileMgr::open_file(file_stream, file);
    if (status) {
        file_stream.close();
    } else {
        std::cout << status << std::endl;
    }

}


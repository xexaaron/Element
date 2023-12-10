#pragma once
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <string>
#include "../config.h"

namespace IO {
    struct FileData {
        std::filesystem::path Path;
        std::string Contents;
        std::string Name;
        size_t Lines;
        size_t Characters;
    };
    class File final {
    public:
        File(std::filesystem::path filepath) : Data{ filepath, "", "", 0, 0} {
            Data.Name = filepath.filename().string();
            ReadFile();
        }
        File(std::filesystem::path filepath, std::string contents) : Data{ filepath, contents,"", static_cast<size_t>(std::count(contents.begin(), contents.end(), '\n')), static_cast<size_t>(contents.size())} {
            Data.Name = filepath.filename().string();
            WriteFile();
        }
        File(File* file) : Data{ file->Data.Path, file->Data.Contents, file->Data.Name, file->Data.Lines, file->Data.Characters} {
            
        }
        ~File() {
            
        }
        std::string CopyFileContents() {
            return std::string(Data.Contents);
        }
        
        FileData Data;
    private: 
       void ReadFile() {
            std::ifstream inputFile(Data.Path);
            if (inputFile.is_open()) {
                std::string line;
                while (std::getline(inputFile, line)) {
                    Data.Contents += line + '\n';
                    for (size_t i = 0; i < line.size(); i++) {
                        Data.Characters++;
                    }
                    Data.Lines++;
                }
                inputFile.close();
            }
        }
        void WriteFile() {
            std::ofstream outputFile(Data.Path);
            if (outputFile.is_open()) {
                outputFile << Data.Contents;
                outputFile.close();
            }
        }
    };
}
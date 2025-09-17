// an exmaple to make a file
/*
#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace custom_bot {

    struct BotData {
        std::string name;
        std::vector<std::string> commands;
    };

    class FileManager {
    public:
        static bool save(const BotData& data, const std::string& filename) {
            std::filesystem::path savePath = "bot_saves/" + filename + ".txt";
            std::filesystem::create_directories("bot_saves");
            
            std::ofstream file(savePath);
            if (!file.is_open()) return false;

            file << data.name << "\n";
            for (const auto& cmd : data.commands) {
                file << cmd << "\n";
            }
            
            file.close();
            return true;
        }

        static bool load(BotData& data, const std::string& filename) {
            std::filesystem::path loadPath = "bot_saves/" + filename + ".txt";
            
            std::ifstream file(loadPath);
            if (!file.is_open()) return false;

            std::getline(file, data.name);
            
            std::string line;
            while (std::getline(file, line)) {
                data.commands.push_back(line);
            }
            
            file.close();
            return true;
        }
    };

    class Bot {
    private:
        BotData m_data;
        
    public:
        void setName(const std::string& name) {
            m_data.name = name;
        }
        
        void addCommand(const std::string& command) {
            m_data.commands.push_back(command);
        }
        
        bool save(const std::string& filename) {
            return FileManager::save(m_data, filename);
        }
        
        bool load(const std::string& filename) {
            return FileManager::load(m_data, filename);
        }
    };
}
    */
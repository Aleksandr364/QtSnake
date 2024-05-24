#ifndef PLAYERACHIEVEMENT_H
#define PLAYERACHIEVEMENT_H
#include <QString>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class PlayerAchievement
{
public:

    QString playerName = {};
    int fruitCount = 0;
    int gameTimeSeconds = 0;
    const std::string achievementsFile = "Achievements.txt";

    PlayerAchievement() = default;
    PlayerAchievement(const QString& playerName, int fruitCount, int gameTimeSeconds) :
        playerName(playerName), fruitCount(fruitCount), gameTimeSeconds(gameTimeSeconds) {}

    const QString& getName() const { return playerName; }
    int getFruits() const { return fruitCount; }
    int getTime() const { return gameTimeSeconds; }

    // Функция для записи достижений в файл.
    static void writeAchievements(const std::vector<PlayerAchievement>& achievements)
    {
        std::ofstream file("Achievements.txt", std::ios::trunc); // Открываем файл для перезаписи.
        if (file.is_open())
        {
            for (const auto& achievement : achievements)
            {
                file << achievement.getName().toStdString() << "\n"
                     << achievement.getFruits() << "\n"
                     << achievement.getTime() << "\n";
            }
            file.close();
        }
    }

    // Функция для чтения достижений из файла.
    static std::vector<PlayerAchievement> readAchievements()
    {
        std::vector<PlayerAchievement> achievements;
        std::ifstream file("Achievements.txt");
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                QString playerName = QString::fromStdString(line);

                if (!std::getline(file, line)) break;
                int fruitCount = std::stoi(line);

                if (!std::getline(file, line)) break;
                int gameTimeSeconds = std::stoi(line);

                achievements.emplace_back(playerName, fruitCount, gameTimeSeconds);
            }
            file.close();
        }
        return achievements;
    }

    // Переопределение операторов для класса PlayerAchievement.
    PlayerAchievement& operator=(const PlayerAchievement& rhs)
    {
        if (&rhs == this) return *this;
        fruitCount = rhs.fruitCount;
        gameTimeSeconds = rhs.gameTimeSeconds;
        return *this;
    }

    bool operator==(const PlayerAchievement& other) const { return fruitCount == other.fruitCount && gameTimeSeconds == other.gameTimeSeconds; }
    bool operator>(const PlayerAchievement& other) const
    {
        if (fruitCount > other.fruitCount) return true;
        if (fruitCount == other.fruitCount && gameTimeSeconds < other.gameTimeSeconds) return true;
        return false;
    }
};

#endif
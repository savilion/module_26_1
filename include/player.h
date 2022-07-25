#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>

class Player
{
    class TrackList
    {
        std::string nameTrack{};
        std::time_t dateCreationTrack{};
        int durationTrack{};
    public:
        void setField(std::string name, std::time_t now, int duration)
        {
            nameTrack = name;
            dateCreationTrack = now;
            durationTrack = duration;
        }
        std::string getNameTrack()
        {
            return nameTrack;
        }
        std::time_t getDateCreationTrack()
        {
            return dateCreationTrack;
        }
        int getDurationTrack()
        {
            return durationTrack;
        }
    };

    bool playbackKey = false;
    bool pauseKey = false;
    int currentTrack{};

    std::vector<TrackList> trackList;

public:

    void setAddTrack(int value)
    {
        std::srand(std::time(nullptr));

        auto *tmpTrack = new TrackList;

        for (int i = 0; i < value; ++i)
        {
            std::string name = "Track#" + std::to_string(i);
            std::time_t now = std::time(nullptr);
            int duration = rand() % 85 + 100;

            tmpTrack->setField(name, now, duration);
            trackList.push_back(*tmpTrack);
        }
        delete tmpTrack;
    }

    void showTrackList(Player* player)
    {
        for (int i = 0; i < player->trackList.size(); ++i)
        {
            std::cout << i << ". " << player->trackList[i].getNameTrack() << std::endl;
        }
    }
    void showTrackInfo(Player* player, int value)
    {
        std::time_t tmp = player->trackList[value].getDateCreationTrack();
        std::tm* local = std::localtime(&tmp);
        std::cout << "Track info: " << std::endl;
        std::cout << "Track name: " << player->trackList[value].getNameTrack() << ". Date created: " << std::put_time(local, "%Y/%m/%d %H:%M:%S") << ". Duration: " << player->trackList[value].getDurationTrack() << " sec" << std::endl;
    }
    void trackPlay(int value)
    {
        if (!playbackKey)
        {
            playbackKey = true;
            currentTrack = value;
            std::cout << "Play " << value << " track" << std::endl;
        }
    }
    void trackPause()
    {
        if (!pauseKey)
        {
            pauseKey = true;
            std::cout << "Track " << currentTrack << " is pause." << std::endl;
        }
        else if (playbackKey)
        {
            pauseKey = false;
        }
    }
    bool getPlayback()
    {
        return playbackKey;
    }
    bool getPause()
    {
        return pauseKey;
    }
    int getTrackNumber()
    {
        return trackList.size();
    }
    void setKeyStop()
    {
        playbackKey = false;
        pauseKey = false;
    }
};

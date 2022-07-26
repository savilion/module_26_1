#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>

class Player
{
    class Track
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

    std::vector<Track> trackList;

public:

    void setAddTrack()
    {
        std::srand(std::time(nullptr));
        int numTrack;
        auto *tmpTrack = new Track;

        std::cout << "How many tracks to add to the player: ";
        std::cin >> numTrack;

        for (int i = 0; i < numTrack; ++i)
        {
            std::string name = "Track#" + std::to_string(i);
            std::time_t now = std::time(nullptr);
            int duration = rand() % 85 + 100;
            tmpTrack->setField(name, now, duration);
            trackList.push_back(*tmpTrack);
        }
        delete tmpTrack;
    }

    void showTrackList()
    {
        for (int i = 0; i < trackList.size(); ++i)
        {
            std::cout << i << ". " << trackList[i].getNameTrack() << std::endl;
        }
    }
    void showTrackInfo(int value)
    {
        std::time_t tmp = trackList[value].getDateCreationTrack();
        std::tm* local = std::localtime(&tmp);
        std::cout << "Track info: " << std::endl;
        std::cout << "Track name: " << trackList[value].getNameTrack() << ". Date created: " << std::put_time(local, "%Y/%m/%d %H:%M:%S") << ". Duration: " << trackList[value].getDurationTrack() << " sec" << std::endl;
    }
    void playTrack(int value)
    {
        playbackKey = true;
        currentTrack = value;
        std::cout << "Play " << currentTrack << " track" << std::endl;
        showTrackInfo(value);
    }
    void keyPlay()
    {
        int value;
        if (!playbackKey)
        {
            showTrackList();
            std::cout << "Enter the track number: ";
            std::cin >> value;
            playTrack(value);
        }
        else if (playbackKey && !pauseKey)
        {
            std::cout << "The track is already playing." << std::endl;
        }
        else if (playbackKey && pauseKey)
        {
            std::cout << "Resume playback." << std::endl;
            pauseKey = false;
        }
    }
    void keyPause()
    {
        if (!pauseKey && playbackKey)
        {
            pauseKey = true;
            std::cout << "Track " << currentTrack << " is pause." << std::endl;
        }
        else if (!playbackKey)
        {
            std::cout << "Nothing is being played" << std::endl;
        }
    }
    void keyNextTrack()
    {
        std::srand(std::time(nullptr));
        int nextTrack = rand()%trackList.size();
        pauseKey = false;
        playbackKey = false;
        playTrack(nextTrack);
    }
    void keyStop()
    {
        if (playbackKey)
        {
            playbackKey = false;
            std::cout << "Playback stopped." << std::endl;
        }
    }
};

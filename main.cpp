#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>

class TrackList
{
    std::vector<std::string> nameTrack;
    std::vector<std::time_t> dateCreatedTrack;
    std::vector<int> durationTrack;
public:
    void setTrackList(std::string& name, std::time_t& date, int& duration)
    {
        nameTrack.push_back(name);
        dateCreatedTrack.push_back(date);
        durationTrack.push_back(duration);
    }

    std::vector<std::string> getNameTrack()
    {
        return nameTrack;
    }

    int numberTrack()
    {
        return nameTrack.size();
    }

    static void showTrackInfo(TrackList* trackList, int value)
    {
        std::tm* local = std::localtime(&trackList->dateCreatedTrack[value]);
        std::cout << "Track info: " << std::endl;
        std::cout << "Track name: " << trackList->nameTrack[value] << ". Date created: " << std::put_time(local, "%Y/%m/%d %H:%M:%S") << ". Duration: " << trackList->durationTrack[value] << " sec" << std::endl;
    }
};


class Player
{
    bool playbackKey = false;
    bool pauseKey = false;
    int currentTrack;
    std::vector<std::string> nameTrack;
public:
    void setCopyTrackToPlayer(const std::vector<std::string>& vec)
    {
        if (vec.empty())
        {
            std::cerr << "Tracks not loaded!" << std::endl;
        }
        else nameTrack.assign(vec.begin(), vec.end());
    }
    static void showTrackList(Player* player)
    {
        for (int i = 0; i < player->nameTrack.size(); ++i)
        {
            std::cout << i << ". " << player->nameTrack[i] << std::endl;
        }
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
    void setKeyStop()
    {
        playbackKey = false;
        pauseKey = false;
    }
};


int main()
{
    std::srand(std::time(nullptr));
    auto* trackList = new TrackList();
    auto* player = new Player();

    for (int i = 0; i < 5; ++i)
    {
        std::string name = "Track#" + std::to_string(i);
        std::time_t now = std::time(nullptr);
        int duration = rand()%85 + 100;

        trackList->setTrackList(name, now, duration);
    }

    player->setCopyTrackToPlayer(trackList->getNameTrack());

    while (true)
    {
        std::string answer;
        std::cout << R"(Enter "play" to start/resume playback, "next" next track, "stop" to stop, "exit" to exit)" << std::endl;
        std::cout << "-> ";
        std::cin >> answer;

        if (answer == "play")
        {
            int num;
            if (player->getPlayback() && !player->getPause())
            {
                std::cout << "The track is already playing." << std::endl;
            }
            else if (player->getPlayback() && player->getPause())
            {
                std::cout << "Resume playback." << std::endl;
            }
            else
            {
                Player::showTrackList(player);
                std::cout << "Enter the track number: ";
                std::cin >> num;
                player->trackPlay(num);
                TrackList::showTrackInfo(trackList,num);
            }
        }
        else if (answer == "pause")
        {
            if (!player->getPlayback()) std::cout << "Nothing is being played" << std::endl;
            else if (!player->getPause())
            {
                player->trackPause();
            }
        }
        else if (answer == "next")
        {
            int nextTrack = rand()%trackList->numberTrack();
            player->setKeyStop();
            player->trackPlay(nextTrack);
            TrackList::showTrackInfo(trackList,nextTrack);
        }
        else if (answer == "stop")
        {
            if (player->getPlayback())
            {
                player->setKeyStop();
                std::cout << "Playback stopped." << std::endl;
            }
        }
        else if (answer == "exit") break;
    }

    delete trackList;
    delete player;
    trackList = nullptr;
    player = nullptr;
    return 0;
}

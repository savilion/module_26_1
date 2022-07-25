#include <iostream>
#include "player.h"


int main()
{

    std::srand(std::time(nullptr));
    auto* player = new Player();

    int numTrack;
    std::cout << "How many tracks to add to the player: ";
    std::cin >> numTrack;

    player->setAddTrack(numTrack);

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
                player->showTrackList(player);
                std::cout << "Enter the track number: ";
                std::cin >> num;
                player->trackPlay(num);
                player->showTrackInfo(player,num);
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
            int nextTrack = rand()%player->getTrackNumber();
            player->setKeyStop();
            player->trackPlay(nextTrack);
            player->showTrackInfo(player,nextTrack);
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

    delete player;
    player = nullptr;
    return 0;
}

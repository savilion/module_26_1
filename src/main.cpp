#include <iostream>
#include "player.h"

int main()
{
    auto* player = new Player();
    player->setAddTrack();

    while (true)
    {
        std::string answer;
        std::cout << R"(Enter "play" to start/resume playback, "next" next track, "stop" to stop, "exit" to exit)" << std::endl;
        std::cout << "-> ";
        std::cin >> answer;

        if (answer == "play")
        {
            player->keyPlay();
        }
        else if (answer == "pause")
        {
            player->keyPause();
        }
        else if (answer == "next")
        {
            player->keyNextTrack();
        }
        else if (answer == "stop")
        {
            player->keyStop();
        }
        else if (answer == "exit") break;
    }

    delete player;
    player = nullptr;
    return 0;
}

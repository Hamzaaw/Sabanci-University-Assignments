//Hamza Wasim
//00030456


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>
#include <iomanip>

using namespace std;

mutex coutMutex, gameMutex, roundMutex;
int targetNumber;
int numRounds;
int lowerBound, upperBound;
bool roundWon = false;
int winnerID = -1;
bool roundStarted = false;
bool gameOver = false;

struct Player {
    int id;
    int score;
};

vector<Player> players;

int random_range(const int &min, const int &max) {
    static thread_local mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void host_function(int numPlayers) {
    {
        lock_guard<mutex> lock(coutMutex);
        cout << endl<<"---------------------------------------------------" << endl;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        cout << "Game started at: " << put_time(ltm, "%X") << endl;
    }
    this_thread::sleep_for(chrono::seconds(3));

    for (int round = 1; round <= numRounds; ++round) {
        {
            lock_guard<mutex> lock(gameMutex);
            targetNumber = random_range(lowerBound, upperBound);
            roundWon = false;
            winnerID = -1;
        }

        {
            lock_guard<mutex> lock(roundMutex);
            roundStarted = true;
        }

        {
            lock_guard<mutex> lock(coutMutex);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            
            if(round == 1){
            cout << "Round " << 1 << " will start 3 seconds later" << endl;
                cout<<endl;
            }
            if(round != 1){
                cout << "Round " << round << " started at: " << put_time(ltm, "%X") << endl;
//                cout<<endl;
            }
            cout << "Target is " << targetNumber << endl << endl;
        }

        while (true) {
            this_thread::sleep_for(chrono::milliseconds(10));
            lock_guard<mutex> lock(gameMutex);
            if (roundWon) {
                players[winnerID].score++;
                break;
            }
        }

        {
            lock_guard<mutex> lock(coutMutex);
            cout << "Player with id " << winnerID << " won round " << round << endl;
            if (round < numRounds) {
                cout <<endl<< "---------------------------------------------------" << endl;
//                cout << "Round " << round + 1 << " will start 3 seconds later" << endl;
                this_thread::sleep_for(chrono::seconds(3));
            }
        }

        {
            lock_guard<mutex> lock(roundMutex);
            roundStarted = false;
        }
    }

    {
        lock_guard<mutex> lock(roundMutex);
        gameOver = true; // signal game over t
        roundStarted = true; //  exit wait loop
    }
}

void player_function(int id) {
    while (true) {
        {
            lock_guard<mutex> lock(roundMutex);
            if (roundStarted) {
                break;
            }
            if (gameOver) {
                return;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }

    for (int round = 1; round <= numRounds; ++round) {
        while (true) {
            {
                lock_guard<mutex> lock(roundMutex);
                if (roundStarted) {
                    break;
                }
                if (gameOver) {
                    return;
                }
            }
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        while (true) {
            {
                lock_guard<mutex> lock(gameMutex);
                if (roundWon) {
                    break;
                }
            }

            int guess = random_range(lowerBound, upperBound);
            bool correctGuess = false;
            {
                lock_guard<mutex> lock(gameMutex);
                if (guess == targetNumber) {
                    roundWon = true;
                    winnerID = id;
                    correctGuess = true;
                }
            }

            {
                lock_guard<mutex> lock(coutMutex);
                time_t now = time(0);
                tm *ltm = localtime(&now);
                cout << "Player with id " << id << " guessed " << guess << (correctGuess ? " correctly" : " incorrectly") << " at: " << put_time(ltm, "%X") << endl;
            }

            if (correctGuess) {
                break;
            }

            this_thread::sleep_for(chrono::seconds(1));
        }

        {
            lock_guard<mutex> lock(roundMutex);
            roundStarted = false;
        }

        {
            lock_guard<mutex> lock(roundMutex);
            if (gameOver) {
                return;
            }
        }
    }
}

int main() {
    int numPlayers;

    cout << "Please enter number of players: ";
    while (!(cin >> numPlayers) || numPlayers < 1) {
        cout << "Number of players cannot be lower than 1!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter number of players: ";
    }

    cout << "Please enter number of rounds: ";
    while (!(cin >> numRounds) || numRounds < 1) {
        cout << "Number of rounds cannot be lower than 1!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter number of rounds: ";
    }

    cout << "Please enter the randomization range: ";
    while (!(cin >> lowerBound >> upperBound) || lowerBound > upperBound) {
        cout << "Lower bound has to be smaller than or equal to higher bound" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter the randomization range: ";
    }

    players.resize(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        players[i].id = i;
        players[i].score = 0;
    }

    vector<thread> playerThreads;
    for (int i = 0; i < numPlayers; ++i) {
        playerThreads.emplace_back(thread(player_function, i));
    }

    thread hostThread(host_function, numPlayers);

    hostThread.join();
    for (auto &t : playerThreads) {
        t.join();
    }

    cout << endl << "Game is over!" << endl;
    cout << "Leaderboard:" << endl;
    for (const auto& player : players) {
        cout << "Player " << player.id << " has won " << player.score << " times" << endl;
    }

    return 0;
}

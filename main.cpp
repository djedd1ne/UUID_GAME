#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <list>
#include <chrono>
#include <thread>
#include <atomic>

std::list<boost::uuids::uuid> generate() {
    std::list<boost::uuids::uuid> uuids;
    boost::uuids::random_generator gen;
    for (int i = 0; i < 100; ++i) {
        boost::uuids::uuid new_uuid = gen();
        uuids.push_back(new_uuid);
    }
    return uuids;
}

char selectRandomCharacter() {
    const std::string characters = "0123456789abcdef";
    int index = std::rand() % 16; // Generate a random index [0, 15]
    return characters[index];
}

bool containsCharacter(const boost::uuids::uuid& uuid, char character) {
    bool ret;
    std::string str = boost::uuids::to_string(uuid);
    ret = str.find(character) != std::string::npos;
    return  ret;
}

void removeUUIDsWithCharacter(std::list<boost::uuids::uuid>& uuids, char character) {
    uuids.remove_if([&character](const boost::uuids::uuid& uuid) { // Use lambda expression
        return containsCharacter(uuid, character);
    });
}

void displayTimeLeft(std::atomic<bool>& running, std::atomic<int>& remainingTime) {
    while (running && remainingTime > 0) {
        std::cout << "\rTime left: " << remainingTime << " seconds ";
        std::flush(std::cout);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --remainingTime;
    }
    if (remainingTime == 0)
        std::cout << "\nTime's Up, Enter a character to proceed" << std::endl; // Move to a new line after countdown ends
}

int main(){
    char guess;
    int score = 0;

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator

    while (true) {
        std::list<boost::uuids::uuid> uuids = generate();
        char randomChar = selectRandomCharacter();
        //std::cout << "Random character: " << randomChar << std::endl; // Print random character
        removeUUIDsWithCharacter(uuids, randomChar);
        std::cout << "Remaining UUIDs after removing those containing random character" << std::endl;
        for (const auto& uuid : uuids) {
            std::cout << boost::uuids::to_string(uuid) << std::endl;
        }

        std::atomic<bool> running(true);
        std::atomic<int> remainingTime(30);
        std::thread timerThread(displayTimeLeft, std::ref(running), std::ref(remainingTime));


        std::cout << "\nPLEASE ENTER A CHARACTER [09-af]" << std::endl;
        auto start = std::chrono::steady_clock::now(); // Capture start time
        std::cin >> guess; // Get input
        auto end = std::chrono::steady_clock::now(); // Capture end time

        running = false;
        timerThread.join();

        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        if ((guess == randomChar || std::tolower(guess) == randomChar) && elapsedSeconds <= 30) {
                score += 30 - elapsedSeconds;
                std::cout << "Correct guess! Your score: " << score << std::endl;
        } else {
            std::cout << "Game Over! Your final score: " << score << std::endl;
            break;
        }
    }

    return 0;
}
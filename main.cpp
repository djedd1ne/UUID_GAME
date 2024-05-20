#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <list>

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

int main(){
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed random generator
    std::list<boost::uuids::uuid> uuids = generate();
    char randomChar = selectRandomCharacter();
    std::cout << "Random character: " << randomChar << std::endl; // print random character

    return 0;
}
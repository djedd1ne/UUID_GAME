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

int main(){
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed random generator
    std::list<boost::uuids::uuid> uuids = generate();
    char randomChar = selectRandomCharacter();
    //std::cout << "Random character: " << randomChar << std::endl; // print random character
    removeUUIDsWithCharacter(uuids, randomChar);
    std::cout << "Remaining UUIDs after removing those containing [" << randomChar << "]:" << std::endl;
    for (const auto& uuid : uuids) {
        std::cout << boost::uuids::to_string(uuid) << std::endl;
    }

    return 0;
}
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
        std::cout << "Generated UUID: " << boost::uuids::to_string(new_uuid) << std::endl;
    }
    return uuids;
}

int main(){
    std::list<boost::uuids::uuid> uuids = generate();
    return 0;
}
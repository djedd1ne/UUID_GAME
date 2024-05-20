#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

boost::uuids::uuid generate() {
    boost::uuids::uuid uuid;
    std::cout << boost::uuids::to_string(uuid) <<std::endl;
    return uuid;
}

int main(){
    boost::uuids::uuid uuid = generate();
    return 0;
}
#include "dataManager.h"
#include "configManager.h"

#include "uuid.h" // stduuid lib

#include <iostream>
#include <string>
#include <filesystem>

void DataMan::Test() {
    std::cout << "===| DATA MAN TEST |===" << std::endl;
    // uuids::uuid testUUID;
    // std::cout << testUUID.is_nil() << std::endl;

    // for (int i = 0; i < 10; i++) {
        // std::cout << CreateUUIDString() << std::endl;
    // }
}

std::string DataMan::CreateUUIDString() {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{generator};

    return uuids::to_string(gen());
}

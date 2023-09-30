//
// Created by Antares on 2023/9/16.
//

#include "tls_wrapper.h"
#include <memory>
#include <thread>
#include <iostream>

void test_body() {
    auto &ptr = Antares::tls_get<std::shared_ptr<int>>();
    ptr = std::make_shared<int>(1);
}

//void test_mingw_fail() {
//    thread_local std::shared_ptr<int> ptr = std::make_shared<int>(0);
//    ptr = std::make_shared<int>(1);
//}

int main() {
    std::thread thread_test(test_body);
    thread_test.join();
//    std::thread thread_mingw_fail(test_mingw_fail);
//    thread_mingw_fail.join();
    std::cout << "test success" << std::endl;
    return 0;
}

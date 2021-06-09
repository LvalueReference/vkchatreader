#ifndef READER_HPP
#define READER_HPP

#include "lib/api/vk_api.hpp"
#include "lib/api/longpoll_api.hpp"
#include "lib/network/network.hpp"
#include "simdjson/simdjson.h"

namespace vk{
    struct reader{
    private:
        vk::vk_api _api;
        vk::longpoll_api _lp;
        /// Всё что ниже - не нужно как поля класса
        simdjson::dom::parser _parser;
        simdjson::dom::element _json;

        std::string _message, _response;
        int _peer_id, _from_id;

        /// Это тоже, скорее всего не нужно как члены класса
        /// Короче, это класс ради класса. Тебе здесь нужна одна функция
        std::string from();
        std::string message();

    public:
        void run();
    };
}

#endif //READER_HPP
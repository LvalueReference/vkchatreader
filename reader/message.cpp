#include "message.hpp"

#include "reader/color.hpp"
#include "fmt/format.h"

using reader::color;

std::string colorize_fwd_template(){
    std::string_view fwd_template = "\t\t\t{}┌[{}{{}}{}]\n\t\t\t└[message]-> {}{{}}{{}}{}\n";

    return fmt::format(fwd_template, fg(color::CLEAR), fg(color::BOLD_GREEN), fg(color::CLEAR), fg(color::BOLD_YELLOW),
                       fg(color::CLEAR));
}

template<class T>
static std::string make_fwd(T from, T types, T text){
    return fmt::format(colorize_fwd_template(), from, types, text);
}

void reader::message::operator=(simdjson::dom::element json){
    _reader_data = reader::reader_data{std::string(json["object"]["message"]["text"]),
                                       json["object"]["message"]["peer_id"], json["object"]["message"]["from_id"]};

    _message_parser = json;
    _json = json;
}

std::string reader::message::message_text() const{
    std::string result = _reader_data.message;

    if (_message_parser.has_attachments()){
        for (const auto& att: _message_parser.get_attachments()){
            result.append(fmt::format(" [{}]", _message_parser.get_attachment_type(att)));
        }
    }

    if (_message_parser.has_reply())
        result.append(fmt::format(" [reply to {}: {}{}] ", _message_parser.get_reply_from(),
                                  _message_parser.get_reply_attachments_types(), _message_parser.get_reply_text()));

    if (_message_parser.has_fwd()){
        result.append(" {fwd message}:\n");

        for (const auto& fwd: _message_parser.get_fwd()){
            result.append(make_fwd(_message_parser.get_fwd_from(fwd), _message_parser.get_fwd_attachments_types(fwd),
                                   _message_parser.get_fwd_text(fwd)));
        }
    }

    return result;
}

std::string reader::message::from() const{
    return (_reader_data.from_id > 0 ? _api.user_get(_reader_data.from_id) : _api.group_get(_reader_data.from_id));
}

std::string reader::message::current_time() const{
    std::ostringstream stream;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    stream << std::put_time(&tm, "%H:%M:%S");

    return stream.str();
}

std::string reader::message::chat_name() const{
    return _api.get_chat_name(_reader_data.peer_id);
}
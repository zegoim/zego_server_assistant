//
// Created by zego on 2019-07-09.
//

#ifndef JSON_TOOLS_HPP
#define JSON_TOOLS_HPP

#include <string>
#include "../rapidjson/document.h"
#include "../rapidjson/pointer.h"
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/writer.h"

#include "../rapidjson/error/en.h"
#include "../rapidjson/pointer.h"
#include "../rapidjson/reader.h"

namespace ZEGO {

    namespace JSON_TOOLS {

        template<typename T>
        inline void AddMember(rapidjson::Document &doc, const char *k, T v) {
            if (!k) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, doc.GetAllocator());

            rapidjson::Value value(v);
            doc.AddMember(key, value, doc.GetAllocator());
        }

        template<typename T>
        inline void AddMember(rapidjson::Value &obj, const char *k, T v,
                            rapidjson::Document::AllocatorType &allocator) {
            if (!k) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, allocator);
            rapidjson::Value value(v);
            obj.AddMember(key, value, allocator);
        }

        template<>
        inline void AddMember(rapidjson::Document &doc, const char *k, bool v) {
            if (!k) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, doc.GetAllocator());

            rapidjson::Value value(v);
            value.SetBool(v);

            doc.AddMember(key, value, doc.GetAllocator());
        }

        template<>
        inline void AddMember(rapidjson::Document &doc, const char *k, double v) {
            if (!k) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, doc.GetAllocator());

            rapidjson::Value value(v);
            value.SetDouble(v);

            doc.AddMember(key, value, doc.GetAllocator());
        }

        template<>
        inline void AddMember(rapidjson::Document &doc, const char *k, const char *v) {
            if (!k || !v) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, doc.GetAllocator());

            rapidjson::Value value;
            value.SetString(v, doc.GetAllocator());

            doc.AddMember(key, value, doc.GetAllocator());
        }


        template<>
        inline void AddMember(rapidjson::Value &obj, const char *k, rapidjson::Value *value,
                            rapidjson::Document::AllocatorType &allocator) {
            if (!k || !value) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, allocator);

            obj.AddMember(key, *value, allocator);
        }


        template<>
        inline void AddMember(rapidjson::Value &obj, const char *k, const char *v,
                            rapidjson::Document::AllocatorType &allocator) {
            if (!k || !v) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, allocator);

            rapidjson::Value value;
            value.SetString(v, allocator);

            obj.AddMember(key, value, allocator);
        }

        template<>
        inline void AddMember(rapidjson::Value &obj, const char *k, int32_t &value,
                            rapidjson::Document::AllocatorType &allocator) {
            if (!k) {
                return;
            }

            rapidjson::Value key;
            key.SetString(k, allocator);

            obj.AddMember(key, value, allocator);
        }

        class JsonTools {
        public:

            static std::string jsonObjectToString(const rapidjson::Value &data, const std::string &name,
                                                const std::string &key) {
                const rapidjson::Value &userInfo = data[name.c_str()];
                if (!userInfo.IsObject() || !userInfo.HasMember(key.c_str())) {
                    return "";
                }

                return userInfo[key.c_str()].GetString();
            }

            static std::int32_t jsonObjectToInt(const rapidjson::Value &data, const std::string &name,
                                                const std::string &key) {
                const rapidjson::Value &userInfo = data[name.c_str()];
                if (!userInfo.IsObject() || !userInfo.HasMember(key.c_str())) {
                    return 0;
                }

                return userInfo[key.c_str()].GetInt();
            }


            static std::string
            jsonToString(const rapidjson::Document &document, const std::string &key) {

                if (document.HasParseError() || !document.HasMember(key.c_str())) {
                    return "";
                }

                std::string str = document[key.c_str()].GetString();

                return str;
            }

            static std::string jsonToString(const rapidjson::Value &data, const std::string &key) {

                if (data.IsString() || !data.HasMember(key.c_str())) {
                    return "null";
                }

                std::string str = data[key.c_str()].GetString();

                return str;
            }

            static std::int32_t jsonToInt(const rapidjson::Value &data, const std::string &key) {

                if (data.IsInt() || !data.HasMember(key.c_str())) {
                    return -1;
                }

                std::int32_t v = data[key.c_str()].GetInt();

                return v;
            }

            static std::int32_t jsonToInt(const rapidjson::Document &document, const std::string &key) {

                if (document.HasParseError() || !document.HasMember(key.c_str())) {
                    return 0;
                }

                if (!document[key.c_str()].IsInt()) {
                    return 0;
                }
                return document[key.c_str()].GetInt();
            }

            static std::string rapiJsonToStr(rapidjson::Value &content) {
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                content.Accept(writer);
                return buffer.GetString();
            }
        };

    }
}

#endif //JSON_TOOLS_HPP

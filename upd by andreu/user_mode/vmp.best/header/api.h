#pragma once

#include <string>
#include <vector>

/*
info
---
uses curl
grabs classes and properties from http://vmp.best/
updates from the site :p
api made in 5 mins
this made in another 5 mins
*/

namespace offsetlib {

    class JsonValue {
    public:
        explicit JsonValue ( const std::string& json );
        bool contains ( const std::string& key ) const;
        std::string get_string ( const std::string& key ) const;
        std::vector<std::string> get_string_array ( ) const;
        std::vector<JsonValue> get_array ( ) const;

    private:
        std::string raw_json;
        std::string get_string_between ( const std::string& s , const std::string& start_delim , const std::string& stop_delim ) const;
    };

    uintptr_t hex_to_uintptr ( const std::string& hex_str );
    uintptr_t get_offset ( const std::string& class_name , const std::string& property_name );
    std::vector<std::string> get_classes ( );
    std::vector<std::string> get_class_properties ( const std::string& class_name );
     
    void initialize ( ); // inits the CURL
    void cleanup ( ); // cleans up the CURL

} // namespace offsetlib

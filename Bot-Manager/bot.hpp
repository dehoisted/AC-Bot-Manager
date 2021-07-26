#pragma once
#include <string>
#include <array>

class Bot {
public:
    std::string skill = "none";
    std::array<const char*, 5> skills = { "bad", "worse", "medium", "good", "best" }; //"good" is the default skill type
    bool idling = true;
    inline static int yes_idle = 1, no_idle = 0;

    Bot(const Bot&) = delete;
    static Bot& Get();

    auto Config() -> void;
    [[nodiscard]] static std::string Get_Random_Name(int length_of_string);

private:
    Bot() = default;
    static Bot instance;
};
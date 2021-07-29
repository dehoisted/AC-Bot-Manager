#pragma once
#include <string>
#include <array>

class Bot {
public:
    std::string skill = "none";
    const std::array<const char*, 5> skills = { "bad", "worse", "medium", "good", "best" }; //"good" is the default skill type

	// Changing of bots settings
    bool shooting = false;
    inline static int no_shoot = 0, yes_shoot = 1;
    bool idling = true;
    inline static int no_idle = 0, yes_idle = 1;
	
    static Bot& Get();
    auto Config() -> void;
    [[nodiscard]] static std::string Get_Random_Name(int length_of_string);

private:
    Bot() = default;
    static Bot instance;
};
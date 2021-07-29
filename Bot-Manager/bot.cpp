#include "pch.h"
#include "bot.hpp"
#include <random>

Bot& Bot::Get()
{
    return instance;
}

void Bot::Config()
{
	if (this->skill == "none")
        skill = "good";
    else {
		static bool valid = false;
		for (auto& s : this->skills)
        {
            if (this->skill == s)
                valid = true;
        }

        if (!valid)
            this->skill = "good";
    }
}

std::string Bot::Get_Random_Name(const int length_of_string)
{
    static std::string randstr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(randstr.begin(), randstr.end(), generator);
    return randstr.substr(0, length_of_string);
}
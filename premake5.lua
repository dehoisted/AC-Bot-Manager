--[[
   premake5.lua
   Only for bot manager, not the injector.
   7/26/2021
--]]

workspace "AC-Bot-Manager"
   configurations { "Debug", "Release" }

project "Bot-Manager"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files 
   { 
      "acf.hpp", "bot.hpp", "framework.h", "mem.h", "pch.h", -- Headers
      "bot.cpp" , "dllmain.cpp", "pch.cpp" -- Sources
   }

   defines
   {
      "WIN32",
      "_CRT_SECURE_NO_WARNINGS";
   }

   links
   {
      "kernel32.lib",
      "user32.lib",
      "shell32";
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      runtime "Debug"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "on"
      runtime "Release"

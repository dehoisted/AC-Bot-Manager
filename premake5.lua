--[[
   premake5.lua
   For both project files, Bot-Manager and BM_Injector
   7/28/2021
--]]

workspace "AC-Bot-Manager"
   configurations { "Debug", "Release" }

project "Bot-Manager"
   kind "SharedLib"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files 
   { 
      "acf.hpp", "bot.hpp", "framework.h", "mem.h", "pch.h",
      "bot.cpp" , "dllmain.cpp", "pch.cpp"
   }

   defines
   {
      "WIN32",
      "_CRT_SECURE_NO_WARNINGS";
   }

   links
   {
      "kernel32",
      "user32",
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

project "BM_Injector"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files 
   { 
      "main.cpp"
   }

   defines
   {
      "WIN32",
      "_CRT_SECURE_NO_WARNINGS";
   }

   links
   {
      "kernel32",
      "user32",
      "shell32";
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      runtime "Debug"

   filter "configurations:Release"
      defines { "NDEBUG", "_CONSOLE"}
      optimize "on"
      runtime "Release"

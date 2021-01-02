#pragma once
#include "engine/Log.hpp"

void InitLogLevel(char* level);

class Window
{
public:
    Window(int argc, char** argv)
    {
        HandleArgs(argc, argv);
    }

    void SetWidth(float width) { _width = width; }
    void SetHeight(float height) { height = _height; }

    float Width() const { return _width; }
    float Height() const { return _height; }

private:
    void HandleArgs(int argc, char** argv)
    {
        InitLogLevel("-none");
        InitScreenSize("hd");

        for (size_t i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-none") == 0 || strcmp(argv[i], "-info") == 0 || strcmp(argv[i], "-warning") == 0)
                InitLogLevel(argv[i]);
            else if (strcmp(argv[i], "-hd") == 0 || strcmp(argv[i], "-fhd") == 0)
                InitScreenSize(argv[i]);
        }
    }

    void InitScreenSize(char* size)
    {
        if (strcmp(size, "-hd") == 0)
        {
            _width = 1280.0f;
            _height = 720.0f;
        }
        else if (strcmp(size, "-fhd") == 0)
        {
            _width = 1920.0f;
            _height = 1080.0f;
        }
    }

    float _width = 1280.0f;
    float _height = 720.0f;
};


void InitLogLevel(char* level)
{
    if (strcmp(level, "-info") == 0)
        Log::Get().SetLevel(LogLevel::INFO);
    else if (strcmp(level, "-warning") == 0)
        Log::Get().SetLevel(LogLevel::WARNING);
    else if (strcmp(level, "-error") == 0)
        Log::Get().SetLevel(LogLevel::ERROR);
    else
        Log::Get().SetLevel(LogLevel::NONE);
}
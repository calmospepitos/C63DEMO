#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <functional>
#include <string>

class Button
{
public:
    Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo);
    ~Button();

    void SetColors(const Color& InColorNeutral, const Color& InHoverNeutral, const Color& InPressedNeutral);
    void DrawAndUpdate();

private:
    Rectangle rect;
    std::string text;
    std::function<void()> action;
    Color colorNeutral, colorHover, colorPressed;
};

#endif // BUTTON_H

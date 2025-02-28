#include "Button.h"
#include <iostream>

// Constructor
Button::Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo)
{
    rect = { (float)InPositionX, (float)InPositionY, (float)InLargeur, (float)InHauteur };
    text = InText;
    action = InActionToDo;
    colorNeutral = RED;
    colorHover = LIGHTGRAY;
    colorPressed = DARKGRAY;
}

// Destructor
Button::~Button() {}

// Set button colors
void Button::SetColors(const Color& InColorNeutral, const Color& InHoverNeutral, const Color& InPressedNeutral)
{
    colorNeutral = InColorNeutral;
    colorHover = InHoverNeutral;
    colorPressed = InPressedNeutral;
}

// Draw and handle button clicks
void Button::DrawAndUpdate()
{
    Vector2 mouse = GetMousePosition();
    Color currentColor = colorNeutral;

    if (CheckCollisionPointRec(mouse, rect))
    {
        currentColor = colorHover;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            currentColor = colorPressed;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            action();  // Execute the button's action
        }
    }

    DrawRectangleRec(rect, currentColor);

    // Calculate text width and height for centering
    int fontSize = 20;  // Change if needed
    int textWidth = MeasureText(text.c_str(), fontSize);
    int textHeight = fontSize; // Raylib fonts are usually fontSize in height

    // Center text inside the button
    int textX = rect.x + (rect.width - textWidth) / 2;
    int textY = rect.y + (rect.height - textHeight) / 2;

    // Draw the button text centered
    DrawText(text.c_str(), textX, textY, fontSize, BLACK);
}
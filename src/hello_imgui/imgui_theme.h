#pragma once
#include "imgui.h"


namespace ImGuiTheme
{
    enum ImGuiTheme_
    {
        ImGuiTheme_ImGuiColorsClassic = 0,
        ImGuiTheme_ImGuiColorsDark,
        ImGuiTheme_ImGuiColorsLight,
        ImGuiTheme_MaterialFlat,
        ImGuiTheme_PhotoshopStyle,
        ImGuiTheme_GrayVariations,
        ImGuiTheme_GrayVariations_Darker,
        ImGuiTheme_MicrosoftStyle,
        ImGuiTheme_Cherry,
        ImGuiTheme_Darcula,
        ImGuiTheme_LightRounded,
        ImGuiTheme_SoDark_AccentBlue,
        ImGuiTheme_SoDark_AccentYellow,
        ImGuiTheme_SoDark_AccentRed,
        ImGuiTheme_BlackIsBlack,
        ImGuiTheme_WhiteIsWhite,
        ImGuiTheme_Count
    };
    const char* ImGuiTheme_Name(ImGuiTheme_ theme);
    ImGuiStyle ThemeToStyle(ImGuiTheme_ theme);
    void ApplyTheme(ImGuiTheme_ theme);


    struct ImGuiThemeTweaks
    {
        // Common rounding for widgets. If < 0, this is ignored.
        float Rounding = -1.f;
        // If rounding is applied, scrollbar rounding needs to be adjusted to be visually pleasing in conjunction with other widgets roundings. Only applied if Rounding > 0.f)
        float RoundingScrollbarRatio = 4.f;
        // Change the alpha that will be applied to windows, popups, etc. If < 0, this is ignored.
        float AlphaMultiplier = -1.f;

        //
        // HSV Color tweaks
        //
        // Change the hue of all widgets (gray widgets will remain gray, since their saturation is zero). If < 0, this is ignored.
        float Hue = -1.f;
        // Multiply the saturation of all widgets (gray widgets will remain gray, since their saturation is zero). If < 0, this is ignored.
        float SaturationMultiplier = -1.f;
        // Multiply the value of all front widgets. If < 0, this is ignored.
        float ValueMultiplierFront = -1.f;
        // Multiply the value of all backgrounds. If < 0, this is ignored.
        float ValueMultiplierBg = -1.f;
    };

    struct ImGuiTweakedTheme
    {
        ImGuiTheme_ Theme = ImGuiTheme_ImGuiColorsDark;
        ImGuiThemeTweaks Tweaks = {};
    };

    ImGuiStyle TweakedThemeThemeToStyle(const ImGuiTweakedTheme& tweaked_theme);
    void ApplyTweakedTheme(const ImGuiTweakedTheme& tweaked_theme);

    // Show the theme selection listbox, the theme tweak widgets, as well as ImGui::ShowStyleEditor. Returns true if modified (Warning, when using ShowStyleEditor, no info about modification is transmitted)
    bool ShowThemeTweakGui(ImGuiTweakedTheme *tweaked_theme);

    // Some tweakable themes
    ImGuiStyle SoDark(float hue);
    ImGuiStyle ShadesOfGray(float rounding=0.f, float value_multiplier_front=1.f, float value_multiplier_bg=1.f);
    ImGuiStyle Darcula(
        float rounding=1.f,
        float hue=-1.f,
        float saturation_multiplier=1.f,
        float value_multiplier_front=1.f,
        float value_multiplier_bg=1.f
    );


} // namespace ImGuiTheme
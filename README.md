# MSettings

A Unreal Engine plugin for implementing customizable game settings that users can change in in-game menus.

## Overview

MSettings provides a flexible framework for creating and managing game settings in Unreal Engine projects. It includes:

- Base classes for different types of settings (discrete options, toggles, etc.)
- Pre-built implementations for common settings like resolution, fullscreen mode, VSync, and scalability
- A subsystem for managing settings lifecycle
- UI widgets for displaying settings in menus
- Data-driven configuration through collections and categories

### Built-in Settings

The plugin includes ready-to-use implementations for common game settings:

- **Resolution**: Allows users to select from available screen resolutions
- **Fullscreen Mode**: Windowed, fullscreen, or borderless fullscreen options
- **VSync**: Enable/disable vertical synchronization
- **Scalability**: Quality settings for graphics, effects, textures, etc., using Unreal's built-in scalability system

## Installation

1. Copy the `MSettings` folder to your project's `Plugins` directory
2. Enable the plugin in your `.uproject` file or through the Unreal Editor
3. Restart the editor

## Basic Usage

### 1. Create a Settings Collection

Create a new `UMGameSettingsCollection` data asset in the Content Browser. Add the settings you want to include by specifying their classes.

### 2. Configure Developer Settings

In Project Settings > Plugins > M Game Settings, set the Game Settings Collection to your created asset.

### 3. Access Settings in Code

```cpp
UMGameSettingsSubsystem* SettingsSubsystem = UGameInstance::GetSubsystem<UMGameSettingsSubsystem>(GetGameInstance());
UMGameSetting_Base* ResolutionSetting = SettingsSubsystem->GetSettingObjectForClass(UMGameSetting_Resolution::StaticClass());
```

### 4. Create Settings UI

Use `UMGameSettingsPanelWidget` in your UMG widgets. Set the `SettingsCategoryDefinition` to define which settings to display.

## Creating Custom Settings

Extend `UMGameSetting_Base` or `UMGameSetting_Discrete` for custom settings. You can either:

- Use built-in scalability settings by extending `UMGameSetting_Scalability_Base` for graphics quality controls
- Create completely custom settings that apply to your own game systems

Example of a custom discrete setting:

```cpp
UCLASS()
class UMyCustomSetting : public UMGameSetting_Discrete
{
    GENERATED_BODY()

    virtual TArray<FName> GetPossibleOptionIds() override
    {
        return { "Low", "Medium", "High" };
    }

    virtual void Apply_Implementation() override
    {
        // Apply the setting to your game systems
    }
};
```

## Features

- Real-time or on-apply setting changes
- Automatic saving/loading of settings
- Blueprint support
- Extensible architecture
- CommonUI integration

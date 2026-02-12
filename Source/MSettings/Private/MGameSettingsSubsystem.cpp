// Copyright (c) Miknios. All rights reserved.


#include "MGameSettingsSubsystem.h"

#include "MGameSettingsCollection.h"
#include "MGameSettingsDeveloperSettings.h"
#include "MGameSetting_Base.h"

void UMGameSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	GameSettingsCollection = UMGameSettingsDeveloperSettings::Get()->GameSettingsCollection.LoadSynchronous();

	if (GameSettingsCollection == nullptr)
	{
		return;
	}

	InitializeSettings();
}

UMGameSetting_Base* UMGameSettingsSubsystem::GetSettingObjectForClass(const TSubclassOf<UMGameSetting_Base> SettingClass)
{
	for (TObjectPtr<UMGameSetting_Base> SettingObject : SettingObjects)
	{
		if (SettingObject.IsA(SettingClass))
		{
			return SettingObject;
		}
	}

	return nullptr;
}

void UMGameSettingsSubsystem::InitializeSettings()
{
	if (GameSettingsCollection == nullptr)
	{
		return;
	}

	SettingObjects.Reserve(GameSettingsCollection->ActiveSettings.Num());
	for (const FMSettingsCollectionEntry& SettingCollectionEntry : GameSettingsCollection->ActiveSettings)
	{
		UMGameSetting_Base* SettingObject = NewObject<UMGameSetting_Base>(this, SettingCollectionEntry.SettingClass);
		if (SettingObject == nullptr)
		{
			continue;
		}

		SettingObjects.Emplace(SettingObject);
	}

	for (TObjectPtr<UMGameSetting_Base> SettingObject : SettingObjects)
	{
		SettingObject->Initialize();
	}
}

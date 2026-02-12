// Copyright (c) Miknios. All rights reserved.


#include "MGameSettingsSaveObject.h"

UMGameSettingsSaveObject* UMGameSettingsSaveObject::Get()
{
	UMGameSettingsSaveObject* SaveObject = GetMutableDefault<UMGameSettingsSaveObject>();
	return SaveObject;
}

void UMGameSettingsSaveObject::Save()
{
	UMGameSettingsSaveObject* SaveObject = Get();
	if (!IsValid(SaveObject))
	{
		return;
	}

	SaveObject->SaveConfig();
}

int32 UMGameSettingsSaveObject::GetSavedValueForSettingName(const FName SettingName)
{
	UMGameSettingsSaveObject* SaveObject = Get();
	if (!IsValid(SaveObject))
	{
		return -1;
	}

	if (!SaveObject->SettingValueForName.Contains(SettingName))
	{
		return -1;
	}

	return SaveObject->SettingValueForName[SettingName];
}

void UMGameSettingsSaveObject::SetSavedValueForSettingName(const FName SettingName, const int32 Value)
{
	UMGameSettingsSaveObject* SaveObject = Get();
	if (!IsValid(SaveObject))
	{
		return;
	}

	SaveObject->SettingValueForName.Emplace(SettingName, Value);
}

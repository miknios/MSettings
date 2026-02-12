// Copyright (c) Miknios. All rights reserved.


#include "MSettingsCategoryDefinition.h"

#include "MGameSetting_Base.h"

TSubclassOf<UMGameSettingWidget_Base> UMSettingsCategoryDefinition::GetWidgetClassForSetting(const UMGameSetting_Base& SettingItem)
{
	for (const FMSettingCategoryEntry& Entry : SettingsInCategory)
	{
		if (Entry.SettingClass == nullptr)
		{
			continue;
		}

		if (Entry.SettingClass == SettingItem.GetClass())
		{
			return Entry.SettingWidgetClass;
		}
	}

	return nullptr;
}

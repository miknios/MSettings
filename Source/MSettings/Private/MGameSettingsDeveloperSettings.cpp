// Copyright (c) Miknios. All rights reserved.


#include "MGameSettingsDeveloperSettings.h"

UMGameSettingsDeveloperSettings* UMGameSettingsDeveloperSettings::Get()
{
	return CastChecked<UMGameSettingsDeveloperSettings>(StaticClass()->GetDefaultObject());
}

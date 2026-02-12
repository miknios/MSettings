// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UI/MGameSettingWidget.h"
#include "MSettingsCategoryDefinition.generated.h"

class UMGameSetting_Base;

USTRUCT(BlueprintType)
struct FMSettingCategoryEntry
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMGameSetting_Base> SettingClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMGameSettingWidget_Base> SettingWidgetClass;
};

/**
 * Defines a series of settings grouped together in UI
 * Assigned to a compatible widget that generates a list of options based on options defined
 */
UCLASS()
class MSETTINGS_API UMSettingsCategoryDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	TArray<FMSettingCategoryEntry> SettingsInCategory;
	
	TSubclassOf<UMGameSettingWidget_Base> GetWidgetClassForSetting(const UMGameSetting_Base& SettingItem);
};

// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MGameSettingsCollection.generated.h"

class UMGameSetting_Base;

USTRUCT(BlueprintType)
struct FMSettingsCollectionEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMGameSetting_Base> SettingClass;
};

UCLASS()
class MSETTINGS_API UMGameSettingsCollection : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMSettingsCollectionEntry> ActiveSettings;
};

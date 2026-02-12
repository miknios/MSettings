// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameSetting_Base.h"
#include "MGameSetting_FullscreenMode.generated.h"

UCLASS()
class MSETTINGS_API UMGameSetting_FullscreenMode : public UMGameSetting_Discrete
{
	GENERATED_BODY()
	
	// ~ UMGameSetting_Base
	virtual void Initialize_Implementation() override;
	virtual void Apply_Implementation() override;
	virtual void SelectSavedOrDefaultValue() override;
	virtual void SelectDefaultValue() override;
	// ~ UMGameSetting_Base

	// ~ UMGameSetting_Discrete
	virtual TArray<FName> GetPossibleOptionIds() override;
	// ~ UMGameSetting_Discrete
	
protected:
	FName GetOptionIdForValue(int32 FullscreenModeValue);
};

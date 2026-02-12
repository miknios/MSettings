// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameSetting_Base.h"
#include "MGameSetting_VSync.generated.h"

UCLASS(Abstract)
class MSETTINGS_API UMGameSetting_VSync : public UMGameSetting_Discrete
{
	GENERATED_BODY()
	
public:
	// ~ UMGameSetting_Base
	virtual void Apply_Implementation() override;
	virtual void SelectSavedOrDefaultValue() override;
	virtual void SelectDefaultValue() override;
	// ~ UMGameSetting_Base
	
	// ~ UMGameSetting_Discrete
	virtual TArray<FName> GetPossibleOptionIds() override;
	// ~ UMGameSetting_Discrete
};

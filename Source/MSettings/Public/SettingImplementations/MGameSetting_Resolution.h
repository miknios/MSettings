// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MGameSetting_Base.h"
#include "MGameSetting_Resolution.generated.h"

UCLASS()
class MSETTINGS_API UMGameSetting_Resolution : public UMGameSetting_Discrete
{
	GENERATED_BODY()

public:
	UMGameSetting_Resolution();
	
	// ~ UMGameSetting_Base
	virtual void Initialize_Implementation() override;
	virtual bool IsAvailable() const override;
	virtual void Apply_Implementation() override;
	virtual void SelectSavedOrDefaultValue() override;
	virtual void SelectDefaultValue() override;
	// ~ UMGameSetting_Base

	// ~ UMGameSetting_Discrete
	virtual TArray<FName> GetPossibleOptionIds() override;
	// ~ UMGameSetting_Discrete

protected:
	static FName MakeResolutionId(const FIntPoint& Resolution);

	FIntPoint GetDesktopResolution();
	FIntPoint GetMaxSupportedResolution();
	FIntPoint GetBestNativeResolution();
	bool IsResolutionAvailableById(const FName ResolutionId);
	bool IsResolutionAvailableByValue(const FIntPoint& Resolution);
	FIntPoint GetResolutionValueForId(const FName ResolutionId);

	void BindToFullscreenModeChanges();
	
	// ~ Delegate Handler
	UFUNCTION()
	void OnFullscreenModeSelectedValueChanged();
	// ~ Delegate Handler

	UPROPERTY(Transient)
	TMap<FName, FIntPoint> ResolutionValueForOptionId;

	UPROPERTY(Transient)
	FName NativeResolutionOptionId;
};

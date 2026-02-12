// Copyright (c) Miknios. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonListView.h"
#include "MGameSettingListView.generated.h"

class UMSettingsCategoryDefinition;

UCLASS(meta = (EntryClass = UMGameSettingWidget_Base))
class MSETTINGS_API UMGameSettingListView : public UCommonListView
{
	GENERATED_BODY()

public:
	void SetCategoryDefinitionAndInitializeList(UMSettingsCategoryDefinition* InCategoryDefinition);

protected:
	// ~ UListView
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass,
	                                                   const TSharedRef<STableViewBase>& OwnerTable) override;
	
	// This function allows to skip non-selectable entries like header when navigating with controller/keyboard 
	virtual bool OnIsSelectableOrNavigableInternal(UObject* SelectedItem) override;
	// ~ UListView

	UPROPERTY(Transient)
	TObjectPtr<UMSettingsCategoryDefinition> SettingCategoryDefinition;
};

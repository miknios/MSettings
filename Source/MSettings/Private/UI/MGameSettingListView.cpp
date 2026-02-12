// Copyright (c) Miknios. All rights reserved.


#include "UI/MGameSettingListView.h"

#include "MGameSettingsSubsystem.h"
#include "MGameSetting_Base.h"
#include "MSettingsCategoryDefinition.h"
#include "UI/MGameSettingWidget.h"

// TODO: subscribe to option changes and refresh editable state for each widget in list
void UMGameSettingListView::SetCategoryDefinitionAndInitializeList(UMSettingsCategoryDefinition* InCategoryDefinition)
{
	SettingCategoryDefinition = InCategoryDefinition;
	if (SettingCategoryDefinition == nullptr)
	{
		return;
	}
	
	UGameInstance* GameInstance = GetGameInstance();
	if (!IsValid(GameInstance))
	{
		return;
	}
	
	UMGameSettingsSubsystem* GameSettingsSubsystem = GetGameInstance()->GetSubsystem<UMGameSettingsSubsystem>();
	if (!IsValid(GameSettingsSubsystem))
	{
		return;
	}

	TArray<UMGameSetting_Base*> Options;
	Options.Reserve(SettingCategoryDefinition->SettingsInCategory.Num());
	for (const FMSettingCategoryEntry& SettingInCategoryEntry : SettingCategoryDefinition->SettingsInCategory)
	{
		UMGameSetting_Base* SettingObject = GameSettingsSubsystem->GetSettingObjectForClass(SettingInCategoryEntry.SettingClass);
		if (!IsValid(SettingObject))
		{
			continue;
		}
		
		Options.Emplace(SettingObject);
	}

	SetListItems(Options);
}

UUserWidget& UMGameSettingListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass,
                                                                  const TSharedRef<STableViewBase>& OwnerTable)
{
	UMGameSetting_Base* SettingItem = Cast<UMGameSetting_Base>(Item);

	TSubclassOf<UMGameSettingWidget_Base> OptionWidgetClass = TSubclassOf<UMGameSettingWidget_Base>(DesiredEntryClass);
	if (SettingCategoryDefinition != nullptr && SettingItem != nullptr)
	{
		if (const TSubclassOf<UMGameSettingWidget_Base> OptionWidgetClassForOption =
			SettingCategoryDefinition->GetWidgetClassForSetting(*SettingItem))
		{
			OptionWidgetClass = OptionWidgetClassForOption;
		}
		else
		{
			//UE_LOG(LogGameSettings, Error, TEXT("UGameSettingListView: No Entry Class Found!"));
		}
	}
	else
	{
		//UE_LOG(LogGameSettings, Error, TEXT("UGameSettingListView: No VisualData Defined!"));
	}

	UMGameSettingWidget_Base& EntryWidget = GenerateTypedEntry<UMGameSettingWidget_Base>(OptionWidgetClass, OwnerTable);

	if (!IsDesignTime())
	{
		if (SettingItem != nullptr)
		{
			EntryWidget.SetSetting(*SettingItem);
		}
	}

	return EntryWidget;
}

bool UMGameSettingListView::OnIsSelectableOrNavigableInternal(UObject* SelectedItem)
{
	return true;
}

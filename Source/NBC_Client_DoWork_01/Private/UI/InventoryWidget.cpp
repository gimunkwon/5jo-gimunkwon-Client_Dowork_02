#include "UI/InventoryWidget.h"

#include "Components/ComboBoxString.h"
#include "Components/GridPanel.h"
#include "Components/MenuAnchor.h"
#include "Components/TextBlock.h"
#include "Player/MyPlayer.h"
#include "Player/Controller/MyPlayerControlloer.h"
#include "Player/Inventory/MyPlayerInventory.h"
#include "UI/InventoryInfoWidget.h"
#include "UI/InventorySlotSelectContextWidget.h"
#include "UI/InventorySlotWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Grid_MaxRow = 5;
	Grid_MaxColumn = 6;
	
	if (Grid_Inven)
	{
		for (int32 Col = 0; Col < Grid_MaxColumn; ++Col)
		{
			Grid_Inven->ColumnFill.Add(1.f);
		}
		for (int32 Row = 0; Row < Grid_MaxRow; ++Row)
		{
			Grid_Inven->RowFill.Add(1.f);
		}
	}
	
	for (int32 Row = 0; Row < Grid_MaxRow; ++Row)
	{
		for (int32 Col = 0; Col < Grid_MaxColumn; ++Col)
		{
			if (WBP_InvenSlot)
			{
				UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, WBP_InvenSlot);
				if (NewSlot)
				{
					Grid_Inven->AddChildToGrid(NewSlot, Row, Col);
					NewSlot->OnButtonPressedOfItemName.AddDynamic(this, &UInventoryWidget::UpdateInfoItemWidget);
					NewSlot->OnRightClicked.AddDynamic(this, &UInventoryWidget::OnRightClickedInvenSlot);
				}
				
			}
		}
	}
	
	ComboBox_PlayerTitle->OnSelectionChanged.AddDynamic(this, &UInventoryWidget::OnPlayerTitleComboxPressed);
	if (MenuA_SelectItem)
	{
		MenuA_SelectItem->OnGetMenuContentEvent.BindDynamic(this, &UInventoryWidget::GetMenuAContext);
	}
	
	CurrentChoiceSlot = nullptr;
}

bool UInventoryWidget::UpdateInventoryItem(UMyPlayerInventory* InventoryInst)
{
	if (!InventoryInst) return false;
	
	UE_LOG(LogTemp,Warning,TEXT("UpdateInventoryItem"));
	
	TArray<UWidget*> ChildrenWidget = Grid_Inven->GetAllChildren();
	
	for (int32 i = 0; i < ChildrenWidget.Num(); i++)
	{
		UInventorySlotWidget* SlotWidget = Cast<UInventorySlotWidget>(ChildrenWidget[i]);
		if (SlotWidget)
		{
			if (InventoryInst->Inventory.IsValidIndex(i))
			{
				SlotWidget->UpdateSlotImage(InventoryInst->Inventory[i].ItemImage,InventoryInst->Inventory[i].ItemName);
			}
		}
	}
	
	return true;
}

void UInventoryWidget::UpdateInfoItemWidget(FName SelectedItemName,UImage* SelectedItemImage)
{
	UE_LOG(LogTemp,Warning,TEXT("아이템의 정보를 위젯에 갱신합니다."));
	if (UInventoryInfoWidget* InfoWidget = Cast<UInventoryInfoWidget>(WBP_ItemInfoWidget))
	{
		InfoWidget->UpdateItemInfo(SelectedItemName,SelectedItemImage);
	}
}

void UInventoryWidget::UpdatePlayerTitleText()
{
	if (Text_PlayerTitle)
	{
		if (AMyPlayerControlloer* PC = Cast<AMyPlayerControlloer>(GetOwningPlayer()))
		{
			if (AMyPlayer* MyOwner = Cast<AMyPlayer>(PC->GetPawn()))
			{
				FString CombineString = "";
				
				UE_LOG(LogTemp,Warning,TEXT("PlayerTitleUpdate..."));
				for (auto it = MyOwner->GetPlayerTitle().CreateConstIterator(); it; ++it)
				{
					const UEnum* EnumPtr = StaticEnum<EPlayer_Title>();
					FString EnumToString = EnumPtr->GetNameStringByValue((int64)*it);
					
					CombineString += EnumToString;
					CombineString += TEXT("\n");
					
					Text_PlayerTitle->SetText(FText::FromString(CombineString));
				}
			}
		}
	}
}

void UInventoryWidget::UpdatePlayerTitleToComboBox()
{
	if (ComboBox_PlayerTitle)
	{
		const UEnum* EnumPtr = StaticEnum<EPlayer_Title>();
		if (EnumPtr)
		{
			for (int32 i = 0; i < EnumPtr->NumEnums() - 1; ++i)
			{
				FString TitleName = EnumPtr->GetNameStringByIndex(i);
				ComboBox_PlayerTitle->AddOption(TitleName);
			}
		}
	}
}

void UInventoryWidget::OnPlayerTitleComboxPressed(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (AMyPlayer* MyOwner = Cast<AMyPlayer>(GetOwningPlayerPawn()))
	{
		const UEnum* EnumPtr = StaticEnum<EPlayer_Title>();
		if (EnumPtr)
		{
			int32 EnumIndex = EnumPtr->GetIndexByName(FName(*SelectedItem));
			
			if (EnumIndex != INDEX_NONE)
			{
				EPlayer_Title SelectedTitle = (EPlayer_Title)EnumIndex;
				MyOwner->SetPlayerTitle(SelectedTitle);
				
				UpdatePlayerTitleText();
			}
		}
	}
}

void UInventoryWidget::OnRightClickedInvenSlot(FName SelectedSlotItem,UInventorySlotWidget* SelectedSlotWidget)
{
	UE_LOG(LogTemp,Warning,TEXT("Current Slot Item %s"),*SelectedSlotItem.ToString());
	if (MenuA_SelectItem)
	{
		MenuA_SelectItem->Open(true);
		CurrentChoiceSlot = SelectedSlotWidget;
	}
}

void UInventoryWidget::OnClosedMenuA()
{
	if (MenuA_SelectItem)
	{
		UE_LOG(LogTemp,Warning,TEXT("메뉴를 닫습니다..."));
		MenuA_SelectItem->Close();
	}
}

UWidget* UInventoryWidget::GetMenuAContext()
{
	UInventorySlotSelectContextWidget* ContextWidget = CreateWidget<UInventorySlotSelectContextWidget>(GetOwningPlayer(),MenuA_SelectItem->MenuClass);
	
	if (ContextWidget)
	{
		UE_LOG(LogTemp,Warning,TEXT("메뉴앵커 생성및 바인딩"))
		
		ContextWidget->OnCloseButton.AddDynamic(this, &UInventoryWidget::OnClosedMenuA);
		ContextWidget->OnUseItemButton.AddDynamic(this, &UInventoryWidget::UseItemFromSlot);
		ContextWidget->OnDeleteItemButton.AddDynamic(this, &UInventoryWidget::DeleteItemFromSlot);
	}
	
	return ContextWidget;
}

void UInventoryWidget::UseItemFromSlot()
{
	UE_LOG(LogTemp,Warning,TEXT("인벤토리 아이템 사용!"));
	if (Grid_Inven)
	{
		if (Grid_Inven->HasChild(CurrentChoiceSlot))
		{
			CurrentChoiceSlot->ClearSlotData(Grid_Inven->GetChildIndex(CurrentChoiceSlot),true);
		}
	}
}

void UInventoryWidget::DeleteItemFromSlot()
{
	UE_LOG(LogTemp,Warning,TEXT("인벤토리 아이템 제거!"));
	
	if (Grid_Inven)
	{
		if (Grid_Inven->HasChild(CurrentChoiceSlot))
		{
			CurrentChoiceSlot->ClearSlotData(Grid_Inven->GetChildIndex(CurrentChoiceSlot),false);
		}
	}
	
}






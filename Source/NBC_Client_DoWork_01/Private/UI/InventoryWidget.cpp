#include "UI/InventoryWidget.h"

#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Player/MyPlayer.h"
#include "Player/Controller/MyPlayerControlloer.h"
#include "Player/Inventory/MyPlayerInventory.h"
#include "UI/InventoryInfoWidget.h"
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
				}
				
			}
		}
	}
	
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



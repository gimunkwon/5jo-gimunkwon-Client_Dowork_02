#include "UI/InventoryWidget.h"

#include "Components/GridPanel.h"
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
	
	UInventorySlotWidget* NewSlot = nullptr;
	
	for (int32 Row = 0; Row < Grid_MaxRow; ++Row)
	{
		for (int32 Col = 0; Col < Grid_MaxColumn; ++Col)
		{
			if (WBP_InvenSlot)
			{
				NewSlot = CreateWidget<UInventorySlotWidget>(this, WBP_InvenSlot);
				if (NewSlot)
				{
					Grid_Inven->AddChildToGrid(NewSlot, Row, Col);
				}
				
			}
		}
	}
	
	NewSlot->OnButtonPressedOfItemName.AddDynamic(this, &UInventoryWidget::UpdateInfoItemWidget);
	
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

void UInventoryWidget::UpdateInfoItemWidget(FName SelectedItemName)
{
	if (UInventoryInfoWidget* InfoWidget = Cast<UInventoryInfoWidget>(WBP_ItemInfoWidget))
	{
		InfoWidget->UpdateItemInfo(SelectedItemName);
		UE_LOG(LogTemp,Warning,TEXT("아이템의 정보를 위젯에 갱신합니다."));
	}
}



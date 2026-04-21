#include "UI/InventoryWidget.h"

#include "Components/GridPanel.h"

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
				UUserWidget* NewSlot = CreateWidget<UUserWidget>(this, WBP_InvenSlot);
				if (NewSlot)
				{
					Grid_Inven->AddChildToGrid(NewSlot, Row, Col);
				}
				
			}
		}
	}
	
	
}

void UInventoryWidget::UpdateInventoryItem(UMyPlayerInventory* InventoryInst)
{
	
}


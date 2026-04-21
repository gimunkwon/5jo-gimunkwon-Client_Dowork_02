#include "UI/InventoryAddItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "DataTable/ItemDataTable.h"
#include "Player/MyPlayer.h"
#include "Player/Controller/MyPlayerControlloer.h"
#include "Player/Inventory/MyPlayerInventory.h"

void UInventoryAddItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_AddItem)
	{
		Btn_AddItem->OnClicked.AddDynamic(this, &UInventoryAddItemWidget::OnButtonPressed);
	}
	
	// DT로 이름이 바뀔때마다 이미지 교체 로직?
	InitializeButtonImage();
}

void UInventoryAddItemWidget::OnButtonPressed()
{
	UE_LOG(LogTemp,Warning,TEXT("%s Button Pressed"),*ItemID.ToString());
	
	AMyPlayerControlloer* MyOwnerPC = Cast<AMyPlayerControlloer>(GetOwningPlayer());
	if (MyOwnerPC)
	{
		if (AMyPlayer* MyOwner = Cast<AMyPlayer>(MyOwnerPC->GetPawn()))
		{
			if (UMyPlayerInventory* MyInven = MyOwner->GetInventory())
			{
				UE_LOG(LogTemp,Warning,TEXT("AddItemLogicOn"));
				MyInven->AddInventoryItem(ItemID);
			}
		}
	}
}

void UInventoryAddItemWidget::InitializeButtonImage()
{
	static const FString ContextString = "DataTable";
	if (ItemDataTable)
	{
		FItemDataTable* Row = ItemDataTable->FindRow<FItemDataTable>(ItemID, ContextString);
		if (Row && Image_Button)
		{
			Image_Button->SetBrushResourceObject(Row->ItemImage);
		}
	}
}


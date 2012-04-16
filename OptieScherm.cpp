/*
 * OptieScherm.cpp
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer, Marijn
 */

#include "OptieScherm.h"

// variabelen voor schermgrootte
int schermBreedte;
int schermHoogte;

OptieScherm::OptieScherm( Screen* parent )
{
	//sla parent scherm op (FotoScherm) om de show() te kunnen aanroepen, zodat dit optiescherm weer gesloten wordt
	this->parent = parent;

	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	schermBreedte = EXTENT_X( screenSize );
	schermHoogte = EXTENT_Y( screenSize );

	//standaard font en grafisch uiterlijk (uit de resource file res.lst)
	Font* font = new MAUI::Font(RES_FONT);
	WidgetSkin* skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* label = new Label(0, 0, 0, 0, NULL);

	//stel achtergrondkleur in
	label->setBackgroundColor(0xd3d3d3);

	// standaard widget label maken
	this->setMain(label);

	// listBox voor de opties maken
	this->listBox = new ListBox(0, 0, schermBreedte, schermHoogte, label, ListBox::LBO_VERTICAL, ListBox::LBA_LINEAR, true);
	listBox->setPaddingTop(10);
	listBox->setPaddingLeft(listBox->getWidth() / 2 - 60);
	listBox->setBackgroundColor(0xffffff);

	//maak rode knop
	this->roodLabel = new Label( 30, 30, 55, 30, NULL, "Rood", 0, font );
	roodLabel->setSkin( skin );
	roodLabel->setPaddingTop(5);
	roodLabel->setPaddingLeft(10);
	this->kleurLabels.add( roodLabel );	//voeg toe aan vector
	listBox->add(roodLabel);

	//maak groene knop
	this->groenLabel = new Label( 30, 70, 55, 30, NULL, "Groen", 0, font );
	groenLabel->setSkin( skin );
	groenLabel->setPaddingTop(5);
	groenLabel->setPaddingLeft(10);
	this->kleurLabels.add( groenLabel );	//voeg toe aan vector
	listBox->add(groenLabel);

	//maak blauwe knop
	this->blauwLabel = new Label( 30, 110, 55, 30, NULL, "Blauw", 0, font );
	blauwLabel->setSkin( skin );
	blauwLabel->setPaddingTop(5);
	blauwLabel->setPaddingLeft(10);
	this->kleurLabels.add( blauwLabel );	//voeg toe aan vector
	listBox->add(blauwLabel);

	//stel grootte plaatje in m.b.v. editbox
	this->plaatjeGrootte = new EditBox(30, 150, 45, 30, NULL, "176", 0x000000, font, true, false, 30, EditBox::IM_NUMBERS);
	plaatjeGrootte->setPaddingTop(5);
	plaatjeGrootte->setPaddingLeft(10);
	this->plaatjeGrootte->setSkin( skin );
	listBox->add(plaatjeGrootte);


	//stel naam plaatje in m.b.v. editbox
	this->plaatjeNaam = new EditBox(30, 190, 150, 30, NULL, "Onderwater spoorlijn ", 0x000000, font, true, false, 3, EditBox::IM_STANDARD);
	plaatjeNaam->setPaddingTop(5);
	plaatjeNaam->setPaddingLeft(10);
	this->plaatjeNaam->setSkin( skin );
	listBox->add(plaatjeNaam);

	// maak toepassen knop
	this->knopLabel = new Label( 30, 250, 85, 30, NULL, "Toepassen", 0, font);
	knopLabel->setPaddingTop(5);
	knopLabel->setPaddingLeft(10);
	knopLabel->setSkin(skin);
	listBox->add(knopLabel);
}

OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
}


//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	return this->achtergrondKleur;
}

// geeft ingestelde grootte plaatje terug
int OptieScherm::getGrootte()
{
	grootte = atoi(this->plaatjeGrootte->getCaption().c_str()); // atoi voor de chars naar int
	return grootte;
}

//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	return this->plaatjeNaam->getCaption(); //caption is de text in een editbox
}


// afvangen toetsinvoer
void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//laat bij MAK_FIRE knop indrukken de parent (FotoScherm dus) weer zien
	if (keyCode == MAK_FIRE)
	{
		parent->show();
	}


	if(keyCode == MAK_DOWN) // naar beneden navigeren, kijken wat is ingedrukt en label eronder veranderen
	{
		if (roodLabel->isSelected())
		{
			roodLabel->setSelected(false);
			groenLabel->setSelected(true);
			achtergrondKleur = 0x00ff00;
		}
		else if (groenLabel->isSelected())
		{
			groenLabel->setSelected(false);
			blauwLabel->setSelected(true);
			achtergrondKleur = 0x0000ff;
		}
		else if (blauwLabel->isSelected())
		{
			blauwLabel->setSelected(false);
			plaatjeGrootte->setSelected(true);
		}
		else if (plaatjeGrootte->isSelected())
		{
			plaatjeGrootte->setSelected(false);
			plaatjeNaam->setSelected(true);
		}
	}

	if(keyCode == MAK_UP) // naar boven navigeren, kijken wat is ingedrukt en label erboven veranderen
	{
		if (groenLabel->isSelected())
		{
			groenLabel->setSelected(false);
			roodLabel->setSelected(true);
			achtergrondKleur = 0xff0000;
		}
		else if (blauwLabel->isSelected())
		{
			blauwLabel->setSelected(false);
			groenLabel->setSelected(true);
			achtergrondKleur = 0x00ff00;
		}
		else if (plaatjeGrootte->isSelected())
		{
			plaatjeGrootte->setSelected(false);
			blauwLabel->setSelected(true);
			achtergrondKleur = 0x0000ff;
		}
		else if (plaatjeNaam->isSelected())
		{
			plaatjeNaam->setSelected(false);
			plaatjeGrootte->setSelected(true);
		}
	}

}

// afvangen aanraking
void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	//doorloop alle kleurlabels om selectie in te stellen
	for (int i = 0; i < kleurLabels.size(); i++)
	{
		//kijk of label in het touch-punt valt
		if (kleurLabels[i]->contains(point.x, point.y))
		{
			kleurLabels[i]->setSelected(true); // in touch-punt? label selected maken
			switch (i)
			{
			case 0: achtergrondKleur = 0xff0000; // rood
			break;
			case 1: achtergrondKleur = 0x00ff00; // groen
			break;
			case 2: achtergrondKleur = 0x0000ff; // blauw
			break;
			}
		}
		else //niet in touch punt? deselect!
		{
			kleurLabels[i]->setSelected(false);
		}
	}

	// toepassen knop in touch-punt?
	if (knopLabel->contains(point.x, point.y))
	{
		parent->show(); // fotoscherm laten zien
	}

	// selecteer plaatjeNaam editbox bij aanraking (of deselecteer)
	if (plaatjeNaam->contains(point.x, point.y))
	{
		plaatjeNaam->setSelected(true);
	}
	else
	{
		plaatjeNaam->setSelected(false);
	}

	// selecteer plaatjeGrootte editbox bij aanraking (of deselecteer)
	if (plaatjeGrootte->contains(point.x, point.y))
	{
		plaatjeGrootte->setSelected(true);
	}
	else
	{
		plaatjeGrootte->setSelected(false);
	}
}


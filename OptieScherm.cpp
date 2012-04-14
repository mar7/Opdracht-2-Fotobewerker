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
	label->setBackgroundColor(0x000000);

	// standaard widget label
	this->setMain(label);


	//maak rode knop
	this->roodLabel = new Label( 20, 50, 75, 30, label, "Rood", 0, font );
	roodLabel->setSkin( skin );
	this->kleurLabels.add( roodLabel );	//voeg toe aan vector

	//maak groene knop
	this->groenLabel = new Label( 20, 90, 75, 30, label, "Groen", 0, font );
	groenLabel->setSkin( skin );
	this->kleurLabels.add( groenLabel );	//voeg toe aan vector

	//maak blauwe knop
	this->blauwLabel = new Label( 20, 110, 75, 30, label, "Blauw", 0, font );
	blauwLabel->setSkin( skin );
	this->kleurLabels.add( blauwLabel );	//voeg toe aan vector

	// maak toepassen knop
	this->knopLabel = new Label( 20, 170, 75, 30, label, "Toepassen", 0, font);
	knopLabel->setSkin(skin);


	//stel grootte plaatje in m.b.v. editbox
	this->plaatjeGrootte = new EditBox(100, 70, 50, 30, label, "176", 0x000000, font, true, false, 30, EditBox::IM_STANDARD);
	this->plaatjeGrootte->setSkin( skin );


	//stel naam plaatje in m.b.v. editbox
	this->plaatjeNaam = new EditBox(100, 100, 100, 30, label, "Naam", 0x000000, font, true, false, 3, EditBox::IM_NUMBERS);
	this->plaatjeNaam->setSkin( skin );
}

OptieScherm::~OptieScherm()
{
	//verwijder objecten van deze klasse
}


//geef ingestelde achtergrondkleur terug
int OptieScherm::getAchtergrondOptie()
{
	//return achtergrond kleur
	return this->achtergrondKleur;
}


//geef ingestelde imagetekst van de editbox terug
const BasicString<char> OptieScherm::getImagetekst()
{
	return this->plaatjeNaam->getCaption(); //caption is de text in een editbox
}



void OptieScherm::keyPressEvent(int keyCode, int nativeCode)
{
	//laat bij MAK_FIRE knop indrukken de parent (FotoScherm dus) weer zien
	if (keyCode == MAK_FIRE)
	{
		parent->show();
	}
}

void OptieScherm::pointerPressEvent(MAPoint2d point)
{
	//doorloop alle kleurlabels om selectie in te stellen
	for (int i = 0; i < kleurLabels.size(); i++)
	{
		//kijk of label in het touch-punt valt
		if (kleurLabels[i]->contains(point.x, point.y))
		{
			kleurLabels[i]->setSelected(true);
			switch (i)
			{
			case 0: achtergrondKleur = 0xff0000;
			break;
			case 1: achtergrondKleur = 0x00ff00;
			break;
			case 2: achtergrondKleur = 0x0000ff;
			break;
			}
		}
		else //niet in touch punt? deselect!
		{
			kleurLabels[i]->setSelected(false);
		}
	}

	if (knopLabel->contains(point.x, point.y))
	{
		parent->show();
	}

	//behandel de editbox bij selecteren (touch), verander de editBox naar je eigen editbox(en)
	if (plaatjeNaam->contains(point.x, point.y))
	{
		plaatjeNaam->setSelected(true);
	}
	else
	{
		plaatjeNaam->setSelected(false);
	}

	if (plaatjeGrootte->contains(point.x, point.y))
	{
		plaatjeGrootte->setSelected(true);
	}
	else
	{
		plaatjeGrootte->setSelected(false);
	}
}


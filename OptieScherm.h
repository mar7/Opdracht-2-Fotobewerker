/*
 * OptieScherm.h
 *
 *  Created on: 3 mrt. 2012
 *      Author: acer, Marijn
 */

#ifndef OPTIESCHERM_H_
#define OPTIESCHERM_H_

#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/EditBox.h>
#include <MAUI/ListBox.h>

#include <MAUTIL/Moblet.h>
#include <MAUTIL/Vector.h>

#include <mastdlib.h> // om atoi te gebruiken

#include "MAHeaders.h"

using namespace MAUtil;
using namespace MAUI;

class OptieScherm : public Screen
{
private:
	Screen* parent; // om het fotoscherm in te stoppen

	// labels die als knoppen dienen
	Vector<Label*> kleurLabels;
	Label* roodLabel;
	Label* groenLabel;
	Label* blauwLabel;
	Label* knopLabel; // toepassen knop

	// editboxen en waardes die opgeslagen moeten worden
	EditBox* plaatjeNaam;
	EditBox* plaatjeGrootte;
	int grootte;
	int achtergrondKleur;

	// listBox voor de opties
	ListBox* listBox;

public:
	OptieScherm( Screen* parent );
	virtual ~OptieScherm();

	void keyPressEvent(int keyCode, int nativeCode);
	void pointerPressEvent(MAPoint2d point);

	int getAchtergrondOptie(); // geeft kleur achtergrond terug
	int getGrootte(); // geeft grootte voor plaatje terug
	const BasicString<char>getImagetekst(); //geeft tekst van editbox terug
};

#endif /* OPTIESCHERM_H_ */

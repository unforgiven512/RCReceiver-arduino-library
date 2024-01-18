#include "makros.h"
#include "debug.h"
#include "RCReceive.h"
/*
  RC_Template.ino - Template for RC Receiver enabled programs - Version 0.2
  Copyright (c) 2012 Wilfried Klaas.  All right reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

const byte PIN_RC = 2; 

// Der Empfänger
RCReceive rcReceiver;

void setup() {
  rcReceiver.attach(PIN_RC);

  // put your setup code here, to run once:
}

void loop() {
  // Aktuellen RC-Wert lesen
  rcReceiver.poll();

  // Nullpunktsbestimmung ?
  if (rcReceiver.hasNP() && !rcReceiver.hasError()) {
    doWork();
  } else if (rcReceiver.hasError()) {
    // Fehlerbehandlung failsafe oder sowas...
  }
}

void doWork() {
  byte value = rcReceiver.getValue();

  // put your main code here, to run repeatedly: 

}

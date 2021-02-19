

![GeoGab Logo](./images/GeoGab.svg)

# Gabriel A. Sieben (Physicist)
Here is a little code I wrote for my HomeDev Smarthings projects. I thought it could be useful for others too. Have fun. Gabriel :)

# Under Construction: Works, but is still in beta status and not yet officially released

# Integrator
Diese elegante, schnelle und einfache Funktion ermittelt den Durchschnittswert von sequenziell kommenden Zahlen über einen vom Programmierer festgelegten Bereich. So zum Beispiel wird der Durchschnitt von den letzten 50 Zahlen einer nicht endende Zahlensquenz gebidet. Der Physiker (ja, so ein Indivium bin ich) spricht hier von einer Glättung der Daten bzw. von einem Frequenzfilter. 

Dies Funktion eignet sich hervorragend um Sensordatenstreams zu glätten und damit die Ergebnisse genauer zu machen. Ja ihr lest richtig! Ihr könnt die Genauigkeit Eures flukutierende Temperatursensors durch einen statistische Rechnung genauer machen. Jeder kennt die Daten die ein DS18B20 Temperatursensor ausgibt. Der Wert ist nicht stabiel. Der Sensor liefert viele Nachkommastellen, obwohl seine Präzession mit +- 0.5 angegeben ist. Dass der Hersteller die Daten des Sensors ungefiltert rausschickt hat einen Grund. Darauf gehe ich später noch einmal ein. Ausserdem eignet sich die Funktion für Eure Sensoren noch aus einem anderen Aspekt. Ich sehe immer wieder, wie selbst semiprofessionelle Programmierer die Daten ihres DS18B20 (oder anderen Sensors) stupide alle paar Minuten rausschicken. Diese Vorgehensweise funktioniert gut. Aber sie ist aus mehreren Aspekten eher ungünstig. Denn: Der Empfänger der Daten speichert die Daten höchstwarscheinlich. Ihr habe also in der Sequent in der Ihr Eure Daten rausschickt einen Datenpunkt. Schickt ihr Eure Daten alle 30 Minuten, habt ihr 48 Datenpunkte am Tag. Steigt die Temperaur schnell an, bekommt ihr das aber im Zweifel erst in 30 Minuten mit. Der Temperaturanstieg ist nicht mit aufgzeichnet. Das geht ohne viel Aufwand sehr viel besser. Nutzt den Integrator und glättet Eure Ergebnisse. Dann sind schon mal die vielen keinen Flukuationen sehr viel weniger. Ausserdem (und das beweise ich hier nicht - dass müsst ihr mir glauben), sind wie erwähnt die Ergebnisse genauer. Nun schickt ihr die Daten nur dann raus, wenn sich die Temperatur um einen von Euch bestimmten Wert geändert hat. Einen sinnvoller Wert kann viel leichter ermittelt werden, wenn die Daten geglättet sind. Ist die Temperatur den ganze Tag stabiel, fallen ensprechend wenige Daten an, die gesendet werden müssen. Ändert sich die Termperatur schnell, bekommt ihr viel mehr Daten geliefert und die Aufzeichnung ist damit sehr viel präzieser. 

## Anleitung
### Erstellen eines Objekts der Methode Integrator: 
`Integrator integrator(Plätze, Breite);`

#### Parameter
Plätze: xxxx
Breite: xxxx

#### Speicherverbrauch
Code: Nicht berechnet aber nicht sonderlich groß
Basis: 
pro slot * breite
1,1 by = xxx
1,2 byte 
bytes

Diese Beispiel erstellt eine Integrator Objekt, dass über die letzen 50 Hinzugefügten Werte den Durschnitt bilde. 

### Hizufügen eines Wertes:
`int durchschnitt=integrator.add(Wert);`

In diesen Beispiel wir der Wert "Wert" hizugefügt. Der Durchschnitt wird als integer angenommen. Stelle sicher, dass int ausreicht. Ansonsten nehme eine größere Variable

### Abfragen des aktuellen Durchshnittwertes:
Falls man den Durchschnitt in obigen Beispiel nicht gleich beim hizufügen des Werts entgegennimmt, kann man ihn auch späger afragen.
Dies erfolgt über: 

`int durchschnitt=itegrator.value();`

oder per direkten Zugriff auf die öffentliche Variable. 

`integrator.Average;`

### Weiterhin:
o Will man wissen, wieviel Plätze man schon belegt hat, verwedent man: `int anzahl=integrator.size();`
o Will man die Durschnittsberechnung neu starten: `integrator.reset();`
o Will man den Status des Integrators auf den Seriellen Port ausgeben: `integrator.printall();`
o Will man die Versionsnummer des Integrators abfragen: `String version = integrator.version();`

## Einschränkungen
o Die mögliche größe der Array ist vom freien Speicher abhängig. Das ist die Natur der Dinge. 
o Es werden keine Kommazahlen verarbeitet. Das werde ich ohne triftigen Grund auch nicht ändern. Durch multiplikation könnte ihr das Komma verschieben und mit integer rechnen. 
o Es werden keine negativen Zahlen verarbeitet. Zahlenreihen die um Null flukuieren können aber durch Verschiebung der Nullachse (einfach einen Wert dazuaddieren) ins positive verschoben werden.   
o Es werden pro slot 4 Bytes gespeichert (uint32). Kleine Zahlen (wie z.B. die Temperatur) verschwenden Speicher. (In der nächsten Major Relase wird das geändert und der Integrator bei keinen Zahlen Speicher spahren.) 
o Es können theoretisch höchstens 4,294,967,296 Zahlen addiert werden, ohne einen Overflow zu reskieren ;-)


# offlinestepper

Offline Stepper für Feuerwerk-Zündanlagen

### Haftungsausschluss ###

Ich uebernehme keine Haftung oder Verantwortung fuer jegliche Schaeden oder
Fehlfunktionen aller Art. Die komplette Verantwortung (z.B. fuer den Bau oder
Verwendung) liegt komplett bei Euch. Ich weise ausdruecklich darauf hin, dass
Fehlfunktionen auftreten koennen. Es koennen auch Designfehler enthalten sein,
die einen Fehler verursachen. Das Gerät hat keinerlei Zulassungen. Das Geraet 
ist daher mit hoechster Vorsicht und den hoechst moeglichen Sicherheitsmaßnahmen 
zu verwenden.

Der Nachbau ist Personen gestattet, die sich entsprechend gut mit Elektronik
auskennen.

Der Nachbau ist des Weiteren nur fuer eigene Zwecke gestattet. Es ist nicht
erlaubt, Geräte zur Vermarktung oder zum Verkauf herzustellen. Es darf auch
nicht für kommerzielle Zwecke kopiert werden.

Ich kann aus zeitlichen Gründen keinen Support oder Hilfe beim Nachbau geben.

### Technische Daten ###

- 5-35V Eingangsspannung via LM2596S
- 15 unabhängige Kanäle
- Testmodus via Taster

### Was ist das ueberhaupt? ###

Der Offline-Stepper ist eine kostengünstige Erweiterung für Feuerwerk-Zündanlagen
und wird an einen Zündkanal der vorhandenen Zündanlage geklemmt.

Das Gerät hat die Besonderheit, dass es keine eigene Zündspannung benötigt, sondern
die Zündspannung von der vorhandenen Zündanlage übernommen und entsprechend geroutet
wird. Dadurch werden weniger elektronische Teile benötigt. Für das Testen der Kanäle
dient eine einfache Knopfzelle und ein Taster.

Das Gerät bietet einen automatischen und einen manuellen Modus.

Im manuellen Modus wird pro Zündimpuls ein Kanal weiter gesteppt. Die letzte Position
wird in einen nicht-flüchtigen Speicher abgelegt, bei einem erneuten Zündimpuls
ausgelesen und um eine Position inkrementiert. Dadurch weiß das Gerät, welche
Zündkreis als nächstes an die Reihe kommt.

Im automatischen Modus werden die Kanäle innerhalb eines Zündimpulses ausgelöst. Zur
Verfügung stehen die 7 Zeiten: von 50 - 200ms in 25ms Schritten. Zu beachten ist hier,
dass der Zündimpuls länger anliegen muss. Bei 50ms und 15 Kanälen also mindestens
750ms + 5ms für den Boot-Vorgang.

### Kurze Bauanleitung ###

01. Teile bestellen (Teileliste)
02. Platinen aetzen lassen (gerber, drill) oder selbst herstellen (PDF)
03. avr-lib und avrdude installieren
04. Software mit make kompilieren
05. das hex File auf den avr flashen
06. bei den Platinen folgende Reihenfolge beim Löten: Widerstände, FETs, IC-Sockel, LEDs, Klemmen
07. den step-down regler auf 5v einmessen
08. bei der FET-Verkabelung auf die Reihenfolge im Sourcecode achten
09. WAGO Frontplatte: sieht schön aus, platzsparend, jedoch kompliziert zu verarbeiten
10. Terminal Frontplatte: sieht schön aus, einfach zu verarbeiten (mein Favorit)
11. das Gerät vor der Inbetriebnahme ausgiebig testen.

### Modusschalter (optional) ###

Standardmäßig befindet sich das Gerät im manuellen Modus. Darüber hinaus ist es möglich, über
die ISP Pins noch weitere Modi zu konfigurieren. Dies kann über einen DIP- oder Kodierschalter
realisiert werden:

        PB3 PB4 PB5
50ms:   0   0   0
75ms:   1   1   0
100ms:  1   0   0
125ms:  0   1   1
150ms:  0   0   1
175ms:  0   1   0
200ms:  1   0   1
m:      1   1   1

Der Zündimpuls ist immer 50ms.

### Belegung der Kanäle / Ports ###

C2 = CH01
C3 = CH02
C4 = CH03
C5 = CH04
D5 = CH05
D6 = CH06
D7 = CH07
D2 = CH08
B1 = CH09
B0 = CH10
D3 = CH11
D4 = CH12
B2 = CH13
C0 = CH14
C1 = CH15

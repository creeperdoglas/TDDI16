Mönsterigenkänning
==================

- Ungefärligt antal timmar spenderade på labben (valfritt):
<5

- Vad är tidskomplexiteten (i ordo-notation) för värstafallstiden av
  programmen som en funktion av N (antal punkter). Ge en kort motivering.
ligger under brute och fast

  Matchar brute-lösningen sitt värstafall i praktiken, eller har den ett
  medelfall som är bättre?
Ja, brute-lösningen matchar sitt värstafall i praktiken eftersom den tvingas genomgå alla möjliga kombinationer av fyra punkter, oavsett hur punkterna är placerade

brute:
algoritmen har ett värsta fall på (𝑂𝑁^4). Brute-force-algoritmen har i praktiken ofta ett medelfall som är bättre än det teoretiska värsta fallet, fortfarande inneffektivt för stora datamängder dock. Medelfallet är i allmänhet bättre än värsta fallet eftersom algoritmen begränsar sökningen till punkter som faktiskt har samma lutning. Den använder dessutom funktionen sameSlope som skippar många onödiga kontroller. 

fast:
fast-lösningen går igenom varje punkt som en referenspunkt p och sorterar de återstående n - 1, sedan sorteringför varje N igen. vilket ger 𝑂(𝑁^2logN). fast matchar inte alltid värstafall då om punkterna är slumpvist distruberade kan det ge snabbare då de inte alltid ligger på linjer och då kan algoritmen snabbt avsluta vissa operationer.


- Fyll i tabel  len nedan med riktiga körtider i sekunder när det känns
  vettigt att vänta på hela beräkningen.
  Ge uppskattningar av körtiden (baserat på tidskomplexiteten)
  i övriga fall.

    
      N       brute       sortering
 ----------------------------------
    150       42  ms         13  ms
    200       103 ms         26  ms
    300       333 ms         56  ms
    400       799 ms         94  ms
    800       6 sekunder     259 ms
   1600       50sekunder     1   sekund
   3200       70 min(U)      4.3 sekunder
   6400       18.8 timmar(U) 18  sekunder
  12800       301 timmar(U)  80  sekunder
          (U)=uppskattning

- Energianvändning

  Antag att du använder mönsterigenkänningsprogrammet för att analysera
  data från en kamera. Kameran sitter i en byggnad och tar en bild
  på stommen av byggnaden var 30:e minut. Bilden förbehandlas sedan
  lite, innan punkter som representerar stommen skickas till
  mönsterigenkänningsprogrammet. Hittas inte tillräckligt många raka
  linjer så betyder det att något håller på att gå sönder, och
  att byggnaden behöver noggrannare inspektion.

  Hur mycket energi sparar du på ett år om du använder din snabbare
  sorteringslösning i stället för brute-lösningen? Du kan anta följande:
  - Systemet körs 24/7 under hela året.
  - Inget annat körs på det här systemet.
  - Systemet drar 8 W när det inte gör något (idle)
  - Systemet drar 36 W när det arbetar (med 1 kärna)
  - Räkna med att ditt program körs var 30:e minut (= 2 gånger/timme)
  - För- och efterbehandling är snabba, så vi kan bortse från dem
  - Indata till programmet innehåller ca 6400 punkter
  - Det är inte skottår (= 365 dagar)

  Att jämföra med drar en kombinerad kyl/frys ca 200 kWh per år
  (enligt Energimyndigheten).
 
  Kom ihåg: energi mäts ofta i kWh, vilket är:
   energi (kWh) = effekt (kW) * tid (h)

  Tips: ett sätt att räkna på är att först räkna förbrukningen av
  ett system som inte gör något på ett helt år, sedan lägga till
  den extra förbrukningen (36 W - 8 W = 28 W) för tiden som systemet
  är aktiv.

  (Siffrorna är löst baserade på en Intel i9-9900K, vi räknar bara på
  CPU:n för enkelhets skull, besparingarna blir sannolikt större om
  vi räknar på större delar av systemet, även om andra komponenter
  också drar ström i "idle".)


basförbrukning (idle)  på 70.08 kwh.

Förbrukning av brute på ett år: 70.08+228.6=298.68kWh

Förbrukning av sotering på ett år: 70.08+0.0706≈70.15kWh

Skillnad: 298.68−70.15=228.53kWh


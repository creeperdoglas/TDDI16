Bildmatchning
=============

- Ungefärligt antal timmar spenderade på labben (valfritt):
 5-10

- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

slow:
O(n^2)


fast:
Läsning av filer: O(n)
Bildläsning och sammandragsberäkning: O(n)
Lagring i unordered_map: O(n)
sammafattning O(n^2) i värsta fall. men kommer ej ske i det här fallet.


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?
  Tips: Använd flaggan "--nowindow" för enklare tidsmätning.
  Tips: Det är okej att uppskatta tidsåtgången för de fall du inte orkar vänta
  på att de blir klara.
  Tips: Vid uppskattning av körtid för "slow.cpp" är det en bra idé att beräkna
  tiden det tar att läsa in (och skala ner) bilderna separat från tiden det tar att
  jämföra bilderna. (Varför?) 
  för att inläsningen bör va ungefär samma för fast och slow.


|--------+-----------+----------+----------|
|        | inläsning | slow.cpp |fast.cpp(tot)|
|--------+-----------+----------+----------|
| tiny   | 93  ms    |  88 ms   |   67 ms  |
| small  | 0,55 s    |  0,73  s |   0,49 s |
| medium | 2,4  s    |  3,1  s  |   2,2  s |
| large  | 51   s    |  370 s   |   55  s  |
|--------+-----------+----------+----------|


- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?

  lägre värde innebär mer grova reprensationer vilket ökar false positives. 


- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna lösa problemet i
  labben? Tycker du att den givna funktionen uppfyller dessa egenskaper?

Styrkor:
Det är relativt enkelt att implementera och ger en snabb första filtrering.
Sammanfattningen är stabil för små förändringar inom samma område, vilket gör att liknande mönster lätt identifieras.
Svagheter:
Den är känslig för små translationer, rotationer, eller förändringar i ljusstyrkan, vilket kan leda till att små variationer i samma bild får olika sammanfattning.


- Ser du några problem med metoden för att se om två bilder är lika dana?
  Föreslå en alternativ metod för att hitta bilder som är lika. Vad har
  ditt/dina förslag för för- och nackdelar jämfört med det som föreslås i
  labben? Fokusera exempelvis på vilka typer av skillnader i bilder som
  hanteras, eller vilken tidskomplexitet som kan uppnås. Ditt förslag behöver
  inte vara snabbare än det som föreslås i labben, men du ska komma på
  åtminstone en fördel med din metod.
  
  Som tidigare nämnt I Svagheter. PHash skulle kunne användas, skulle ta bort problemet som vår lösning har då den mot små bortser förändringar i ljusstyrka, brus och även vissa små geometriska skillnader då den omvandlar till gråskala. men tar längre tid och compute_summary skulle behövas göras om. Sammfattat är vår metod snabbast men har lite större risk för att missa.




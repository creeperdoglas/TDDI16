Bildmatchning
=============

Uppdatering:
komplettering klar


- Ungefärligt antal timmar spenderade på labben (valfritt):
 ungefär 10

- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

slow:
O(n^2)


fast: 
kanske skulle vara (m*n) då storleken på bilden spelar roll
O(n)


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?

tiden det tar att läsa in (och skala ner) bilderna separat från tiden det tar att
  jämföra bilderna. (Varför?) 
  för att inläsningen bör va ungefär samma för fast och slow.

inläsning är endast för slow, slow.cpp är hur lång tid matchning tog och fast är den totala tiden för match+inläsning i fast.
|--------+-----------+----------+----------|
|        | inläsning | slow.cpp |fast.cpp  |
|--------+-----------+----------+----------|
| tiny   | 93  ms    |  88 ms   |   64 ms  |
| small  | 0,55 s    |  0,73  s |   0,5 s  |
| medium | 2,4  s    |  3,1  s  |   2,2  s |
| large  | 51   s    |  370 s   |   56  s  |
|--------+-----------+----------+----------|


- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?

bra att hitta en "sweet spot" som inte tar bort liknande men inte ger false positives. 5 på 6 , 8 på 8 och 9 på 10 .
för låg ger false positives, för hög tar bort liknande.

- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna lösa problemet i
  labben? Tycker du att den givna funktionen uppfyller dessa egenskaper?

  Tolerans mot små förändringar, Summeringen ska kunna hantera små variationer, som t.ex. små ljusförändringar.
  Vår klarar det, men ej mot större förändringar som rotation/skala. Dock är större förändringar inte det man är ute efter i det här fallet.

  Ha låg risk för kollison, en bra hash-funktion ska minimera risken för att två olika bilder får samma hash.
  Vår baseras på enkla ljusjämförelser, finns en risk för kollisioner om olika bilder har liknande ljusmönster. alltså det skulle ge false positives.

  Effektiv: den behöver vara Effektiv så att ej tar lång tid vid många bilder 
  Vår är tillräckligt bra för att identifiera dubbletter som delar liknande ljusmönster och väldigt Effektiv.



- Ser du några problem med metoden för att se om två bilder är lika dana?
  Föreslå en alternativ metod för att hitta bilder som är lika. Vad har
  ditt/dina förslag för för- och nackdelar jämfört med det som föreslås i
  labben? Fokusera exempelvis på vilka typer av skillnader i bilder som
  hanteras, eller vilken tidskomplexitet som kan uppnås. Ditt förslag behöver
  inte vara snabbare än det som föreslås i labben, men du ska komma på
  åtminstone en fördel med din metod.
  
 PHash skulle kunne användas, skulle ta bort problemet som vår lösning har då den mot små bortser förändringar i ljusstyrka, brus och även vissa små geometriska skillnader då den omvandlar till gråskala. men tar längre tid och compute_summary skulle behövas göras om. Sammfattat är vår metod snabbast men har lite större risk för att missa.

Projekt ICP 2024/2025 - Simulátor Moorovho automatu

Autori:

	Patrik Prochazka, xprochp00
	Miroslav Bašista, xbasism00
	Filip Ficka, xfickaf00

Popis programu:

Program po spustení umožňuje užívateľovi vytvárať automaty pomocou grafického prostredia s možnosťou pridávania stavov a hrán.
Jednotlivým stavom sa dokáže priradiť jedinečná funkcionalita a hranám sa dajú nastaviť podmienky prechodu.
Všetko za pomoci informačného panelu nachádzajúceho sa na pravej strane aplikácie.
Každému automatu je umožnené priradiť meno, popis, vstupy, výstupy a premenné ktoré sú v rámci automatu používané.
Podmienky sa píšu v štýle Javascriptu a sú podporované následné operácie:

=  -> priradenie
== -> rovnosť
!= -> nerovnosť
>= -> väčšie rovné
<= -> menšie rovné
>  -> väčšie
<  -> menšie
&& -> logické áno
|| -> logické alebo

Pre špeciálne časové prechody sa používa objekt moore, ktorý obsahuje metódu timer. Do tejto metódy sa odosiela požadovaný čas, ktorý má simulácia počkať. Po uplynutí tohto času sa automat presunie do nasledujúceho stavu.
Každá podmienka prechodu by mala vracať logickú hodnotu true alebo false.
Okrem vytvorenia sa dajú automaty exportovať do .json súborov a taktiež je podporované aj opätovné nahranie predošlých exportovaných automatov.
Pre samotné spustenie a simuláciu stačí stlačiť tlačidlo 'simulate' ktoré pripraví automat a otvorí terminál do ktorého sa budú vypisovať postupné kroky simulácie.
Po ukončení je možné automat resetovať a nad novým vstupom spustiť program znovu alebo zadať nový vstup a pokračovať v simulácii.

Makefile:
make            -> preloží program
make run        -> preloží a spustí program
make doxygen    -> vygeneruje html dokumentáciu
make doxyClean  -> zmaže vygenerovanú dokumentáciu
make clean      -> vymaže preložený program
make zip        -> vytvorí komprimovaný priečinok s obsahom adresára
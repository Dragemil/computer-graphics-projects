---
title: "Dokumentacja projektu LearnOpenGL"
author: "Emil Dragañczuk"
date: "luty 2020"
output: pdf_document
---

# Dokumentacja
**SKONFIGUROWANE WY£¥CZNIE NA DEBUG'U x86**

## Technologia
Projekt graficzny oparty na technologii OpenGL.

## Modele
Wykorzystane zosta³y 3 modele wraz z teksturami:
* model pi³ki pla¿owej,
* model stadionu pi³karskiego,
* model azjatyckiego lampionu.

## Funkcjonalnoœci
Stadion jest g³ówn¹ scen¹. Nad nim po œrodku znajduje siê jeden stacjonarny lampion
bêd¹cy Ÿród³em œwiat³a punktowego. W czterach rogach stadionu znajduj¹ siê
jeszcze 4 lampiony, poruszaj¹ce siê jednostajnie w górê i w dó³, one ju¿ s¹
reflektorami. Ich œwiat³o zawsze jest skierowane na pi³kê pla¿ow¹ na stadionie.
Pi³ka potrafi siê toczyæ (ruch + obroty), spowalniaj¹c, symuluj¹c tarcie oraz skrêcaæ.
U¿ytkownik ma wp³yw na ruch i skrêcanie pi³ki. Nieustannie zmienia siê pora dnia.
Kamera ma 4 opcje.

## Technikalia
Oœwietlenie modelem Phonga lub Blinna. Cieniowanie modelem Phonga
lub Gourauda. Œwiat³o zanika wraz z odleg³oœci¹.

# Instrukcja
1. Kamera
   * 1 - kamera sta³a
   * 2 - kamera sta³a œledz¹ca pi³kê
   * 3 - kamera pod¹¿aj¹ca za pi³k¹
   * 4 - kamera swobodna: ruch WASD + myszka
2. Pi³ka
   * Spacja - przyspieszenie
   * <- - skrêt w lewo
   * -> - skrêt w prawo
   * R - reset pi³ki do pozycji pocz¹tkowej
3. Cieniowanie
   * G - cieniowanie Gourauda
   * H - cieniowanie Phonga
4. Oœwietlanie
   * B - oœwietlanie Blinna
   * N - oœwietlanie Phonga

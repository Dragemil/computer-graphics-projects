---
title: "Dokumentacja projektu LearnOpenGL"
author: "Emil Draga�czuk"
date: "luty 2020"
output: pdf_document
---

# Dokumentacja
**SKONFIGUROWANE WY��CZNIE NA DEBUG'U x86**

## Technologia
Projekt graficzny oparty na technologii OpenGL.

## Modele
Wykorzystane zosta�y 3 modele wraz z teksturami:
* model pi�ki pla�owej,
* model stadionu pi�karskiego,
* model azjatyckiego lampionu.

## Funkcjonalno�ci
Stadion jest g��wn� scen�. Nad nim po �rodku znajduje si� jeden stacjonarny lampion
b�d�cy �r�d�em �wiat�a punktowego. W czterach rogach stadionu znajduj� si�
jeszcze 4 lampiony, poruszaj�ce si� jednostajnie w g�r� i w d�, one ju� s�
reflektorami. Ich �wiat�o zawsze jest skierowane na pi�k� pla�ow� na stadionie.
Pi�ka potrafi si� toczy� (ruch + obroty), spowalniaj�c, symuluj�c tarcie oraz skr�ca�.
U�ytkownik ma wp�yw na ruch i skr�canie pi�ki. Nieustannie zmienia si� pora dnia.
Kamera ma 4 opcje.

## Technikalia
O�wietlenie modelem Phonga lub Blinna. Cieniowanie modelem Phonga
lub Gourauda. �wiat�o zanika wraz z odleg�o�ci�.

# Instrukcja
1. Kamera
   * 1 - kamera sta�a
   * 2 - kamera sta�a �ledz�ca pi�k�
   * 3 - kamera pod��aj�ca za pi�k�
   * 4 - kamera swobodna: ruch WASD + myszka
2. Pi�ka
   * Spacja - przyspieszenie
   * <- - skr�t w lewo
   * -> - skr�t w prawo
   * R - reset pi�ki do pozycji pocz�tkowej
3. Cieniowanie
   * G - cieniowanie Gourauda
   * H - cieniowanie Phonga
4. O�wietlanie
   * B - o�wietlanie Blinna
   * N - o�wietlanie Phonga

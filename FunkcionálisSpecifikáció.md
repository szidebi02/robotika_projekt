# Funkcionális specifikáció
## 1. Vágyálomrendszer leírása
A projektrünk egy növény gondozó/figyelő rendszer amely segítségével fenntarthatjuk a virágaink, növényeink számára megfelelő életkörülményeket. A hőmérséklet érzékelő, fényérzékelő és talajnedvesség érzékelővel figyelemmel követhezjük a körülmények alakulását.
Nem megfelelő létszükségletek esetén a ledek illetve a szirénarandszer figyelmezteti a felhasználót a változtatásra.
## 2. Alkatrész lista:
- Arduino Uno R3
- hőmérséklet-érzékelő (TMP36)
- szórtfény-érzékelő (fototranzisztor)
- talajnedvesség érzékelő
- lcd kijelző (MCP23008-alapú, 32 LCD 16 x 2 (I2C))
- hangszóró (Piezo)
- 1 színű ledek a megfigyeléshez:
  - kék
  - sárga
  - zöld
- 1 színű ledek a szirénázáshoz:
  - kék
  - piros  
- ellenállások ledekhez
- jumper kábelek
## 3. Használati esetek (működés)
- A kijelzőn folyamatosan figyelemmel követhetjük a hőmérséklet, fény és talajnedvesség adatokat.
- A kék led kigyullad amennyiben a talajnedvesség nem megfelelő.
- A sárga led kigyullad amennyiben a fény nem megfelelő. 
- A zöld led kigyillad amennyiben a hőmérséklet nem megfelelő.
- Sziréna indul -> nagy a baj
## 4. Képernyőtervek (sematikus rajz és CAD tervrajz)
![image](https://user-images.githubusercontent.com/113984073/237050119-b489ff32-7ad7-4129-98fc-f4e6bcf93c1e.png)

## 5. Forgatókönyvek (állapotátmenet gráf)

# levenstein_distance
Implementation of Levenstein distance in C with some other features.
```
użycie:
levenstein-distance <-h|--help>
levenstein-distance <słowo1> <słowo2>
levenstein-distance [--filename FILENAME] [--index N]

-h
--help
ten komunikat

<słowo1>
<słowo2>
porównanie dwóch słów

--filename FILENAME
porównanie wszystkich słów z pliku FILENAME (domyślnie ./lwords.txt)

--index N
    domyślnie w porównaniu występują wszystkie kombinacje słów
    jeśli napisać argument N to w porównaniu pojawią się tylko
    kombinacje ze słowem w pliku FILENAME

--average
    średnia wartość różnic

--std-dev
    odchylenie standardowe

```

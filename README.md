# Zamek-elektroniczny

        1.Temat projektu
Zamek elektroniczny z wielopoziomową kontrolą dostępu.

        2.Zespół projektowy
Martyna Kłosek
Jakub Mazurczyk

        3.Cel i zakres projektu
Niniejszy projekt jest studenckim przedsięwzięciem, które na celu ma stworzenie projektu zamkaelektronicznego z wielopoziomową kontrolą dostępu. Naszym celem, jest połączeniem elektroniki orazprogramowania za pomocą programu ArduinoIDE. Zamek w swoim założeniu posiada trójstopniowąkotrolę, w której skład wchodzą:

a) pomiar temperatury ciała.

b) odczyt breloka.
        
c) wpisanie poprawnego kodu.

        4.Opis rozwiązania technicznego
Celem projektu było zaprojektowanie, zmontowanie i zaprogramowanie układu zamka elektronicz-nego z wielopoziomową kontrolą dostępu.

Zamek powinien spełniać kryteria bezpieczeństwa, tak aby mógł zostać wykorzystany w różnychplacówkach lub instytutach, które cenią sobie bezpieczeństwo np. jako zamek drzwi wejściowych, zamekpomieszczenia ograniczonego dostępu, zamek sejfu, skrytki, szafki. Jednak z uwagi na charakterystykęprojektu i dobór czujników, system zamka jest dedykowany głównie placówek medycznych.

System  posiada  trójstopniową  kontrolę  dostępu,  która  jest  zastosowana  w  trybie  kaskadowym  -użytkownik musi przejść po kolei każdy z etapów blokady by uzyskać dostęp i otworzyć zamek. Infor-macje o etapie rozbrajania oraz o postęp w ich wyłączaniu, są na bieżąco wyświetlane użytkownikowi.

Dodatkowo podczas próby rozbrojenia danego etapu blokady użytkownik jest informowany o jejpowodzeniu lub jego braku, poprzez zapalenie się odpowiednio zielonej lub czerwonej diody LED naokres 3 sekund.

Potencjalny  użytkownik,  który  chce  otworzyć  zamek,  w  pierwszej  kolejności  jest  informowany  okonieczności zmierzenia temperatury. Powinien on w tym momencie przyłożyć palec dominującej dło-ni do powierzchni czujnika i zczytać pomiar temperatury z opuszka palca. Program w tym momenciemierzy temperaturę przez 15 sekund. Jeśli w tym czasie temperatura ciała będzie w akceptowalnymzakresie, użytkownik zostanie dopuszczony do następnej blokady. W innym przypadku zostanie po-informowany  o  nieodpowiedniej  temperaturze  a  program  zacznie  swoje  działanie  od  początku.  Wprzypadku opuszka palca prawidłowa temperatura wynosi od 25 do 31 stopni Celsjusza.

Drugą blokadą jest odczyt poprawnego breloka lub karty magnetycznej. Podobnie jak w przypadkupierwszej blokady, użytkownik zostanie poinformowany o stanie powodzenia operacji. W przypadkuniepowodzenia program wraca do początku działania. W przypadku zgodności breloka dostajemy siędo ostatniej, trzeciej blokady, którą jest podanie 4 cyfrowego kodu.

Gdy zostanie wpisany poprawny kod użytkownik dostaje odpowiednią informację, oraz komunikat ootwarciu drzwi. Uruchamia się również 5 sekundowy stoper odliczający pozostały czas otwarcia zamka.Serwomechnizm zmienia swoją pozycję o 90 stopni na 5 sekund co symuluje otwarcie się zamka. Poupływie 5 sekud zamek się zamyka a program zaczyna swoją pracę od początku, tak by móc zostaćobsłużony przez następnego użytkownika.

        5.Demonstracja gotowego projektu.
https://www.youtube.com/watch?v=zHujV_-ubi0&ab_channel=MartynaK%C5%82osek

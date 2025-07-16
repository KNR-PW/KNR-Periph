 Tu znajduje się projekt Platformio z oryginalnym plikiem źródłowym src + headerem dopisanym przeze mnie (do wysyłania sygnału okresowego - dla nas nieprzydatne).

- Żeby działał interfejs po WiFi należy odkomentować wszystkie funkcje wołane w setup i w loop zostawić pustą pętle.

- Zadaniem na teraz jest zmiana funkcji jednego z przycisków UI (np do zmiany pozycji tak, by nie zmieniał go o mały kąt, ale zawsze o 90 stopni).

Dodatkowe informacje warte uwagi:

W /include zawarte są wszystkie ciekawe funkcje warte uwagi. Warto posługiwać się opcją search w VSCode - ułatwia to znalezienie miejsc kodu do modyfikacji.

Głównie obchodzą nas STSCTRL.h - jak dobrze kojarze i patrze tutaj są zdefiniowane te podstawowe funkcje do sterowania.

Można też zrobić to oddolnie -> w headerze servo_control.h mamy zdefiniowaną funkcje, gdzie bezpośrednio przypisuje wartość pozycji funkcją st.WritePosEx() z określoną predkością i przyspieszeniem
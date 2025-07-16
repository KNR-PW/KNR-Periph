Tu znajduje się projekt PlatformIO do sterowania silnikami BLDC wykorzystując timery oraz do tego zczytywanie danych z czujnika prądu i wysyłanie ich interfejsem szeregowym. 

- Do weryfikacji jest dobre sterowanie wypełnieniem PWM (chyba najłatiej będzie podejrzeć oscyloskopem), bo przy zadawaniu liczby 10 silniki kręcą się wolno, przy 20 jest duży skokowy wzrost prędkości, a przy 80 osiągane jest maksimum. Trzeba dobrze to skalibrować.

- Weryfikacja (pod sam koniec już przy integracji) danych z czujnika przy obciążeniu (na sucho będziemy wysyłać komendy do serw i patrzeć jak zmienia się prąd)


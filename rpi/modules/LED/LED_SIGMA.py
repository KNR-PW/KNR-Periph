import board
import neopixel
import time

# Parameters
LED_COUNT = 5               # Diods number on strip ALL
LED_PIN = board.D18         # GPIO18 (pin 12) – standard PWM port for WS2812 (RGB library)
LED_BRIGHTNESS = 1          # Bright 0.0 - 1.0
LED_ORDER = neopixel.GRB    # Color order (GRB for WS2812)

# Initialize the NeoPixel strip
# Set up the NeoPixel strip
pixels = neopixel.NeoPixel(
    LED_PIN, LED_COUNT, brightness=LED_BRIGHTNESS, auto_write=False, pixel_order=LED_ORDER
)

def kolor(kolor_rgb):
    for i in range(LED_COUNT):
        pixels[i] = kolor_rgb
    pixels.show()

try:
    while True:
        print("\nChoses color: r - red, g - green, b - blue, w - white, o - off, q - quit")
        cmd = input("Chose: ").lower()

        if cmd == 'r':
            kolor((255, 0, 0))
            print("Red")
        elif cmd == 'g':
            kolor((0, 255, 0))
            print("Green")
        elif cmd == 'b':
            kolor((0, 0, 255))
            print("Blue")
        elif cmd == 'w':
            kolor((255, 255, 255))
            print("White")
        elif cmd == 'o':
            kolor((0, 0, 0))
            print("LED OFF")
        elif cmd == 'q':
            print("Closing...")
            break
        else:
            print("Unknown command")
        time.sleep(0.1)

except KeyboardInterrupt:
    print("Przerwano przez użytkownika.")

finally:
    kolor((0, 0, 0))
    print("LED shut down")

######################__LIBRARIES__#####################
# sudo pip3 install rpi_ws281x adafruit-circuitpython-neopixel
# sudo python3 -m pip install --force-reinstall adafruit-blinka


# Scheamtic for raspbery pi 4B
# +5V
# GPIO18 (pin 12)
# GND
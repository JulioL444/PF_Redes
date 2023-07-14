import requests
import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector

URL = 'http://192.168.0.101'  # URL del Arduino
PORT = 80  # Puerto del servidor
WIFI_SSID = 'Nexxt_2D7348'
WIFI_PASSWORD = 'ganancias5'

cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.5, maxHands=1)

# Conectar a la red WiFi
print("Conectando a la red WiFi...")
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Ajustar el tamaño del buffer de captura para evitar retrasos
cap.set(cv2.CAP_PROP_FPS, 30)  # Ajustar los FPS de captura
while True:
    if cap.isOpened():
        break

# Establecer la conexión WiFi
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Restaurar el tamaño del buffer de captura a su valor original
cap.set(cv2.CAP_PROP_FPS, 30)  # Restaurar los FPS de captura a su valor original

while True:
    success, img = cap.read()
    img = cv2.resize(img, (500, 350))
    img = detector.findHands(img)
    l, box = detector.findPosition(img, draw=False)

    if l:
        f = detector.fingersUp()
        s = (list(map(int, f)))
        w = sum(s)
        data = str(w) + '\n'  # Preparar los datos para enviar

        try:
            response = requests.post(f"{URL}:{PORT}", data=data, timeout=1)  # Enviar datos al servidor en Arduino
            print("Respuesta del servidor:", response.text)
        except requests.exceptions.RequestException as e:
            print("Error de conexión:", e)

    cv2.imshow('Image', img)

    if cv2.waitKey(20) & 0xFF == 27:
        break

cv2.destroyAllWindows()

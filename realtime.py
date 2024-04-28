# IMPORTS 
import cv2
from deepface import DeepFace
import time

# TIME
t0 = time.time() # start time in seconds
  
# Open a connection to the webcam (0 represents the default camera)
cap = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    
    t1 = time.time() # current time
    num_seconds = t1 - t0 # diff
    if num_seconds > 30:  # break after 30 seconds
      break
  
    # Check if the frame is valid
    if not ret:
        print("Error: Couldn't capture frame. Exiting.")
        break

    # Perform emotion detection on the frame
    result = DeepFace.analyze(frame, actions=['emotion'])

    # Print the result
    print(result)

    # Break the loop when the 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam
cap.release()
cv2.destroyAllWindows()

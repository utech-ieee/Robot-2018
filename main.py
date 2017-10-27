import cv2 as cv
import sys


cascPath = sys.argv[1]
faceCascade = cv.CascadeClassifier(cascPath)

cv.namedWindow('view')
capture = cv.VideoCapture(0)

if capture.isOpened(): #1st Frame
	returnVal, frame = capture.read()
else:
	returnVal = False

while returnVal:
    
    returnVal, frame = capture.read()

    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags=cv.cv.CV_HAAR_SCALE_IMAGE
    )

    # Draw a rectangle around the faces
    for (x, y, w, h) in faces:
        cv.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

    cv.imshow("view", frame)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break
capture.release()
cv.DestroyAllWindows()